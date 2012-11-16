/* -------------------------------------------------------------------------------------------------
This file is part of the Nbbf Copy Protection Library (Nbbf)
 
Nbbf is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
 
Nbbf is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU Lesser Public License for more details.
 
You should have received a copy of the GNU Lesser Public License
along with Nbbf.  If not, see <http://www.gnu.org/licenses/>.
------------------------------------------------------------------------------------------------- */
#include <stdafx.h>
#include <msi.h>
#include <msiquery.h>
#include <shared.h>

#define MSIK_PIDKEY TEXT("PIDKEY")
#define MSIK_PIDCHECK TEXT("PIDCHECK")
#define MSIK_MANUFACTURERID TEXT("MANUFACTURERID")
#define MSIK_PRODUCTID TEXT("PRODUCTID")
#define MSIV_TRUE TEXT("TRUE")
#define MSIV_FALSE TEXT("FALSE")

extern "C" __declspec(dllexport) bool __stdcall InstallDirect(LPSTR lpstrKey, LONG lID1, LONG lID2)
//--------------------------------------------------------------------------------------------------
// This function installs the key in the system.  Essentially, it decodes the specifies key;
// compares the stored values for the manufacturer and product IDs against those that were passed;
// and if they match then the key is installed.
//
// The usage is intended to be this way:  the installer specifies values for the manufacturer and
// product IDs.  The user specifies the installation key.  When the installation key is valid then
// all proceeds as expected.
//--------------------------------------------------------------------------------------------------
{
	bool blnReturn;

	blnReturn = false;

	if (Out(lpstrKey, lID1, lID2))
		if (CheckKeyValues(lpstrKey, lID1, lID2, 0))
			if (InstallKey(lpstrKey, lID1, lID2))
				blnReturn = true;

	return blnReturn;
}

extern "C" __declspec(dllexport) UINT __stdcall InstallMSI(MSIHANDLE hInstall)
//--------------------------------------------------------------------------------------------------
// This function installs the key via integration with the Microsoft Installer.
//--------------------------------------------------------------------------------------------------
{
	PTCHAR pstrResult;
	DWORD dwBuffer;
	TCHAR tchKey[MAX_PATH];
	CHAR achKey[MAX_PATH];
	TCHAR tchManuID[MAX_PATH];
	TCHAR tchProdID[MAX_PATH];
	LONG lManuID;
	LONG lProdID;
	LPSTR lpstrEnd;

	pstrResult = MSIV_FALSE;

	dwBuffer = sizeof(tchKey) / sizeof(TCHAR);

	//----------------------------------------------------------------------------------------------
	// Microsoft's installer stores the license key that the user entered in a key/value pair
	// named PIDKEY.
	//----------------------------------------------------------------------------------------------
	if (MsiGetProperty(hInstall, MSIK_PIDKEY, tchKey, &dwBuffer) == ERROR_SUCCESS)
	{
		//------------------------------------------------------------------------------------------
		// Convert the key from wide-character to ASCII (8-bit).
		//------------------------------------------------------------------------------------------
		CW2A convKey(tchKey);

		strcpy_s(achKey, sizeof(achKey), convKey);

		//------------------------------------------------------------------------------------------
		// The Windows Installer includes the literals in the key mask, so we need to remove the '-'
		// characters.
		//------------------------------------------------------------------------------------------
		dwBuffer = strlen(achKey);

		for (int iIndex = 0; iIndex < (int)dwBuffer; iIndex++)
			if (strchr(BASE32_CHARSET, achKey[iIndex]) == 0)
			{
				strcpy_s(&achKey[iIndex], sizeof(achKey) - iIndex, &achKey[iIndex + 1]);
				iIndex--;
				dwBuffer--;
			}

		//------------------------------------------------------------------------------------------
		// Get the manufacturer and product IDs from the .msi file.
		//------------------------------------------------------------------------------------------
		dwBuffer = sizeof(tchManuID) / sizeof(TCHAR);

		if (MsiGetProperty(hInstall, MSIK_MANUFACTURERID, tchManuID, &dwBuffer) == ERROR_SUCCESS)
		{
			dwBuffer = sizeof(tchProdID) / sizeof(TCHAR);

			if (MsiGetProperty(hInstall, MSIK_PRODUCTID, tchProdID, &dwBuffer) == ERROR_SUCCESS)
			{
				//----------------------------------------------------------------------------------
				// the .msi file contains wide-character versions of the values, so convert them
				// to ASCII so that we can then convert them to numbers.
				//----------------------------------------------------------------------------------
				CW2A convManuID(tchManuID);
				CW2A convProdID(tchProdID);

				lManuID = strtol(convManuID, &lpstrEnd, BASE_HEX);
				lProdID = strtol(convProdID, &lpstrEnd, BASE_HEX);

				//----------------------------------------------------------------------------------
				// Code reuse for the win!
				//----------------------------------------------------------------------------------
				if (InstallDirect(achKey, lManuID, lProdID))
					pstrResult = MSIV_TRUE;
			}
		}
	}

	//----------------------------------------------------------------------------------------------
	// Unfortunately, if we return MSIV_FALSE the installer provides no real feedback to the user
	// so we have to display - ick! - a message box on our own.  It is, in my opinion, rather
	// shortsighted of Microsoft to provide no way of displaying a message with the same look
	// and feel of the installer.
	//----------------------------------------------------------------------------------------------
	if (_tcscmp(pstrResult, MSIV_FALSE) == 0)
		MessageBox(GetForegroundWindow(), 
				   TEXT("Either an invalid license key was specified or an error occurred."), 
				   TEXT("Error"), 
				   MB_OK | MB_ICONERROR | MB_APPLMODAL);

	MsiSetProperty(hInstall, MSIK_PIDCHECK, pstrResult);
	return 0;
}
