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
	vector<string> queryArgs = splitQueryArguments(query);
	string attributes = queryArgs[0];
	string tableName = queryArgs[1];
	string whereArgs = queryArgs[2];

	Table strippedTable = stripRecords(getTableByName(tableName), whereArgs);
	strippedTable = selectAttributes(strippedTable, attributes);
}

void Database::evalDeleteQuery(string query){
	vector<string> queryArgs = splitQueryArguments(query);
}

// example WHERE {{School = TAMU} AND {Number = 42}}
Table Database::stripRecords(Table table, string args) {
	Table newTable;
	for(int i = 0; i < table.getSize(); i++) {
		Record record = table.getRecord(i);
		if(recordMatches(table.getAttributes(), record, args)) {
			newTable.insert(record);
		}
	}
	return newTable;
}

Table Database::selectAttributes(Table table, string attributes) {
	// break up the attributes string and remove those from the table then return
}

// TODO ----------------------------------------
bool Database::recordMatches(vector<string> attributeNames, Record record, string args) {
		return true;
}

Table Database::getTableByName(string tableName) {
	vector<string>::iterator nameIter = tableNames.begin();
	vector<Table>::iterator tableIter = tables.begin();
	Table index;
	while(nameIter != tableNames.end()) {
		nameIter++;
		tableIter++;
		if(nameIter->data == tableName) {
			index = *tableIter;
			break;
		}
	}
	return index;
}

vector<string> Database::splitQueryArguments(string query) {
	vector<string> args;

	// Strip off the SELECT
	int caratPos = query.find("SELECT");
	query = query.substr(caratPos+1);

	// Grab the SELECT args and put them in the vector
	caratPos = query.find("FROM");
	args.push_back(query.substr(0,caratPos-1));

	// Strip off the FROM
	query = query.substr(caratPos+1);

	// Grab the FROM args and put them in the vector
	caratPos = query.find("WHERE");
	args.push_back(query.substr(0,caratPos-1));

	// Strip off the WHERE
	query = query.substr(caratPos+1);

	// Push the WHERE args to the vector
	args.push_back(query);

	return args;
}

