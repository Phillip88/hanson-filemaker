/////////////////////////////////////////////////
// @author: Phillip VU <phat.vu.enclave.vn>
// Date created : Nov 20, 2012
//
// All classes that implement one-way hash functions in Crypto++ are derived from HashTransformation. 
// A class derived from HashTransformation can be used either directly or indirectly.
// When used directly, the whole hashing operation can be completed in one step by calling the 
// CalculateDigest method, or in multiple steps by first calling the Update method several times and 
// then wrapping up by calling the Final method.
// Indirect use of a HashTransformation derivative can be done through a wrapper class like HashFilter, 
// which enables one to use a hashing algorithm in a manner conforming to the Filter paradigm (a family 
// within the BufferedTransformation hierarchy).
// After a hash module's Final method is called - either by calling Final directly, or indirectly by 
// calling CalculateDigest or by calling HashFilter::MessageEnd() on a filter initialized with the hash module, 
// the hash module is ready to calculate another hash, just as if the hash module had just been initialized.
// The HashTransformation base class also provides the methods Verify and VerifyDigest. These methods are used
// similarly to Final and CalculateDigest, respectively, with the only distinction that they verify the 
// computed digest to a supplied digest instead of calculating a digest. For implementations of regular one-way 
// hash functions, calling VerifyDigest() is equivalent to calling CalculateDigest() and then manually comparing 
// the calculated digest with a supplied one. However, note that this is not the case with message authentication 
// codes (which are also derived from HashTransformation and use the same interface).
// Src: http://www.cryptopp.com/wiki/User_Guide:_cryptlib.h
//
/////////////////////////////////////////////////

// Crypto++
#include "hex.h"        // HexEncoder
#include "files.h"

using namespace std;
using namespace CryptoPP;

namespace hash
{
	 void DumpHash_SingleStep( HashTransformation& hash, 
							   char const* hashAlgorithmName,
							   string const& strData);

	 void DumpHash( HashTransformation& hash,
				   char const* szModuleName,
				   string const& strDataPart1,
		           string const& strDataPart2,
				   string const& strDataPart3);

	 void DumpHash_MultiStep(CryptoPP::HashTransformation& hash,
						     char const* hashAlgorithmName,
						     std::string const& strDataPart1,
						     std::string const& strDataPart2,
						     std::string const& strDataPart3);

	 void DumpHash_HashFilter(CryptoPP::HashTransformation& hash,
						     char const* hashAlgorithmName,
						     std::string const& strDataPart1,
						     std::string const& strDataPart2,
						     std::string const& strDataPart3);
}