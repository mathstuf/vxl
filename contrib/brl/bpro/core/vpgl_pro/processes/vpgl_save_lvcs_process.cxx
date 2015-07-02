// This is brl/bpro/core/vpgl_pro/processes/vpgl_save_lvcs_process.cxx
#include <bprb/bprb_func_process.h>
//:
// \file

#include <bprb/bprb_parameters.h>
#include <vcl_iostream.h>
#include <vpgl/vpgl_lvcs.h>
#include <vpgl/vpgl_lvcs_sptr.h>

//: Save a lvcs
//: initialization
bool vpgl_save_lvcs_process_cons(bprb_func_process& pro)
{
  // this process takes two inputs:
  vcl_vector<vcl_string> input_types;
  input_types.push_back("vpgl_lvcs_sptr");
  input_types.push_back("vcl_string");
  // this process has no output
  vcl_vector<vcl_string> output_types;
  return pro.set_input_types(input_types) && pro.set_output_types(output_types);
}

//:execute the process
bool vpgl_save_lvcs_process(bprb_func_process& pro)
{
  if (!pro.verify_inputs()) {
    vcl_cerr << pro.name() << ": Wrong inputs!!!\n";
    return false;
  }
  // get input
  vpgl_lvcs_sptr lvcs = pro.get_input<vpgl_lvcs_sptr>(0);
  vcl_string filename = pro.get_input<vcl_string>(1);

  if (!lvcs) {
    vcl_cerr << pro.name() << ": input lvcs is empty!!\n";
    return false;
  }
  // save to file
  vcl_ofstream ofs(filename.c_str());
  if (!ofs.good()) {
    vcl_cerr << pro.name() << ": Error opening lvcs file: " << filename << "!!\n";
    return false;
  }

  lvcs->write(ofs);
  ofs.close();
  return true;
}


//: Create a lvcs and save it into lvcs file
//: initialization
bool vpgl_create_and_save_lvcs_process_cons(bprb_func_process& pro)
{
  //this process takes four inputs:
  // 0: (float)  latitude
  // 1: (float)  longitude
  // 2: (float)  elevation
  // 3: (string) lvcs cs name
  // 4: (string) lvcs filename to save
  bool ok=false;
  vcl_vector<vcl_string> input_types;
  input_types.push_back("float");
  input_types.push_back("float");
  input_types.push_back("float");
  input_types.push_back("vcl_string");
  input_types.push_back("vcl_string");
  ok = pro.set_input_types(input_types);
  if (!ok) return ok;

  // process has no outputs
  vcl_vector<vcl_string> output_types;
  ok = pro.set_output_types(output_types);
  if (!ok) return ok;

  return true;
}

//: Execute the process
bool vpgl_create_and_save_lvcs_process(bprb_func_process& pro)
{
  if (!pro.verify_inputs()) {
    vcl_cout << pro.name() << ": The number of inputs should be " << pro.input_types().size() << vcl_endl;
    return false;
  }

  // get the inputs
  float lat = pro.get_input<float>(0);
  float lon = pro.get_input<float>(1);
  float el  = pro.get_input<float>(2);
  vcl_string cs_name = pro.get_input<vcl_string>(3);
  vcl_string lvcs_filename = pro.get_input<vcl_string>(4);

  // create lvcs
  vpgl_lvcs lvcs(lat, lon, el, vpgl_lvcs::str_to_enum(cs_name.c_str()), vpgl_lvcs::DEG, vpgl_lvcs::METERS);
  // save to file
  vcl_ofstream ofs(lvcs_filename.c_str());
  if (!ofs.good()) {
    vcl_cerr << "Error opening lvcs filename " << lvcs_filename << '\n';
    return false;
  }

  lvcs.write(ofs);

  return true;
}

