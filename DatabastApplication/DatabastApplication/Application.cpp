#include "Database.h"
#include <fstream>
#include <iostream>

using namespace std;

Table loadData(string filename); // Loads a table from a .csv
int getMenuSelection(); // Shows the menu and gets the choice

int main() {
	//Initialize the database
	Database database = Database();

	//Add the tables
	database.addTable(loadData("chefmozaccepts.csv"), "Payments");
	database.addTable(loadData("chefmozcuisine.csv"), "Cuisines");
	database.addTable(loadData("chefmozparking.csv"), "Parking");
	database.addTable(loadData("geoplaces2.csv"), "Restaurants");
	database.addTable(loadData("userprofile.csv"), "Customers");
	database.addTable(loadData("rating_final.csv"), "Ratings");

	for(;;) {
		int choice = getMenuSelection();
		switch(choice) {
		case 1:
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
	cout << "\t" << "1) Do cool stuff" << endl;
	cout << "\t" << "2) Do something else" << endl;
	cout << "\t" << "0) Exit" << endl;
	cout << "Enter your selection (number): ";
	int choice;
	cin >> choice;
	return choice;
}


Table loadData(string filename) {
	//TODO - build a table from the csv file.
	ifstream file = ifstream(filename);
	Table table = Table();
	string line;
	getline(file, line);

	//Fill the attributes
	stringstream sstream(line);
	string item;
	while(getline(sstream, item, ',')) {
		table.addAttribute(item, Table::Type::string);
	}

	//Fill the table with records
	while(getline(file, line)) {
		Record record = Record();

		stringstream sstream(line);
		string item;
		int index = 0;
		while(getline(sstream, item, ',')) {
			record.modifyRecordEntry(index++, item);
		}

		table.insertRecord(record);
	}

	// Close and return
	file.close();
	return table;
}