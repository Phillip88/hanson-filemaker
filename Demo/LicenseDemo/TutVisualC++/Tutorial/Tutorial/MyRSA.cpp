#include "MyRSA.h"

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