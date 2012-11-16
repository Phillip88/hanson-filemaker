#include "csoftwarekey.h"   

// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
RETVALUE CSoftwareKey::ComputeSoftwareKey(
							const BYTE pMachineCode[MACHINE_CODE_DIM], 
							BYTE pSoftwareKey[SOFTWAREKEY_DIM])
{
	RETVALUE		lReturnValue = SUCCESS;

	pSoftwareKey[0] = pMachineCode[1];
	pSoftwareKey[1] = pMachineCode[4];
	pSoftwareKey[2] = pMachineCode[3];
	pSoftwareKey[3] = pMachineCode[2];
	pSoftwareKey[4] = pMachineCode[5];
	pSoftwareKey[5] = pMachineCode[0];

	return lReturnValue;
}

// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
RETVALUE CSoftwareKey::VerifySoftwareKey(
							const char* pSoftwareKeyString, 
							bool* pIsValid)
{
	RETVALUE		lReturnValue = SUCCESS;

	bool			lIsValid = true;

	BYTE lMACaddress[MAC_DIM];
	lReturnValue = RetrieveMACAddress(lMACaddress);

	BYTE lMachineCode[MACHINE_CODE_DIM];
	lReturnValue = ComputeMachineCode(lMACaddress, lMachineCode);

	BYTE lSoftwareKey[SOFTWAREKEY_DIM];
	lReturnValue = ComputeSoftwareKey(lMachineCode, lSoftwareKey); 

	char* lSoftwareKeyString = NULL;
	lReturnValue = Buffer2String(
						lSoftwareKey, 
						SOFTWAREKEY_DIM, 
						&lSoftwareKeyString);


	unsigned int lSoftwareKeyStringLen = strlen(lSoftwareKeyString);
	unsigned int lpSoftwareKeyStringLen = strlen(pSoftwareKeyString);

	if (lSoftwareKeyStringLen != lpSoftwareKeyStringLen)
	{
		lIsValid = false;
		*pIsValid = lIsValid;
		return lReturnValue;
	}

	for (unsigned int i = 0; i<lSoftwareKeyStringLen; i++)
	{
		BYTE lKey1 = lSoftwareKeyString[i];
		BYTE lKey2 = pSoftwareKeyString[i];

		if (lKey1 != lKey2)
		{
			lIsValid = false;
			break;
		}
	}

	*pIsValid = lIsValid;
	return lReturnValue;
}

// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
RETVALUE CSoftwareKey::Buffer2String(
								const BYTE* pBuffer, 
								const unsigned int pBufferSize, 
								char** pString)
{
	RETVALUE		lReturnValue = SUCCESS;

	unsigned int	lOutStringSize = (pBufferSize*3) + 1;
	
	// it is the caller that it is on charge to delete this pointer
	char*			lOutString = new char[lOutStringSize];
	sprintf(lOutString,"%s","");

	char lAppString[4];
	for (unsigned int i = 0; i < pBufferSize; i++)
	{
		BYTE b = pBuffer[i];

		// NOTE: 3 chars in out string for each byte in input buffer
		sprintf(lAppString,"%03u",b); 
		strcat(lOutString,lAppString);
	}
	
	*pString = lOutString;

	return lReturnValue;
}


// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
RETVALUE CSoftwareKey::String2Buffer(
								const char*		pString,
								BYTE**			pBuffer, 
								unsigned int*	pBufferSize)
{
	RETVALUE		lReturnValue = SUCCESS;

	unsigned int	lOutBufferSize = strlen(pString) / 3;

	
	// it is the caller that it is on charge to delete this pointer
	BYTE*	lOutBuffer = new BYTE[lOutBufferSize];
	

	char lAppString[4];

	unsigned int j	= 0;
	unsigned int j1 = 0;
	unsigned int j2 = 0;
	unsigned int j3 = 0;

	for (unsigned int i = 0; i < lOutBufferSize; i++)
	{
		j1 = j++;
		j2 = j++;
		j3 = j++;

		sprintf(
			lAppString,
			"%c%c%c",
			pString[j1],
			pString[j2],
			pString[j3]);

		// NOTE: one byte in output buffer for each 3 chars in input string
		BYTE b = (BYTE) atoi(lAppString);

		lOutBuffer[i] = b;
	}
	
	*pBuffer = lOutBuffer;
	*pBufferSize = lOutBufferSize;

	return lReturnValue;
}


// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
RETVALUE CSoftwareKey::GetSoftwareKeyStringFromIniFile(
											const char* pFilePath, 
											char** pSoftwareKeyString)
{
	RETVALUE		lReturnValue = SUCCESS;

	unsigned int l_SoftwareKeyAsStringLen = SOFTWAREKEY_DIM * 3 + 1;
	char* l_SoftwareKeyAsString = new char[l_SoftwareKeyAsStringLen];

	DWORD l_NumCopied = GetPrivateProfileStringA (
			"protection",					// section name
			"softwarekey",					// key name
            "",								// default string
			l_SoftwareKeyAsString,			// destination buffer
			l_SoftwareKeyAsStringLen,		// size of destination buffer
            pFilePath);						// initialization file name

	if (l_NumCopied == 0)
	{
		lReturnValue = ERROR_SOFTWAREKEY_NOT_FOUND;
		return lReturnValue;
	}

	*pSoftwareKeyString = l_SoftwareKeyAsString;

	return lReturnValue;
}

// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
RETVALUE CSoftwareKey::ComputeMachineCode(
									const BYTE pMACaddress[MAC_DIM], 
									BYTE pMachineCode[6])
{
	RETVALUE		lReturnValue = SUCCESS;

	pMachineCode[0] = pMACaddress[5];
	pMachineCode[1] = pMACaddress[0];
	pMachineCode[2] = pMACaddress[4];
	pMachineCode[3] = pMACaddress[1];
	pMachineCode[4] = pMACaddress[3];
	pMachineCode[5] = pMACaddress[2];
	
	return lReturnValue;
}

// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
RETVALUE CSoftwareKey::RetrieveMACAddress(BYTE pMACaddress[MAC_DIM])
{
	RETVALUE		lReturnValue = SUCCESS;
	GUID			lGUID;
	OSVERSIONINFO	lVersionInfo;
	
	lVersionInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	
	BOOL lResult = GetVersionEx(&lVersionInfo);	

	if (!lResult)
	{
		return ERROR_API_CALL_FAILED;
	}

	// Win 2000, Win XP, Win Me
	if	( 
		( lVersionInfo.dwMajorVersion == 5 ) 
		|| 
		( 
			( lVersionInfo.dwMajorVersion == 4 ) 
			&& 
			( lVersionInfo.dwMinorVersion == 90 ) 
		)
		)
	{
		typedef VOID  (CALLBACK* PROC)(UUID*); 

		HINSTANCE		lLib; 
		PROC			UuidCreateSequential; 
		
		lLib = LoadLibrary("RPCRT4"); 
 
		if (lLib != NULL) 
		{ 
			UuidCreateSequential = (PROC) GetProcAddress(
											lLib, 
											"UuidCreateSequential"); 
 
			if (UuidCreateSequential != NULL) 
			{
				UuidCreateSequential(&lGUID); 
			}
			else
			{
				return ERROR_API_CALL_FAILED;
			}
 
			lResult = FreeLibrary(lLib); 
		}
		else
		{
			return ERROR_FAILURE_WHILE_LOADING_LIBRARY;
		}
	}
	else
	// Win NT (without any service pack)
	// NOTE: The string field  szCSDVersion of the structure OSVERSIONINFO 
	// give us information about the installed service pack. If the string 
	// is empty, then no service pack has been installed. If the string is 
	// something like "Service Pack 3", this means that service pack 3 
	// has been installed.
	if	( lVersionInfo.dwMajorVersion < 5 ) 
	{
		HRESULT h = CoCreateGuid(&lGUID);
	}
	else
	{
		return ERROR_OS_VERSION_NOT_SUPPORTED;
	}

	// Retrieve the MAC address 
	// (Bytes 2 through 7 of Data4 keeps the MAC address).
	for (int i=0;i<MAC_DIM;i++)
	{
		pMACaddress[i]=lGUID.Data4[i+2];
	}

	return lReturnValue;
}


