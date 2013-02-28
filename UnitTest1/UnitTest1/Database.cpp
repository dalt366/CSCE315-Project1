#include "Database.h"

Database::Database() { }

bool Database::addTable(Table table, string name){
	// There is database corruption if these sizes are different
	bool sameName=true;
	for(int i=0; i < tableNames.size();i++){
		if(tableNames[i] == name){
		sameName = false;
		}
		else
		sameName = true;
	}
	bool error = (tables.size() != tableNames.size()) && (getTableByName(name) != NULL);
	if(!error && sameName) {
		tables.push_back(table);
		tableNames.push_back(name);
	}
	// Return true if success (no error)
	return (!error && sameName);
}

bool Database::dropTable(string name){
	vector<string>::iterator nameIter = tableNames.begin();
	vector<Table>::iterator tableIter = tables.begin();
	while(nameIter != tableNames.end()) {
		if(*nameIter == name) {
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

	Table strippedTable = stripRecords(*(getTableByName(tableName)), whereArgs);
	strippedTable = selectAttributes(strippedTable, attributes);

	return strippedTable;
}
//Todo doesnt work for correctly deleteing
void Database::evalDeleteQuery(string query){
	vector<string> queryArgs = splitQueryArguments(query);
	string attributes = queryArgs[0];
	string tableName = queryArgs[1];
	string whereArgs = queryArgs[2];
	bool drop;

	Table strippedTable = stripRecords(*(getTableByName(tableName)), whereArgs);
	strippedTable = selectAttributes(strippedTable, attributes);

	for(int i=0; i < strippedTable.getSize();i++){
		if(tableNames[0] == whereArgs){
		drop = false;
		}
		else
		drop = true;
	}
}

Table Database::stripRecords(Table table, string args) {
	Table newTable;
	for(int i = 0; i < table.getSize(); i++) {
		Record record = table.getRecord(i);
		if(recordMatchesArgs(table.getAttributes(), table.getAttributeTypes(), record, args)) {
			newTable.insert(record);
		}
	}
	return newTable;
}

Table Database::selectAttributes(Table table, string attributes) {
	return table;
}

// TODO ----------------------------------------
// example WHERE {{School = TAMU} AND {Number = 42}}
bool Database::recordMatchesArgs(vector<string> attributeNames, vector<Table::TYPE> attributeTypes, Record record, string args) {
	// Trim the leading whitespace
	while(args[0] == ' ')
		args = args.substr(1);

	char c = args[0];
	string s1, s2;
	bool match;
	switch(c) {
	case '{':
		match = recordMatchesArgs(attributeNames, attributeTypes, record, args.substr(1));
		break;
	case 'A':
		if(args[1] == 'N' && args[2] == 'D') {
			match = match && recordMatchesArgs(attributeNames, attributeTypes, record, args.substr(3));
		}
		break;
	case 'O':
		if(args[1] == 'R') {
			match = match || recordMatchesArgs(attributeNames, attributeTypes, record, args.substr(2));
		}
	case 'N':
		if(args[1] == 'O' && args[2] == 'T') {
			match = !recordMatchesArgs(attributeNames, attributeTypes, record, args.substr(3));
		}
		break;
	default:
		match = expression(attributeNames, attributeTypes, record, args.substr(2));
	}
	return match;
}

bool Database::expression(vector<string> attributeNames, vector<Table::TYPE> attributeTypes, Record record, string args) {
	string attribute1 = getAttributeInArgs(args);
	args = args.substr(attribute1.length());
	string term1 = term(attributeNames, record, attribute1);

	// Trim whitespace between term and operator
	while(args[0] == ' ')
		args = args.substr(1);

	char c = args[0];
	switch(c) {
	case '<':
		if(args[1] == '=') {
			string term2 = term(attributeNames, record, getAttributeInArgs(args.substr(2)));
			return term1.compare(term2) >= 0;
		}
		else {
			string term2 = term(attributeNames, record, getAttributeInArgs(args.substr(1)));
			return term1.compare(term2) > 0;
		}
	case '>':
		if(args[1] == '=') {
			string term2 = term(attributeNames, record, getAttributeInArgs(args.substr(2)));
			return term1.compare(term2) <= 0;
		}
		else {
			string term2 = term(attributeNames, record, getAttributeInArgs(args.substr(1)));
			return term1.compare(term2) < 0;
		}
	case '=':
		if(args[1] == '=') {
			args = args.substr(1);
		}
		else {
			string term2 = term(attributeNames, record, getAttributeInArgs(args.substr(1)));
			return term1.compare(term2) == 0;
		}
	case '!':
		{
		string term2 = term(attributeNames, record, getAttributeInArgs(args.substr(2)));
		return term1.compare(term2) != 0;
		}
	default:
		return false;
	}
}

string Database::term(vector<string> attributeNames, Record record, string term) {	
	for(int i = 0; i < attributeNames.size(); i++) {
		if(term.compare(attributeNames[i]) == 0)
			return record.getEntry(i);
	}
	return "";
}

string Database::getAttributeInArgs(string term) {
	// Trim the leading whitespace
	while(term[0] == ' ')
		term = term.substr(1);

	string columnName = "";
	while(isalpha(term[0])) {
		columnName.append("" + term[0]);
		term = term.substr(1);
	}
	return columnName;
}

Table::TYPE Database::getAttributeType(vector<string> attributeNames, vector<Table::TYPE> attributeTypes, string attribute) {
	for(int i = 0; i < attributeNames.size(); i++) {
		if(attribute.compare(attributeNames[i]) == 0)
			return attributeTypes[i];
	}
	return Table::TYPE(2);
}



Table * Database::getTableByName(string tableName) {
	int pos1 = tableName.find('{');
	int pos2 = tableName.find('}');
	tableName = tableName.substr(pos1, pos2);
	vector<string>::iterator nameIter = tableNames.begin();
	vector<Table>::iterator tableIter = tables.begin();
	Table * index = NULL;
	while(nameIter != tableNames.end()) {
		if(*nameIter == tableName) {
			index = &(*tableIter);
			break;
		}
		nameIter++;
		tableIter++;
	}
	return index;
}

vector<string> Database::splitQueryArguments(string query) {
	vector<string> args;

	// Strip off the SELECT
	int caratPos = query.find("SELECT");
	query = query.substr(caratPos+6);

	// Grab the SELECT args and put them in the vector
	caratPos = query.find("FROM");
	args.push_back(query.substr(0,caratPos-1));

	// Strip off the FROM
	query = query.substr(caratPos+4);

	// Grab the FROM args and put them in the vector
	caratPos = query.find("WHERE");
	args.push_back(query.substr(0,caratPos-1));

	// Strip off the WHERE
	query = query.substr(caratPos+5);

	// Push the WHERE args to the vector
	args.push_back(query);

	return args;
}

