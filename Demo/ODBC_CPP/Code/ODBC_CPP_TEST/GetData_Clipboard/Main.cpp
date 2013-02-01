#include <windows.h>
#include <stdio.h>
#include <conio.h>
 

 
int main()
{
  HANDLE h;
   
  if (!OpenClipboard(NULL))
    printf("Can't open clipboard");
   
  h = GetClipboardData(CF_TEXT);
  if (h == NULL)
	  printf("NULL");
  printf("%s\n", (char *)h);
 
  CloseClipboard();
  getch();
  return 0;
}