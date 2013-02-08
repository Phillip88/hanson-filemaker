
#include "Utils.h"

namespace utils
{
	/**
	* Insert hyphen into string
	* ex : ASAFS12SDA23GFQ --> ASAFS-12SDA-23GFQ
	*/
	void formatStringWithHiphen(std::string &inp)
	{
		unsigned int i;
		for(i=5; i<inp.length(); i+=6)
		{
			inp.insert(i, "-");
		}
	}

	/**
	* Open folder browser.
	* Return the selected folder.
	*/
	bool GetFolder(std::string& folderpath, const char* szCaption = NULL, HWND hOwner = NULL)
	{
		// folderpath - A reference to the string that will contain the folder path if successful.
		// szCaption - An optional message for the dialog.
		// hOwner - An optional handle to the parent window.
		bool retVal = false;

		// The BROWSEINFO struct tells the shell 
		// how it should display the dialog.
		BROWSEINFO bi;
		memset(&bi, 0, sizeof(bi));

		bi.ulFlags   = BIF_USENEWUI;
		bi.hwndOwner = hOwner;
		bi.lpszTitle = szCaption;

		// must call this if using BIF_USENEWUI
		::OleInitialize(NULL);

		// Show the dialog and get the itemIDList for the selected folder.
		LPITEMIDLIST pIDL = ::SHBrowseForFolder(&bi);

		if(pIDL != NULL)
		{
			// Create a buffer to store the path, then get the path.
			char buffer[_MAX_PATH] = {'\0'};
			if(::SHGetPathFromIDList(pIDL, buffer) != 0)
			{
				// Set the string value.
				folderpath = buffer;
				retVal = true;
			}		

			// free the item id list
			CoTaskMemFree(pIDL);
		}

		::OleUninitialize();

		return retVal;
	}

	bool GetConnectionViaODBC(tiodbc::connection &conn, std::string dsn_name, std::string usr, std::string pwd)
	{
		// Create a connection with an ODBC Data Source
		if (!conn.connect(dsn_name, usr, pwd))
		{
			return false;
		}
		return true;
	}

	/*
	* Get the current local time with format : MM/DD/YYYY
	*/
	std::string GetCurrentLocalDate()
	{
		time_t     now = time(0);
		struct tm  tstruct;
		char       buf[80];
		tstruct = *localtime(&now);
		strftime(buf, sizeof(buf), "%m/%d/%Y", &tstruct);

		return buf;
	}

	// Make a tm structure representing this date
	std::tm make_tm(int year, int month, int day)
	{
		std::tm tm = {0};
		tm.tm_year = year - 1900; // years count from 1900
		tm.tm_mon = month - 1;    // months count from January=0
		tm.tm_mday = day;         // days count from 1
		return tm;
	}

	
	const int seconds_per_day = 60*60*24;
	int DayInDifference(std::tm tm1, std::tm tm2)
	{
		// Arithmetic time values.
		// On a posix system, these are seconds since 1970-01-01 00:00:00 UTC
		std::time_t time1 = std::mktime(&tm1);
		std::time_t time2 = std::mktime(&tm2);

		// Divide by the number of seconds in a day
		// To be fully portable, we shouldn't assume that these are Unix/Windows time;
		// instead, we should use "difftime" to give the difference in seconds
		return (int)std::difftime(time1, time2) / seconds_per_day;
	}
}