#ifdef DBDLL_EXPORTS
#define DBDLL_API __declspec(dllexport) 
#else
#define DBDLL_API __declspec(dllimport) 
#endif

#ifndef _TABLE_H_
#define _TABLE_H_

#include "Record.h"
#include "AttributeList.h"
#include <vector>
#include <string>
#include <exception>
#include <climits>
#include <cfloat>
using namespace std;

class DBDLL_API Table {

public:
	//Default Contructor for an empty table
	Table();
	
	//Constructor that takes a list of attributes
	Table(const vector<AttributeList>& attributes);
	
	//Takes in a single attribute name and type, and adds a column to the end of the table with that new attribute.
	//Any entries currently in the table should get NULL for that entry.
	//Returns whether the operation was successful
	bool addAttribute(const string& name, AttributeList::attribute_t type);
	
	//Takes an attribute name and deletes it from the table
	//Returns whether the operation was successful
	bool deleteAttribute(const string& name);
	
	//Takes a record and adds it to the table
	//Returns whether the operation was successful
	bool insert(const Record& r);
	
	//Returns a list of the attributes and types for the table
	vector<AttributeList> getAttributes() const;
	
	//Return the number of records in the given table
	int getSize() const;
	
	class DBDLL_API TableIterator {
	//  This class is used to access individual Records in the Table.
	public:

		TableIterator();
		TableIterator(int _index, Table* _table);

		// Returns Record at index
		Record get() const;

		// Increment index, and return the Record at new index
		Record next();

		// Decrement index, and return the Record at new index
		Record prev();

	private:

		// The index of the iterator is the row of the Table that the iterator
		// refers to.
		int index;

		//This refers to which Table it works with.
		Table* table;
	};

	typedef TableIterator Iterator;

	Iterator first(); // iterator to first record
	Iterator last(); // iterator to last record

	//Replaces the name for the attribute given by the first string with the second string
	//Returns true if operation succeeds, and returns false otherwise
	bool renameAttribute(const string& attributeName, const string& replaceWith);

	//Computes the cross join of Table t1 and Table t2
	static Table crossJoin(const Table& t1, const Table& t2);

	//Sums the attributes of Type T.
	//Type T must be able to be added
	template<class T> T sumAttribute(const string& attributeName) const;

	//Counts the number of non-null elements of attributeName
	template<class T> int countAttribute(const string& attributeName) const;

	//Finds the minimum element of Type T
	//Type T must be able to be compared
	template<class T> T minAttribute(const string& attributeName) const;

	//Finds the maximum element of Type T
	//Type T must be able to be compared
	template<class T> T maxAttribute(const string& attributeName) const;

private:

	// Specifies the number of Attributes (or columns) in the Table.
	int numAttributes;

	// Specifies the number of Records (or rows) in the Table.
	int numRecords;

	vector<AttributeList> attributes;
};

void print(const Table& t);

//Sums the attributes of Type T.
//Type T must be able to be added
template<class T> T Table::sumAttribute(const string& attributeName) const {
	T sum = T();
	for(int i = 0; i<numAttributes; i++)
	{
		if(attributes[i].getName().compare(attributeName) == 0)
		{
			for(int j = 0; j<numRecords; j++)
			{
				switch(attributes[i].getType())
				{
				case AttributeList::INT:
					sum += atoi(attributes[i].getAt(j).c_str());
					break;
				case AttributeList::FLOAT:
					sum += atof(attributes[i].getAt(j).c_str());
					break;
				case AttributeList::STRING: case AttributeList::DATE:
					throw runtime_error("INVALID SUM TYPE");
				}
			}
			break;
		}
	}
	return sum;
}

//Counts the number of non-null elements of Type T
//TODO: Look more at this
template<class T> int Table::countAttribute(const string& attributeName) const {
	int count = 0;
	for(int i = 0; i<numAttributes; i++)
	{
		if(attributes[i].getName().compare(attributeName) == 0)
		{
			for(int j = 0; j<numRecords; j++)
			{
				switch(attributes[i].getType())
				{
				case AttributeList::INT:
					if(atoi(attributes[i].getAt(j).c_str()) != 0)
						count++;
					break;
				case AttributeList::FLOAT:
					if(atof(attributes[i].getAt(j).c_str()) != 0.0)
						count++;
					break;
				case AttributeList::STRING: case AttributeList::DATE:
					if(attributes[i].getAt(j) != "NULL")
						count++;
				}
			}
			break;
		}
	}
	return count;
}

//Finds the minimum element of Type T
//Type T must be able to be compared
template<class T> T Table::minAttribute(const string& attributeName) const {
	T t = T();
	for(int i = 0; i<numAttributes; i++)
	{
		if(attributes[i].getName().compare(attributeName) == 0)
		{
			//Set to MAX
			switch(attributes[i].getType())
			{
			case AttributeList::INT:
				t = INT_MAX;
				break;
			case AttributeList::FLOAT:
				t = FLT_MAX;
				break;
			case AttributeList::STRING: case AttributeList::DATE:
				throw runtime_error("INVALID MIN TYPE");
			}
			for(int j = 0; j<numRecords; j++)
			{
				switch(attributes[i].getType())
				{
				case AttributeList::INT:
					if(atoi(attributes[i].getAt(j).c_str()) < t)
						t = atoi(attributes[i].getAt(j).c_str());
					break;
				case AttributeList::FLOAT:
					if(atof(attributes[i].getAt(j).c_str()) < t)
						t = atof(attributes[i].getAt(j).c_str());
				}
			}
			break;
		}
	}
	return t;
}

//Finds the maximum element of Type T
//Type T must be able to be compared
template<class T> T Table::maxAttribute(const string& attributeName) const {
	T t = T();
	for(int i = 0; i<numAttributes; i++)
	{
		if(attributes[i].getName().compare(attributeName) == 0)
		{
			//Set to MIN
			switch(attributes[i].getType())
			{
			case AttributeList::INT:
				t = INT_MIN;
				break;
			case AttributeList::FLOAT:
				t = FLT_MIN;
				break;
			case AttributeList::STRING: case AttributeList::DATE:
				throw runtime_error("INVALID MAX TYPE");
			}
			for(int j = 0; j<numRecords; j++)
			{
				switch(attributes[i].getType())
				{
				case AttributeList::INT:
					if(atoi(attributes[i].getAt(j).c_str()) > t)
						t = atoi(attributes[i].getAt(j).c_str());
					break;
				case AttributeList::FLOAT:
					if(atof(attributes[i].getAt(j).c_str()) > t)
						t = atof(attributes[i].getAt(j).c_str());
				}
			}
			break;
		}
	}
	return t;
}

#endif _TABLE_H_
