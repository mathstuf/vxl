#ifndef brct_windows_frame_h_
#define brct_windows_frame_h_
//--------------------------------------------------------------------------------
//:
// \file
// \brief Manager for multiview gui applications
// \author
//   Kongbin Kang
//
// \endverbatim
//--------------------------------------------------------------------------------

#include <vgui/vgui_wrapper_tableau.h>
#include <vgui/vgui_easy3D_tableau.h>
#include <vgui/vgui_easy3D_tableau_sptr.h>
#include <vgui/vgui_easy2D_tableau.h>
#include <vgui/vgui_easy2D_tableau_sptr.h>
#include <vgui/vgui_grid_tableau.h>
#include <vgui/vgui_grid_tableau_sptr.h>
#include <vgui/vgui_menu.h>
#include <vgl/vgl_point_2d.h>
#include <vgl/vgl_point_3d.h>
#include <vgui/vgui_soview3D.h>
#include <vgui/vgui_soview2D.h>
#include <bmvl/brct/kalman_filter.h>

class vgui_window;

//: A manager for displaying segmentation results.
class brct_windows_frame : public vgui_wrapper_tableau
{
 public:
  brct_windows_frame();
  ~brct_windows_frame();
  static brct_windows_frame *instance();

  //:methods for menu callbacks
  void quit();
  void add_curve2d(vcl_vector<vgl_point_2d<double> > &pts);
  void remove_curve2d();
  void add_curve3d(vcl_vector<vgl_point_3d<double> > &pts);
  void remove_curve3d();
  void init_kalman();

  void init();

  //: the virtual handle function
  virtual bool handle(const vgui_event&);

 protected:
  //:internal utility methods
  
  //: it clean the memory allocated by init. it should be called by quit()
  void clean_up();

 private:
  //: get track of all the 3d points added into 3d tableau
  vcl_vector<vgui_lineseg3D* > curves_3d_;

  //: 2d curve at time t
  vcl_vector<vgui_soview2D_lineseg* > curves_2d_;
  
  //: 2d curve at time 0
  vcl_vector<vgui_soview2D_lineseg* > curves_2d_0_;
  
  //: kalman filter
  kalman_filter* kalman_;
  vgui_easy2D_tableau_sptr tab_2d_;
  vgui_easy3D_tableau_sptr tab_3d_;
  vgui_grid_tableau_sptr grid_;
  static brct_windows_frame *instance_;
};

#endif // brct_windows_frame_h_
