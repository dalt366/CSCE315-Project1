#pragma once

#ifndef RECORD_H
#define RECORD_H

#include <vector>
#include <string>

using namespace std;

class Record{
public:

	/*!
      Creates a record with an arbitrary number of entries
    */
	Record();
<<<<<<< .mine
=======
	Record(vector<string>);											//Takes a vector of strings and stores them in Entries
>>>>>>> .r10

<<<<<<< .mine
	/*!
      Creates a record using the specified entries
	  \param entries the entries to populate the record with
    */
	Record(vector<string> entries);

	/*!
      Modifies an entry at the specified column
	  \param columnNumber the column to modify
	  \param newEntry the entry to replace the old one with
    */
	void modifyEntry(int columnNumber, string newEntry);

	/*!
      Gets the entry at the specified column
	  \param columnNumber the column number to return
	  \return the entry at the specified column
    */
	string getEntry(int columnNumber);

=======
	void modifyEntry(int rowNumber);								//Modifies an entry in a specified row and column

	string getEntryRow(int rowNumber);								//Gets the entry at the specified row and column;

>>>>>>> .r10
private:

	vector<string> entries;

};

#endif