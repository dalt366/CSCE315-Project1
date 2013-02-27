#ifdef DBDLL_EXPORTS
#define DBDLL_API __declspec(dllexport) 
#else
#define DBDLL_API __declspec(dllimport) 
#endif

#ifndef _RECORD_H_
#define _RECORD_H_

#include <vector>
#include <string>
using namespace std;

//Relies on the user to keep the strings ordered properly
class DBDLL_API Record {

public:

	Record();

	//The Record must have a vector to specify its ordering.
	Record(const vector<string>& theData);

	//Input: Takes the index of the value to be retrieved
	//Output: Returns the value at index
	string getAt(int index) const;

	//Input: Takes the index of the value to be changed
	//Output: Whether the operation succeeded
	bool setAt(int index, const string& newValue);

	//Input: None
	//Output: The amount of elements in the Record
	int size(void) const;
private:

	vector<string> data;
};

#endif _RECORD_H_
