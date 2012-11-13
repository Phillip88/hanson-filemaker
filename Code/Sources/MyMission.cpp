//  version of this plug-in, as defined in the FMTConfig.h header file.
//
//  As a bonus for you, if you pass the string "platform" as a parameter to this
//  function, it will respond with the information about which code is being
//  used, whether it is Mac OS X code, or Windows code. If you pass the string
//  "long" to this function, a long version string consisting of the plug-in's
//  name and version is returned.
//
////////////////////////////////////////////////////////////////////////////////


#include "FMPlugin.h"
#include "FMTemplate/FMTemplate.h"

FMX_PROC(fmx::errcode) MyFunction1(short          funcId,
                                   const fmx::ExprEnv&  environment,
                                   const fmx::DataVect& dataVect,
                                   fmx::Data&     result )
{
	#pragma unused(funcId,environment)

	fmx::errcode        err = 0;
    FMX_Unichar         pluginName[256];
    FMX_Unichar         pluginVersion[256];
    fmx::TextAutoPtr    tempText;
    fmx::TextAutoPtr    resultText;
    
    if( dataVect.Size() > 0 )
    {
        //We have at least one parameter. Read it and return correct information.
        const fmx::Text& parameter1 = dataVect.AtAsText(0);
        
        if( tempText->Assign(""), *tempText == parameter1 )
        {
            //If the parameter is null, then return Hello World
            char *str;
			str = "Hello World";
			resultText->Assign(str);
        }
	}
	err = result.SetAsText( *resultText, dataVect.At(0).GetLocale() );
	return err;
}

