#include "Database.h"
#include <fstream>
#include <iostream>

using namespace std;

Table loadData(string filename); 

int main() {
	//Initialize the database
	Database database = Database();

	//Add the tables
	database.addTable(loadData("userprofile.csv"), "Customers");
}

Table loadData(string filename) {
	//TODO - build a table from the csv file.
	Table table = Table();
	return table;
}