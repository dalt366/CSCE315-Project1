#include <list>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>

#ifndef RECORD_H
#define RECORD_H

class __declspec(dllimport) Record {
public:
	Record();
	Record(const Record &in);
	Record(std::list<std::string>* _initialValues);
	~Record();

   std::string* accessRecordEntry(int entry);
   void modifyRecordEntry(int entry, std::string newEntryValue);
   std::string retrieveRecordEntry(int entry) const;
   unsigned getNumEntries() const;
   
private:
	std::list<std::string> tuple;
};

#endif
