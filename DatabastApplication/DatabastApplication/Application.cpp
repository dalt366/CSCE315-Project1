#include "Application.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

int main() {
	//Initialize the database
	Database * database = new Database();

	//Add the tables
	Table * table = new Table();
	Application::loadData(*table, "./data/chefmozaccepts.csv");
	database->addTable(*table, "Payments");

	table = new Table();
	Application::loadData(*table, "./data/chefmozcuisine.csv");
	database->addTable(*table, "Cuisines");

	table = new Table();
	Application::loadData(*table, "./data/chefmozparking.csv");
	database->addTable(*table, "Parking");

	table = new Table();
	Application::loadData(*table, "./data/geoplaces2.csv");
	database->addTable(*table, "Restaurants");

	table = new Table();
	Application::loadData(*table, "./data/userprofile.csv");
	database->addTable(*table, "Customers");

	table = new Table();
	Application::loadData(*table, "./data/rating_final.csv");
	database->addTable(*table, "Ratings");

	for(;;) {
		int choice = Application::getMenuSelection();
		switch(choice) {
		case Application::MENU::EXIT:
			return 0; // Exit program with success code
		case Application::MENU::CUSTOMER_INFO:
			Application::printCustomerInfo(*database);
			break;			
		case Application::MENU::RESTAURANT_INFO:
			Application::printRestaurantInfo(*database);
			break;
		case Application::MENU::RESTAURANT_RATINGS:
			Application::printRestaurantRatings(*database);
			break;
		case Application::MENU::CUSTOMER_BREAKDOWN:
			Application::customerBreakdown(*database);
			break;
		case Application::MENU::CUSTOMER_RATINGS:
			Application::printCustomerRatings(*database);
			break;
		case Application::MENU::CUISINE_TYPES:
			Application::printCuisineTypes(*database);
			break;
		case Application::MENU::RESTAURANT_BY_CUISINE:
			Application::printRestaurantsByCuisine(*database);
			break;
		case Application::MENU::PAYMENT_TYPES:
			Application::printPaymentBreakdown(*database);
		case Application::MENU::PRINT_TABLES:
			Application::printTables(*database);
			break;
		case Application::MENU::PRINT_RECORDS:
			Application::printRecords(*database);
			break;
		default:
			cout << "Invalid choice \n\n" << endl;
		}
	}
}

int Application::getMenuSelection() {
	int choice = 0;
	string input = "";
	cout << "---------" << endl;
	cout << "MAIN MENU" << endl;
	cout << "---------" << endl;
	cout << "\t" << "0)  Exit" << endl;
	cout << "\t" << "1)  Print information about a specific customer" << endl;
	cout << "\t" << "2)  Print information about a specific restaurant" << endl;
	cout << "\t" << "3)  Print ratings for a specific restaurant" << endl;
	cout << "\t" << "4)  Print out a breakdown of a certain customer attribute" << endl;
	cout << "\t" << "5)  Print ratings for a specific customer" << endl;
	cout << "\t" << "6)  Print a breakdown of cuisine types offered by retaurants" << endl;
	cout << "\t" << "7)  Look up restaurants by cuisine type" << endl;
	cout << "\t" << "8)  Print a breakdown of payment types accepted" << endl;
	cout << "\t" << "9)  Print the list of tables" << endl;
	cout << "\t" << "10) Print the records in a table (Warning! A lot of info!)" << endl;
	cout << "Enter your selection (number): ";
	cin >> input;
	choice = atoi(input.c_str());
	return choice;
}

// Prints information about a specific customer
void Application::printCustomerInfo(Database &db) {
	printf("Enter the customer name (case sensitive): ");
	string customerName;
	cin >> customerName;

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
void Application::printRestaurantInfo(Database &db) {
	printf("Enter the restaurant name (case sensitive): ");
	string restaurantName;
	cin.get();
	getline(cin, restaurantName);

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
void Application::printRestaurantRatings(Database &db) {
	printf("Enter the restaurant name (case sensitive): ");
	string restaurantName;
	cin.get();
	getline(cin, restaurantName);

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
	printf("%-15s %%%-14.2f %%%-14.2f %%%-14.2f \n", "Acceptance:", rating/count/2*100, foodRating/count/2*100, serviceRating/count/2*100);
}

// Lists attributes and presents a percentage breakdown based on that attribute
void Application::customerBreakdown(Database &db) {
	vector<Table> tables = db.getTables();
	vector<string> tableNames = db.listTables();
	int i = 0;
	while(tableNames[i].compare("Customers") != 0) {
		i++;
		if(i >= tableNames.size())
			break;
	}

	vector<AttributeList> attributes = tables[i].getAttributes();
	printf("For which attribute would you like to get a percentage break down? \n");
	for(unsigned int i = 0; i < attributes.size(); i++) {
		printf("Attribute %i is \"%s\"\n", i, attributes[i].getName().c_str());
	}

	printf("\nPlease enter your choice(number). The default will be choice 0: ");
	string input;
	int choice;
	cin >> input;
	choice = atoi(input.c_str());
	if(choice < 0 || choice >= attributes.size()) {
		choice = 0;
	}

	map<string, float> frequency;
	int total = 0;
	for(int j = 0; j < tables[i].getSize(); j++) {
		string item = attributes[choice].getAt(j);
		frequency[item] = frequency[item] + 1;
		total++;
	}

	map<string, float>::iterator iter = frequency.begin();
	printf("Here is a percentage breakdown of customer's attribute \"%s\"\n", attributes[choice].getName().c_str());
	while(iter != frequency.end()) {
		printf("%-25s %5.2f%%\n", iter->first.c_str(), iter->second/total*100);
		iter++;
	}
	printf("\n");
}

// Prints all the ratings for a customer based off name.
void Application::printCustomerRatings(Database &db) {	
	printf("Enter the customer name (case sensitive): ");
	string customerName;
	cin >> customerName;

	vector<string> attributes = vector<string>();
	Table queryResult = db.query(attributes, "Ratings", "userID = \"" + customerName + "\"");
	vector<AttributeList> attr_lists = queryResult.getAttributes();
	if(queryResult.getSize() == 0) {
		printf("Rating query failed. \"%s\" has no ratings!\n", customerName.c_str());
		return;
	}
	printf("User %s has rated the following places:\n", customerName.c_str());
	printf("%-15s %-15s %-15s %-15s\n", "placeID", "Rating", "Food Rating", "Service Rating");
	double rating = 0, foodRating = 0, serviceRating = 0, count = 0;
	//Start at 1 to skip the attribute type
	for(int i = 0; i < queryResult.getSize(); ++i) {
		rating += atoi(attr_lists[2].getAt(i).c_str());
		foodRating += atoi(attr_lists[3].getAt(i).c_str());
		serviceRating += atoi(attr_lists[4].getAt(i).c_str());
		count++;
		printf("%-15s %-15s %-15s %-15s \n",  attr_lists[1].getAt(i).c_str(),  attr_lists[2].getAt(i).c_str(),  attr_lists[3].getAt(i).c_str(),  attr_lists[4].getAt(i).c_str());
	}
	printf("%-15s %%%-14.2f %%%-14.2f %%%-14.2f \n", "Acceptance:", rating/count/2*100, foodRating/count/2*100, serviceRating/count/2*100);
}

void Application::printCuisineTypes(Database &db) {
	vector<Table> tables = db.getTables();
	vector<string> tableNames = db.listTables();
	int i = 0;
	while(tableNames[i].compare("Cuisines") != 0) {
		i++;
		if(i >= tableNames.size())
			break;
	}
	vector<AttributeList> attributes = tables[i].getAttributes();

	int choice = 1; // Second column (cuisine type)

	map<string, float> frequency;
	int total = 0;
	printf("Working");
	for(int j = 0; j < tables[i].getSize(); j++) {
		string item = attributes[choice].getAt(j);
		frequency[item] = frequency[item] + 1;
		total++;
		if(j%30 == 0)
			printf(".");
	}
	printf("\n");

	map<string, float>::iterator iter = frequency.begin();
	printf("Here is a percentage breakdown of cuisine types\n", attributes[choice].getName().c_str());
	while(iter != frequency.end()) {
		printf("%-25s %5.2f%% - %.0f out of %i \n", iter->first.c_str(), iter->second/total*100, iter->second, total);
		iter++;
	}
	printf("\n");
	printf("Would you like to see restaurants for a specific cuisine type? (yes/no): ");
	string option;
	cin >> option;
	if(option.compare("yes") == 0) {
		Application::printRestaurantsByCuisine(db);
	}
}

void Application::printRestaurantsByCuisine(Database &db) {	
	printf("What type of cuisine do you want to search for (case sensitive): ");
	string cuisineType;
	cin >> cuisineType;

	vector<string> attributes = vector<string>();
	Table queryResult = db.query(attributes, "Cuisines", "Rcuisine = \"" + cuisineType + "\"");
	vector<AttributeList> attr_lists = queryResult.getAttributes();
	if(queryResult.getSize() == 0) {
		printf("Cuisine query failed. \"%s\" must not be a cuisine type!\n", cuisineType.c_str());
		return;
	}
	

	// Buggy. This should work but doesn't for some reason. Problem with query() ?
	printf("Here is a list of restaurants that have \"%s\" cuisine. \n", cuisineType.c_str());
	for (int i = 0; i < queryResult.getSize(); ++i) {
		Table smallQuery = db.query(attributes, "Restaurants", "placeID = \"" + attr_lists[0].getAt(i) + "\"");
		vector<AttributeList> result = smallQuery.getAttributes();
		if(smallQuery.getSize() != 0)
			printf("%s, ", result[0].getAt(0).c_str());
		else
			printf("%s, ", attr_lists[0].getAt(i).c_str());
	}
	printf("\n");
	printf("Would you like to get information for a specific restaurant? (yes/no): ");
	string option;
	cin >> option;
	if(option.compare("yes") == 0) {
		Application::printRestaurantInfo(db);
	}
}

void Application::printPaymentBreakdown(Database &db) {
	vector<Table> tables = db.getTables();
	vector<string> tableNames = db.listTables();
	int i = 0;
	while(tableNames[i].compare("Payments") != 0) {
		i++;
		if(i >= tableNames.size())
			break;
	}

	vector<AttributeList> attributes = tables[i].getAttributes();
	printf("Working.");
	map<string, float> frequency;
	int total = 0;
	for(int j = 0; j < tables[i].getSize(); j++) {
		string item = attributes[1].getAt(j);
		frequency[item] = frequency[item] + 1;
		if(j%50 == 0) {
			printf(".");
		}
		if(j>0) {
			if(attributes[0].getAt(j-1).compare(attributes[0].getAt(j)) != 0) {
				total++;
			}
		}
	}

	printf("\n");

	map<string, float>::iterator iter = frequency.begin();
	printf("Here is a percentage breakdown of payment types:\n");
	while(iter != frequency.end()) {
		printf("%5.2f%% of restaurants accept \"%s\"\n", iter->second/total*100, iter->first.c_str());
		iter++;
	}
	printf("\n");
}

// Used for debug purposes
void Application::printRecords(Database &db) {
	printf("Enter the table name: ");
	string tableName;
	cin >> tableName;
	cin.get();
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
			printf("Record number %i\n", i+1);
			printf("----------------\n");
			for (unsigned int j = 0; j < attr_lists.size(); ++j) {
				printf("%-20s: %s \n", attr_lists[j].getName().c_str(), attr_lists[j].getAt(i).c_str());
			}
			printf("Press enter to see the next record...\n");
			cin.get();
		}
	}
}

// Used for debug purposes
void Application::printTables(Database &db) {
	cin.get();
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
		printf("Press enter to see the next table...\n");
		cin.get();
	}
}


void Application::loadData(Table& destTable, string filename) {
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