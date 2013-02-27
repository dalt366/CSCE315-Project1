#ifdef DBDLL_EXPORTS
#define DBDLL_API __declspec(dllexport) 
#else
#define DBDLL_API __declspec(dllimport) 
#endif

#ifndef _ATTRIBUTE_LIST_H_
#define _ATTRIBUTE_LIST_H_

#include <vector>
#include <string>
using namespace std;

class DBDLL_API AttributeList {
/*  This class stores all of the data for one column of a Table. Each attribute
	has a name, one of four types (integer, float, variable-length string, or
	date), and an array of entries.
 */
public:

	// Possible types for an attribute, as specified in the project handout.
	enum attribute_t { INT, FLOAT, STRING, DATE };

	AttributeList();
	AttributeList(string _name, attribute_t _type);

	// Getters
	string getName() const;
	attribute_t getType() const;
	string getAt(int _index) const;
	vector<string> getEntries() const;

	// Setters
	bool setName(const string& _name);
	bool setType(attribute_t _type);
	bool setAt(int _index, const string& _value);
	bool setEntries(const vector<string>& _entries);

private:

	// The name of the attribute. This acts as the column heading on a Table.
	string name;

	// The type of the attribute. All entries in this attribute must have the same type.
	attribute_t type;

	// An array of entries for this attribute. These are all of the rows of a specified
	// column of the table, and as such their values must all have the same type.
	vector<string> entries;
};

#endif _ATTRIBUTE_LIST_H_