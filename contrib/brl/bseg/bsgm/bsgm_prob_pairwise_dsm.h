// This is brl/bseg/bsgm/bsgm_prob_pairwise_dsm.h
#ifndef bsgm_prob_pairwise_dsm_h
#define bsgm_prob_pairwise_dsm_h

//:
// \file
// \brief A class to provide a convenient interface to compute a pairwise dsm
// \author J.L. Mundy
// \date February 11, 2019
//
// \verbatim
//  Modifications
//   Sept. 3, 2019
//   JLM - added additional probability factor based on the rate of change in z with respect to disparity
// \endverbatim
// uses the SGM algorithm to compute a pair of disparity images, normal and reverse.
// the reverse disparity image is computed by simply flipping the order of the
// images passed to the SGM algorithm. The forward and reverse disparity images are
// converted to a 3-d pointset by finding the 3-d points that produce the observed
// disparities.  A probability is applied to each forward 3-d point based on the 3-d distance
// between a forward point and the closest point from the reverse reconstruction
//
// There can be different conventions concerning the sign of disparity values
// In the case of bsgm_disparity_estimator, disparity is defined as the horizontal translation
// required to move from a pixel in the reference image to the corresponding pixel in the
// target image.

//In more detail, consider the following call to the multi-scale estimator:
//
// bsgm_multiscale_disparity_estimator mde(params_.de_params_, ni_, nj_, num_disparities(), num_active_disparities());
// mde.compute(rect_bview0_, rect_bview1_, invalid_map_, min_disparity_,
//             invalid_disp, params_.multi_scale_mode_, disp_r_);
//
// given a pixel (1182, 897) in rect_bview0 and the dispairity value at that location in the dispairity image,
// disp_r_, of -15.0, the corresponding pixel in rect_bview1 is (1167, 897)
//
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <math.h>
#include <vpgl/vpgl_affine_camera.h>
#include <vgl/vgl_point_2d.h>
#include <vgl/vgl_box_3d.h>
#include <vgl/vgl_pointset_3d.h>
#include <vil/vil_image_view.h>
#include <vil/vil_new.h>
#include <bpgl/algo/bpgl_rectify_affine_image_pair.h>
#include <bsta/bsta_histogram.h>
#include "bsgm_disparity_estimator.h" // for disparity_estimator_params


struct pairwise_params{
  pairwise_params():
    active_disparity_factor_(0.5), downscale_exponent_(2), multi_scale_mode_(0),  //1
    point_sample_dist_(0.3f), upsample_scale_factor_(1.0f),
    std_dev_(3.75*point_sample_dist_), num_nearest_nbrs_(5), shadow_thresh_(20),
    use_z_vs_d_prob_(false), min_z_vs_d_scale_(1.0f), z_vs_d_std_dev_(1.0f),
    quad_interp_(false)
  {
    set_shadow_thresh(shadow_thresh_);  //default
    set_quad_interp(quad_interp_);
  }
  void set_shadow_thresh(float thresh){ de_params_.shadow_thresh = thresh; shadow_thresh_ = thresh;}
  void set_quad_interp(bool interp) {
    de_params_.perform_quadratic_interp=interp; quad_interp_ = interp;
  }
  bsgm_disparity_estimator_params de_params_; // internal disparity estimator params
  float active_disparity_factor_; // what fraction of full disparity range is used for fine search
  int downscale_exponent_;   // in coarse to fine disparity, what is the downsample ratio as 2^exponent
  int multi_scale_mode_;     // see disparity_estimator
  float point_sample_dist_;  // the height map grid spacing, also relates to consistent distance tolerance
  float upsample_scale_factor_; // upsample the rectified images by scale factor
  float std_dev_;            // the standard deviation of consistent disparity point distances
  bool use_z_vs_d_prob_;     // multiply height probabilty with additional z vs d scale probability factor
  float min_z_vs_d_scale_;   // the lowest z vs d scale factor that is typically obtained in meters/pixel
  float z_vs_d_std_dev_;     // the standard deviation for the z vs d Gaussian distribution
  size_t num_nearest_nbrs_;  // number of nearest neighbors in the pointset to find closest and to interpolate
  size_t shadow_thresh_;     // intensity level out of 255 below which is considered to be in shadow, thus invalid
  bool quad_interp_;         // if true, perform quadratic interpolation of disparity with respect to cost
};


class bsgm_prob_pairwise_dsm
{
 public:
  bsgm_prob_pairwise_dsm() = default;

  bsgm_prob_pairwise_dsm(vil_image_resource_sptr const& resc0, vpgl_affine_camera<double> const& acam0,
                         vil_image_resource_sptr const& resc1, vpgl_affine_camera<double> const& acam1)
  {
    rip_.set_images_and_cams(resc0, acam0, resc1, acam1);
  }

  bsgm_prob_pairwise_dsm(vil_image_view<unsigned char> const& view0, vpgl_affine_camera<double> const& acam0,
                         vil_image_view<unsigned char> const& view1, vpgl_affine_camera<double> const& acam1)
  {
    rip_.set_images_and_cams(vil_new_image_resource_of_view(view0), acam0, vil_new_image_resource_of_view(view1), acam1);
  }


  // ACCESSORS-----

  //: parameters
  void set_params(pairwise_params const& params) {params_ = params;}
  pairwise_params params() const {return params_;}

  //: minimum dispartity to start search along an epipolar line
  void set_min_disparity(int min_disparity) {min_disparity_ = min_disparity;}
  int min_disparity() const {return min_disparity_;}

  //: maximum dispartity to end search along an epipolar line
  void set_max_disparity(int max_disparity) {max_disparity_ = max_disparity;}
  int max_disparity() const{return max_disparity_;}

  //: number of disparities
  int num_disparities() { return (max_disparity_ - min_disparity_); }

  //: how many disparity values are searched around the coarse search result
  int num_active_disparities() {
    return static_cast<int>(num_disparities()*params_.active_disparity_factor_);
  }

  //: plane elevation for minimum least squares disparity
  void set_midpoint_z(double mid_z) {mid_z_ = mid_z;}
  void midpoint_z(double mid_z) {mid_z_ = mid_z;}

  //: scene box for analysis
  void set_scene_box(vgl_box_3d<double> scene_box) { scene_box_ = scene_box; }
  vgl_box_3d<double> scene_box() const { return scene_box_; }

  //: rectified images and cams
  const vil_image_view<vxl_byte>& rectified_bview0() const  {return rect_bview0_;}
  const vil_image_view<vxl_byte>& rectified_bview1() const  {return rect_bview1_;}
  const vpgl_affine_camera<double>& rectified_acam0() const {return rip_.rect_acam0();}
  const vpgl_affine_camera<double>& rectified_acam1() const {return rip_.rect_acam1();}

  //: disparity results
  vil_image_view<vxl_byte> invalid_map_fwd() const { return bool_to_byte(invalid_map_fwd_); }
  vil_image_view<vxl_byte> invalid_map_rev() const { return bool_to_byte(invalid_map_rev_); }
  const vil_image_view<float>& disparity_fwd() const {return disparity_fwd_;}
  const vil_image_view<float>& disparity_rev() const {return disparity_rev_;}

  //: triangulation results
  // uses rectified cams to reconstruct 3-d scene geometry
  // produces a 3-d pointset and a z(x,y) heightmap
  const vil_image_view<float>& tri_3d_fwd() const {return tri_3d_fwd_;}
  const vil_image_view<float>& tri_3d_rev() const {return tri_3d_rev_;}

  const vil_image_view<float>& heightmap_fwd() const {return heightmap_fwd_;}
  const vil_image_view<float>& heightmap_rev() const {return heightmap_rev_;}

  const vgl_pointset_3d<float> ptset_fwd() const {return ptset_fwd_;}
  const vgl_pointset_3d<float> ptset_rev() const {return ptset_rev_;}

  //: probablistic results
  const vgl_pointset_3d<float> prob_ptset() const {return prob_ptset_;}
  bsta_histogram<float> prob_pdf() const {return prob_distr_;}

  const vil_image_view<float>& prob_heightmap() const {return prob_heightmap_z_;}
  const vil_image_view<float>& prob_confidence() const { return prob_heightmap_prob_; }


  // PROCESS-----

  //: image rectification
  void rectify();

  //: compute disparities
  // fwd: arg order rectified image0:image1
  // rev: arg order rectified image1:image0
  void compute_disparity_fwd();
  void compute_disparity_rev();

  //: compute height data (tri_3d, ptset, heightmap)
  void compute_height_fwd();
  void compute_height_rev();

  //: comptute probablistic height
  bool compute_prob();

  //: main process method
  bool process(bool with_consistency_check = true)
  {
    // rectification
    this->rectify();

    // compute foward disparity & height
    this->compute_disparity_fwd();
    this->compute_height_fwd();

    // consistency check & probablistic analysis
    if (with_consistency_check) {
      this->compute_disparity_rev();
      this->compute_height_rev();

      if (!compute_prob())
        return false;
    }
    return true;
  }

  // MISC-----

  //: apply a color map to the probabilty values and
  //  output a color point cloud as ascii
  bool save_prob_ptset_color(std::string const& path) const;

  // for debug purposes
  bool load_images_and_cams(std::string const& image0_path, std::string const& cam0_path,
                            std::string const& image1_path, std::string const& cam1_path)
  {
    return rip_.load_images_and_cams(image0_path, cam0_path, image1_path, cam1_path);
  }


 protected:

  // compute disparity for generic inputs
  void compute_disparity(
      const vil_image_view<vxl_byte>& img,
      const vil_image_view<vxl_byte>& img_reference,
      vil_image_view<bool>& invalid,
      vil_image_view<float>& disparity);

  // compute height for generic inputs
  void compute_height(
    const vpgl_affine_camera<double>& cam,
    const vpgl_affine_camera<double>& cam_reference,
    const vil_image_view<float>& disparity,
    vil_image_view<float>& tri_3d,
    vgl_pointset_3d<float>& ptset,
    vil_image_view<float>& heightmap);

  // z vs disparity scale
  bool z_vs_disparity_scale(double& scale) const;

  // boolean to byte image conversion
  vil_image_view<vxl_byte> bool_to_byte(const vil_image_view<bool>& img) const;

  // scene box as float
  vgl_box_3d<float> scene_box_as_float() const;

 private:

  pairwise_params params_;
  bpgl_rectify_affine_image_pair rip_;
  size_t ni_;
  size_t nj_;
  int min_disparity_;
  int max_disparity_;

  double mid_z_ = NAN;
  double z_vs_disp_scale_ = 1.0;

  vgl_box_3d<double> scene_box_;

  vil_image_view<vxl_byte> rect_bview0_;
  vil_image_view<vxl_byte> rect_bview1_;

  // disparity data
  vil_image_view<bool> invalid_map_fwd_;
  vil_image_view<bool> invalid_map_rev_;
  vil_image_view<float> disparity_fwd_;
  vil_image_view<float> disparity_rev_;

  // triangulated data
  vil_image_view<float> tri_3d_fwd_;
  vil_image_view<float> tri_3d_rev_;

  // height data
  vgl_pointset_3d<float> ptset_fwd_;
  vgl_pointset_3d<float> ptset_rev_;

  vil_image_view<float> heightmap_fwd_;
  vil_image_view<float> heightmap_rev_;

  // probablistic data
  vgl_pointset_3d<float> prob_ptset_;
  bsta_histogram<float> prob_distr_;

  vil_image_view<float> prob_heightmap_z_;
  vil_image_view<float> prob_heightmap_prob_;

};

#endif // bsgm_prob_pairwise_dsm_h_
