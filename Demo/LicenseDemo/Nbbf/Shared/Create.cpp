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
#include <stdlib.h>
#include "shared.h"
#include <time.h>

bool _stdcall In(LPSTR pchKey, LPSTR pchOverlay)
//--------------------------------------------------------------------------------------------------
// This function encrypts the specified key using the specified overlay.  It uses a cipher block
// chaining algorithm (sometimes known as n-bit block feedback encryption) which essentially uses
// the previous encryption result as input to the current encryption iteration.  The upshot of this
// is that data at the beginning of the string affects the encrypted results after it.
//--------------------------------------------------------------------------------------------------
{
	int iLenKey;
	int iLenOver;
	LPSTR pbBuf;
	int iIndex;
	LPSTR pchVal;
	char bVal1;
	char bVal2;
	bool blnReturn;

	iLenKey = strlen(pchKey);
	iLenOver = strlen(pchOverlay);

	//----------------------------------------------------------------------------------------------
	// The resulting data is the same size as the input, so build the results in a separate buffer.
	//----------------------------------------------------------------------------------------------
	pbBuf = (LPSTR)calloc(iLenKey, sizeof(char));

	for (iIndex = 0; iIndex < iLenKey; iIndex++)
	{
		//------------------------------------------------------------------------------------------
		// Find the position of the current input byte in the digit set.  If not found then exit.
		//------------------------------------------------------------------------------------------
		pchVal = strchr(BASE32_CHARSET, pchKey[iIndex]);

		if (!pchVal)
			break;

		//------------------------------------------------------------------------------------------
		// Convert to a numerical value.
		//------------------------------------------------------------------------------------------
		bVal1 = (char)(pchVal - BASE32_CHARSET);

		//------------------------------------------------------------------------------------------
		// Repeat the above conversion for the current overlay byte.
		//------------------------------------------------------------------------------------------
		pchVal = strchr(BASE32_CHARSET, pchOverlay[iIndex % iLenOver]);

		if (!pchVal)
			break;

		bVal2 = (char)(pchVal - BASE32_CHARSET);

		//------------------------------------------------------------------------------------------
		// XOR the two values plus the n-1'th encrypted byte if this is not the first byte of
		// data.
		//------------------------------------------------------------------------------------------
		pbBuf[iIndex] = bVal1 ^ bVal2;

		if (iIndex > 0)
			pbBuf[iIndex] ^= pbBuf[iIndex - 1];

		//------------------------------------------------------------------------------------------
		// Convert back from a numerical value to the appropriate digit.
		//------------------------------------------------------------------------------------------
		pchKey[iIndex] = (char)BASE32_CHARSET[pbBuf[iIndex]];
	}

	//----------------------------------------------------------------------------------------------
	// Cleanup.
	//----------------------------------------------------------------------------------------------
	free(pbBuf);

	blnReturn = (iIndex == iLenKey);

	if (!blnReturn)
		memset(pchKey, 0, iLenKey);

	return blnReturn;
}

bool _stdcall In(LPSTR pchKey, LONG lManuID, LONG lProdID)
//--------------------------------------------------------------------------------------------------
// This overloaded function converts the specified manufacturer and product IDs into the encryption
// overlay then calls the other version of the In function to encrypt the data.
//--------------------------------------------------------------------------------------------------
{
	CHAR achOverlay[MAX_KEYLEN + 1];

	OverlayFromIDs(lManuID, lProdID, achOverlay);

	return In(pchKey, achOverlay);
}
