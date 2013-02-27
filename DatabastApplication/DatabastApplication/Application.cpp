#include "API.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

void loadData(Table& destTable, string filename); // Loads a table from a .csv
int getMenuSelection(); // Shows the menu and gets the choice
void printTables(Database &db);
void printRecords(Database &db, string tableName);

int main() {
	//Initialize the database
	Database * database = new Database();

	//Add the tables
	Table * table = new Table();
	loadData(*table, "./data/chefmozaccepts.csv");
	database->addTable(*table, "Payments");

	table = new Table();
	loadData(*table, "./data/chefmozcuisine.csv");
	database->addTable(*table, "Cuisines");

	table = new Table();
	loadData(*table, "./data/chefmozparking.csv");
	database->addTable(*table, "Parking");

	table = new Table();
	loadData(*table, "./data/geoplaces2.csv");
	database->addTable(*table, "Restaurants");

	table = new Table();
	loadData(*table, "./data/userprofile.csv");
	database->addTable(*table, "Customers");

	table = new Table();
	loadData(*table, "./data/rating_final.csv");
	database->addTable(*table, "Ratings");

	for(;;) {
		int choice = getMenuSelection();
		switch(choice) {
		case 1:
			printTables(*database);
			break;
		case 2:
			{
			printf("Enter the table name: ");
			string tableName;
			cin >> tableName;
			printRecords(*database, tableName);
			break;
			}
		default:
			cout << "Invalid choice \n\n" << endl;
		}
		if(choice == 0) {
			break;
		}
	}
	return 0; // Program exit 
}

int getMenuSelection() {
	cout << "MAIN MENU" << endl;
	cout << "---------" << endl;
	cout << "\t" << "1) Print the list of tables" << endl; //Currently for debug purposes
	cout << "\t" << "2) Print the records in a table" << endl; //Currently for debug purposes
	cout << "\t" << "3) Another cool option!" << endl;
	cout << "\t" << "0) Exit" << endl;
	cout << "Enter your selection (number): ";
	int choice;
	cin >> choice;
	return choice;
}

// Used for debug purposes
void printRecords(Database &db, string tableName) {	
	vector<string> tableNames = db.listTables();
	int index = -1;
	for(unsigned int i = 0; i < tableNames.size(); i++) {
		if(tableNames[i].compare(tableName) == 0) {
			index = i;
		}
	}
	if(index == -1) {
		// Table not found.
		printf("Table %s not found \n", tableName.c_str());
		return;
	}
	else {
		Table table = db.getTables()[index];
		Table::Iterator iter = table.first();
		while(true) {
			Record record = iter.next();
			if(record.size() <= 0) {
				// End the loop, last record reached?
				break;
			}
			for(int i = 0; i < record.size(); i++) {
				printf("%s", record.getAt(i).c_str());
			}
			printf("\n");
		}
	}
}

// Used for debug purposes
void printTables(Database &db) {
	vector<Table> tables = db.getTables();
	vector<string> tableNames = db.listTables();
	for(unsigned int i = 0; i < tables.size(); i++) {
		printf("Table number %i is called %s \n", i+1, tableNames[i].c_str());
		printf("---------------------------- \n");
		printf("Attributes:\n");
		vector<AttributeList> attributes = tables[i].getAttributes();
		for(unsigned int j = 0; j < attributes.size(); j++) {
			printf("Attribute %i is called %s with type %i \n", j, attributes[j].getName().c_str(), attributes[j].getType());
		}
		printf("\n");
	}
}


void loadData(Table& destTable, string filename) {
	printf("Loading filename %s \n", filename.c_str());
	//TODO - build a table from the csv file.
	ifstream file = ifstream(filename.c_str());
	string line;
	string line2;
	getline(file, line);
	getline(file, line2);

	stringstream sstream(line);
	stringstream sstream2(line2);
	string item, type;
	//Fill the attributes
	while(getline(sstream, item, ',')) {
		getline(sstream2, type, ',');
		destTable.addAttribute(item, AttributeList::attribute_t(atoi(type.c_str())));
	}

	//Fill the table with records
	while(getline(file, line)) {
		Record record = Record();

		stringstream sstream(line);
		string item;
		int index = 0;
		while(getline(sstream, item, ',')) {
			//printf("Loading item %s \n", item.c_str());
			record.setAt(index++, item);
		}

		destTable.insert(record);
	}

	// Close and return
	file.close();
}