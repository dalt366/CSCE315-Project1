#ifndef RECORD_H
#define RECORD_H

#include <vector>
#include <string>

using namespace std;

class Record{
public:

	Record();
	Record(vector<string>);											//Takes a vector of strings and stores them in Entries

	void modifyEntry(int rowNumber);								//Modifies an entry in a specified row and column

	string getEntryRow(int rowNumber);								//Gets the entry at the specified row and column;

private:

	vector<string> entries;

};

#endif