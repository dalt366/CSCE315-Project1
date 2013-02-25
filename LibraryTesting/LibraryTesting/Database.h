#include "Table.h"
#ifndef DATABASE_H
#define DATABASE_H

#define TOKEN_KIND_OP 'o'
#define TOKEN_KIND_NUM '8'
#define TOKEN_KIND_ATT 'a'
#define TOKEN_KIND_VAL 'v'
#define TOKEN_KIND_LOG 'l'

class __declspec(dllimport)  Database {
private:
	class Token;

public:
	Database();
	Database(const Database&);
	~Database();

	void addTable(Table table, std::string name);
	void dropTable(std::string tableName);
	std::list<std::string> listTables();
	std::list<Table> getTables() const;
	std::list<std::string> getNames() const;
	Table query(std::list<std::string> tableAttributes ,std::string tableName, std::string whereArgument);
	void deleteRecord(std::string tableName, std::string whereArgument);
	double stringToDouble(std::string);

	// Parser functions
	enum token { eq, neq, lt, lte, gt, gte, and, or, not};
	std::vector<Token> vectorToken;

private:
	std::list<std::string> tableNames;
	std::list<Table> tables;
	bool doesRecordPass(std::list<std::string> attributes, Record record, std::vector<Token> vectorToken);
};

class Database::Token {
public:
	char kind;
	double value;
	std::string name;
	bool check;
	token op;
	Token() {}
	Token(char ch) :kind(ch), value(0) { }
	Token(char ch, double val) :kind(ch), value(val) { }
	Token(char ch, std::string n) :kind(ch), name(n) { }
	Token(char ch, bool b) :kind(ch), check(b) {}
	Token(char ch, token n) :kind(ch), op(n) {}
};

#endif
