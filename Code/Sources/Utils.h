#include <sstream>
#include <iostream>
#include <tchar.h>
#include "shlobj.h"
#include <string>
#include <conio.h>
namespace utils
{
	bool GetFolder(std::string& folderpath, const char* szCaption, HWND hOwner);
	void formatStringWithHiphen(std::string &inp);
}