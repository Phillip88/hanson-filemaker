#include <sstream>
#include <iostream>
#include <tchar.h>
#include "shlobj.h"
#include <string>
#include <conio.h>
#include "./tiodbc.hpp"
#include <ctime>
namespace utils
{
	bool GetFolder(std::string& folderpath, const char* szCaption, HWND hOwner);
	void formatStringWithHiphen(std::string &inp);
	bool GetConnectionViaODBC(tiodbc::connection &conn, std::string dsn_name, std::string usr, std::string pwd);
	std::string GetCurrentLocalDate();
	// Make a tm structure representing this date
	std::tm make_tm(int year, int month, int day);
	int DayInDifference(std::tm tm1, std::tm tm2);
}