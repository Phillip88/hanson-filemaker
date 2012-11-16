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
#include "Create.h"
#include <shared.h>

STDMETHODIMP CCreate::Create(LONG lID1, LONG lID2, LONG lID3, BSTR * pbstrKey)
//--------------------------------------------------------------------------------------------------
// This COM method generates a license key given the manufacturer and product IDs and a bit-flag
// set of licensed capabilities.  These are specified in lID1, lID2, and lID3 respectively.  A BSTR
// is returned as the result.
//--------------------------------------------------------------------------------------------------
{
	CHAR achKey[MAX_KEYLEN + 1];
	HRESULT hrReturn;

	//----------------------------------------------------------------------------------------------
	// Initialize the key.
	//----------------------------------------------------------------------------------------------
	memset(achKey, PAD_KEY, MAX_KEYLEN);
	achKey[MAX_KEYLEN] = 0;

	//----------------------------------------------------------------------------------------------
	// Put the current date / time components in the key so that the result has some degree of 
	// randomness to it.  Remember:  the contents at the beginning of the string to be encrypted
	// affect the encrypted result from that point on.
	//----------------------------------------------------------------------------------------------
	SetKeyDateTime(achKey);

	//----------------------------------------------------------------------------------------------
	// Add the manufacturer and product IDs and the licensed capabilities.
	//----------------------------------------------------------------------------------------------
	LongToKey(lID1, achKey, OFF_MANUFACTURER);
	LongToKey(lID2, achKey, OFF_PRODUCT);
	LongToKey(lID3, achKey, OFF_CAPS);

	//----------------------------------------------------------------------------------------------
	// Convert the key to uppercase before processing just in case there are some lowercase
	// hexadecimal digits.  The base 32 digit set uses uppercase characters only.
	//----------------------------------------------------------------------------------------------
	_strupr_s(achKey, sizeof(achKey));

	//----------------------------------------------------------------------------------------------
	// Encrypt, copy the result into a BSTR, then return.
	//----------------------------------------------------------------------------------------------
	if (!In(achKey, lID1, lID2))
		hrReturn = OLE_E_CANTCONVERT;

	else
	{
		CComBSTR objReturn(achKey);

		*pbstrKey = objReturn.Copy();
		hrReturn = S_OK;
	}

	return hrReturn;
}
