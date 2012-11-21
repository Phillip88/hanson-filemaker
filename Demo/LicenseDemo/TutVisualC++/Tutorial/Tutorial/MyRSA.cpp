#include "MyRSA.h"
#include "hex.h"
#include "rsa.h"
#include "osrng.h"
#include "pssr.h"
#include "secblock.h"
#include <exception>

using namespace std;
using namespace CryptoPP;

namespace rsa
{
	void RsaGenerateStringKeys(string & publicKeyStr, string & privateKeyStr)
	{
		// Pseudo Random Number Generator
        CryptoPP::AutoSeededRandomPool rng;

        // Generate Parameters
        CryptoPP::InvertibleRSAFunction params;
        params.GenerateRandomWithKeySize( rng, 1536 );

        CryptoPP::RSA::PrivateKey privateKey( params );
        CryptoPP::RSA::PublicKey publicKey( params );

        CryptoPP::HexEncoder encoder;

        // save public Key
        encoder.Attach( new CryptoPP::StringSink( publicKeyStr ) );
        publicKey.Save( encoder );

        // save private Key
        encoder.Attach( new CryptoPP::StringSink( privateKeyStr ) );
        privateKey.Save( encoder );
	}
}

namespace utils
{
	void SaveVectorToFile(const std::wstring& fileName, const std::vector<char>& data)
    {
        HANDLE hFile = CreateFileW(fileName.c_str(), GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, 0, NULL);
        if(hFile == INVALID_HANDLE_VALUE)
            throw std::logic_error("SaveVectorToFile : can't open file ");
        utils::CHandleGuard fileGuard(hFile);
        DWORD bytesWriten = 0;
        if(!WriteFile(hFile, &data[0], (DWORD)data.size(), &bytesWriten, 0))
            throw std::logic_error("SaveVectorToFile : can't write to file ");
    }
}