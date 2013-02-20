#ifdef DBDLL_EXPORTS
#define DBDLL_API __declspec(dllexport) 
#else
#define DBDLL_API __declspec(dllimport) 
#endif

#pragma once

/* Database.h
 * 
 * Author: Brent Walther
 * Last Revised: Feb 20, 2013 2:30PM
 */

#include <vector>
#include "Table.h"

using namespace std;

class DBDLL_API Database {
public:

	/*!
      Creates an empty database.
    */
	Database();

	/*!
      Takes a single table and a name, and adds that table to the database
	  \param Table the table to add
	  \param name the name of the table
	  \return whether the table was added successfully
    */
	bool addTable(Table table, string name);

	/*!
      Takes a table name and deletes it from the database
	  \param name the name of the table
	  \return whether the table was dropped successfully
    */
	bool dropTable(string name);

	/*!
	  \return a vector of all tables in the database
    */
	vector<Table> getTables();

	/*!
	  \return a vector of all table names in the database
    */
	vector<string> listTables();

	/*!
	  Query the database using a query string. The syntax is detailed in the parameter with the {command} being able to be one of the following:
		-Comparisons of =, !=, >, <, >=, <=  (only between attributes/values of the same type)
		-AND, OR, and NOT
		-Parentheses.  No more than 3 levels of parentheses are supported
	  \param query the query constructed in one full string in the following format: SELECT {attributeName1, {attributeName2 ...}} FROM {tableName} WHERE {command}
	  \return the table resulting from the query
    */
	Table evalQuery(string query);
	void evalDeleteQuery(string query);

private:
	vector<Table> tables;
};
