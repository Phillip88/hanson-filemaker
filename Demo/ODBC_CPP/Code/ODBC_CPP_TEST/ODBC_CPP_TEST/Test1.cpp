#include "./tiodbc.hpp"
#include <iostream>
#include <conio.h>

using namespace std;

int main()
{   
    tiodbc::connection my_connection;
    tiodbc::statement my_statement;

    // Create a connection with an ODBC Data Source
    if (!my_connection.connect("Phillip_Test", "admin", ""))
    {
        cout << "Cannot connect to the Data Source" << endl
            << my_connection.last_error();
		getch();
        return 1;
    }

    // Execute a direct query
    if (!my_statement.execute_direct(my_connection, "SELECT * FROM Phillip_Test"))
    {
        cout << "Cannot execute query!" << endl
            << my_connection.last_error();
        return 2;
    }

    // Get results from statement
    while(my_statement.fetch_next())
    {
        // print all fields for each row
        for(int i = 1;i <= my_statement.count_columns(); i ++)
            cout << my_statement.field(i).as_string() << "\t";

        cout << endl;
    }
	getch();
    return 0;
}