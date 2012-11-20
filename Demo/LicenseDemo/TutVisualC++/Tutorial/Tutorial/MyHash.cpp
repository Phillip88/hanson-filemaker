#include "MyHash.h"

using namespace std;
using namespace CryptoPP;

namespace hash {

	/**
	* The whole hashing operation can be completed in one step.
	*/
	void DumpHash_SingleStep( HashTransformation& hash, 
							  char const* hashAlgorithmName,
							  string const& strData)
	{
		// Cannot use std::string for buffer;
		// its internal storage might not be contiguous
		SecByteBlock sbbDigest(hash.DigestSize());
	  
		// sbbDigest now contains the hash of strData.
		hash.CalculateDigest(sbbDigest.begin(),
							(byte const*) strData.data(),
							strData.size());
	  
		cout << hashAlgorithmName << " Single-Step: ";
		HexEncoder(new FileSink(cout)).Put(sbbDigest.begin(), sbbDigest.size());
		cout << endl;
	} // end DumpHash_SingleStep


	/**
	* The whole hashing operation can be completed in multiple steps
	* by first calling the Update method several times and then wrapping 
	* up by calling the Final method.
	*/
	void DumpHash_MultiStep(HashTransformation& hash,
						    char const* hashAlgorithmName,
						    string const& strDataPart1,
						    string const& strDataPart2,
						    string const& strDataPart3)
    {
		hash.Update((byte const*) strDataPart1.data(), strDataPart1.size());
		hash.Update((byte const*) strDataPart2.data(), strDataPart2.size());
		hash.Update((byte const*) strDataPart3.data(), strDataPart3.size());

		// Cannot use std::string for buffer;
		// its internal storage might not be contiguous
		SecByteBlock sbbDigest(hash.DigestSize());

		hash.Final(sbbDigest.begin());

		cout << hashAlgorithmName << " Multi-Step:  ";
		HexEncoder(new FileSink(cout)).Put(sbbDigest.begin(), sbbDigest.size());
		cout << endl;
    } // DumpHash_MultiStep

	void DumpHash_HashFilter(HashTransformation& hash,
						     char const* hashAlgorithmName,
						     string const& strDataPart1,
						     string const& strDataPart2,
						     string const& strDataPart3)
	{
		// Here, we are free to use std::string as the destination,
		// because StringSink uses the correct std::string interface to append data
		string strDigest;
		HashFilter hashFilter(hash, new StringSink(strDigest));
		hashFilter.Put((byte const*) strDataPart1.data(), strDataPart1.size());
		hashFilter.Put((byte const*) strDataPart2.data(), strDataPart2.size());
		hashFilter.Put((byte const*) strDataPart3.data(), strDataPart3.size());
		hashFilter.MessageEnd();

		cout << hashAlgorithmName << " HashFilter:  ";
		StringSource(strDigest, true,
		  new HexEncoder(
			  new FileSink(cout)));
		cout << endl;
	 }

	/**
	* Test function, call the above functions.
	*/
	void DumpHash( HashTransformation& hash,
				   char const* hashAlgorithmName,
				   string const& strDataPart1,
		           string const& strDataPart2,
				   string const& strDataPart3)
	{
		DumpHash_SingleStep(hash, hashAlgorithmName, strDataPart1 + strDataPart2 + strDataPart3);
		DumpHash_MultiStep(hash, hashAlgorithmName, strDataPart1, strDataPart2, strDataPart3);
		DumpHash_HashFilter(hash, hashAlgorithmName, strDataPart1, strDataPart2, strDataPart3);
	}
}