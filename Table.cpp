#include "Table.h"

void Table::add(string attributeName, TYPE type){
	columns.insert(std::pair<string,TYPE>(attributeName, type));
}

void Table::deleteFunction(string attributeName){
	columns.erase(attributeName);
}

void Table::insert(Record record){
	records.push_back(record);
}

map<string,Table::TYPE> Table::getAttributes(){    
    return columns;
}

int Table::getSize(){
	return records.size();
}

Record Table::getRecord(int rowNumber){
	return records[rowNumber];
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

float Table::getSum(string attributeName){
	return 0;
}

int Table::getCount(string attributeName){
	return 0;
}

float Table::getMin(string attributeName){
	return 0;
}

float Table::getMax(string attributeName){
	return 0;
}
