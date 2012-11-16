#include "csoftwarekey.h" 

// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
int main(int argc, char* argv[])
{
	RETVALUE lResult = SUCCESS;

	printf("\nSoftware key - Vendor Tool - Software key generator\n\n");

	if (argc != 3)
	{		
		printf("Usage is:\n\n");
		printf("softwarekey_vendortool -v MachineCode\n\n");
	}
	else
	if (strcmp(argv[1],"-v")==0)
	{
		// Get the machine code from the command line
		BYTE*			lMachineCode = NULL;
		unsigned int	lMachineCodeSize = 0;
		lResult = CSoftwareKey::String2Buffer(
									argv[2], 
									&lMachineCode, 
									&lMachineCodeSize); 
		
		// Compute the software key
		BYTE lSoftwareKey[SOFTWAREKEY_DIM];
		lResult = CSoftwareKey::ComputeSoftwareKey(lMachineCode, lSoftwareKey); 

		// Print the software key
		char* lSoftwareKeyString = NULL;
		lResult = CSoftwareKey::Buffer2String(
						lSoftwareKey, 
						SOFTWAREKEY_DIM, 
						&lSoftwareKeyString);
		
		printf(
			"\nThe software key for the machine code [%s] is: %s\n\n", 
			argv[2], 
			lSoftwareKeyString);
	} 
	else
	{
		printf("Usage is:\n\n");
		printf("softwarekey_vendortool -v MachineCode\n\n");
	}

	return 0;
}

