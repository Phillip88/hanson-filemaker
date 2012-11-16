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
#ifndef GLOBAL_INCLUDED
#define GLOBAL_INCLUDED

#define NBBF_ERROR_BASE 0xC0080000
#define NBBF_CANT_RETRIEVE (NBBF_ERROR_BASE + 1)

//--------------------------------------------------------------------------------------------------
// BASE32_CHARSET is used to generate the encrypted string.  Note that the entire hexadecimal set
// is in here.  This is important because the numbers that are used to build the non-encrypted
// string are all converted to hexadecimal before being passed to the encryption routine.
//--------------------------------------------------------------------------------------------------
#define BASE32_CHARSET (LPSTR)"AB0CD1EF2HI3KL4MN5PQ6RS7TV8WX9YZ"

//--------------------------------------------------------------------------------------------------
// MAX_PARTLEN is the number of (encoded) characters that each part occupies in the resulting
// string.
//
// MAX_KEYLEN is the maximum length of the resulting string.
//
// Note that the relationship is a little less than obvious.  See the PARTOFFSET formula below.
//--------------------------------------------------------------------------------------------------
#define MAX_PARTLEN 4
#define MAX_KEYLEN 25

#define BASE_HEX 16

#define LWORD(lValue) (int)(lValue & 0xFFFF)
#define UWORD(lValue) (int)((lValue & 0xFFFF0000) >> 16)

#define PAD_KEY (char)'0'
#define PAD_PART "00000000"

//--------------------------------------------------------------------------------------------------
// These are the actual components of the non-encrypted string.  These are concatenated together to
// form the entire string, which is then passed to the encryption routine to actually generate the
// license key.
// 
// PARTOFFSET is a macro that allows us to easily determine where each part goes or may be found
// for decryption.
//
// OFF_TIME is the offset of the time component.  Note that this needs to be first so that the
// seconds component adds a fair amount of randomness to the encrypted string due to the nature
// of the algorithm used (n-bit block feedback).
//
// OFF_DATE is the offset of the date component.  This allows us to determine when the key was
// generated, but could be used to substitute the date the key was used to install the software.
// This lends itself to a "30 day evaluation" type of license.
//
// OFF_MANUFACTURER and OFF_PRODUCT are the manufacturer and product IDs
//
// OFF_CAPS is a 16-bit (based on MAX_PARTLEN specifying the number of hexadecimal digits in the
// number) set of flags that the caller can use to specify components that are accessible using
// the license key.
//--------------------------------------------------------------------------------------------------
#define PARTOFFSET(part) (MAX_PARTLEN * part + part)
#define OFF_TIME PARTOFFSET(0)
#define OFF_DATE PARTOFFSET(1)
#define OFF_MANUFACTURER PARTOFFSET(2)
#define OFF_PRODUCT PARTOFFSET(3)
#define OFF_CAPS PARTOFFSET(4)

//--------------------------------------------------------------------------------------------------
// TIMETOPART converts an hour / minute / second tuplet into a single number that may be converted
// to hexadecimal for addition into the unencrypted string.  Note that, due to the number of bits
// available in a MAX_PARTLEN component, the hour is ignored.  This is strictly used for adding
// randomization to the encrypted string so the loss of precision is acceptable.
//
// Seconds are stored in 7 bits (0-63).  Minutes are stored in 7 bits (0-63).  This yields a number
// with 14 bits of precision.
//
// DATETOPART converts a month / day / year (1900 offset) into a single number that may be converted
// to hexadecimal for addition into the unencrypted string.
//
// Year is stored as an offset from the year 2000 and uses 7 bits (0-63).  Day of the year is stored
// in 9 bits (0-512).  This yields a number with 16 bits of precision.
//--------------------------------------------------------------------------------------------------
#define TIMETOPART(h, m, s) (((s & 0x7F) << 7) | (m & 0x7F))
#define DATETOPART(yd, y) ((((y - 100) & 0x7F) << 9) | yd)

#define PARTTOYEAR(l) ((l >> 9) + 100)
#define PARTTOYEARDAY(l) (l & 0x1FF)

void _stdcall OverlayFromIDs(LONG lManuID, LONG lProdID, LPSTR lpstrPad);
void _stdcall SetKeyDateTime(LPSTR lpstrKey);
void _stdcall LongToKey(LONG lNumber, LPSTR lpstrKey, INT iOffset);
bool _stdcall In(LPSTR pchKey, LPSTR pchOverlay);
bool _stdcall In(LPSTR pchKey, LONG lManuID, LONG lProdID);
bool _stdcall Out(LPSTR pchKey, LPSTR pchOverlay);
bool _stdcall Out(LPSTR pchKey, LONG lManuID, LONG lProdID);
bool _stdcall CheckKeyValues(LPSTR pchKey, LONG lManuID, LONG lProdID, LONG lCaps);
bool _stdcall InstallKey(LPSTR lpstrKey, LONG lManuID, LONG lProdID);
bool _stdcall RetrieveKey(LPSTR lpstrKey, LONG szKey, LONG lManuID, LONG lProdID);

#endif // #ifndef GLOBAL_INCLUDED