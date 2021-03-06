#pragma once

#include <map>
#include "Record.h"

using namespace std;

class Table {
public:
	//! An enum representing attribute types
	enum TYPE {INT, FLOAT, STRING, DATE};

    /*!
      Creates an empty table with no rows or columns
    */
	Table();

    /*!
      Creates a table from specified columns
	  \param columnNames A vector of the column names
	  \param columnTypes A vector of the respective types
    */
	Table(vector<string> columnNames, vector<Table::TYPE> columnTypes);

    /*!
	  Takes in a single attribute name and type, and adds a column to the end of the table with that new attribute.  Any entries currently in the table should get NULL for that entry.
      \param attributeName the name of the new attribute
      \param type the type of the attribute
    */
	void add(string attributeName, TYPE type);

    /*!
	  Takes an attribute name and deletes it from the table.
      \param attributeName the name of the attribute to delete
    */
	void deleteFunction(string attributeName);

	/*!
	  Takes a record and adds it to the table
      \param record the record to add
    */
	void insert(Record record);

	/*!
      \return A vector of the attribute names in table order
    */
	vector<string> getAttributes();

	/*!
      \return A vector of the attribute types in table order. This order will match the return order of getAttributes()
    */
	vector<Table::TYPE> getAttributeTypes();

	/*!
      \return the number of records in the table
    */
	int getSize();

	/*!
	  \param rowNumber the row number to retrieve from the table
      \return the requested record from the table, or an empty record if the record isn't found
    */
	Record getRecord(int rowNumber);

	/*!
	  Takes two names, and replaces the name for the attribute given by the first name with the second name
	  \param oldName the name to be replaced
	  \param newName the name to change it to
    */
	void renameAttribute(string oldName, string newName);

	/*!
	  Takes two tables as input and produces one table as output.
	  \param table1 the first table
	  \param table2 the second table
    */
	Table crossJoin(Table table1, Table table2);

	/*!
	  Take a single attribute name as input, and computes the sum of all records
	  \param attributeName the name of the column (attribute) to use
    */
	float getSum(string attributeName);

	/*!
	  Take a single attribute name as input, and counts non-null entries
	  \param attributeName the name of the column (attribute) to use
    */
	int getCount(string attributeName);

	/*!
	  Take a single attribute name as input, and finds the minimum of all records
	  \param attributeName the name of the column (attribute) to use
    */
	float getMin(string attributeName);

	/*!
	  Take a single attribute name as input, and finds the maximum of all records
	  \param attributeName the name of the column (attribute) to use
    */
	float getMax(string attributeName);

private:
	vector<Record> records;
	vector<string> columnNames;
	vector<Table::TYPE> columnTypes;

	bool isValidRecordNumber(int recordNumber);
	int indexOfAttribute(string attributeName);
};
