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


FMX_PROC(fmx::errcode) GenerateProductKey(short          funcId,
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

	using namespace std;
	using namespace CryptoPP;
    
    if( dataVect.Size() > 0 )
    {
        //We have at least one parameter. Read it and return correct information.
		char *paramAsChar;
        const fmx::Text& param = dataVect.AtAsText(0);
		GetAsciiFMText(param, paramAsChar);
		string paramAsStr(paramAsChar);

		//HashTransformation hash;
		CryptoPP::RIPEMD160 hash;
		SecByteBlock sbbDigest(hash.DigestSize());

		// sbbDigest now contains the hash of strData.
		hash.CalculateDigest(sbbDigest.begin(),
							(byte const*) paramAsStr.data(),
							 paramAsStr.size());
	  
		string hashValue;
		HexEncoder(new StringSink(hashValue)).Put(sbbDigest.begin(), sbbDigest.size());
		utils::formatStringWithHiphen(hashValue);

		resultText->Assign(&hashValue[0]);
	}
	err = result.SetAsText( *resultText, dataVect.At(0).GetLocale() );
	return err;
}