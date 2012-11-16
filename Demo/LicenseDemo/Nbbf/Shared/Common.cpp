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
#include <time.h>
#include "shared.h"

#define FMT_LONGTOHEX			"%04lX"
#define FMT_OVERLAY				"%04lX%04lX%04lX"
#define OVERLAY_RANDOMNESS		0x5555
#define OVERLAY_OFFSET			3

void _stdcall OverlayFromIDs(LONG lManuID, LONG lProdID, LPSTR lpstrPad)
//--------------------------------------------------------------------------------------------------
// This function creates the overlay used for the encryption.  It is the hexadecimal digits of the 
// Product and Manufacturer IDs with a numerical offset applied to both.  This is prefixed by the 
// binary XOR of the two in order to add some predictable randomness to it.
//--------------------------------------------------------------------------------------------------
{
	CHAR achPad[MAX_KEYLEN + 1];

	sprintf_s(achPad, 
			  sizeof(achPad), 
			  FMT_OVERLAY, 
			  lProdID ^ lManuID ^ OVERLAY_RANDOMNESS, 
			  lProdID + OVERLAY_OFFSET, 
			  lManuID + OVERLAY_OFFSET);

	strcpy_s(lpstrPad, sizeof(achPad), achPad);
}

void _stdcall SetKeyDateTime(LPSTR lpstrKey)
//--------------------------------------------------------------------------------------------------
// This function adds some components of the current time to the front of the key so that the
// rest of the key is randomized to some degree.  The date is also added as the year - 2000 plus
// the day of the year.  This will easily allow us to calculate the number of days elapsed since
// the product was installed.
//--------------------------------------------------------------------------------------------------
{
	time_t tNow;
	struct tm tGmt;

	time(&tNow);
	gmtime_s(&tGmt, &tNow);

	LongToKey(LWORD(TIMETOPART(tGmt.tm_hour, tGmt.tm_min, tGmt.tm_sec)), lpstrKey, OFF_TIME);
	LongToKey(LWORD(DATETOPART(tGmt.tm_yday, tGmt.tm_year)), lpstrKey, OFF_DATE);
}

void _stdcall LongToKey(LONG lNumber, LPSTR lpstrKey, INT iOffset)
//--------------------------------------------------------------------------------------------------
// This function converts the specified number to text and stores it in the specified part location
// within the key buffer.
//--------------------------------------------------------------------------------------------------
{
	CHAR achPart[MAX_KEYLEN + 1];

	sprintf_s(achPart, sizeof(achPart), FMT_LONGTOHEX, lNumber);
	memcpy_s(&lpstrKey[iOffset], MAX_PARTLEN, achPart, MAX_PARTLEN);
}