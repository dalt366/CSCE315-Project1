#ifndef DATABASE_H
#define DATABASE_H

/* First revision of Database.h
 * 
 * Author: Brent Walther
 * Last Revised: Feb 04, 2013 12:01PM
 */

#include "Table.h"
#include <list>

using namespace std;

class Database {
public:
	Database() { };
	bool addTable(Table table, string name);
	bool dropTable(string name);
	list<Table> getTables();
	list<string> listTables();
	Table evalQuery(string query);
	void evalDeleteQuery(string query);

private:
	vector<Table> tables;
}

#endif