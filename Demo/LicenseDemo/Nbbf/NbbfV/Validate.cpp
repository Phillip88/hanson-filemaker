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
#include "stdafx.h"
#include "Validate.h"
#include <shared.h>
#include <time.h>

#define CONV_YEARSPERLEAP		4
#define CONV_DAYSPERLEAPYEAR	366
#define CONV_DAYSPERYEAR		365

STDMETHODIMP CValidate::Validate(LONG lID1, LONG lID2, LONG lID3, VARIANT_BOOL* pbValid)
//--------------------------------------------------------------------------------------------------
// This method validates that there is an installed license key matching the manufacturer and
// product IDs.  It also checks that the requested capabilities were licensed.
//--------------------------------------------------------------------------------------------------
{
	CHAR achKey[MAX_KEYLEN + 1];
	HRESULT hrReturn;

	*pbValid = VARIANT_FALSE;
	hrReturn = NBBF_CANT_RETRIEVE;

	if (RetrieveKey(achKey, sizeof(achKey), lID1, lID2))
	{
		hrReturn = S_OK;

		if (CheckKeyValues(achKey, lID1, lID2, lID3))
			*pbValid = VARIANT_TRUE;
	}

	return hrReturn;
}

STDMETHODIMP CValidate::Elapsed(LONG lID1, LONG lID2, LONG* plElapsed)
//--------------------------------------------------------------------------------------------------
// This method returns the number of days that have elapsed since the license for the specified
// manufacturer and product IDs was installed.
//--------------------------------------------------------------------------------------------------
{
	CHAR achKey[MAX_KEYLEN + 1];
	HRESULT hrReturn;
	CHAR achPart[MAX_PARTLEN + 1];
	LONG lDate;
	LPSTR lpstrEnd;
	LONG lYear;
	LONG lDayOfYear;
	time_t tNow;
	struct tm tGmNow;

	if (!RetrieveKey(achKey, sizeof(achKey), lID1, lID2))
		hrReturn = NBBF_CANT_RETRIEVE;

	else
	{
		hrReturn = S_OK;

		//---------------------------------------------------------------------------------------------
		// Get the date from the installation data
		//---------------------------------------------------------------------------------------------
		memset(achPart, 0, sizeof(achPart));
		strncpy_s(achPart, sizeof(achPart), &achKey[OFF_DATE], MAX_PARTLEN);
		lDate = strtol(achPart, &lpstrEnd, BASE_HEX);
		lYear = PARTTOYEAR(lDate);
		lDayOfYear = PARTTOYEARDAY(lDate);

		//---------------------------------------------------------------------------------------------
		// Get the current UTC date
		//---------------------------------------------------------------------------------------------
		time(&tNow);
		gmtime_s(&tGmNow, &tNow);

		//---------------------------------------------------------------------------------------------
		// Calculate the number of days elapsed from the installation date until now
		//---------------------------------------------------------------------------------------------
		if (lYear == tGmNow.tm_year)
			lDayOfYear = tGmNow.tm_yday - lDayOfYear;

		else
		{
			//-----------------------------------------------------------------------------------------
			// If we're here, it's because the years are different.  Therefore, calculate the number
			// of days from the installation date until the end of the year, and then add the full
			// year's worth of days until we've accounted for all of the years.  Finally, add the
			// partial year's worth of days.
			//-----------------------------------------------------------------------------------------
			if ((lYear % CONV_YEARSPERLEAP) == 0)
				lDayOfYear = CONV_DAYSPERLEAPYEAR - lDayOfYear + 1;

			else
				lDayOfYear = CONV_DAYSPERYEAR - lDayOfYear + 1;

			while (lYear < tGmNow.tm_year)
			{
				lDayOfYear += ((lYear % CONV_YEARSPERLEAP) == 0) ? CONV_DAYSPERLEAPYEAR : CONV_DAYSPERYEAR;
				lYear++;
			}

			lDayOfYear += tGmNow.tm_yday;
		}

		*plElapsed = lDayOfYear;
	}

	return hrReturn;
}
