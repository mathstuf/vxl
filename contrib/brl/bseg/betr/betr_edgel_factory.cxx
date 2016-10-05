#include "betr_edgel_factory.h"
#include <sdet/sdet_detector.h>
#include <vdgl/vdgl_digital_curve.h>
#include <vdgl/vdgl_interpolator.h>
#include <vdgl/vdgl_edgel_chain.h>
#include <vdgl/vdgl_edgel.h>
#include <brip/brip_vil_float_ops.h>
#include <vil/vil_image_resource.h>
#include <vil/vil_image_view_base.h>
#include <vil/vil_image_view.h>
#include <vil/vil_save.h>
#include <vil/vil_new.h>
#include <vil/vil_resample_bicub.h>
#include <bsol/bsol_algs.h>
#include <vsol/vsol_polygon_2d.h>
#include <vsol/vsol_point_2d.h>
#include <vsl/vsl_binary_io.h>
#include <vsl/vsl_vector_io.h>
void betr_edgel_factory::set_parameters(float sigma, float noise_multiplier, double gradient_range, unsigned nbins){
  sdet_detector_params params;
  params.smooth = sigma;
  params.noise_multiplier = noise_multiplier;
  params.aggressive_junction_closure=1;
  params.filterFactor = 0.0;
  params.borderp = false;
  params_ = params;
  gradient_range_ = gradient_range;
  nbins_ = nbins;
}
void betr_edgel_factory::set_parameters(float sigma, float noise_multiplier, double upsample_factor){
params_.smooth = sigma; 
 params_.noise_multiplier = noise_multiplier;
 params_.aggressive_junction_closure=1;
 params_.filterFactor = 0.0;
 params_.borderp = false;
 upsample_factor_ = upsample_factor;
}
bool betr_edgel_factory::add_image(std::string const& iname, vil_image_resource_sptr const& imgr){
  if (!imgr||!imgr->ni()||!imgr->nj())
  {
    std::cout << "empty image resource when adding image\n";
    return false;
  }
  images_[iname]=imgr;
  brip_roi_sptr broi = new brip_roi(imgr->ni(), imgr->nj());
  rois_[iname] = broi;
  return true;
}
bool betr_edgel_factory::add_region(std::string const& iname, std::string const& region_name,
                                    vsol_box_2d_sptr const& box){
  brip_roi_sptr broi = rois_[iname];
  if(!broi){
    std::cout << "null roi for image " << iname << '\n';
    return false;
  }
  unsigned n = broi->n_regions();
  broi->add_region(box);
  regions_[iname][region_name] = n;
  return true;
}
bool betr_edgel_factory::add_region(std::string const& iname, std::string const& region_name, vsol_polygon_2d_sptr const& poly){
  brip_roi_sptr broi = rois_[iname];
  if(!broi){
    std::cout << "null roi for image " << iname << '\n';
    return false;
  }
  unsigned n = broi->n_regions();
  vsol_box_2d_sptr box = poly->get_bounding_box();
  bool good = this->add_region(iname, region_name, box);
  if(good)
    polys_[iname][n] = poly;
  return good;
}
bool betr_edgel_factory::add_region_from_origin_and_size(std::string const& iname, std::string const& region_name,
                                                         unsigned i0, unsigned j0, unsigned ni, unsigned nj){
  brip_roi_sptr broi = rois_[iname];
  if(!broi){
    std::cout << "null roi for image " << iname << '\n';
    return false;
  }
  unsigned n = broi->n_regions();
  broi->add_region(i0, j0, ni, nj);
  regions_[iname][region_name] = n;
  return true;
}
bool betr_edgel_factory::process(std::string iname, std::string region_name){
  vil_image_resource_sptr imgr = images_[iname];
  if(!imgr){
    std::cout << "image " << iname << " not found in map \n";
    return false;
  }
  brip_roi_sptr roi = rois_[iname];
  if(!roi){
    std::cout << "roi for " << iname << " not found in map \n";
    return false;
  }
  unsigned region_id = regions_[iname][region_name];
  unsigned ni = roi->csize(region_id);
  unsigned nj = roi->rsize(region_id);
  unsigned min_size = 10;
  if(ni < min_size || nj <min_size ){
    std::cout << "roi " << region_name <<  " for " << iname << " is empty \n";
    return false;
  }
  int imin = roi->cmin(region_id);
  int jmin = roi->rmin(region_id);
  //debug
  int imax = imin + ni;
  int jmax = jmin + nj;
  std::cout << "region(" << iname << ':' << region_name << ")(" << imin << ',' << jmin << ")->(" << imax << ',' << jmax <<")\n";
  //
  brip_roi_sptr temp_roi = new brip_roi();
  temp_roi->add_region(imin, jmin, ni, nj);
  vil_image_resource_sptr clip_resc;
  if(!brip_vil_float_ops::chip(imgr, temp_roi, clip_resc)){
    std::cout << " clip function failed for (" << imin << ' ' << jmin << ' ' << ni << ' ' << nj << ") on " << iname << '\n';
    return false;
  }
  if(clip_resc->pixel_format()==VIL_PIXEL_FORMAT_FLOAT){
    vil_image_view<vxl_byte> view = brip_vil_float_ops::convert_to_byte(clip_resc);
    clip_resc = vil_new_image_resource_of_view(view);
  }
  // check if chip needs to be upsampled
  if(upsample_factor_ != 1.0){
    double dni = static_cast<double>(clip_resc->ni()), dnj = static_cast<double>(clip_resc->nj());
    dni *= upsample_factor_; dnj *= upsample_factor_;
    unsigned ni = static_cast<unsigned>(dni), nj = static_cast<unsigned>(dnj);
    if(clip_resc->pixel_format()==VIL_PIXEL_FORMAT_UINT_16){
      vil_image_view<unsigned short> temp = clip_resc->get_view(), uptemp;
      vil_resample_bicub(temp, uptemp, ni, nj);
      clip_resc = vil_new_image_resource_of_view(uptemp);
    }else if(clip_resc->pixel_format()==VIL_PIXEL_FORMAT_BYTE){
      vil_image_view<unsigned char> temp = clip_resc->get_view(), uptemp;
      vil_resample_bicub(temp, uptemp, ni, nj);
      clip_resc = vil_new_image_resource_of_view(uptemp);
    }
  }
#if 0
  //debug
  std::string dir =  "D:/tests/kandahar_test/";
  std::string fname = dir + iname + "_" + region_name + ".tif";
  vil_save_image_resource(clip_resc, fname.c_str());
#endif
  sdet_detector det(params_);
    
  det.SetImage(clip_resc);

  if(!det.DoContour()){
    std::cout << "Edgel detection failed\n";
    return false;
  }
  std::vector<vdgl_digital_curve_sptr> vd_edges;
  if (!det.get_vdgl_edges(vd_edges)){
    std::cout << "Detection worked but returned no edgels\n";
    return false;
  }
 
  edgels_[iname][region_name] = vd_edges;

  unsigned region_index = regions_[iname][region_name];
  vsol_polygon_2d_sptr poly = polys_[iname][region_index];
    std::vector<double> gmags;
  if(!poly){
    std::cout << "warning - can't find region poly - using roi instead\n";
    this->grad_mags(iname, region_name, gmags);
  }else
    this->grad_mags(iname, region_name, poly, gmags);
  bsta_histogram<double> h(gradient_range_, nbins_);
  for( std::vector<double>::iterator git = gmags.begin();
       git != gmags.end();++git)
    h.upcount(*git, (1.0 + (*git)));//increase weight to favor high gradient values (small objects)
  
  if(h.area()<3.0*nbins_){
    std::cout << "insufficient edges in region " << region_name << " - fatal" << std::endl;
    return false;
  }
  grad_hists_[iname][region_name] = h;
  return true;
}
bool betr_edgel_factory::grad_mags(std::string iname, std::string region_name, std::vector<double>& mags){
  std::vector< vdgl_digital_curve_sptr >  vd_edges = edgels_[iname][region_name];
  if(!vd_edges.size()){
    std::cout << "no edgels for the specified region " << iname << ':' << region_name << '\n';
    return false;
  }
  for (std::vector<vdgl_digital_curve_sptr>::iterator eit = vd_edges.begin();
       eit != vd_edges.end(); ++eit)
  {
      //get the edgel chain
    vdgl_interpolator_sptr itrp = (*eit)->get_interpolator();
    vdgl_edgel_chain_sptr ech = itrp->get_edgel_chain();
    unsigned int n = ech->size();
    for (unsigned int i=0; i<n;i++)
    {
      vdgl_edgel ed = (*ech)[i];
      double grad_mag = ed.get_grad();
      mags.push_back(grad_mag);
    }
  }
  return true;
}
bool betr_edgel_factory::grad_mags(std::string iname, std::string region_name, vsol_polygon_2d_sptr const& poly,
                                   std::vector<double>& mags){
  vgl_polygon<double>  vpoly = bsol_algs::vgl_from_poly(poly);
  brip_roi_sptr broi = rois_[iname];
  if(!broi){
    std::cout << "no roi for " << iname << '\n';
    return false;
  }
  unsigned region_index = regions_[iname][region_name];
  std::vector< vdgl_digital_curve_sptr >  vd_edges = edgels_[iname][region_name];
  if(!vd_edges.size()){
    std::cout << "no edgels for the specified region " << iname << ':' << region_name << '\n';
    return false;
  }
  double x0 = static_cast<double>(broi->cmin(region_index));
  double y0 = static_cast<double>(broi->rmin(region_index));
  for (std::vector<vdgl_digital_curve_sptr>::iterator eit = vd_edges.begin();
       eit != vd_edges.end(); ++eit)
  {
      //get the edgel chain
    vdgl_interpolator_sptr itrp = (*eit)->get_interpolator();
    vdgl_edgel_chain_sptr ech = itrp->get_edgel_chain();
    unsigned int n = ech->size();
    for (unsigned int i=0; i<n;i++)
    {
      vdgl_edgel& ed = (*ech)[i];
      double x = ed.get_x(), y = ed.get_y();
      x/= upsample_factor_; y/=upsample_factor_;
      x += x0, y += y0;
     // ed.set_x(x); ed.set_y(y);
      if(!vpoly.contains(x, y))
        continue;
      double grad_mag = ed.get_grad();
      mags.push_back(grad_mag);
    }
  }
  return true;
}
bool betr_edgel_factory::save_edgels(std::string const& dir) const {
  std::map<std::string, std::map<std::string, std::vector< vdgl_digital_curve_sptr > > >::const_iterator iit = edgels_.begin();
  for(; iit != edgels_.end(); ++iit){
	  const std::pair<std::string, std::map<std::string, std::vector< vdgl_digital_curve_sptr > > >& emap = *iit;
    for(std::map<std::string, std::vector< vdgl_digital_curve_sptr > >::const_iterator eit = emap.second.begin();
        eit != emap.second.end(); ++eit){
      std::string region_name = eit->first;
      std::vector< vdgl_digital_curve_sptr > edges = eit->second;
      std::vector<vsol_digital_curve_2d_sptr> vsol_edges = sdet_detector::convert_vdgl_to_vsol(edges);
      // convert to spatial object 2d
      std::vector<vsol_spatial_object_2d_sptr> sos;
      for(std::vector<vsol_digital_curve_2d_sptr>::const_iterator cit = vsol_edges.begin();
          cit!= vsol_edges.end(); ++cit){
        vsol_spatial_object_2d_sptr ec = dynamic_cast<vsol_spatial_object_2d*>(cit->ptr());
        sos.push_back(ec);
      }
      std::string path = dir + region_name + "_edges.vsl";
      vsl_b_ofstream ostr(path);
      if(!ostr){
        std::cout << "couldn't open binary stream for " << path << '\n';
        return false;
      }
      vsl_b_write(ostr, sos);
      ostr.close();
    }
}
  return true;
}
bool betr_edgel_factory::save_edgels_in_poly(std::string const& identifier, std::string const& dir){
  std::map<std::string, std::map<std::string, std::vector< vdgl_digital_curve_sptr > > >::const_iterator iit = edgels_.begin();
  for(; iit != edgels_.end(); ++iit){
    const std::pair<std::string, std::map<std::string, std::vector< vdgl_digital_curve_sptr > > >& emap = *iit;
    std::string iname = emap.first;
    for(std::map<std::string, std::vector< vdgl_digital_curve_sptr > >::const_iterator eit = emap.second.begin();
        eit != emap.second.end(); ++eit){
      std::string region_name = eit->first;
      unsigned index = regions_[iname][region_name];
      vsol_polygon_2d_sptr poly = polys_[iname][index];
      if(!poly){
        std::cout << "Null polygon in save_edgel_in_poly\n";
        return false;
      }
      vgl_polygon<double>  vpoly = bsol_algs::vgl_from_poly(poly);
      std::vector< vdgl_digital_curve_sptr > edges = eit->second;
      std::vector<vsol_digital_curve_2d_sptr> vsol_edges = sdet_detector::convert_vdgl_to_vsol(edges);
      // convert to spatial object 2d
      std::vector<vsol_spatial_object_2d_sptr> sos;
      for(std::vector<vsol_digital_curve_2d_sptr>::const_iterator cit = vsol_edges.begin();
          cit!= vsol_edges.end(); ++cit){
        unsigned n = (*cit)->size();
        for(unsigned i = 0; i<n; ++i){
          vsol_point_2d_sptr p = (*cit)->point(i);
          if(!vpoly.contains(p->x(), p->y()))
            continue;
          vsol_spatial_object_2d_sptr sp = dynamic_cast<vsol_point_2d*>(p.ptr());
        sos.push_back(sp);
        }
      }
      std::string path = dir + identifier + "_" + region_name + "_edges.vsl";
      vsl_b_ofstream ostr(path);
      if(!ostr){
        std::cout << "couldn't open binary stream for " << path << '\n';
        return false;
      }
      vsl_b_write(ostr, sos);
      ostr.close();
    }
}
  return true;

}
vil_image_resource_sptr betr_edgel_factory::
edgel_image(std::string iname, std::string region_name, unsigned& i_offset, unsigned& j_offset){
  brip_roi_sptr roi = rois_[iname];
  if(!roi){
    std::cout << "roi for " << iname << " not found in map \n";
    return VXL_NULLPTR;
  }
  unsigned region_id = regions_[iname][region_name];
  unsigned ni = roi->csize(region_id);
  unsigned nj = roi->rsize(region_id);
  i_offset = static_cast<unsigned>(roi->cmin(region_id));
  j_offset = static_cast<unsigned>(roi->rmin(region_id));
  vil_image_view<vxl_byte> view(ni, nj);
  view.fill(vxl_byte(0));
  vsol_polygon_2d_sptr poly = polys_[iname][region_id];
  if(!poly){
    std::cout << "Null polygon in edgel_image for " << iname << ':' << region_name << "\n";
    return VXL_NULLPTR;
  }
  vgl_polygon<double>  vpoly = bsol_algs::vgl_from_poly(poly);
  std::vector< vdgl_digital_curve_sptr > edges = edgels_[iname][region_name];
  if(edges.size() == 0){
    std::cout << "No edgels for " << iname << ':' << region_name << "\n";
    return VXL_NULLPTR;
  }
  double grad_scale = 255.0/gradient_range_;
  for(std::vector< vdgl_digital_curve_sptr >::iterator vit = edges.begin();
      vit != edges.end(); ++vit){
    vdgl_edgel_chain_sptr echain = (*vit)->get_interpolator()->get_edgel_chain();
    if(!echain){
      std::cout << "Null edgel chain " << iname << ':' << region_name << "\n";
      return VXL_NULLPTR;
    }
    unsigned n = echain->size();
    unsigned bdr = 3;
    for(unsigned k = 0; k<n; ++k){
      vdgl_edgel& e = echain->edgel(k);
      double x = e.get_x(), y = e.get_y();
      x/= upsample_factor_; y/=upsample_factor_;
      if(!vpoly.contains(x+i_offset, y+j_offset))
        continue;
      unsigned i = static_cast<unsigned>(x), j = static_cast<unsigned>(y);
	  // clean away border hash due to convolving and upsampling
      if(i < bdr || j < bdr  || i > (ni-bdr-1) || j > (nj-bdr-1))
        continue;
      double g = e.get_grad();
      double v = g*grad_scale;
      if(v>255.0)
        v= 255;
      view(i,j) = static_cast<vxl_byte>(v);
    }
  }
  vil_image_resource_sptr ret = vil_new_image_resource_of_view(view);
  return ret;
}
