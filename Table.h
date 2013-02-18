#include <list>
#include <stdlib.h>
#include <map>
#include <iterator>
#include <string>
#include "Record.h"

using namespace std;
enum {INT, FLOAT, STRING, DATE};

class Table {
public:
	Table(map<string,string>); 
	void add(string attribute, string type);
	void deleteFunction(string name);
	void insert(Record record);
	map<string,string> getAttributes();
	int getSize(Table table);
	iterator<Record> begin();
	iterator<Record> end();
	void rename(string name1, string name2);
	Table cross_join(Table table1, Table table2);
};

/*
  Constructor of a table.  An empty constructor should be allowed, to create a table with no rows or columns.
·         A constructor should also be supported that takes a list of attribute names and types (this can be done in multiple ways – you could have two lists (one with names, one with types), or use a new structure with a name/type, pass in as arrays, or as some other container, etc.
·         An add function that takes in a single attribute name and type, and adds a column to the end of the table with that new attribute.  Any entries currently in the table should get NULL for that entry.
·         A delete function that takes an attribute name and deletes it from the table.
·         An insert command that takes a record and adds it to the table.
·         A get attributes command that returns a list of the attributes and types for that table
·         A get size command that returns the number of records in the table
·         An iterator of some sort that can be used to return individual records from the table.  There are many ways this can be done.
·         A rename attribute command that takes two names, and replaces the name for the attribute given by the first name with the second name.
·         A cross join command that takes two tables as input and produces one table as output.
   Routines that take a single attribute name as input, and compute the following:
o   Sum
o   Count (counts non-null entries only)
o   Min
o   Max
*/