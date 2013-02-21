#include "Record.h"
#include <iostream>

Record::Record(vector<string> entries){
	this->entries = entries;
}

void Record::modifyEntry(int columnNumber, string newEntry) {
	if(isValidColNum(columnNumber)) {
		entries[columnNumber] = newEntry;
	}
}

string Record::getEntry(int columnNumber){
	if(isValidColNum(columnNumber)) {
		return entries[columnNumber];
	}
	else {
		return "";
	}
}

bool Record::isValidColNum(int columnNumber) {
	return columnNumber >= 0 && columnNumber < entries.size();
}