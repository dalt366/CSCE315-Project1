#include "Record.h"
#include <iostream>

Record::Record(vector<string> records){

	entries = records;

}

void Record::modifyEntry(int rowNumber){

	string newRecords;

	cout << "Enter new records" << endl;

	cin >> newRecords; 

	entries[rowNumber] = newRecords;

}

string Record::getEntryRow(int rowNumber){

	return entries[rowNumber];

}