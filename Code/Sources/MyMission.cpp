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
#include "FMTemplate/FMUtils.h"

#include <sstream>
#include <iostream>
#include <vector>
#include "resource.h"
#include "Utils.h"

// CryptoC++
#include "ripemd.h"
#include "hex.h"
#include "files.h"


FMX_PROC(fmx::errcode) GenerateLicenseKey(short          funcId,
										  const fmx::ExprEnv&  environment,
										  const fmx::DataVect& dataVect,
										  fmx::Data&     result )
{
	#pragma unused(funcId,environment)

	using namespace fmx;
	using namespace std;
	using namespace CryptoPP;

	fmx::errcode        err = 0;
    FMX_Unichar         pluginName[256];
    FMX_Unichar         pluginVersion[256];
    TextAutoPtr    tempText;
    TextAutoPtr    resultText;

    if( dataVect.Size() == 2 )
    {
        //We have at least one parameter. Read it and return correct information.
		char *param1AsChar, *param2AsChar;
        const Text& param = dataVect.AtAsText(0);
		GetAsciiFMText(dataVect.AtAsText(0), param1AsChar);
		GetAsciiFMText(dataVect.AtAsText(1), param2AsChar);
		string param1AsStr(param1AsChar);
		string param2AsStr(param2AsChar);

		//HashTransformation hash;
		RIPEMD160 hash;
		SecByteBlock sbbDigest(hash.DigestSize());

		// sbbDigest now contains the hash of strData.
		hash.CalculateDigest(sbbDigest.begin(),
							(byte const*) (param1AsStr+param2AsStr).data(),
							(param1AsStr+"HANSON2012"+param2AsStr).size());
	  
		string hashValue;
		HexEncoder(new StringSink(hashValue)).Put(sbbDigest.begin(), sbbDigest.size());
		utils::formatStringWithHiphen(hashValue);

		resultText->Assign(&hashValue[0]);
	}
	err = result.SetAsText( *resultText, dataVect.At(0).GetLocale() );
	return err;
}