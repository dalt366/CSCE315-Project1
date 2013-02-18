#include "Record.h"
#include <iostream>

Record::Record(vector<string> entries){

	this->entries = entries;

}

void Record::modifyEntry(int columnNumber, string newEntry) {

	entries[columnNumber] = newEntry;

}

string Record::getEntry(int columnNumber){

	return entries[columnNumber];

}