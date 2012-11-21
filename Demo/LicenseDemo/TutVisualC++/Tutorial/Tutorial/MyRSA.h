#ifndef __UTILS_H__
#define __UTILS_H__

#include <Windows.h>
#include <vector>

using namespace std;

namespace rsa
{
	void RsaGenerateStringKeys(string & publicKeyStr, string & privateKeyStr);
}

namespace utils
{
	class CHandleGuard
    {
        HANDLE h_;
        CHandleGuard(CHandleGuard&);
        CHandleGuard& operator=(CHandleGuard&);
		public:
			explicit CHandleGuard(HANDLE h=0)
				:h_(h){}
			~CHandleGuard(void)
			{
				if(h_)CloseHandle(h_);
			}
			HANDLE get() const {return h_;}
			HANDLE release()
			{
				HANDLE tmp = h_;
				h_ = 0;
				return tmp;
			}
			void reset(HANDLE h)
			{
				if(h_)CloseHandle(h_);
				h_ = h;
			}
    };

	void SaveVectorToFile(const std::wstring& fileName, const std::vector<char>& data);
}

#endif