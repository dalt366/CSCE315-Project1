#include "API.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

void loadData(Table& destTable, string filename); // Loads a table from a .csv
int getMenuSelection(); // Shows the menu and gets the choice
void printTables(Database &db);

int main() {
	//Initialize the database
	Database * database = new Database();

	//Add the tables
	Table * table = new Table();
	loadData(*table, "chefmozaccepts.csv");
	database->addTable(*table, "Payments");

	table = new Table();
	loadData(*table, "chefmozcuisine.csv");
	database->addTable(*table, "Cuisines");

	table = new Table();
	loadData(*table, "chefmozparking.csv");
	database->addTable(*table, "Parking");

	table = new Table();
	loadData(*table, "geoplaces2.csv");
	database->addTable(*table, "Restaurants");

	table = new Table();
	loadData(*table, "userprofile.csv");
	database->addTable(*table, "Customers");

	table = new Table();
	loadData(*table, "rating_final.csv");
	database->addTable(*table, "Ratings");

	for(;;) {
		int choice = getMenuSelection();
		switch(choice) {
		case 1:
			printTables(*database);
			break;
		case 2:
			break;
		default:
			cout << "Invalid choice" << endl;
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
	cout << "\t" << "1) Print the list of tables" << endl;
	cout << "\t" << "2) Do something else" << endl;
	cout << "\t" << "0) Exit" << endl;
	cout << "Enter your selection (number): ";
	int choice;
	cin >> choice;
	return choice;
}

void printTables(Database &db) {
	vector<Table> tables = db.getTables();
	vector<string> tableNames = db.listTables();
	for(unsigned int i = 0; i < tables.size(); i++) {
		printf("Table number %i is called %s\n", i+1, tableNames[i]);
		printf("----------------------------\n");
		printf("Attributes:\n");
		vector<AttributeList> attributes = tables[i].getAttributes();
		for(unsigned int j = 0; j < attributes.size(); i++) {
			printf("Attribute %i is called %s with type %s\n", j, attributes[j].getName(), attributes[j].getType());
		}
		printf("\n");
	}
}


void loadData(Table& destTable, string filename) {
	//TODO - build a table from the csv file.
	ifstream file = ifstream(filename);
	string line;
	getline(file, line);

	stringstream sstream(line);
	string item;
	//Fill the attributes
	while(getline(sstream, item, ',')) {
		destTable.addAttribute(item, AttributeList::attribute_t::STRING);
	}

	//Fill the table with records
	while(getline(file, line)) {
		Record record = Record();

		stringstream sstream(line);
		string item;
		int index = 0;
		while(getline(sstream, item, ',')) {
			record.setAt(index++, item);
		}

		destTable.insert(record);
	}

	// Close and return
	file.close();
}