#include "API.h"

class Application {
public:
	static int getMenuSelection(); // Shows the menu and gets the choice
	static void loadData(Table& destTable, string filename); // Loads a table from a .csv
	static void printTables(Database &db);
	static void printRecords(Database &db);
	static void printCustomerInfo(Database &db);
	static void printRestaurantInfo(Database &db);
	static void printRestaurantRatings(Database &db);
	static void customerBreakdown(Database &db);
	static void printCustomerRatings(Database &db);
	static void printCuisineTypes(Database &db);
	static void printRestaurantsByCuisine(Database &db);
	static void printPaymentBreakdown(Database &db);
	enum MENU { EXIT, CUSTOMER_INFO, RESTAURANT_INFO, RESTAURANT_RATINGS, CUSTOMER_BREAKDOWN, CUSTOMER_RATINGS, CUISINE_TYPES, RESTAURANT_BY_CUISINE, PAYMENT_TYPES, PRINT_TABLES, PRINT_RECORDS };
};