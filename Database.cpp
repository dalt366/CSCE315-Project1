#include "Database.h"

bool Database::addTable(Table table, string name){
	// There is database corruption if these sizes are different
	bool error = tables.size() != tableNames.size();
	if(!error) {
		tables.push_back(table);
		tableNames.push_back(name);
	}
	// Return true if success (no error)
	return !error;
}

bool Database::dropTable(string name){
	vector<string>::iterator nameIter = tableNames.begin();
	vector<Table>::iterator tableIter = tables.begin();
	while(nameIter != tableNames.end()) {
		if(nameIter->data == name) {
			// Found the table. Erase it and return true
			tableNames.erase(nameIter);
			tables.erase(tableIter);
			return true;
		}
		nameIter++;
		tableIter++;
	}
	// Table name not found
	return false;
}

vector<Table> Database::getTables(){
	return tables;
}

vector<string> Database::listTables(){
	return tableNames;
}

Table Database::evalQuery(string query){
}

void Database::evalDeleteQuery(string query){
}