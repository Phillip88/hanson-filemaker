#include "stdafx.h"   

#include "csoftwarekey.h"

// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
int main(int argc, char* argv[])
{
	RETVALUE lResult = SUCCESS;

	// Get the software key from the ini file
	char*	lSoftwareKeyStringFromIniFile=NULL;
	char*	lFilePath="..\\softwarekey_demo\\protected_comp.ini";
	
	lResult = CSoftwareKey::GetSoftwareKeyStringFromIniFile(
				lFilePath, 
				&lSoftwareKeyStringFromIniFile);

	// Verify the software key retrieved from the INI file
	bool lIsValid = false;
	lResult = CSoftwareKey::VerifySoftwareKey(
								lSoftwareKeyStringFromIniFile, 
								&lIsValid);

	if (!lIsValid)
	{
		MessageBox(NULL,"wrong software key","error",MB_OK);
		return 1;
	}

	// do work
	MessageBox(NULL,"correct software key installed","ok",MB_OK);

	return 0;
}


