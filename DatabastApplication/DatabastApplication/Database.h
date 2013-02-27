#ifdef DBDLL_EXPORTS
#define DBDLL_API __declspec(dllexport) 
#else
#define DBDLL_API __declspec(dllimport) 
#endif

#ifndef _DATABASE_H_
#define _DATABASE_H_

#include "Table.h"
#include <map>
#include <vector>
#include <string>
using namespace std;

class DBDLL_API Database {

public:
	//Default Constructor to create empty database
	Database();

	//Creates Database with given set of tables and names
	Database(const vector<Table>& tables, const vector<string>& names);

	//Adds a table to the database
	//Returns whether the operation was successful
	bool addTable(const Table& toAdd, const string& name);

	//Removes a table from the database, taking its name
	//Returns whether the operation was successful
	//Returns false if the table was not found
	bool removeTable(const string& name);

	//Returns a vector of all the Table names in the Database
	vector<string> listTables();

	//Returns a vector of all the Tables in the Database
	vector<Table> getTables();

	//The query command
	//_select shall be a vector that is a list of attribute names to be returned
	//If all attributes are to be returned, _select shall be NULL
	//_from shall be the name of the table from which to find the data
	//_where shall be comparisons and logical AND, OR, NOT
	//Comparisons shall be  =, !=, >, <, >=, <= between the same type
	//If no conditions are to be met, _where shall be empty
	//Example: (attribute1 = attribute2) AND (attribute2 <= attribute4)
	Table query(const vector<string>& _select, const string& _from, const string& _where);

	//Returns the number of Records removed from the Table defined by _from
	//_select shall be a vector that is a list of attribute names to be deleted
	//If all attributes are to be deleted, _select shall be NULL
	//_from shall be the name of the table from which to find the data
	//_where shall be comparisons and logical AND, OR, NOT
	//Comparisons shall be  =, !=, >, <, >=, <= between the same type
	//If no conditions are to be met, _where shall be empty
	//Example: (attribute1 = attribute2) AND (attribute2 <= attribute4)
	int deleteRecords(const vector<string>& _select, const string& _from, const string& _where);

private:
	map<string, Table> tables;
};

#endif _DATABASE_H_
