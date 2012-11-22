#include "Utils.h"

namespace utils
{
	/**
	* Insert hyphen into string
	* ex : ASAFS12SDA23GFQ --> ASAFS-12SDA-23GFQ
	*/
	void formatStringWithHiphen(std::string &inp)
	{
		int i;
		for(i=5; i<inp.length(); i+=6)
		{
			inp.insert(i, "-");
		}
	}
}