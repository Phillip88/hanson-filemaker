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

#pragma mark GenerateLicenseKey
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

#pragma mark OpenFolderBrowser
FMX_PROC(fmx::errcode) OpenFolderBrowser(short funcId,
									     const fmx::ExprEnv&  environment,
									     const fmx::DataVect& dataVect,
									     fmx::Data&     result )
{
	#pragma unused(funcId,environment)

	using namespace fmx;

	fmx::errcode        err = 0;
	TextAutoPtr    resultText;

    if( dataVect.Size() == 1 )
    {
		std::string szPath("");

		if (utils::GetFolder(szPath, "Select a folder.", NULL) == true) 
		{
			resultText->Assign(szPath.c_str());
		}
		else
		{
			resultText->Assign("No folder selected!");
		}
	}
	err = result.SetAsText( *resultText, dataVect.At(0).GetLocale() );
	return err;
}

#pragma mark CheckNetworkStatus
FMX_PROC(fmx::errcode) CheckNetworkStatus(short funcId,
									      const fmx::ExprEnv&  environment,
									      const fmx::DataVect& dataVect,
									      fmx::Data&     result )
{
	#pragma unused(funcId,environment)

	using namespace fmx;

	fmx::errcode        err = 0;
	TextAutoPtr    resultText;

    if( dataVect.Size() == 1 )
    {
		int i; 
		i = system ("ping -n 1 www.google.com >nul");
		if (i == 1)
		{
			resultText->Assign("Failed");
		}
		else
		{
			resultText->Assign("Success");
		}
	}
	err = result.SetAsText( *resultText, dataVect.At(0).GetLocale() );
	return err;
}

#pragma mark GetDataFromClipBoard
FMX_PROC(fmx::errcode) GetDataFromClipBoard(short funcId,
									        const fmx::ExprEnv&  environment,
									        const fmx::DataVect& dataVect,
									        fmx::Data&     result )
{
	#pragma unused(funcId,environment)

	using namespace fmx;

	fmx::errcode        err = 0;
	TextAutoPtr    resultText;
	char * strResult;

    if( dataVect.Size() == 1 )
    {
		HANDLE h;
   
		if (!OpenClipboard(NULL))
			strResult = "Can't open clipboard";
		else
		{
			h = GetClipboardData(CF_TEXT);
			// if the content is not a text, NULL will be returned.
			if (h == NULL)
				strResult = "NULL";
			else
				strResult = (char *) h;
		}

		CloseClipboard();
		resultText->Assign(strResult);
	}
	err = result.SetAsText( *resultText, dataVect.At(0).GetLocale() );
	return err;
}

#pragma mark SubString
FMX_PROC(fmx::errcode) SubString(short funcId,
								 const fmx::ExprEnv&  environment,
							     const fmx::DataVect& dataVect,
							     fmx::Data&     result )
{
	#pragma unused(funcId,environment)

	using namespace fmx;

	fmx::errcode   err = 0;
	TextAutoPtr    resultText;
	// This function will be excuted with the following assumptions:
	// + the first parameter is a string.
	// + the second and third parameter can be converted from string to int as well
	//   (e.g : "5", "10", "abc" is not in this case )
	// + the value second parameter must be less than the length of the first parameter.

    if( dataVect.Size() == 3 )
    {
		char *param1AsChar, *param2AsChar, *param3AsChar;
		GetAsciiFMText(dataVect.AtAsText(0), param1AsChar);
		GetAsciiFMText(dataVect.AtAsText(1), param2AsChar);
		GetAsciiFMText(dataVect.AtAsText(2), param3AsChar);
		std::string str(param1AsChar);
		int from, to;
		std::stringstream(param2AsChar) >> from;
		std::stringstream(param3AsChar) >> to;

		resultText->Assign(str.substr(from, to).c_str());
	}
	err = result.SetAsText( *resultText, dataVect.At(0).GetLocale() );
	return err;
}