#include "stdafx.h"  

#include "csoftwarekey.h"

// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
int main(int argc, char* argv[])
{
	RETVALUE lResult = SUCCESS;

	printf("\nSoftware key - Customer Tool - Machine code generator\n\n");

	if (argc != 2)
	{		
		printf("Usage is:\n\n");
		printf("softwarekey_customertool -g\n\n");
	}
	else
	if (strcmp(argv[1],"-g")==0)
	{
		// Retrieve the MAC address
		BYTE lMACaddress[MAC_DIM];
		lResult = CSoftwareKey::RetrieveMACAddress(lMACaddress);

		// Compute the machine code
		BYTE lMachineCode[MACHINE_CODE_DIM];
		lResult = CSoftwareKey::ComputeMachineCode(
									lMACaddress, 
									lMachineCode);

		// Print the machine code
		char* lMachineCodeString = NULL;
		lResult = CSoftwareKey::Buffer2String(
									lMachineCode, 
									MACHINE_CODE_DIM, 
									&lMachineCodeString);

		printf("\nThe machine code is: %s\n\n", lMachineCodeString);
	} 
	else
	{
		printf("Usage is:\n\n");
		printf("softwarekey_customertool -g\n\n");	
	}

	return 0;
}

