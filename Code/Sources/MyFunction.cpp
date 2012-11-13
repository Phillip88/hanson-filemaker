////////////////////////////////////////////////////////////////////////////////
//
// Hanson -Filemaker
// Written by Phillip VU <phat.vu@enclave.vn>
//
////////////////////////////////////////////////////////////////////////////////

#include "stdio.h"
#include "FMPlugin.h"
#include "FMTemplate/FMTemplate.h"
#include "FMTemplate/FMUtils.h"

FMX_PROC(fmx::errcode) MyFunction(short          funcId,
                                  const fmx::ExprEnv&  environment,
                                  const fmx::DataVect& dataVect,
                                  fmx::Data&     result )
{
	#pragma unused(funcId,environment)

	fmx::errcode        err = 0;
    //FMX_Unichar         pluginName[256];
    //FMX_Unichar         pluginVersion[256];
    fmx::TextAutoPtr    emptyText;
    fmx::TextAutoPtr    resultText;
	char* rtnText = "Hello World";
    emptyText->Assign("");
    if( dataVect.Size() > 0 )
    {
        //We have at least one parameter. Read it and return correct information.
        const fmx::Text& parameter1 = dataVect.AtAsText(0);
        if( *emptyText == parameter1 )
        {
            //If the parameter is null, then return Hello World
			resultText->Assign(rtnText);
        } else {
			char *paramAsChar;
			char *finalRs = new char[50];
			GetAsciiFMText(parameter1, paramAsChar);
			strcpy(finalRs, "");
			strcat(finalRs, rtnText);
			strcat(finalRs, paramAsChar);
			resultText->Assign(finalRs);
		}
	}
	err = result.SetAsText( *resultText, dataVect.At(0).GetLocale() );
	return err;
}

