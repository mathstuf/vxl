# Microsoft Developer Studio Project File - Name="vgui" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=vgui - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "vgui.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "vgui.mak" CFG="vgui - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "vgui - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "vgui - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=xicl6.exe
RSC=rc.exe

!IF  "$(CFG)" == "vgui - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
MTL=midl.exe
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /Ob2 /I "$(IUEROOT)\vcl\config.win32-vc60" /I "$(IUEROOT)\vcl" /I "$(IUEROOT)\vxl" /I "$(IUEROOT)\oxl" /D "WIN32" /D "NDEBUG" /D "_LIB" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=xilink6.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\Release\vgui.lib"

!ELSEIF  "$(CFG)" == "vgui - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
MTL=midl.exe
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /Ob2 /I "$(IUEROOT)\vcl\config.win32-vc60" /I "$(IUEROOT)\vcl" /I "$(IUEROOT)\vxl" /I "$(IUEROOT)\oxl" /D "WIN32" /D "_DEBUG" /D "_LIB" /FR /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=xilink6.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\Debug\vgui.lib"

!ENDIF 

# Begin Target

# Name "vgui - Win32 Release"
# Name "vgui - Win32 Debug"
# Name "vgui - Win32 ReleaseWithDBInfo"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\internals\trackball.c
# End Source File
# Begin Source File

SOURCE=".\Templates\vbl_array_2d+vgui_grid_tableau+-grid_data-.cxx"
# End Source File
# Begin Source File

SOURCE=".\Templates\vbl_smart_ptr+vgui_command-.cxx"
# End Source File
# Begin Source File

SOURCE=".\Templates\vbl_smart_ptr+vgui_tableau-.cxx"
# End Source File
# Begin Source File

SOURCE=".\Templates\vcl_algorithm+vgui_style~-.cxx"
# End Source File
# Begin Source File

SOURCE=".\Templates\vcl_list+vgui_event-.cxx"
# End Source File
# Begin Source File

SOURCE=".\Templates\vcl_map+vgui_style~.vgui_soview~-.cxx"
# End Source File
# Begin Source File

SOURCE=".\Templates\vcl_vector+vcl_pair+vil_image.vcl_vector+GLuint-~-~-.cxx"
# End Source File
# Begin Source File

SOURCE=".\Templates\vcl_vector+vgui_dialog_impl+-element-.cxx"
# End Source File
# Begin Source File

SOURCE=".\Templates\vcl_vector+vgui_event-.cxx"
# End Source File
# Begin Source File

SOURCE=".\Templates\vcl_vector+vgui_image_tableau~-.cxx"
# End Source File
# Begin Source File

SOURCE=".\Templates\vcl_vector+vgui_soview2D_lineseg~-.cxx"
# End Source File
# Begin Source File

SOURCE=".\Templates\vcl_vector+vgui_menu_item-.cxx"
# End Source File
# Begin Source File

SOURCE=".\Templates\vcl_vector+vgui_observer~-.cxx"
# End Source File
# Begin Source File

SOURCE=".\Templates\vcl_vector+vgui_polytab+-item-.cxx"
# End Source File
# Begin Source File

SOURCE=".\Templates\vcl_vector+vgui_rubberbander_sptr-.cxx"
# End Source File
# Begin Source File

SOURCE=".\Templates\vcl_vector+vgui_slab~-.cxx"
# End Source File
# Begin Source File

SOURCE=".\Templates\vcl_vector+vgui_slot-.cxx"
# End Source File
# Begin Source File

SOURCE=".\Templates\vcl_vector+vgui_soview2D~-.cxx"
# End Source File
# Begin Source File

SOURCE=".\Templates\vcl_vector+vgui_soview3D~-.cxx"
# End Source File
# Begin Source File

SOURCE=".\Templates\vcl_vector+vgui_soview~-.cxx"
# End Source File
# Begin Source File

SOURCE=".\Templates\vcl_vector+vgui_style~-.cxx"
# End Source File
# Begin Source File

SOURCE=".\Templates\vcl_vector+vgui_tableau_sptr-.cxx"
# End Source File
# Begin Source File

SOURCE=".\Templates\vcl_vector+vgui_tableau~-.cxx"
# End Source File
# Begin Source File

SOURCE=".\Templates\vcl_vector+vgui_tview+-icon-.cxx"
# End Source File
# Begin Source File

SOURCE=".\Templates\vcl_vector+vgui_toolkit~-.cxx"
# End Source File
# Begin Source File

SOURCE=.\vgui.cxx
# End Source File
# Begin Source File

SOURCE=.\internals\vgui_accelerate.cxx
# End Source File
# Begin Source File

SOURCE=.\internals\vgui_accelerate_mfc.cxx
# End Source File
# Begin Source File

SOURCE=.\internals\vgui_accelerate_tag.cxx
# End Source File
# Begin Source File

SOURCE=.\vgui_active_visible.cxx
# End Source File
# Begin Source File

SOURCE=.\vgui_adaptor.cxx
# End Source File
# Begin Source File

SOURCE=.\internals\vgui_adaptor_mixin.cxx
# End Source File
# Begin Source File

SOURCE=.\internals\vgui_adaptor_tableau.cxx
# End Source File
# Begin Source File

SOURCE=.\internals\vgui_back_project.cxx
# End Source File
# Begin Source File

SOURCE=.\vgui_blackbox.cxx
# End Source File
# Begin Source File

SOURCE=.\vgui_button.cxx
# End Source File
# Begin Source File

SOURCE=.\vgui_cache_wizard.cxx
# End Source File
# Begin Source File

SOURCE=.\vgui_camera.cxx
# End Source File
# Begin Source File

SOURCE=.\vgui_clear_tableau.cxx
# End Source File
# Begin Source File

SOURCE=.\vgui_color.cxx
# End Source File
# Begin Source File

SOURCE=.\vgui_color_text.cxx
# End Source File
# Begin Source File

SOURCE=.\vgui_command.cxx
# End Source File
# Begin Source File

SOURCE=.\vgui_composite.cxx
# End Source File
# Begin Source File

SOURCE=.\vgui_debug_tableau.cxx
# End Source File
# Begin Source File

SOURCE=.\vgui_deck_tableau.cxx
# End Source File
# Begin Source File

SOURCE=.\vgui_dialog.cxx
# End Source File
# Begin Source File

SOURCE=.\internals\vgui_dialog_field.cxx
# End Source File
# Begin Source File

SOURCE=.\internals\vgui_dialog_impl.cxx
# End Source File
# Begin Source File

SOURCE=.\vgui_displaybase.cxx
# End Source File
# Begin Source File

SOURCE=.\vgui_displaylist2D.cxx
# End Source File
# Begin Source File

SOURCE=.\vgui_displaylist3D.cxx
# End Source File
# Begin Source File

SOURCE=.\vgui_drag_mixin.cxx
# End Source File
# Begin Source File

SOURCE=.\vgui_drag_tableau.cxx
# End Source File
# Begin Source File

SOURCE=.\internals\vgui_draw_line.cxx
# End Source File
# Begin Source File

SOURCE=.\vgui_easy2D.cxx
# End Source File
# Begin Source File

SOURCE=.\vgui_easy3D.cxx
# End Source File
# Begin Source File

SOURCE=.\vgui_enhance.cxx
# End Source File
# Begin Source File

SOURCE=.\vgui_error_dialog.cxx
# End Source File
# Begin Source File

SOURCE=.\vgui_event.cxx
# End Source File
# Begin Source File

SOURCE=.\vgui_event_condition.cxx
# End Source File
# Begin Source File

SOURCE=.\vgui_event_loop.cxx
# End Source File
# Begin Source File

SOURCE=.\vgui_event_server.cxx
# End Source File
# Begin Source File

SOURCE=.\internals\vgui_file_field.cxx
# End Source File
# Begin Source File

SOURCE=.\vgui_find.cxx
# End Source File
# Begin Source File

SOURCE=.\vgui_function_tableau.cxx
# End Source File
# Begin Source File

SOURCE=.\vgui_glut.cxx
# End Source File
# Begin Source File

SOURCE=.\vgui_grid_tableau.cxx
# End Source File
# Begin Source File

SOURCE=.\vgui_image_blender.cxx
# End Source File
# Begin Source File

SOURCE=.\vgui_image_renderer.cxx
# End Source File
# Begin Source File

SOURCE=.\vgui_image_tableau.cxx
# End Source File
# Begin Source File

SOURCE=.\internals\vgui_invert_homg4x4.cxx
# End Source File
# Begin Source File

SOURCE=.\vgui_key.cxx
# End Source File
# Begin Source File

SOURCE=.\vgui_listmanager2D.cxx
# End Source File
# Begin Source File

SOURCE=.\vgui_load.cxx
# End Source File
# Begin Source File

SOURCE=.\vgui_macro.cxx
# End Source File
# Begin Source File

SOURCE=.\vgui_matrix_state.cxx
# End Source File
# Begin Source File

SOURCE=.\vgui_menu.cxx
# End Source File
# Begin Source File

SOURCE=.\vgui_message.cxx
# End Source File
# Begin Source File

SOURCE=.\vgui_modifier.cxx
# End Source File
# Begin Source File

SOURCE=.\internals\vgui_multiply_4x4.cxx
# End Source File
# Begin Source File

SOURCE=.\vgui_observable.cxx
# End Source File
# Begin Source File

SOURCE=.\vgui_observer.cxx
# End Source File
# Begin Source File

SOURCE=.\internals\vgui_overlay_helper.cxx
# End Source File
# Begin Source File

SOURCE=.\vgui_pixel.cxx
# End Source File
# Begin Source File

SOURCE=.\vgui_polytab.cxx
# End Source File
# Begin Source File

SOURCE=.\vgui_popup_params.cxx
# End Source File
# Begin Source File

SOURCE=.\vgui_projection_inspector.cxx
# End Source File
# Begin Source File

SOURCE=.\vgui_quit_tableau.cxx
# End Source File
# Begin Source File

SOURCE=.\internals\vgui_rasterpos.cxx
# End Source File
# Begin Source File

SOURCE=.\vgui_roi_tableau.cxx
# End Source File
# Begin Source File

SOURCE=.\vgui_rubberbander.cxx
# End Source File
# Begin Source File

SOURCE=.\vgui_section_buffer.cxx
# End Source File
# Begin Source File

SOURCE=.\vgui_section_buffer_of.cxx
# End Source File
# Begin Source File

SOURCE=.\vgui_section_render.cxx
# End Source File
# Begin Source File

SOURCE=.\vgui_shell_tableau.cxx
# End Source File
# Begin Source File

SOURCE=".\Templates\vgui_simple_command+vgui_active_visible-.cxx"
# End Source File
# Begin Source File

SOURCE=".\Templates\vgui_simple_command+vgui_adaptor-.cxx"
# End Source File
# Begin Source File

SOURCE=".\Templates\vgui_simple_command+vgui_clear_tableau-.cxx"
# End Source File
# Begin Source File

SOURCE=".\Templates\vgui_simple_command+vgui_tableau-.cxx"
# End Source File
# Begin Source File

SOURCE=.\internals\vgui_simple_field.cxx
# End Source File
# Begin Source File

SOURCE=.\vgui_slab.cxx
# End Source File
# Begin Source File

SOURCE=.\vgui_slot.cxx
# End Source File
# Begin Source File

SOURCE=.\internals\vgui_slot_data.cxx
# End Source File
# Begin Source File

SOURCE=.\vgui_soview.cxx
# End Source File
# Begin Source File

SOURCE=.\vgui_soview2D.cxx
# End Source File
# Begin Source File

SOURCE=.\vgui_soview3D.cxx
# End Source File
# Begin Source File

SOURCE=.\vgui_statusbar.cxx
# End Source File
# Begin Source File

SOURCE=.\vgui_statusbuf.cxx
# End Source File
# Begin Source File

SOURCE=.\internals\vgui_string_field.cxx
# End Source File
# Begin Source File

SOURCE=.\vgui_style.cxx
# End Source File
# Begin Source File

SOURCE=.\vgui_style_factory.cxx
# End Source File
# Begin Source File

SOURCE=.\vgui_tableau.cxx
# End Source File
# Begin Source File

SOURCE=.\vgui_tag.cxx
# End Source File
# Begin Source File

SOURCE=.\vgui_test.cxx
# End Source File
# Begin Source File

SOURCE=.\vgui_text_graph.cxx
# End Source File
# Begin Source File

SOURCE=.\vgui_text_put.cxx
# End Source File
# Begin Source File

SOURCE=.\vgui_text_tableau.cxx
# End Source File
# Begin Source File

SOURCE=.\vgui_texture_hacks.cxx
# End Source File
# Begin Source File

SOURCE=.\vgui_toolkit.cxx
# End Source File
# Begin Source File

SOURCE=.\internals\vgui_transpose_4x4.cxx
# End Source File
# Begin Source File

SOURCE=.\vgui_tview.cxx
# End Source File
# Begin Source File

SOURCE=.\vgui_tview_launcher.cxx
# End Source File
# Begin Source File

SOURCE=.\internals\vgui_un_project.cxx
# End Source File
# Begin Source File

SOURCE=.\vgui_utils.cxx
# End Source File
# Begin Source File

SOURCE=.\vgui_viewer2D.cxx
# End Source File
# Begin Source File

SOURCE=.\vgui_viewer3D.cxx
# End Source File
# Begin Source File

SOURCE=.\vgui_window.cxx
# End Source File
# Begin Source File

SOURCE=.\vgui_wrapper_tableau.cxx
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\dll.h
# End Source File
# Begin Source File

SOURCE=.\internals\trackball.h
# End Source File
# Begin Source File

SOURCE=.\trackball.h
# End Source File
# Begin Source File

SOURCE=.\vgui.h
# End Source File
# Begin Source File

SOURCE=.\vgui_3D.h
# End Source File
# Begin Source File

SOURCE=.\internals\vgui_accelerate.h
# End Source File
# Begin Source File

SOURCE=.\internals\vgui_accelerate_mfc.h
# End Source File
# Begin Source File

SOURCE=.\internals\vgui_accelerate_x11.h
# End Source File
# Begin Source File

SOURCE=.\vgui_active_visible.h
# End Source File
# Begin Source File

SOURCE=.\vgui_adaptor.h
# End Source File
# Begin Source File

SOURCE=.\internals\vgui_adaptor_mixin.h
# End Source File
# Begin Source File

SOURCE=.\vgui_adaptor_mixin.h
# End Source File
# Begin Source File

SOURCE=.\internals\vgui_adaptor_tableau.h
# End Source File
# Begin Source File

SOURCE=.\internals\vgui_back_project.h
# End Source File
# Begin Source File

SOURCE=.\vgui_bbox.h
# End Source File
# Begin Source File

SOURCE=.\vgui_bitab.h
# End Source File
# Begin Source File

SOURCE=.\vgui_blackbox.h
# End Source File
# Begin Source File

SOURCE=.\vgui_boundingbox.h
# End Source File
# Begin Source File

SOURCE=.\vgui_button.h
# End Source File
# Begin Source File

SOURCE=.\vgui_cache_wizard.h
# End Source File
# Begin Source File

SOURCE=.\vgui_camera.h
# End Source File
# Begin Source File

SOURCE=.\vgui_clear_tableau.h
# End Source File
# Begin Source File

SOURCE=.\vgui_clip.h
# End Source File
# Begin Source File

SOURCE=.\vgui_color.h
# End Source File
# Begin Source File

SOURCE=.\vgui_color_text.h
# End Source File
# Begin Source File

SOURCE=.\vgui_command.h
# End Source File
# Begin Source File

SOURCE=.\vgui_composite.h
# End Source File
# Begin Source File

SOURCE=.\vgui_condition.h
# End Source File
# Begin Source File

SOURCE=.\vgui_debug_tableau.h
# End Source File
# Begin Source File

SOURCE=.\vgui_deck.h
# End Source File
# Begin Source File

SOURCE=.\vgui_dialog.h
# End Source File
# Begin Source File

SOURCE=.\internals\vgui_dialog_field.h
# End Source File
# Begin Source File

SOURCE=.\vgui_dialog_field.h
# End Source File
# Begin Source File

SOURCE=.\internals\vgui_dialog_impl.h
# End Source File
# Begin Source File

SOURCE=.\vgui_dialog_impl.h
# End Source File
# Begin Source File

SOURCE=.\vgui_displaybase.h
# End Source File
# Begin Source File

SOURCE=.\vgui_displaylist2D.h
# End Source File
# Begin Source File

SOURCE=.\vgui_displaylist3D.h
# End Source File
# Begin Source File

SOURCE=.\vgui_drag_mixin.h
# End Source File
# Begin Source File

SOURCE=.\vgui_drag_tableau.h
# End Source File
# Begin Source File

SOURCE=.\internals\vgui_draw_line.h
# End Source File
# Begin Source File

SOURCE=.\vgui_easy2D.h
# End Source File
# Begin Source File

SOURCE=.\vgui_easy3D.h
# End Source File
# Begin Source File

SOURCE=.\vgui_enhance.h
# End Source File
# Begin Source File

SOURCE=.\vgui_error_dialog.h
# End Source File
# Begin Source File

SOURCE=.\vgui_event.h
# End Source File
# Begin Source File

SOURCE=.\vgui_event_server.h
# End Source File
# Begin Source File

SOURCE=.\internals\vgui_file_field.h
# End Source File
# Begin Source File

SOURCE=.\vgui_file_field.h
# End Source File
# Begin Source File

SOURCE=.\vgui_function_tableau.h
# End Source File
# Begin Source File

SOURCE=.\vgui_fwd.h
# End Source File
# Begin Source File

SOURCE=.\vgui_gl.h
# End Source File
# Begin Source File

SOURCE=.\vgui_glu.h
# End Source File
# Begin Source File

SOURCE=.\vgui_glut.h
# End Source File
# Begin Source File

SOURCE=.\vgui_glx.h
# End Source File
# Begin Source File

SOURCE=.\vgui_grid_tableau.h
# End Source File
# Begin Source File

SOURCE=.\vgui_image.h
# End Source File
# Begin Source File

SOURCE=.\vgui_image_blender.h
# End Source File
# Begin Source File

SOURCE=.\vgui_image_renderer.h
# End Source File
# Begin Source File

SOURCE=.\vgui_image_tableau.h
# End Source File
# Begin Source File

SOURCE=.\vgui_image_tableau_sptr.h
# End Source File
# Begin Source File

SOURCE=.\internals\vgui_invert_homg4x4.h
# End Source File
# Begin Source File

SOURCE=.\vgui_key.h
# End Source File
# Begin Source File

SOURCE=.\vgui_listmanager2D.h
# End Source File
# Begin Source File

SOURCE=.\vgui_load.h
# End Source File
# Begin Source File

SOURCE=.\vgui_macro.h
# End Source File
# Begin Source File

SOURCE=.\vgui_manipulator.h
# End Source File
# Begin Source File

SOURCE=.\vgui_matrix_state.h
# End Source File
# Begin Source File

SOURCE=.\vgui_menu.h
# End Source File
# Begin Source File

SOURCE=.\vgui_message.h
# End Source File
# Begin Source File

SOURCE=.\vgui_modifier.h
# End Source File
# Begin Source File

SOURCE=.\vgui_mult.h
# End Source File
# Begin Source File

SOURCE=.\internals\vgui_multiply_4x4.h
# End Source File
# Begin Source File

SOURCE=.\vgui_observable.h
# End Source File
# Begin Source File

SOURCE=.\vgui_observer.h
# End Source File
# Begin Source File

SOURCE=.\internals\vgui_overlay_helper.h
# End Source File
# Begin Source File

SOURCE=.\vgui_overlay_helper.h
# End Source File
# Begin Source File

SOURCE=.\vgui_overlay_test.h
# End Source File
# Begin Source File

SOURCE=.\vgui_pixel.h
# End Source File
# Begin Source File

SOURCE=.\vgui_polytab.h
# End Source File
# Begin Source File

SOURCE=.\vgui_popup_params.h
# End Source File
# Begin Source File

SOURCE=.\vgui_print_tableau.h
# End Source File
# Begin Source File

SOURCE=.\vgui_proj.h
# End Source File
# Begin Source File

SOURCE=.\vgui_projection_inspector.h
# End Source File
# Begin Source File

SOURCE=.\vgui_quit_tableau.h
# End Source File
# Begin Source File

SOURCE=.\internals\vgui_rasterpos.h
# End Source File
# Begin Source File

SOURCE=.\vgui_rasterpos.h
# End Source File
# Begin Source File

SOURCE=.\vgui_roi_tableau.h
# End Source File
# Begin Source File

SOURCE=.\vgui_rubberbander.h
# End Source File
# Begin Source File

SOURCE=.\vgui_satellite.h
# End Source File
# Begin Source File

SOURCE=.\vgui_section.h
# End Source File
# Begin Source File

SOURCE=.\vgui_section_buffer.h
# End Source File
# Begin Source File

SOURCE=.\vgui_section_buffer_of.h
# End Source File
# Begin Source File

SOURCE=.\vgui_section_render.h
# End Source File
# Begin Source File

SOURCE=.\vgui_shell_tableau.h
# End Source File
# Begin Source File

SOURCE=.\internals\vgui_simple_field.h
# End Source File
# Begin Source File

SOURCE=.\vgui_simple_field.h
# End Source File
# Begin Source File

SOURCE=.\vgui_slot.h
# End Source File
# Begin Source File

SOURCE=.\internals\vgui_slot_data.h
# End Source File
# Begin Source File

SOURCE=.\vgui_smartptr.h
# End Source File
# Begin Source File

SOURCE=.\vgui_soview.h
# End Source File
# Begin Source File

SOURCE=.\vgui_soview2D.h
# End Source File
# Begin Source File

SOURCE=.\vgui_soview3D.h
# End Source File
# Begin Source File

SOURCE=.\vgui_spinner.h
# End Source File
# Begin Source File

SOURCE=.\vgui_statusbar.h
# End Source File
# Begin Source File

SOURCE=.\vgui_statusbuf.h
# End Source File
# Begin Source File

SOURCE=.\internals\vgui_string_field.h
# End Source File
# Begin Source File

SOURCE=.\vgui_string_field.h
# End Source File
# Begin Source File

SOURCE=.\vgui_style.h
# End Source File
# Begin Source File

SOURCE=.\vgui_style_factory.h
# End Source File
# Begin Source File

SOURCE=.\vgui_tableau.h
# End Source File
# Begin Source File

SOURCE=.\vgui_tableau_sptr.h
# End Source File
# Begin Source File

SOURCE=.\vgui_tablet.h
# End Source File
# Begin Source File

SOURCE=.\vgui_tag.h
# End Source File
# Begin Source File

SOURCE=.\vgui_test.h
# End Source File
# Begin Source File

SOURCE=.\vgui_text.h
# End Source File
# Begin Source File

SOURCE=.\vgui_texture_hacks.h
# End Source File
# Begin Source File

SOURCE=.\vgui_token2D.h
# End Source File
# Begin Source File

SOURCE=.\vgui_token3D.h
# End Source File
# Begin Source File

SOURCE=.\internals\vgui_transpose_4x4.h
# End Source File
# Begin Source File

SOURCE=.\vgui_tritab.h
# End Source File
# Begin Source File

SOURCE=.\vgui_tview.h
# End Source File
# Begin Source File

SOURCE=.\vgui_tview_launcher.h
# End Source File
# Begin Source File

SOURCE=.\internals\vgui_un_project.h
# End Source File
# Begin Source File

SOURCE=.\vgui_utils.h
# End Source File
# Begin Source File

SOURCE=.\vgui_viewer2D.h
# End Source File
# Begin Source File

SOURCE=.\vgui_viewer2D_sptr.h
# End Source File
# Begin Source File

SOURCE=.\vgui_viewer3D.h
# End Source File
# Begin Source File

SOURCE=.\vgui_window.h
# End Source File
# Begin Source File

SOURCE=.\vgui_wrapper_tableau.h
# End Source File
# Begin Source File

SOURCE=.\vgui_zoomer.h
# End Source File
# End Group
# End Target
# End Project
