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
#include <windows.h>
#include <stdio.h>
#include "shared.h"

#define REGK_SOFTWARE_NBBF		"SOFTWARE\\Nbbf"

#define FMT_REGKEY				"%08lX%08lX"

bool _stdcall InstallKey(LPSTR lpstrKey, LONG lManuID, LONG lProdID)
//--------------------------------------------------------------------------------------------------
// This function installs the specified key.  While we could extract the manufacturer and product
// IDs from the key itself, this method is only called from a routine that already has them
// separated.  Therefore, we'll require the caller to specify them as arguments to save some time.
//--------------------------------------------------------------------------------------------------
{
	CHAR achRegKey[MAX_KEYLEN+1];
	CHAR achRegValue[MAX_KEYLEN+1];
	CHAR achOverlay[MAX_KEYLEN+1];
	bool blnReturn;
	HKEY hkRoot;
	DWORD dwDisp;

	achRegValue[0] = 0;
	strncat_s(achRegValue, sizeof(achRegValue), lpstrKey, sizeof(achRegValue));

	//----------------------------------------------------------------------------------------------
	// We need to store the product key as a value other than the product key to at least make it 
	// more difficult to deduce, i.e. a simple registry search for the product key won't yield the 
	// answer.  Therefore, we will produce a string of the hexadecimal digits of the product and 
	// manufacturer IDs and encrypt the key yielding the subkey in the registry under which we will 
	// store the encrypted product key.
	//----------------------------------------------------------------------------------------------
	sprintf_s(achRegKey, sizeof(achRegKey), FMT_REGKEY, lProdID, lManuID);

	//----------------------------------------------------------------------------------------------
	// Create the encryption overlay and reset the date / time in the key to the current date / time.
	// This latter operation is required since the generation of the key has no idea when the product
	// will actually be installed.  Therefore, the Elapsed method of the validation object will not
	// be able to return an accurate number unless we do this.
	//----------------------------------------------------------------------------------------------
	OverlayFromIDs(lManuID, lProdID, achOverlay);
	SetKeyDateTime(achRegValue);

	blnReturn = false;
	hkRoot = NULL;

	try
	{
		//------------------------------------------------------------------------------------------
		// Generate the registry key name and value to be stored therein.
		//
		// Using exceptions for error handling is a bad practice generally but since this will
		// never be used in a high-performance application we shouldn't be terribly concerned.
		//------------------------------------------------------------------------------------------
		if (!In(achRegKey, achOverlay))
			throw 1;

		if (!In(achRegValue, achOverlay))
			throw 2;

		//------------------------------------------------------------------------------------------
		// Update the registry.
		//------------------------------------------------------------------------------------------
		if (RegCreateKeyExA(HKEY_LOCAL_MACHINE,
							REGK_SOFTWARE_NBBF, 
							0,
							NULL,
							REG_OPTION_NON_VOLATILE,
							KEY_WRITE,
							NULL,
							&hkRoot,
							&dwDisp) != ERROR_SUCCESS)
			throw 3;

		if (RegSetValueExA(hkRoot, 
						   achRegKey,
						   0,
						   REG_SZ, 
						   (LPBYTE)achRegValue, 
						   strlen(achRegValue) + 1) != ERROR_SUCCESS)
			throw 4;

		blnReturn = true;
	}
	catch (int iCode)
	{
	}

	//----------------------------------------------------------------------------------------------
	// Cleanup.
	//----------------------------------------------------------------------------------------------
	if (hkRoot != NULL)
		RegCloseKey(hkRoot);

	return blnReturn;
}

bool _stdcall RetrieveKey(LPSTR lpstrKey, LONG szKey, LONG lManuID, LONG lProdID)
//--------------------------------------------------------------------------------------------------
// This function retrieves the license key from the registry.  Unlike InstallKey where we could have
// extracted the manufacturer and product IDs from the license key, we do not (yet) know what the
// license key is so this is impossible to do.
//--------------------------------------------------------------------------------------------------
{
	CHAR achRegKey[MAX_KEYLEN+1];
	CHAR achRegValue[MAX_KEYLEN+1];
	CHAR achOverlay[MAX_KEYLEN+1];
	bool blnReturn;
	DWORD dwSzValue;
	HKEY hkRoot;
	DWORD dwDisp;
	DWORD dwType;

	//----------------------------------------------------------------------------------------------
	// See comments in InstallKey about the need to obfuscate the registry key name and the product
	// key value.
	//----------------------------------------------------------------------------------------------
	sprintf_s(achRegKey, sizeof(achRegKey), FMT_REGKEY, lProdID, lManuID);

	OverlayFromIDs(lManuID, lProdID, achOverlay);

	blnReturn = false;
	lpstrKey[0] = 0;
	dwType = REG_SZ;
	dwSzValue = sizeof(achRegValue);
	hkRoot = NULL;

	try
	{
		//------------------------------------------------------------------------------------------
		// Generate the registry key name.
		//
		// Using exceptions for error handling is a bad practice generally but since this will
		// never be used in a high-performance application we shouldn't be terribly concerned.
		//------------------------------------------------------------------------------------------
		if (!In(achRegKey, achOverlay))
			throw 1;

		//------------------------------------------------------------------------------------------
		// Query the registry.
		//------------------------------------------------------------------------------------------
		if (RegCreateKeyExA(HKEY_LOCAL_MACHINE,
							REGK_SOFTWARE_NBBF, 
							0,
							NULL,
							REG_OPTION_NON_VOLATILE,
							KEY_READ,
							NULL,
							&hkRoot,
							&dwDisp) != ERROR_SUCCESS)
			throw 2;

		if (RegQueryValueExA(hkRoot,
							 achRegKey,
							 0,
							 &dwType,
							 (LPBYTE)achRegValue,
							 &dwSzValue) != ERROR_SUCCESS)
			throw 3;

		if (!Out(achRegValue, achOverlay))
			throw 4;

		strncat_s(lpstrKey, szKey, achRegValue, sizeof(achRegValue));
		blnReturn = true;
	}
	catch (int iCode)
	{
	}

	//----------------------------------------------------------------------------------------------
	// Cleanup.
	//----------------------------------------------------------------------------------------------
	if (hkRoot != NULL)
		RegCloseKey(hkRoot);

	return blnReturn;
}