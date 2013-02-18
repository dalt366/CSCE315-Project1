#include "Table.h"

void Table::add(string attributeName, TYPE type){
	
}

void Table::deleteFunction(string attributeName){

}

void Table::insert(Record record){

}
/*
map<string,Table::TYPE> Table::getAttributes(){
	 map<"hello",Table::STRING> theMap;
    
    return theMap;
}*/

int Table::getSize(){
	return 2;
}

Record Table::getRecord(int rowNumber){
	return records[rowNumber];
}

void Table::renameAttribute(string oldName, string newName){

}

Table Table::crossJoin(Table table1, Table table2){
	return table1;
}

float Table::getSum(string attributeName){
	return 2;
}

int Table::getCount(string attributeName){
	return 2;
}

float Table::getMin(string attributeName){
	return 2;
}

float Table::getMax(string attributeName){
	return 2;
}
