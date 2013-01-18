
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
}