#include "Table.h"

Table::Table(vector<string> columnNames, vector<Table::TYPE> columnTypes) {
	this->columnNames = columnNames;
	this->columnTypes = columnTypes;
}

void Table::add(string attributeName, TYPE type){
	columnNames.push_back(attributeName);
	columnTypes.push_back(type);
}

void Table::deleteFunction(string attributeName){
	columns.erase(attributeName);
}

void Table::insert(Record record){
	records.push_back(record);
}

vector<string> Table::getAttributeNames() {    
    return columnNames;
}

int Table::getSize(){
	return records.size();
}

Record Table::getRecord(int rowNumber){
	if(isValidRecordNumber(rowNumber)) {
		return records[rowNumber];
	}
	else {
		// returns an empty record if invalid row number
		return Record();
	}
}

void Table::renameAttribute(string oldName, string newName){
	std::map<string,TYPE>::iterator position = columns.find("oldName");
	if(position != columns.end()) {
		TYPE type = position->second;
		columns.erase(position);
		add(newName, type);
	}
}

Table Table::crossJoin(Table table1, Table table2){
	return table1;
}

float Table::getSum(string attributeName) {
	int index = indexOfAttribute(attributeName);
	float sum = 0;
	for(int i = 0; i < getSize(); i++) {
		sum += atof(getRecord(i).getEntry(index).c_str());
	}
	return sum;
}

int Table::getCount(string attributeName) {
	int index = indexOfAttribute(attributeName);
	int count = 0;
	for(int i = 0; i < getSize(); i++) {
		if(getRecord(i).getEntry(index).c_str() != "") {
			count++;
		}
	}
	return count;
}

float Table::getMin(string attributeName) {
	int index = indexOfAttribute(attributeName);
	float minimum = atof(getRecord(0).getEntry(index).c_str());
	for(int i = 1; i < getSize(); i++) {
		float current = atof(getRecord(i).getEntry(index).c_str());
		if(current < minimum) {
			minimum = current;
		}
	}
	return minimum;
}

float Table::getMax(string attributeName) {
	int index = indexOfAttribute(attributeName);
	float maximum = atof(getRecord(0).getEntry(index).c_str());
	for(int i = 1; i < getSize(); i++) {
		float current = atof(getRecord(i).getEntry(index).c_str());
		if(current > maximum) {
			maximum = current;
		}
	}
	return maximum;
}

bool Table::isValidRecordNumber(int recordNumber) {
	return recordNumber >= 0 && recordNumber < records.size();
}

int Table::indexOfAttribute(string attributeName) {
	vector<string>::iterator columnIter = columnNames.begin();
	int index = 0;
	while(columnIter->data != attributeName) {
		columnIter++;
		index++;
		if(columnIter == columnNames.end()) {
			index = 0;
			break;
		}
	}
	return index;
}