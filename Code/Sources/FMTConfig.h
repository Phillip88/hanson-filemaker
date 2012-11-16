//////////////////////////////////////////////////////////////////////////////////////
//  
//  FMTConfig.h - Definitions used to configure 24U Plug-In Template
//
//  Version 3.0, Copyright ©2002-2010 by 24U Software. All rights reserved.
//
//  Written by Tomas Zahradnicky, HOnza Koudelka, and Josef Andrysek
//
////////////////////////////////////////////////////////////////////////////////
//
//  The latest version of 24U Plug-In Template is available for download from:
//
//  http://www.24uSoftware.com/PlugInTemplate 
//
////////////////////////////////////////////////////////////////////////////////
//
//  24U Sample Code - Terms of use
//
//  Under the terms of the 24U Software License Agreement, 24U s.r.o. grants
//  you a non-exclusive royalty-free Developer License (3.2) to use 24U Plug-In
//  Template solely to compile plug-ins for use with FileMaker products.
//
//  Redistribution of 24U Sample Code in the source form, as part of
//  an open-source plug-in project is permitted provided that the following
//  conditions are met:
//
//  * Redistributions of source code must retain the copyright notice, the terms
//    of use, and the "24U Software License Agreement" document.
//
//  * We require that you make it clear in the source wherever modified that the
//    code was descended from 24U Sample Code, but that you've made changes.
//
//  See the "License.txt" and "24U Software License Agreement.pdf" files
//  for detailed terms of use and licensing conditions.
//
////////////////////////////////////////////////////////////////////////

//
//  This header file contains all necessary constant definitions for building
//  your plug-in. Start your plug-in development by carefully configuring this
//  file, and you'll be ready to start coding for your external functions.
//  This header should not be included into your sources. It's only purpose
//  is to configure the template. If you need to define some constatns to be
//  used by both your code and the template, define them in your own header
//  file, such as FMPlugin.h, and include that header file here.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef __FMTConfig_h__
#define __FMTConfig_h__

#include "FMPlugin.h"


////////////////////////////////////////////////////////////////////////////////
//
//  Shared constants
//
/////////////////////////////////////////////////////////////////////////////
//
//  The following constants configure your plug-in to behave well under
//  FileMaker applications and to be well recognized on both Mac OS and
//  Windows operating systems. It is recommended to always set all these
//  contants up to contain accurate information about your plug-in.
//

// Constant is a 4 characters long ID of your Plug-In
// The ID must be unique for each Plug-In and must not begin with "F", "FM", or "Web" as these IDs are reserved by FileMaker, Inc
// To make sure you will use a unique ID, you should register the ID as a creator code at the Apple Developer Technical Support 
// web site even if you won't be creating a Mac OS X version of your Plug-In. To register IDs, go to the support pages on the 
// Apple Computer web site at Apple Developer Connection and look for a link to Creator Type or Data Type Registration.
#define PLUGIN_ID_STRING        "25PU"

#define PLUGIN_NAME             "Hanson Plug-In"
#define PLUGIN_VERSION          "1.0"

#define PLUGIN_VERSION_MAJOR		0x01
#define PLUGIN_VERSION_MINOR		0x0
#define PLUGIN_VERSION_BUILD		0x0


#define PLUGIN_INFO             "This plug-in aims License module in Hanson project."

#define COMPANY_NAME            "Enclave"
#define COPY_STATEMENT          "Copyright ©2012 by " COMPANY_NAME


// Set the WANT_IDLE constant to 1 if you want FileMaker to call your Plug-In periodically in idle time to let 
// it do any idle processing. If you set this constant to 1, your idle functions in the "FMPluginHandlers.cpp" 
// file will be called periodically whenever the FileMaker application has nothing else to do. If you don't need 
// any idle processing, set this constant to 0 so that you don't steal processing time from FileMaker.
#define WANT_IDLE               0           // set to 1 if you want idle-processing


// constant defines if your Plug-In should have the "Configure..." button enabled in 
// the Plug-Ins panel of the FileMaker Application Preferences dialog box
// If you set this constant to 1, the button will be enabled and after clicking on it, 
// your Preferences() function in the "FMPluginHandlers.cpp" file will get called.
#define WANT_PREFERENCES        0           // set to 1 if you want to handle preferences


////////////////////////////////////////////////////////////////////////////////
//
//  Mac OS X constants
//
/////////////////////////////////////////////////////////////////////////////
//
//  Define Mac OS X specific information for you plug-in below.
//

#define PLUGIN_BUNDLE_ID    "vn.enclaveit.hanson.plugin"


////////////////////////////////////////////////////////////////////////////////
//
//  Windows constants
//
/////////////////////////////////////////////////////////////////////////////
//
//  Define Windows specific information for you plug-in below.
//

// A hint for user who accidentally renames your plug-in
#define FILE_NAME_PC        "FMPlugin.fmx"  

#define PLUGIN_INFO_PC      "This file is a FileMaker applications plug-in. To make this file effective, drop it into FileMaker's Extensions folder and launch the FileMaker application."

#define COMPANY_URL         "http://www.enclave.vn/"


////////////////////////////////////////////////////////////////////////////////
//
//  Function definitions
//
/////////////////////////////////////////////////////////////////////////////
//
//  Do not modify the following enum, use the defined constants to configure
//  MINIMUM and MAXIMUM parameters required for each function
//  (the FUNCTION_X_PARAMS macros)
//

#ifndef __PLIST__
enum {
    kAtLeast_0_Parameters = 0,
    kAtLeast_1_Parameter  = 1,
    kAtLeast_2_Parameters = 2,
    kAtLeast_3_Parameters = 3,
    kAtLeast_4_Parameters = 4,
    kAtLeast_5_Parameters = 5,
    kAtLeast_6_Parameters = 6,
    kAtLeast_7_Parameters = 7,
    kAtLeast_8_Parameters = 8,
    kAtLeast_9_Parameters = 9,
    kAtLeast_10_Parameters = 10,

    kAtWorst_0_Parameters = 0,
    kAtWorst_1_Parameter  = 1,
    kAtWorst_2_Parameters = 2,
    kAtWorst_3_Parameters = 3,
    kAtWorst_4_Parameters = 4,
    kAtWorst_5_Parameters = 5,
    kAtWorst_6_Parameters = 6,
    kAtWorst_7_Parameters = 7,
    kAtWorst_8_Parameters = 8,
    kAtWorst_9_Parameters = 9,
    kAtWorst_10_Parameters = 10,
    kAtWorst_Unlimited_Parameters = -1
};
#endif // __PLIST__

/////////////////////////////////////////////////////////////////////////////
//
//  Define your external functions here. For each of your functions,
//  uncomment the first commented block of defines, and set up the
//  function's name, flags, parameters and prototype.
// 
////////////////////////////////////////////////////////////////////////////

// Function definitions

#define FUNCTION_1_C_NAME         X24FT_Version
#define FUNCTION_1_FLAGS          fmx::ExprEnv::kMayEvaluateOnServer | fmx::ExprEnv::kDisplayInAllDialogs
#define FUNCTION_1_PARAMS         kAtLeast_0_Parameters, kAtWorst_1_Parameter
#define FUNCTION_1_PROTOTYPE      "X24FT_Version( { versionFormat } )"


#define FUNCTION_2_C_NAME         MyFunction
// This function vailable for both client and server-side calculations
#define FUNCTION_2_FLAGS          fmx::ExprEnv::kMayEvaluateOnServer | fmx::ExprEnv::kDisplayInAllDialogs
// This function is going to take TWO parameters, the first one being REQUIRED, 
// and the second one OPTIONAL
#define FUNCTION_2_PARAMS         kAtLeast_0_Parameters, kAtWorst_1_Parameter
// #define FUNCTION_2_PROTOTYPE      "Helloworld({ hello })"
#define FUNCTION_2_PROTOTYPE      "MyFunction(param1; { param2 } )"


#define FUNCTION_2_C_NAME         VerifyResultEncryped
// This function vailable for both client and server-side calculations
#define FUNCTION_2_FLAGS          fmx::ExprEnv::kMayEvaluateOnServer | fmx::ExprEnv::kDisplayInAllDialogs
// This function is going to take TWO parameters, the first one being REQUIRED, 
// and the second one OPTIONAL
#define FUNCTION_2_PARAMS         kAtLeast_0_Parameters, kAtWorst_1_Parameter
#define FUNCTION_2_PROTOTYPE      "VerifyResultEncryped_TEST(param1; { param2 } )"

/*
#define FUNCTION_3_C_NAME         Plato_Sum
#define FUNCTION_3_FLAGS          fmx::ExprEnv::kMayEvaluateOnServer | fmx::ExprEnv::kDisplayInAllDialogs
#define FUNCTION_3_PARAMS         kAtLeast_0_Parameters, kAtLeast_2_Parameters
#define FUNCTION_3_PROTOTYPE      "Plato_Sum( param1, param2 )"
*/

//#define FUNCTION_4_C_NAME         X24FT_Function4
//#define FUNCTION_4_FLAGS          fmx::ExprEnv::kMayEvaluateOnServer | fmx::ExprEnv::kDisplayInAllDialogs
//#define FUNCTION_4_PARAMS         kAtLeast_0_Parameters, kAtWorst_Unlimited_Parameters
//#define FUNCTION_4_PROTOTYPE      "X24FT_Function4( param1 ; ... )"

//#define FUNCTION_5_C_NAME         X24FT_Function5
//#define FUNCTION_5_FLAGS          fmx::ExprEnv::kMayEvaluateOnServer | fmx::ExprEnv::kDisplayInAllDialogs
//#define FUNCTION_5_PARAMS         kAtLeast_0_Parameters, kAtWorst_Unlimited_Parameters
//#define FUNCTION_5_PROTOTYPE      "X24FT_Function5( param1 ; ... )"

//#define FUNCTION_6_C_NAME         X24FT_Function6
//#define FUNCTION_6_FLAGS          fmx::ExprEnv::kMayEvaluateOnServer | fmx::ExprEnv::kDisplayInAllDialogs
//#define FUNCTION_6_PARAMS         kAtLeast_0_Parameters, kAtWorst_Unlimited_Parameters
//#define FUNCTION_6_PROTOTYPE      "X24FT_Function6( param1 ; ... )"

//#define FUNCTION_7_C_NAME         X24FT_Function7
//#define FUNCTION_7_FLAGS          fmx::ExprEnv::kMayEvaluateOnServer | fmx::ExprEnv::kDisplayInAllDialogs
//#define FUNCTION_7_PARAMS         kAtLeast_0_Parameters, kAtWorst_Unlimited_Parameters
//#define FUNCTION_7_PROTOTYPE      "X24FT_Function7( param1 ; ... )"

//#define FUNCTION_8_C_NAME         X24FT_Function8
//#define FUNCTION_8_FLAGS          fmx::ExprEnv::kMayEvaluateOnServer | fmx::ExprEnv::kDisplayInAllDialogs
//#define FUNCTION_8_PARAMS         kAtLeast_0_Parameters, kAtWorst_Unlimited_Parameters
//#define FUNCTION_8_PROTOTYPE      "X24FT_Function8( param1 ; ... )"

//#define FUNCTION_9_C_NAME         X24FT_Function9
//#define FUNCTION_9_FLAGS          fmx::ExprEnv::kMayEvaluateOnServer | fmx::ExprEnv::kDisplayInAllDialogs
//#define FUNCTION_9_PARAMS         kAtLeast_0_Parameters, kAtWorst_Unlimited_Parameters
//#define FUNCTION_9_PROTOTYPE      "X24FT_Function9( param1 ; ... )"

//#define FUNCTION_10_C_NAME         X24FT_Function10
//#define FUNCTION_10_FLAGS          fmx::ExprEnv::kMayEvaluateOnServer | fmx::ExprEnv::kDisplayInAllDialogs
//#define FUNCTION_10_PARAMS         kAtLeast_0_Parameters, kAtWorst_Unlimited_Parameters
//#define FUNCTION_10_PROTOTYPE      "X24FT_Function10( param1 ; ... )"

////////////////////////////////////////////////////////////////////////////////

#endif // __FMTConfig_h__
