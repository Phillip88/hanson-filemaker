#include "MyHash.h"
#include "MyRSA.h"

// Crypto++
#include "sha.h"        // SHA-1, SHA-256, SHA-384, SHA-512
#include "ripemd.h"     // RIPEMD160
#include "crc.h"        // CRC-32

//std
#include <conio.h>
#include <stdio.h>

using namespace std;
using namespace CryptoPP;

/**
* For hashing functions like SHA, RIPEMD
*/
void hashTest()
{	
	using namespace hash;

	cout << "How to implement Hash function using cryptoC++ lib" << "\n\n";

	// Data as input of hash function
	string strDataPart1 = "The quick brown fox jumps over the ";
    string strDataPart2 = "lazy ";
    string strDataPart3 = "dog";

	try
	{
		DumpHash(SHA(), "SHA", strDataPart1, strDataPart2, strDataPart3);
		DumpHash(SHA256(), "SHA256", strDataPart1, strDataPart2, strDataPart3);
		DumpHash(RIPEMD160(), "RIPEMD160", strDataPart1, strDataPart2, strDataPart3);
		DumpHash(CRC32(), "CRC32", strDataPart1, strDataPart2, strDataPart3);
	}
	catch (CryptoPP::Exception const& e)
    {
          cout << "CryptoPP::Exception caught: " << endl
               << e.what() << endl;
    }
} // end hashTest()

/**
* For RSA implemention test.
*/
void rsaTest()
{
	using namespace rsa;

	cout << "How to implement RSA using cryptoC++ lib" << "\n\n";

	std::string publicKey;
    std::string privateKey;

	RsaGenerateStringKeys(publicKey, privateKey);
	cout << "Public key : " << publicKey << endl
		 << "Private key: " << privateKey << endl;
}

int main()
{
	int action;
	
    printf("1. Hash\n");
    printf("2. RSA\n");
    printf("3. [Place Holder]\n");
    printf("4. [Place Holder]\n");
    printf("5. Exit\n");

	do{   
		printf("--------------------");
		printf("\nSelect on action:\n");
        scanf("%d", &action);
        switch(action){
             case 1:
                  hashTest();
                  break;
             case 2:
                  rsaTest();
                  break;                  
             case 3:
                 printf("3. Exit\n");
                  break;
             case 4:
                 printf("4. Exit\n");
                  break;
        };
    }while(action!=5);
	
	return 0;
}