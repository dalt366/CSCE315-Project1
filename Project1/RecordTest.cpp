#include "Record.h"
#include <iostream>

int main(){

	string exit;
	vector<string> entries;

	entries.push_back("HEY THERE");

	entries.push_back("TEST123" );

	Record record(entries);

	cout << record.getEntryRow(0) << endl;


	cin >> exit;



}