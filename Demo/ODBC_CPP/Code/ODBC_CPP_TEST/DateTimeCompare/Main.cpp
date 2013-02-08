/*#include <string.h>
#include <stdio.h>
#include <conio.h>

char string1[] = "2012-12-06";
char string2[] = "2012-12-07";

int main( void )
{
   char tmp[20];
   int result;

   printf( "Compare strings:\n   %s\n   %s\n\n\n", string1, string2 );
   result = strcmp( string1, string2 );

   if( result > 0 )        strcpy( tmp, "greater than" );
   else if( result < 0 )   strcpy( tmp, "less than" );
   else    strcpy( tmp, "equal to" );

   printf( "   strcmp:   String 1 is %s string 2\n\n", tmp );

   getch();
   return 0;
}
*/
#include <ctime>
#include <conio.h>
#include <stdio.h>

// Make a tm structure representing this date
std::tm make_tm(int year, int month, int day)
{
    std::tm tm = {0};
    tm.tm_year = year - 1900; // years count from 1900
    tm.tm_mon = month - 1;    // months count from January=0
    tm.tm_mday = day;         // days count from 1
    return tm;
}

int main( void )
{
	// Structures representing the two dates
	std::tm tm1 = make_tm(2012,12,20);    // April 2nd, 2012
	std::tm tm2 = make_tm(2012,12,25);    // February 2nd, 2003

	// Arithmetic time values.
	// On a posix system, these are seconds since 1970-01-01 00:00:00 UTC
	std::time_t time1 = std::mktime(&tm1);
	std::time_t time2 = std::mktime(&tm2);

	// Divide by the number of seconds in a day
	const int seconds_per_day = 60*60*24;
	std::time_t difference = (time1 - time2) / seconds_per_day;    

	// To be fully portable, we shouldn't assume that these are Unix time;
	// instead, we should use "difftime" to give the difference in seconds:
	int portable_difference = (int)std::difftime(time1, time2) / seconds_per_day;

	printf( " %d ", (int)std::difftime(time1, time2) / seconds_per_day );

	getch();
	return 0;
}