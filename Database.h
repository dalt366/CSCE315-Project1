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
	vector<string> tableNames;

	/*
		This function will split the query into a vector containing three things:
		[0] = args from SELECT (attribute names)
		[1] = arg from FROM (table name)
		[2] = args from WHERE (have to parse this further)
	*/
	vector<string> splitQueryArguments(string query);

	// Strips the records from the table that don't match "args" and then returns it back
	Table stripRecords(Table table, string args);

	Table selectAttributes(Table table, string attributes);

	 // Return the table of the given name
	Table getTableByName(string tableName);

	// Test a record to see if it matches the arguments from WHERE
	bool recordMatches(vector<string> attributeNames, Record record, string args);


};
