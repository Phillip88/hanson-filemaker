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
#include <stdlib.h>
#include "shared.h"
#include <time.h>

bool _stdcall CheckKeyValues(LPSTR pchKey, LONG lManuID, LONG lProdID, LONG lCaps)
//--------------------------------------------------------------------------------------------------
// This function extracts the manufacturer and product IDs and the licensed capabilities from the
// specified key and compares them to the specified values.  Note that licensed capabilities can
// be a superset of the lCaps argument, so we need to perform a binary AND operation to ensure that
// all of the bits are set rather than a logical comparison for equality.
//--------------------------------------------------------------------------------------------------
{
	CHAR achPart[MAX_PARTLEN + 1];
	LONG lCompManuID;
	LONG lCompProdID;
	LONG lCompCaps;
	LPSTR lpstrEnd;

	memset(achPart, 0, sizeof(achPart));
	strncpy_s(achPart, sizeof(achPart), &pchKey[OFF_MANUFACTURER], MAX_PARTLEN);
	lCompManuID = strtol(achPart, &lpstrEnd, BASE_HEX);

	memset(achPart, 0, sizeof(achPart));
	strncpy_s(achPart, sizeof(achPart), &pchKey[OFF_PRODUCT], MAX_PARTLEN);
	lCompProdID = strtol(achPart, &lpstrEnd, BASE_HEX);

	memset(achPart, 0, sizeof(achPart));
	strncpy_s(achPart, sizeof(achPart), &pchKey[OFF_CAPS], MAX_PARTLEN);
	lCompCaps = strtol(achPart, &lpstrEnd, BASE_HEX);

	return ((lManuID == lCompManuID) && (lProdID == lCompProdID) && ((lCaps & lCompCaps) == lCaps));
}

bool _stdcall Out(LPSTR pchKey, LPSTR pchOverlay)
//--------------------------------------------------------------------------------------------------
// This function decrypts the specified key using the specified overlay.  It uses a cipher block
// chaining algorithm (sometimes known as n-bit block feedback encryption) which essentially uses
// the previous decryption result as input to the current decryption iteration.
//--------------------------------------------------------------------------------------------------
{
	int iLenKey;
	int iLenOver;
	LPSTR pbBuf;
	int iIndex;
	LPSTR pchVal;
	char bVal1;
	char bVal2;
	char bVal3;
	bool blnReturn;

	iLenKey = strlen(pchKey);
	iLenOver = strlen(pchOverlay);

	//----------------------------------------------------------------------------------------------
	// The resulting data is the same size as the input, so build the results in a separate buffer.
	//----------------------------------------------------------------------------------------------
	pbBuf = (LPSTR)calloc(iLenKey, sizeof(char));

	for (iIndex = iLenKey - 1; iIndex >= 0; iIndex--)
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
		// data.  Unlike the encryption routine where this value was already calculated, we have
		// to manually calculate it here before XOR'ing it.
		//------------------------------------------------------------------------------------------
		pbBuf[iIndex] = bVal1 ^ bVal2;

		if (iIndex > 0)
		{
			pchVal = strchr(BASE32_CHARSET, pchKey[iIndex - 1]);

			if (!pchVal)
				break;

			bVal3 = (char)(pchVal - BASE32_CHARSET);

			pbBuf[iIndex] ^= bVal3;
		}

		//------------------------------------------------------------------------------------------
		// Convert back from a numerical value to the appropriate digit.
		//------------------------------------------------------------------------------------------
		pchKey[iIndex] = (char)BASE32_CHARSET[pbBuf[iIndex]];
	}

	//----------------------------------------------------------------------------------------------
	// Cleanup.
	//----------------------------------------------------------------------------------------------
	free(pbBuf);

	blnReturn = (iIndex < 0);

	if (!blnReturn)
		memset(pchKey, 0, iLenKey);

	return blnReturn;
}

bool _stdcall Out(LPSTR pchKey, LONG lManuID, LONG lProdID)
//--------------------------------------------------------------------------------------------------
// This overloaded function converts the specified manufacturer and product IDs into the decryption
// overlay then calls the other version of the Out function to decrypt the data.
//--------------------------------------------------------------------------------------------------
{
	CHAR achOverlay[MAX_KEYLEN + 1];

	OverlayFromIDs(lManuID, lProdID, achOverlay);

	return Out(pchKey, achOverlay);
}
