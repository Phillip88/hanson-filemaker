#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int main ()
{
  int i;
  

  i=system ("ping -n 1 www.google.com >nul");
  if (i = 1)
		{
			printf ("FAILED");
		}
		else
		{
			printf ("OK");
		}
  

  getch();
  return 0;
}