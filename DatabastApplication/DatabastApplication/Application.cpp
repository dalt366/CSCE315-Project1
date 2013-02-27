#include "API.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

void loadData(Table& destTable, string filename); // Loads a table from a .csv
int getMenuSelection(); // Shows the menu and gets the choice
void printTables(Database &db);
void printRecords(Database &db, string tableName);
void printCustomerInfo(Database &db, string customerName);
void printRestaurantInfo(Database &db, string restaurantName);
void printRestaurantRatings(Database &db, string restaurantName);
enum MENU { EXIT, CUSTOMER_INFO, RESTAURANT_INFO, RESTAURANT_RATINGS };

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
		case -1:
			{
				printTables(*database);
				break;
			}
		case -2:
			{
				printf("Enter the table name: ");
				string tableName;
				cin >> tableName;
				printRecords(*database, tableName);
				break;
			}
		case MENU::EXIT:
			{
				return 0; // Success
			}
		case MENU::CUSTOMER_INFO:
			{
				printf("Enter the customer name: ");
				string customerName;
				cin >> customerName;
				printCustomerInfo(*database, customerName);
				break;
			}
		case MENU::RESTAURANT_INFO:
			{
				printf("Enter the restaurant name: ");
				string restaurantName;
				cin.get();
				getline(cin, restaurantName);
				printRestaurantInfo(*database, restaurantName);
				break;
			}
		case MENU::RESTAURANT_RATINGS:
			{
				printf("Enter the restaurant name: ");
				string restaurantName;
				cin.get();
				getline(cin, restaurantName);
				printRestaurantRatings(*database, restaurantName);
				break;
			}
		default:
			{
				cout << "Invalid choice \n\n" << endl;
			}
		}
	}
}

int getMenuSelection() {
	int choice = 0;
	string input = "";
	cout << "MAIN MENU" << endl;
	cout << "---------" << endl;
	cout << "\t" << "1) Print information about a specific customer" << endl;
	cout << "\t" << "2) Print information about a specific restaurant" << endl;
	cout << "\t" << "3) Print ratings for a sepcific restaurant" << endl;
	cout << "\t" << "0) Exit" << endl;
	cout << "\t" << "-1) Print the list of tables (DEBUG)" << endl; //Currently for debug purposes
	cout << "\t" << "-2) Print the records in a table (DEBUG)" << endl; //Currently for debug purposes
	cout << "Enter your selection (number): ";
	cin >> input;
	choice = atoi(input.c_str());
	return choice;
}

// Prints information about a specific customer
void printCustomerInfo(Database &db, string customerName) {
	vector<string> attributes = vector<string>();
	Table queryResult = db.query(attributes, "Customers", "userID = \"" + customerName + "\"");
	vector<AttributeList> attr_lists = queryResult.getAttributes();
	if(queryResult.getSize() == 0) {
		printf("Customer \"%s\" could not be found\n", customerName.c_str());
		return;
	}
	for (int i = 0; i < queryResult.getSize(); ++i) {
		for (unsigned int j = 0; j < attr_lists.size(); ++j) {
			printf("%-17s %s \n", attr_lists[j].getName().c_str(),  attr_lists[j].getAt(i).c_str());
		}
		printf("\n");
	}
	return;
}

// Print information about a sepcific restaurant
void printRestaurantInfo(Database &db, string restaurantName) {
	vector<string> attributes = vector<string>();
	Table queryResult = db.query(attributes, "Restaurants", "(name = \"" + restaurantName + "\") OR (placeID = \"" + restaurantName + "\")");
	vector<AttributeList> attr_lists = queryResult.getAttributes();
	if(queryResult.getSize() == 0) {
		printf("Restaurant \"%s\" could not be found\n", restaurantName.c_str());
		return;
	}
	for (int i = 0; i < queryResult.getSize(); ++i) {
		for (unsigned int j = 0; j < attr_lists.size(); ++j) {
			printf("%-17s %s \n", attr_lists[j].getName().c_str(),  attr_lists[j].getAt(i).c_str());
		}
		printf("\n");
	}
	return;
}

// Prints all the ratings for a restaurant based off name.
// It grabs the placeID from Restaurants table then querys the Ratings table with the ID
void printRestaurantRatings(Database &db, string restaurantName) {
	vector<string> attributes = vector<string>();
	attributes.push_back("placeID");
	attributes.push_back("name");
	Table queryResult = db.query(attributes, "Restaurants", "name = \"" + restaurantName + "\"");
	vector<AttributeList> attr_lists = queryResult.getAttributes();
	if(queryResult.getSize() == 0) {
		printf("Restaurant \"%s\" could not be found\n", restaurantName.c_str());
		return;
	}
	string placeID = attr_lists[0].getAt(0);
	//printf("Found placeID %s", placeID.c_str());
	attributes.clear();
	queryResult = db.query(attributes, "Ratings", "placeID = \"" + placeID + "\"");
	attr_lists = queryResult.getAttributes();
	if(queryResult.getSize() == 0) {
		printf("Rating query failed. \"%s\" has no ratings!\n", restaurantName.c_str());
		return;
	}
	printf("%-15s %-15s %-15s %-15s\n", "userID", "Rating", "Food Rating", "Service Rating");
	double rating = 0, foodRating = 0, serviceRating = 0, count = 0;
	//Start at 1 to skip the attribute type
	for(int i = 0; i < queryResult.getSize(); ++i) {
		rating += atoi(attr_lists[2].getAt(i).c_str());
		foodRating += atoi(attr_lists[3].getAt(i).c_str());
		serviceRating += atoi(attr_lists[4].getAt(i).c_str());
		count++;
		printf("%-15s %-15s %-15s %-15s \n",  attr_lists[0].getAt(i).c_str(),  attr_lists[2].getAt(i).c_str(),  attr_lists[3].getAt(i).c_str(),  attr_lists[4].getAt(i).c_str());
	}
	printf("%-15s %%%-14f %%%-14f %%%-14f \n", "Acceptance:", rating/count/2*100, foodRating/count/2*100, serviceRating/count/2*100);
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
		printf("Table \"%s\" not found \n", tableName.c_str());
		return;
	}
	else {
		Table table = db.getTables()[index];
		vector<AttributeList> attr_lists = table.getAttributes();
		for (int i = 0; i < table.getSize(); ++i) {
			for (unsigned int j = 0; j < attr_lists.size(); ++j) {
				printf("%s ", attr_lists[j].getAt(i).c_str());
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
		stringstream sstream(line);
		vector<string> items = vector<string>();
		string item = "";
		int index = 0;
		while(getline(sstream, item, ',')) {
			//printf("Loading item %s \n", (*item).c_str());
			items.push_back(item);
			//printf("Loaded item %s \n", record->getAt(0));
		}

		destTable.insert(Record(items));
	}

	// Close and return
	file.close();
}