#include "Record.h"
#ifndef TABLE_H
#define TABLE_H

class __declspec(dllexport) Table {	
public:
	enum Type {INT, FLOAT, string, DATE};

	Table();
	Table(const Table &in);
	Table(std::list<std::string>*, std::list<Type>*);
	~Table();

	void addAttribute(std::string name, Type type);
	bool deleteAttribute(std::string name);
	void insertRecord(Record record);
	std::list<std::string> getAttributes(); // returns a std::list of the form "type attribute"
	unsigned int getSize();
	bool renameAttribute(std::string oldName, std::string newName);
	Table crossJoin(Table firstTable, Table secondTable);
	std::list<Record> getRecords() const;
	std::list<std::string> getFields() const;
	std::list<Type> getTypes() const;

	float getSum(std::string attributeName);
	int getCount(std::string attributeName);
	float getMin(std::string attributeName);
	float getMax(std::string attributeName);

	double stringToDouble(std::string _string);

private:
	std::list<std::string> fields;
	std::list<Record> records;
	std::list<Type> types; // Used to keep track of the data types of records
};

#endif
