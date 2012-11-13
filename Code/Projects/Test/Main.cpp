#include<stdio.h>
#include<conio.h>
#include<string.h>

void test1();

void main()
{
	test1();
	getch();
}

void test1()
{
	char *foo = "foo";
	char *bar = "bar";
	char *str = new char[50];
	strcpy (str, "");
	strcat (str, foo);
	strcat (str, bar);
	printf(str);
}