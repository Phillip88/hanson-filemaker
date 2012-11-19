// initializing C++
#include <iostream>
#include "sha.h"

using namespace std;

// declaring function prototypes
float addition (float a, float b);

//main function
int main ()
{
	float x;		//
	float y;		//declares variables
	float n;		//
	int b;
	b = 1;			//sets value of b to 1
	cout << "Simple Addition Calc- First Program";		//displays info about program
	while (b==1)										//creates loop so the program runs as long as the person wants to add numbers
	{
		//following code prompts the user for 2 numbers to add and calls function addition to display results
		cout << "\n" << "Type a number to add (can also use negetive, decimals, etc.): ";
		cin >> x;
		cout << " Second number: ";
		cin >> y;
		n = addition (x,y);
		cout << "Ans: " << x << " + " << y << " = " << n << "\n";
		//following code sets b to the value the user imputs to determine if the loop is broken to end the program
		cout << "Solve another operation? (1=yes, 2=no): ";
		cin >> b;
		cout << "\n";
		if (b==2)
		cout << "Terminating application.";
	}
	//ends the main function of the code
	return 0;
	}
//following function adds the numbers
float addition (float a, float b)
{
	float c;
	c = a+b;
	return (c);
}

void test()
{
	CryptoPP::SHA256 hash;
}
//END C++ CODE