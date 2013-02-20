#include "Database.h"
#include <vector>
#include <string>
#include "CppUnitTest.h"

using namespace std;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Team8TestCode
{		
	TEST_CLASS(UnitTest1)
	{
	public:

		//Record
		/* Tests for creation of a record with 1 entry passed as argument */
		TEST_METHOD(RecordEntryTest1){
			vector<string> ent2;
			ent2.push_back("test");
			Record r(ent2);
			//do column numbers start at 1 or 0?
			Assert::AreEqual<string>(r.getEntry(0),"test");
		}

		/* Tests for the modification of a record entry */
		TEST_METHOD(RecordModificationTest1){
			vector<string> ent2;
			ent2.push_back("test");
			Record r(ent2);
			//do column numbers start at 1 or 0?
			r.modifyEntry(0,"test2");
			Assert::AreEqual<string>(r.getEntry(0),"test2");
		}

		/* Tests for the modification of a record entry, size 2 */
		TEST_METHOD(RecordModificationTest2){
			vector<string> ent2;
			ent2.push_back("test");
			ent2.push_back("test2");
			Record r(ent2);
			//do column numbers start at 1 or 0?
			r.modifyEntry(1,"test3");
			Assert::AreEqual<string>(r.getEntry(1),"test3");
		}

		//End of record

		// Tests that the default constructor makes a table of size 0 records
		TEST_METHOD(TableSizeTest1){
			Table t;
			Assert::AreEqual(t.getSize(), 0);
		}

		// Tests the default constructor, attribute size = 0
		TEST_METHOD(TableAttributeSizeTest1){
			Table t;
			Assert::AreEqual(t.getAttributes().size(),(size_t) 0);
		}

		// Tests that the constructor correctly sets the size
		TEST_METHOD(TableSizeTest2){ //constructor test?
			map<string, Table::TYPE> m;
			m["School"] = Table::TYPE::STRING;
			Table t(m);
			Assert::AreEqual(t.getSize(), 0);
		}

		// Test attributes size
		TEST_METHOD(TableAttributeSizeTest2){ //constructor test?
			map<string, Table::TYPE> m;
			m["School"] = Table::TYPE::STRING;
			Table t(m);
			Assert::AreEqual(t.getAttributes().size(),(size_t) 1);
		}

		// Test attribute size with add function
		TEST_METHOD(TableAddAttributeTest1){ //add function test?
			Table t;
			t.add("Number", Table::INT);
			Assert::AreEqual(t.getAttributes().size(),(size_t) 1);
		}

		// Test attribute size with add function, on table created with map constructor
		TEST_METHOD(TableAddAttributeTest2){
			map<string, Table::TYPE> m;
			m["School"] = Table::TYPE::STRING;
			Table t(m);
			t.add("Number", Table::INT);
			Assert::AreEqual(t.getAttributes().size(),(size_t) 2);
		}

		// Test add attribute with STRING type
		TEST_METHOD(TableAddAttributeTest3){
			Table t;
			t.add("String", Table::TYPE::STRING);
			string s = "false";
			if(t.getAttributes()["String"] == Table::TYPE::STRING) s = "true";
			Assert::AreEqual<string>(s, "true");
		}

		// Test add attribute with INT type
		TEST_METHOD(TableAddAttributeTest4){
			Table t;
			t.add("Int", Table::TYPE::INT);
			string s = "false";
			if(t.getAttributes()["Int"] == Table::TYPE::INT) s = "true";
			Assert::AreEqual<string>(s, "true");
		}

		// Test add attribute with FLOAT type
		TEST_METHOD(TableAddAttributeTest5){
			Table t;
			t.add("Float", Table::TYPE::FLOAT);
			string s = "false";
			if(t.getAttributes()["Float"] == Table::TYPE::FLOAT) s = "true";
			Assert::AreEqual<string>(s, "true");
		}

		// Test add attribute with DATE type
		TEST_METHOD(TableAddAttributeTest6){
			Table t;
			t.add("Date", Table::TYPE::DATE);
			string s = "false";
			if(t.getAttributes()["Date"] == Table::TYPE::DATE) s = "true";
			Assert::AreEqual<string>(s, "true");
		}

		// Test add and delete on default constructor
		TEST_METHOD(TableDeleteTest1){ //m does nothing here - removed, added add function
			Table t;
			t.add("School", Table::STRING);
			t.deleteFunction("School");
			Assert::AreEqual(t.getAttributes().size(),(size_t) 0);
		}

		// Test add and delete on table with two attributes (default constructor)
		TEST_METHOD(TableDeleteTest2){//m does nothing here - commented, add School
			Table t;
			t.add ("School",Table::STRING);
			t.add("Number", Table::INT);
			t.deleteFunction("School");
			Assert::AreEqual(t.getAttributes().size(),(size_t) 1);
		}

		// Test delete on table with one attribute, (map constructor)
		TEST_METHOD(TableDeleteTest3){ //same as above
			map<string, Table::TYPE> m;
			m["Number"] = Table::TYPE::INT;
			Table t(m);
			t.deleteFunction("Number");
			Assert::AreEqual(t.getAttributes().size(),(size_t) 0);
		}

		// Test delete on table with two attributes, (map constructor)
		TEST_METHOD(TableDeleteTest4){ //same as above
			map<string, Table::TYPE> m;
			m["School"] = Table::TYPE::STRING;
			m["Number"] = Table::TYPE::INT;
			Table t(m);
			t.deleteFunction("Number");
			Assert::AreEqual(t.getAttributes().size(),(size_t) 1);
		}

		// Test if delete deletes properly
		TEST_METHOD(TableDeleteTest5){
			map<string, Table::TYPE> m;
			m["School"] = Table::TYPE::STRING;
			m["Number"] = Table::TYPE::INT;
			Table t(m);
			t.deleteFunction("Number");
			string s = "false";
			if(t.getAttributes().count("Number") > 0) s = "true";
			Assert::AreEqual<string>(s,"false");
		}

		// Test table insert
		TEST_METHOD(TableInsertTest1){
			map<string, Table::TYPE> m;
			m["School"] = Table::TYPE::STRING;
			Table t(m);
			vector<string> vec;
			vec.push_back("TAMU");
			Record r(vec);
			t.insert(r);
			Assert::AreEqual(t.getSize(), 1);
		}

		// Test table insert size 2
		TEST_METHOD(TableInsertTest2){
			map<string, Table::TYPE> m;
			m["School"] = Table::TYPE::STRING;
			m["Number"] = Table::TYPE::INT;
			Table t(m);
			vector<string> vec;
			vec.push_back("TAMU");
			vec.push_back("42");
			Record r(vec);
			t.insert(r);
			Assert::AreEqual(t.getSize(), 2);
		}

		// Test that the entry inserted is correct
		TEST_METHOD(TableInsertTest3){
			map<string, Table::TYPE> m;
			m["School"] = Table::TYPE::STRING;
			Table t(m);
			vector<string> vec;
			vec.push_back("TAMU");
			Record r(vec);
			t.insert(r);
			//addressing starts at 0 or 1?
			Assert::AreEqual<string>(t.getRecord(0).getEntry(0), "TAMU");
		}

		// Test that the entry inserted is correct (size 2)
		TEST_METHOD(TableInsertTest4){
			map<string, Table::TYPE> m;
			m["School"] = Table::TYPE::STRING;
			m["Number"] = Table::TYPE::INT;
			Table t(m);
			vector<string> vec;
			vec.push_back("TAMU");
			vec.push_back("42");
			Record r(vec);
			t.insert(r);
			//addressing starts at 0 or 1?
			Assert::AreEqual<string>(t.getRecord(0).getEntry(1), "42");
		}

		// Test that the entry inserted is correct (add() method, size 1)
		TEST_METHOD(TableInsertTest5){
			Table t;
			t.add("String", Table::TYPE::STRING);
			vector<string> vec;
			vec.push_back("Test");
			Record r(vec);
			t.insert(r);
			//addressing starts at 0 or 1?
			Assert::AreEqual<string>(t.getRecord(0).getEntry(0), "Test");
		}

		// Test that the entry inserted is correct (add() method, size 2)
		TEST_METHOD(TableInsertTest6){
			Table t;
			t.add("String", Table::TYPE::STRING);
			t.add("Num", Table::TYPE::INT);
			vector<string> vec;
			vec.push_back("Test");
			vec.push_back("99");
			Record r(vec);
			t.insert(r);
			//addressing starts at 0 or 1?
			Assert::AreEqual<string>(t.getRecord(0).getEntry(1), "99");
		}

		// Test that the entry inserted is correct (add() method, size 2)
		TEST_METHOD(TableInsertTest7){
			Table t;
			t.add("String", Table::TYPE::STRING);
			t.add("Date", Table::TYPE::DATE);
			vector<string> vec;
			vec.push_back("Test");
			vec.push_back("1980/07/07");
			Record r(vec);
			t.insert(r);
			//addressing starts at 0 or 1?
			Assert::AreEqual<string>(t.getRecord(0).getEntry(1), "1980/07/07");
		}

	/*Table size checks for multiple records*/

		/*Test of 3 record elements*/
		TEST_METHOD(tableSize_3elem){
			map<string, Table::TYPE> m;
			m["Student"] = Table::TYPE::STRING;
			Table t(m);
			vector<string> vec;
			vec.push_back("Bob");
			Record r(vec);
			t.insert(r);
			vector<string> vec2;
			vec2.push_back("Bill");
			Record r2(vec2);
			t.insert(r2);
			vector<string> vec3;
			vec3.push_back("Jill");
			Record r3(vec3);
			t.insert(r3);
			Assert::AreEqual(t.getSize(), 3); 
		}

		/*Test of 2 record elements*/
		TEST_METHOD(tableSize_2elem){
			map<string, Table::TYPE> m;
			m["School"] = Table::TYPE::STRING;
			Table t(m);
			vector<string> vec;
			vec.push_back("TAMU");
			Record r(vec);
			t.insert(r);
			vector<string> vec2;
			vec2.push_back("TU");
			Record r2(vec2);
			t.insert(r2);
			Assert::AreEqual(t.getSize(), 2); 
		}

		/*Test of 1 record elements*/
		TEST_METHOD(tableSize_1elem){
			map<string, Table::TYPE> m;
			m["School"] = Table::TYPE::STRING;
			Table t(m);
			vector<string> vec;
			vec.push_back("TAMU");
			Record r(vec);
			t.insert(r);
			Assert::AreEqual(t.getSize(), 1); 
		}
	/*tests for renameAttribute*/

		/*1 Attribute, 1 record*/
		TEST_METHOD(renameAttribute1){
			map<string, Table::TYPE> m;
			m["School"] = Table::TYPE::STRING;
			Table t(m);
			vector<string> vec;
			vec.push_back("school1");
			Record r(vec);
			t.insert(r);
			t.renameAttribute("School", "Place");
			string s = "false";
			if(t.getAttributes()["Place"] == Table::TYPE::STRING) s = "true";
			Assert::AreEqual<string>(s, "true"); //not too sure about this
		}

		/*1 Attribute, 1 record*/
		TEST_METHOD(renameAttribute2){
			map<string, Table::TYPE> m;
			m["School"] = Table::TYPE::STRING;
			Table t(m);
			vector<string> vec;
			vec.push_back("school1");
			Record r(vec);
			t.insert(r);
			t.renameAttribute("School", "Place");
			string s = "false";
			if(t.getAttributes().count("Place") > 0) s = "true";
			Assert::AreEqual<string>(s, "true");
		}

		// 1 Attribute, 1 record
		TEST_METHOD(renameAttribute3){
			map<string, Table::TYPE> m;
			m["School"] = Table::TYPE::STRING;
			Table t(m);
			vector<string> vec;
			vec.push_back("school1");
			Record r(vec);
			t.insert(r);
			t.renameAttribute("School", "Place");
			string s = "false";
			if(t.getAttributes().count("School") > 0) s = "true";
			Assert::AreEqual<string>(s, "false");
		}

		/*1 Attribute, 0 records*/
		TEST_METHOD(renameAttribute4){
			map<string, Table::TYPE> m;
			m["School"] = Table::TYPE::STRING;
			Table t(m);
			t.renameAttribute("School", "Place");
			string s = "false";
			if(t.getAttributes()["Place"] == Table::TYPE::STRING) s = "true";
			Assert::AreEqual<string>(s, "true"); //not too sure about this
		}

		/*1 Attribute, 0 records*/
		TEST_METHOD(renameAttribute5){
			map<string, Table::TYPE> m;
			m["School"] = Table::TYPE::STRING;
			Table t(m);
			t.renameAttribute("School", "Place");
			string s = "false";
			if(t.getAttributes().count("Place") > 0) s = "true";
			Assert::AreEqual<string>(s, "true");
		}

		// 1 Attribute, 0 records
		TEST_METHOD(renameAttribute6){
			map<string, Table::TYPE> m;
			m["School"] = Table::TYPE::STRING;
			Table t(m);
			t.renameAttribute("School", "Place");
			string s = "false";
			if(t.getAttributes().count("School") > 0) s = "true";
			Assert::AreEqual<string>(s, "false");
		}

		/*2 Attributes, 0 records*/
		TEST_METHOD(renameAttribute7){
			map<string, Table::TYPE> m;
			m["Number"] = Table::TYPE::INT;
			m["School"] = Table::TYPE::STRING;
			Table t(m);
			t.renameAttribute("School", "Place");
			string s = "false";
			if(t.getAttributes()["Place"] == Table::TYPE::STRING) s = "true";
			Assert::AreEqual<string>(s, "true"); //not too sure about this
		}

		/*2 Attributes, 0 records*/
		TEST_METHOD(renameAttribute8){
			map<string, Table::TYPE> m;
			m["Number"] = Table::TYPE::INT;
			m["School"] = Table::TYPE::STRING;
			Table t(m);
			t.renameAttribute("School", "Place");
			string s = "false";
			if(t.getAttributes().count("Place") > 0) s = "true";
			Assert::AreEqual<string>(s, "true");
		}

		// 2 Attributes, 0 records
		TEST_METHOD(renameAttribute9){
			map<string, Table::TYPE> m;
			m["Number"] = Table::TYPE::INT;
			m["School"] = Table::TYPE::STRING;
			Table t(m);
			t.renameAttribute("School", "Place");
			string s = "false";
			if(t.getAttributes().count("School") > 0) s = "true";
			Assert::AreEqual<string>(s, "false");
		}

	/*Test of cross join function for two tables*/
		
		/*Same size tables - Record size check*/
		TEST_METHOD(crossJoin_SameSizeR){ 
			map<string, Table::TYPE> m;
			m["School"] = Table::TYPE::STRING;
			Table t(m);
			vector<string> vec;
			vec.push_back("TAMU");
			Record r(vec);
			t.insert(r);
			map<string, Table::TYPE> m1;
			m1["Student"] = Table::TYPE::STRING;
			Table t1(m1);
			vector<string> vec1;
			vec1.push_back("John");
			Record r1(vec1);
			t1.insert(r1);
			Table t3;
			t3.crossJoin(t, t1);
			Assert::AreEqual(t3.getSize(), 1); //should only be one: (TAMU, John)? 
		}

		/*Same size tables - Attribute size check*/
		TEST_METHOD(crossJoin_SameSizeA){ 
			map<string, Table::TYPE> m;
			m["School"] = Table::TYPE::STRING;
			Table t(m);
			vector<string> vec;
			vec.push_back("TAMU");
			Record r(vec);
			t.insert(r);
			vector<string> vec2;
			vec2.push_back("TU");
			Record r2(vec2);
			t.insert(r2);
			map<string, Table::TYPE> m1;
			m1["Student"] = Table::TYPE::STRING;
			Table t1(m1);
			vector<string> vec3;
			vec3.push_back("John");
			Record r3(vec3);
			t1.insert(r3);
			vector<string> vec4;
			vec4.push_back("Jill");
			Record r4(vec4);
			t1.insert(r4);
			Table t3;
			t3.crossJoin(t, t1);
			Assert::AreEqual(t.getAttributes().size(),(size_t) 4); //(tamu, john), (tamu, jill), (tu, john), (tu, jill)
		}

		/*Different sized tables - Record size check*/
		TEST_METHOD(crossJoin_DifferentSizeR){ 
			map<string, Table::TYPE> m;
			m["School"] = Table::TYPE::STRING;
			Table t(m);
			vector<string> vec;
			vec.push_back("TAMU");
			Record r(vec);
			t.insert(r);
			vec.clear();
			vec.push_back("TU");
			Record r2(vec);
			t.insert(r2);
			vec.clear();
			vec.push_back("Baylor");
			Record r3(vec);
			t.insert(r3);
			vec.clear();
			vec.push_back("ACU");
			Record r4(vec);
			t.insert(r4);
			map<string, Table::TYPE> m1;
			m1["Student"] = Table::TYPE::STRING;
			Table t1(m1);
			vector<string> vec1;
			vec1.push_back("John");
			Record r5(vec1);
			t1.insert(r5);
			vec1.clear();
			vec1.push_back("Bob");
			Record r6(vec1);
			t1.insert(r6);
			vec1.clear();
			vec1.push_back("Bill");
			Record r7(vec1);
			t1.insert(r7);
			Table t3;
			t3.crossJoin(t, t1);
			Assert::AreEqual(t3.getSize(), 12);  //size = sizeof(table1) * sizeof(table2) 
		}
		/*Different sized tables - Attribute size check*/
		TEST_METHOD(crossJoin_DifferentSizeA){
			map<string, Table::TYPE> m;
			m["School"] = Table::TYPE::STRING;
			Table t(m);
			vector<string> vec;
			vec.push_back("TAMU");
			Record r(vec);
			t.insert(r);
			vec.clear();
			vec.push_back("TU");
			Record r2(vec);
			t.insert(r2);
			vec.clear();
			vec.push_back("Baylor");
			Record r3(vec);
			t.insert(r3);
			vec.clear();
			vec.push_back("ACU");
			Record r4(vec);
			t.insert(r4);
			map<string, Table::TYPE> m1;
			m1["Student"] = Table::TYPE::STRING;
			Table t1(m1);
			vector<string> vec1;
			vec1.push_back("John");
			Record r5(vec1);
			t1.insert(r5);
			vec1.clear();
			vec1.push_back("Bob");
			Record r6(vec1);
			t1.insert(r6);
			vec1.clear();
			vec1.push_back("Bill");
			Record r7(vec1);
			t1.insert(r7);
			Record r1(vec1);
			t1.insert(r1);
			Table t3;
			t3.crossJoin(t, t1);
			Assert::AreEqual(t3.getAttributes().size(),(size_t) 2);  //numAttributes = numAtt(table1) + numAtt(table2)
		}

				/*1 full, 1 empty - Record size check*/
		TEST_METHOD(crossJoin_FullEmptyR1){ 
			map<string, Table::TYPE> m;
			m["School"] = Table::TYPE::STRING;
			Table t(m);
			vector<string> vec;
			vec.push_back("TAMU");
			Record r(vec);
			t.insert(r);
			map<string, Table::TYPE> m1;
			m1["Student"] = Table::TYPE::STRING;
			Table t1(m1);
			Table t3;
			t3.crossJoin(t, t1);
			Assert::AreEqual(t3.getSize(), 0); //Cross join with empty table should yield 0 records 
		}

		/*1 full, 1 empty - Attribute size check*/
		TEST_METHOD(crossJoin_FullEmptyA1){ 
			map<string, Table::TYPE> m;
			m["School"] = Table::TYPE::STRING;
			Table t(m);
			vector<string> vec;
			vec.push_back("TAMU");
			Record r(vec);
			t.insert(r);
			vector<string> vec2;
			vec2.push_back("TU");
			Record r2(vec2);
			t.insert(r2);
			map<string, Table::TYPE> m1;
			m1["Student"] = Table::TYPE::STRING;
			Table t1(m1);
			Table t3;
			t3.crossJoin(t, t1);
			Assert::AreEqual(t.getAttributes().size(),(size_t) 2); //Cross join with empty table should yield sum of attributes
		}

		/*different types full-empty - Record size check*/
		TEST_METHOD(crossJoin_FullEmptyR2){ 
			map<string, Table::TYPE> m; 
			m["Age"] = Table::TYPE::INT;
			Table t(m);
			vector<string> vec;
			vec.push_back("42");
			Record r2(vec);
			t.insert(r2);
			vec.clear();
			vec.push_back("11");
			Record r3(vec);
			t.insert(r3);
			vec.clear();
			vec.push_back("14");
			Record r4(vec);
			t.insert(r4);
			vec.clear();
			map<string, Table::TYPE> m1;
			m1["Student"] = Table::TYPE::STRING;
			Table t1(m1);
			Table t2;
			t2.crossJoin(t, t1);
			Assert::AreEqual(t2.getSize(), 0); //Cross join with an empty table should yield 0 records 
		}

		/*different types full-empty - Attribute size check*/

		TEST_METHOD(crossJoin_FullEmptyA2){ 
			map<string, Table::TYPE> m; 
			m["Age"] = Table::TYPE::FLOAT;
			Table t(m);
			vector<string> vec;
			vec.push_back("42.3");
			Record r2(vec);
			t.insert(r2);
			vec.clear();
			vec.push_back("11.1");
			Record r3(vec);
			t.insert(r3);
			vec.clear();
			vec.push_back("14.0");
			Record r4(vec);
			t.insert(r4);
			vec.clear();
			map<string, Table::TYPE> m1;
			m1["Student"] = Table::TYPE::STRING;
			Table t1(m1);
			Table t2;
			t2.crossJoin(t, t1);
			Assert::AreEqual(t.getAttributes().size(),(size_t) 2); //Cross join with an empty table should yield sum of attributes 
		}

		/*full-empty no attributes in one table - Attribute size check*/

		TEST_METHOD(crossJoin_FullEmptyA3){ 
			map<string, Table::TYPE> m; 
			m["Age"] = Table::TYPE::FLOAT;
			Table t(m);
			vector<string> vec;
			vec.push_back("42.3");
			Record r2(vec);
			t.insert(r2);
			vec.clear();
			vec.push_back("11.1");
			Record r3(vec);
			t.insert(r3);
			vec.clear();
			vec.push_back("14.0");
			Record r4(vec);
			t.insert(r4);
			vec.clear();
			Table t1;
			Table t2;
			t2.crossJoin(t, t1);
			Assert::AreEqual(t.getAttributes().size(),(size_t) 1); //Cross join with an empty table should yield sum of attributes 
		}

		/*Reverse cross join (parameters in crossJoin reversed) - Record size check*/
		TEST_METHOD(crossJoin_FullEmptyR3){ 
			map<string, Table::TYPE> m;
			m["School"] = Table::TYPE::STRING;
			Table t(m);
			vector<string> vec;
			vec.push_back("TAMU");
			Record r(vec);
			t.insert(r);
			map<string, Table::TYPE> m1;
			m1["Student"] = Table::TYPE::STRING;
			Table t1(m1);
			Table t3;
			t3.crossJoin(t1, t);
			Assert::AreEqual(t3.getSize(), 0); //Cross join with empty table should yield 0 records 
		}
		/*Reverse cross join - Attribute size check*/
		TEST_METHOD(crossJoin_FullEmptyA){ 
			map<string, Table::TYPE> m;
			m["School"] = Table::TYPE::STRING;
			Table t(m);
			vector<string> vec;
			vec.push_back("TAMU");
			Record r(vec);
			t.insert(r);
			vector<string> vec2;
			vec2.push_back("TU");
			Record r2(vec2);
			t.insert(r2);
			map<string, Table::TYPE> m1;
			m1["Student"] = Table::TYPE::STRING;
			Table t1(m1);
			Table t3;
			t3.crossJoin(t1, t);
			Assert::AreEqual(t.getAttributes().size(),(size_t) 2); //Cross join with empty table should yield sum of attributes
		}
		//^ need more cross join tests

		// Sum tests for INT, case with 0 elements
		TEST_METHOD(IntSumTest0){
			map<string, Table::TYPE> m;
			m["Number"] = Table::TYPE::INT;
			Table t(m);
			Assert::AreEqual<float>(t.getSum("Number"), 0.0);  //0 entries should return 0?
		}

		// Sum tests for INT, case with 1 element, 0
		TEST_METHOD(IntSumTest1){
			map<string, Table::TYPE> m;
			m["Number"] = Table::TYPE::INT;
			Table t(m);
			vector<string> vec;
			vec.push_back("0");
			Record r1(vec);
			t.insert(r1);
			Assert::AreEqual<float>(t.getSum("Number"), 0.0);
		}

		// Sum tests for INT, case with 1 element, 5
		TEST_METHOD(IntSumTest2){
			map<string, Table::TYPE> m;
			m["Number"] = Table::TYPE::INT;
			Table t(m);
			vector<string> vec;
			vec.push_back("5");
			Record r1(vec);
			t.insert(r1);
			Assert::AreEqual<float>(t.getSum("Number"), 5.0);
		}

		// Sum tests for INT, case with 2 elements, both 0
		TEST_METHOD(IntSumTest3){
			map<string, Table::TYPE> m;
			m["Number"] = Table::TYPE::INT;
			Table t(m);
			vector<string> vec;
			vec.push_back("0");
			Record r1(vec);
			t.insert(r1);
			vec.clear();
			vec.push_back("0");
			Record r2(vec);
			t.insert(r2);
			Assert::AreEqual<float>(t.getSum("Number"), 0.0);
		}

		// Sum tests for INT, case with 2 elements, 5 and 7
		TEST_METHOD(IntSumTest4){
			map<string, Table::TYPE> m;
			m["Number"] = Table::TYPE::INT;
			Table t(m);
			vector<string> vec;
			vec.push_back("7");
			Record r1(vec);
			t.insert(r1);
			vec.clear();
			vec.push_back("5");
			Record r2(vec);
			t.insert(r2);
			Assert::AreEqual<float>(t.getSum("Number"), 12.0);
		}

		// Sum tests for FLOAT, case with 0 elements
		TEST_METHOD(FloatSumTest0){
			map<string, Table::TYPE> m;
			m["Number"] = Table::TYPE::FLOAT;
			Table t(m);
			Assert::AreEqual<float>(t.getSum("Number"), 0.0);
		}

		// Sum tests for FLOAT, case with 1 element, 0.0
		TEST_METHOD(FloatSumTest1){
			map<string, Table::TYPE> m;
			m["Number"] = Table::TYPE::FLOAT;
			Table t(m);
			vector<string> vec;
			vec.push_back("0.0");
			Record r1(vec);
			t.insert(r1);
			Assert::AreEqual<float>(t.getSum("Number"), 0.0);
		}

		// Sum tests for FLOAT, case with 1 element, 0.0
		TEST_METHOD(FloatSumTest2){
			map<string, Table::TYPE> m;
			m["Number"] = Table::TYPE::FLOAT;
			Table t(m);
			vector<string> vec;
			vec.push_back("5.0");
			Record r1(vec);
			t.insert(r1);
			Assert::AreEqual<float>(t.getSum("Number"), 5.0);
		}

		// Sum tests for FLOAT, case with 2 elements, 0.0 and 0.0
		TEST_METHOD(FloatSumTest3){
			map<string, Table::TYPE> m;
			m["Number"] = Table::TYPE::FLOAT;
			Table t(m);
			vector<string> vec;
			vec.push_back("0.0");
			Record r1(vec);
			t.insert(r1);
			vec.clear();
			vec.push_back("0.0");
			Record r2(vec);
			t.insert(r2);
			Assert::AreEqual<float>(t.getSum("Number"), 0.0);
		}

		// Sum tests for FLOAT, case with 2 elements, 5.0 and 7.0
		TEST_METHOD(FloatSumTest4){
			map<string, Table::TYPE> m;
			m["Number"] = Table::TYPE::FLOAT;
			Table t(m);
			vector<string> vec;
			vec.push_back("0.0");
			Record r1(vec);
			t.insert(r1);
			vec.clear();
			vec.push_back("0.0");
			Record r2(vec);
			t.insert(r2);
			Assert::AreEqual<float>(t.getSum("Number"), 12.0);
		}

		// Count tests, 0 elements
		TEST_METHOD(CountTest1){
			map<string, Table::TYPE> m;
			m["Number"] = Table::TYPE::FLOAT;
			Table t(m);
			Assert::AreEqual<int>(t.getCount("Number"), 0);
		}

		// Count tests, 1 element
		TEST_METHOD(CountTest2){
			map<string, Table::TYPE> m;
			m["Number"] = Table::TYPE::FLOAT;
			Table t(m);
			vector<string> vec;
			vec.push_back("0.0");
			Record r1(vec);
			t.insert(r1);
			Assert::AreEqual<int>(t.getCount("Number"), 1);
		}

		// Count tests, 2 elements
		TEST_METHOD(CountTest3){
			map<string, Table::TYPE> m;
			m["Number"] = Table::TYPE::FLOAT;
			Table t(m);
			vector<string> vec;
			vec.push_back("0.0");
			Record r1(vec);
			t.insert(r1);
			vec.clear();
			vec.push_back("0.0");
			Record r2(vec);
			t.insert(r2);
			Assert::AreEqual<int>(t.getCount("Number"), 2);
		}

		// Min test for int, 0 elements  ***What should this be?
		TEST_METHOD(IntMinTest1){
			map<string, Table::TYPE> m;
			m["Number"] = Table::TYPE::INT;
			Table t(m);
			Assert::AreEqual<float>(t.getMin("Number"), 0);
		}

		// Min test for int, 1 element
		TEST_METHOD(IntMinTest2){
			map<string, Table::TYPE> m;
			m["Number"] = Table::TYPE::INT;
			Table t(m);
			vector<string> vec;
			vec.push_back("5");
			Record r(vec);
			t.insert(r);
			Assert::AreEqual<float>(t.getMin("Number"), 5.0);
		}

		// Min test for int, 2 elements
		TEST_METHOD(IntMinTest3){
			map<string, Table::TYPE> m;
			m["Number"] = Table::TYPE::INT;
			Table t(m);
			vector<string> vec;
			vec.push_back("5");
			Record r(vec);
			t.insert(r);
			vec.clear();
			vec.push_back("2");
			Record r2(vec);
			t.insert(r2);
			Assert::AreEqual<float>(t.getMin("Number"), 2.0);
		}

		// Min test for float, 0 elements ***??
		TEST_METHOD(FloatMinTest1){
			map<string, Table::TYPE> m;
			m["Number"] = Table::TYPE::FLOAT;
			Table t(m);
			Assert::AreEqual<float>(t.getMin("Number"), 0.0);
		}

				// Min test for int, 1 element
		TEST_METHOD(FloatMinTest2){
			map<string, Table::TYPE> m;
			m["Number"] = Table::TYPE::FLOAT;
			Table t(m);
			vector<string> vec;
			vec.push_back("5");
			Record r(vec);
			t.insert(r);
			Assert::AreEqual<float>(t.getMin("Number"), 5.0);
		}

		// Min test for int, 2 elements
		TEST_METHOD(FloatMinTest3){
			map<string, Table::TYPE> m;
			m["Number"] = Table::TYPE::INT;
			Table t(m);
			vector<string> vec;
			vec.push_back("5");
			Record r(vec);
			t.insert(r);
			vec.clear();
			vec.push_back("3");
			Record r2(vec);
			t.insert(r2);
			Assert::AreEqual<float>(t.getMin("Number"), 3.0);
		}

		// Max test for int, 0 elements  ***What should this be?
		TEST_METHOD(IntMaxTest1){
			map<string, Table::TYPE> m;
			m["Number"] = Table::TYPE::INT;
			Table t(m);
			Assert::AreEqual<float>(t.getMax("Number"), 0.0);
		}

		// Max test for int, 1 element
		TEST_METHOD(IntMaxTest2){
			map<string, Table::TYPE> m;
			m["Number"] = Table::TYPE::INT;
			Table t(m);
			vector<string> vec;
			vec.push_back("10");
			Record r(vec);
			t.insert(r);
			Assert::AreEqual<float>(t.getMax("Number"), 10.0);
		}

		// Max test for int, 2 elements
		TEST_METHOD(IntMaxTest3){
			map<string, Table::TYPE> m;
			m["Number"] = Table::TYPE::INT;
			Table t(m);
			vector<string> vec;
			vec.push_back("10");
			Record r(vec);
			t.insert(r);
			vec.clear();
			vec.push_back("100");
			Record r2(vec);
			t.insert(r2);
			Assert::AreEqual<float>(t.getMax("Number"), 100.0);
		}

		// Max test for float, 0 elements  ***What should this be?
		TEST_METHOD(FloatMaxTest1){
			map<string, Table::TYPE> m;
			m["Number"] = Table::TYPE::FLOAT;
			Table t(m);
			Assert::AreEqual<float>(t.getMax("Number"), 0.0);
		}

		// Max test for float, 1 element
		TEST_METHOD(FloatMaxTest2){
			map<string, Table::TYPE> m;
			m["Number"] = Table::TYPE::FLOAT;
			Table t(m);
			vector<string> vec;
			vec.push_back("10.0");
			Record r(vec);
			t.insert(r);
			Assert::AreEqual<float>(t.getMax("Number"), 10.0);
		}

		// Max test for int, 2 elements
		TEST_METHOD(FloatMaxTest3){
			map<string, Table::TYPE> m;
			m["Number"] = Table::TYPE::FLOAT;
			Table t(m);
			vector<string> vec;
			vec.push_back("10.0");
			Record r(vec);
			t.insert(r);
			vec.clear();
			vec.push_back("100.0");
			Record r2(vec);
			t.insert(r2);
			Assert::AreEqual<float>(t.getMax("Number"), 100.0);
		}
		//end of table


		//Database
		// Blank constructor, make sure number of tables is 0
		TEST_METHOD(DatabaseConstructorTest1){
			Database d;
			Assert::AreEqual<int>(d.getTables().size(), 0);
		}

		// Blank constructor, make sure number of tables is 0
		TEST_METHOD(DatabaseConstructorTest2){
			Database d;
			Assert::AreEqual<int>(d.listTables().size(), 0);
		}

		// Add a table, check size
		TEST_METHOD(DatabaseAddTableTest1){
			Database d;
			Table t;
			d.addTable(t, "Table");
			Assert::AreEqual<int>(d.getTables().size(), 1);
		}

		// Add a table, check for that name
		TEST_METHOD(DatabaseAddTableTest2){
			Database d;
			Table t;
			d.addTable(t, "Table");
			Assert::AreEqual<string>(d.listTables()[0], "Table");
		}

		// Check the bool returned by addTable
		TEST_METHOD(DatabaseAddTableTest3){
			Database d;
			Table t;
			bool b = d.addTable(t, "Table");
			Assert::AreEqual<bool>(b, true);
		}

		// No two tables should have the same name?
		TEST_METHOD(DatabaseAddTableTest4){
			Database d;
			Table t;
			d.addTable(t, "Table");
			Table t2;
			bool b = d.addTable(t2, "Table");
			Assert::AreEqual<bool>(b, false);
		}

		// Drop table test
		TEST_METHOD(DatabaseDropTableTest1){
			Database d;
			Table t;
			d.addTable(t, "Table");
			d.dropTable("Table");
			Assert::AreEqual<int>(d.getTables().size(), 0);
		}

		// Drop table test
		TEST_METHOD(DatabaseDropTableTest2){
			Database d;
			Table t;
			d.addTable(t, "Table");
			bool b = d.dropTable("Table");
			Assert::AreEqual<bool>(b, true);
		}

		// Drop table test, dropping a nonexistant table
		TEST_METHOD(DatabaseDropTableTest3){
			Database d;
			Table t;
			d.addTable(t, "Table");
			bool b = d.dropTable("Table2");
			Assert::AreEqual<bool>(b, false);
		}

		// GetTable test
		TEST_METHOD(DatabaseGetTableTest1){
			Database d;
			Table t;
			d.addTable(t, "Table");
			Assert::AreEqual<int>(d.getTables().size(), 1);
		}

		// GetTable test
		TEST_METHOD(DatabaseGetTableTest2){
			Database d;
			Table t;
			Table t2;
			d.addTable(t, "Table");
			d.addTable(t2, "Table2");
			Assert::AreEqual<int>(d.getTables().size(), 2);
		}

		// GetTable test + dropTable
		TEST_METHOD(DatabaseGetTableTest3){
			Database d;
			Table t;
			Table t2;
			d.addTable(t, "Table");
			d.addTable(t2, "Table2");
			d.dropTable("Table");
			Assert::AreEqual<int>(d.getTables().size(), 1);
		}

		// ListTables test
		TEST_METHOD(DatabaseListTableTest1){
			Database d;
			Table t;
			d.addTable(t, "Table");
			bool iselem = false;
			vector<string> vec = d.listTables();
			for(int i = 0; i < vec.size(); i++){   //loop checks to see if there is a table named "Table" in the DB
				if(vec[i] == "Table") iselem = true;
			}
			Assert::AreEqual<bool>(iselem, true);
		}

		// ListTables test
		TEST_METHOD(DatabaseListTableTest2){
			Database d;
			Table t;
			Table t2;
			d.addTable(t, "Table");
			d.addTable(t2, "Table2");
			bool iselem = false;
			vector<string> vec = d.listTables();
			for(int i = 0; i < vec.size(); i++){   //loop checks to see if there is a table named "Table" in the DB
				if(vec[i] == "Table2") iselem = true;
			}
			Assert::AreEqual<bool>(iselem, true);
		}

	// ListTables test
		TEST_METHOD(DatabaseListTableTest3){
			Database d;
			Table t;
			Table t2;
			d.addTable(t, "Table");
			d.addTable(t2, "Table2");
			d.dropTable("Table");
			bool iselem = false;
			vector<string> vec = d.listTables();
			for(int i = 0; i < vec.size(); i++){   //loop checks to see if there is a table named "Table" in the DB
				if(vec[i] == "Table") iselem = true;
			}
			Assert::AreEqual<bool>(iselem, false);
		}

		// Query Testings
		TEST_METHOD(QueryTest1){
			Database d;
			Table t;
			t.add("School", Table::TYPE::STRING);
			vector<string> vec;
			vec.push_back("TAMU");
			Record r(vec);
			t.insert(r);
			d.addTable(t, "Table");
			Table t2;
			t2 = d.evalQuery("SELECT {{School}} FROM {Table} WHERE {{School = TAMU}}");
			map<string, Table::TYPE> m2;
			m2 = t2.getAttributes();
			string s = "false";
			if(t.getAttributes().count("School") > 0) s = "true";
			Assert::AreEqual<string>(s, "true");
		}

		// Query Testings
		TEST_METHOD(QueryTes2){
			Database d;
			Table t;
			t.add("School", Table::TYPE::STRING);
			vector<string> vec;
			vec.push_back("TAMU");
			Record r(vec);
			t.insert(r);
			d.addTable(t, "Table");
			Table t2;
			t2 = d.evalQuery("SELECT {{School}} FROM {Table} WHERE {{School = TAMU}}");
			map<string, Table::TYPE> m2;
			m2 = t2.getAttributes();
			string s = "false";
			if(t.getAttributes().count("TAMU") > 0) s = "true";
			Assert::AreEqual<string>(s, "false");
		}

		// Query Testings, AND
		TEST_METHOD(QueryTes3){
			Database d;
			Table t;
			t.add("School", Table::TYPE::STRING);
			t.add("Number", Table::TYPE::INT);
			vector<string> vec;
			vec.push_back("TAMU");
			vec.push_back("42");
			Record r(vec);
			t.insert(r);
			d.addTable(t, "Table");
			Table t2;
			t2 = d.evalQuery("SELECT {{School},{Number}} FROM {Table} WHERE {{School = TAMU} AND {Number = 42}}");
			map<string, Table::TYPE> m2;
			m2 = t2.getAttributes();
			string s = "false";
			if(t.getAttributes().count("School") == 1) s = "true";
			Assert::AreEqual<string>(s, "true");
		}

		// Query Testings, AND
		TEST_METHOD(QueryTes4){
			Database d;
			Table t;
			t.add("School", Table::TYPE::STRING);
			t.add("Number", Table::TYPE::INT);
			vector<string> vec;
			vec.push_back("TAMU");
			vec.push_back("42");
			Record r(vec);
			t.insert(r);
			d.addTable(t, "Table");
			Table t2;
			t2 = d.evalQuery("SELECT {{School},{Number}} FROM {Table} WHERE {{School = TAMU} AND {Number = 42}}");
			map<string, Table::TYPE> m2;
			m2 = t2.getAttributes();
			string s = "false";
			if(t.getAttributes().count("TAMU") > 0) s = "true";
			Assert::AreEqual<string>(s, "false");
		}

		// Query Testings, AND
		TEST_METHOD(QueryTes5){
			Database d;
			Table t;
			t.add("School", Table::TYPE::STRING);
			t.add("Number", Table::TYPE::INT);
			vector<string> vec;
			vec.push_back("TAMU");
			vec.push_back("42");
			Record r(vec);
			t.insert(r);
			d.addTable(t, "Table");
			Table t2;
			t2 = d.evalQuery("SELECT {{School},{Number}} FROM {Table} WHERE {{School = TAMU} AND {Number = 42}}");
			map<string, Table::TYPE> m2;
			m2 = t2.getAttributes();
			string s = "false";
			//if(t.getAttributes().count("School") > 0 && t.getAttributes().count("Number") > 0) s = "true";
			Record r2 = t2.getRecord(0);
			if(r2.getEntry(0) == "TAMU" && r2.getEntry(1) == "42") s = "true";
			Assert::AreEqual<string>(s, "true");
		}

		// Query Testings, AND
		TEST_METHOD(QueryTes6){
			Database d;
			Table t;
			t.add("School", Table::TYPE::STRING);
			t.add("Number", Table::TYPE::INT);
			vector<string> vec;
			vec.push_back("TAMU");
			vec.push_back("42");
			Record r(vec);
			t.insert(r);
			d.addTable(t, "Table");
			Table t2;
			t2 = d.evalQuery("SELECT {{School},{Number}} FROM {Table} WHERE {{School = TAMU} AND {Number = 32}}");
			map<string, Table::TYPE> m2;
			m2 = t2.getAttributes();
			string s = "false";
			if(t.getSize() > 0) s = "true";
			Assert::AreEqual<string>(s, "false");
		}

		// Query Testings, AND
		TEST_METHOD(QueryTes6v2){
			Database d;
			Table t;
			t.add("School", Table::TYPE::STRING);
			t.add("Number", Table::TYPE::INT);
			vector<string> vec;
			vec.push_back("TAMU");
			vec.push_back("42");
			Record r(vec);
			t.insert(r);
			d.addTable(t, "Table");
			Table t2;
			t2 = d.evalQuery("SELECT {{School},{Number}} FROM {Table} WHERE {{School = TAMU} AND {Number = 32}}");
			map<string, Table::TYPE> m2;
			m2 = t2.getAttributes();
			string s = "false";
			//if(t.getAttributes().count("School") > 0 && t.getAttributes().count("Number") > 0) s = "true";
			if(t.getSize() == 0) s = "true";
			Assert::AreEqual<string>(s, "true");
		}

		// Query Testings, AND
		TEST_METHOD(QueryTes7){
			Database d;
			Table t;
			t.add("School", Table::TYPE::STRING);
			t.add("Number", Table::TYPE::INT);
			vector<string> vec;
			vec.push_back("TAMU");
			vec.push_back("42");
			Record r(vec);
			t.insert(r);
			d.addTable(t, "Table");
			Table t2;
			t2 = d.evalQuery("SELECT {{School},{Number}} FROM {Table} WHERE {{School = TAMU} AND {Number = 32}}");
			map<string, Table::TYPE> m2;
			m2 = t2.getAttributes();
			string s = "false";
			if(t.getAttributes().count("School") == 0 && t.getAttributes().count("Number") == 0) s = "true";
			Assert::AreEqual<string>(s, "true");
		}

		// Query Testings, AND
		TEST_METHOD(QueryTes8){
			Database d;
			Table t;
			t.add("School", Table::TYPE::STRING);
			t.add("Number", Table::TYPE::INT);
			vector<string> vec;
			vec.push_back("TAMU");
			vec.push_back("42");
			Record r(vec);
			t.insert(r);
			d.addTable(t, "Table");
			Table t2;
			t2 = d.evalQuery("SELECT {{School}} FROM {Table} WHERE {{School = TAMU} AND {Number = 32}}");
			map<string, Table::TYPE> m2;
			m2 = t2.getAttributes();
			string s = "false";
			if(t.getAttributes().count("School") > 0 && t.getAttributes().count("Number") == 0) s = "true";
			Assert::AreEqual<string>(s, "true");
		}
		
		// Query Testings, AND
		TEST_METHOD(QueryTes9){
			Database d;
			Table t;
			t.add("School", Table::TYPE::STRING);
			t.add("Number", Table::TYPE::INT);
			vector<string> vec;
			vec.push_back("TAMU");
			vec.push_back("42");
			Record r(vec);
			t.insert(r);
			d.addTable(t, "Table");
			Table t2;
			t2 = d.evalQuery("SELECT {{Number}} FROM {Table} WHERE {{School = TAMU} AND {Number = 42}}");
			map<string, Table::TYPE> m2;
			m2 = t2.getAttributes();
			string s = "false";
			if(t.getAttributes().count("School") == 0 && t.getAttributes().count("Number") == 1) s = "true";
			Assert::AreEqual<string>(s, "true");
		}

		
		// Query Testings, AND
		TEST_METHOD(QueryTes10){
			Database d;
			Table t;
			t.add("School", Table::TYPE::STRING);
			t.add("Number", Table::TYPE::INT);
			vector<string> vec;
			vec.push_back("TAMU");
			vec.push_back("42");
			Record r(vec);
			t.insert(r);
			d.addTable(t, "Table");
			Table t2;
			t2 = d.evalQuery("SELECT {{School}} FROM {Table} WHERE {{School = TAMU} AND {NOT{Number = 32}}}");
			map<string, Table::TYPE> m2;
			m2 = t2.getAttributes();
			string s = "false";
			//if(t.getAttributes().count("School") > 0 && t.getAttributes().count("Number") == 0) s = "true";
			Record r2 = t2.getRecord(0);
			if(r2.getEntry(0) == "TAMU") s = "true";
			Assert::AreEqual<string>(s, "true");
		}

		// Query Testings, AND
		TEST_METHOD(QueryTes11){
			Database d;
			Table t;
			t.add("School", Table::TYPE::STRING);
			t.add("Number", Table::TYPE::INT);
			vector<string> vec;
			vec.push_back("TAMU");
			vec.push_back("42");
			Record r(vec);
			t.insert(r);
			d.addTable(t, "Table");
			Table t2;
			t2 = d.evalQuery("SELECT {{School}} FROM {Table} WHERE {{School = TU} OR {Number = 32}}");
			map<string, Table::TYPE> m2;
			m2 = t2.getAttributes();
			string s = "false";
			//if(t.getAttributes().count("School") > 0 && t.getAttributes().count("Number") == 0) s = "true";
			if(t2.getSize() == 0) s = "true";
			Assert::AreEqual<string>(s, "true");
		}

		// DeleteQuery Testings, AND
		TEST_METHOD(DeleteQueryTest1){
			Database d;
			Table t;
			t.add("School", Table::TYPE::STRING);
			t.add("Number", Table::TYPE::INT);
			vector<string> vec;
			vec.push_back("TAMU");
			vec.push_back("42");
			Record r(vec);
			t.insert(r);
			d.evalDeleteQuery("SELECT {{School},{Number}} FROM {Table} WHERE {{School != TAMU}}");
			string s = "false";
			Table t2;
			t2 = d.getTables()[0];
			if(t2.getSize() == 1) s = "true";
			Assert::AreEqual<string>(s, "true");
		}

		// DeleteQuery Testings, AND
		TEST_METHOD(DeleteQueryTes2){
			Database d;
			Table t;
			t.add("School", Table::TYPE::STRING);
			t.add("Number", Table::TYPE::INT);
			vector<string> vec;
			vec.push_back("TAMU");
			vec.push_back("42");
			Record r(vec);
			t.insert(r);
			d.evalDeleteQuery("SELECT {{School},{Number}} FROM {Table} WHERE {{School = TAMU}}");
			string s = "false";
			Table t2;
			t2 = d.getTables()[0];
			if(t2.getSize() == 1) s = "true";
			Assert::AreEqual<string>(s, "false");
		}

		// DeleteQuery Testings, AND
		TEST_METHOD(DeleteQueryTes3){
			Database d;
			Table t;
			t.add("School", Table::TYPE::STRING);
			t.add("Number", Table::TYPE::INT);
			vector<string> vec;
			vec.push_back("TAMU");
			vec.push_back("42");
			Record r(vec);
			t.insert(r);
			d.evalDeleteQuery("SELECT {{School},{Number}} FROM {Table} WHERE {{School = TAMU} AND {Number == 3}}");
			string s = "false";
			Table t2;
			t2 = d.getTables()[0];
			if(t2.getSize() == 1) s = "true";
			Assert::AreEqual<string>(s, "true");
		}

		// DeleteQuery Testings, AND
		TEST_METHOD(DeleteQueryTes4){
			Database d;
			Table t;
			t.add("School", Table::TYPE::STRING);
			t.add("Number", Table::TYPE::INT);
			vector<string> vec;
			vec.push_back("TAMU");
			vec.push_back("42");
			Record r(vec);
			t.insert(r);
			d.evalDeleteQuery("SELECT {{School},{Number}} FROM {Table} WHERE {{School = TAMU} AND {Number > 3}}");
			string s = "false";
			Table t2;
			t2 = d.getTables()[0];
			if(t2.getSize() == 1) s = "true";
			Assert::AreEqual<string>(s, "false");
		}

		// DeleteQuery Testings, AND
		TEST_METHOD(DeleteQueryTes5){
			Database d;
			Table t;
			t.add("School", Table::TYPE::STRING);
			t.add("Number", Table::TYPE::INT);
			vector<string> vec;
			vec.push_back("TAMU");
			vec.push_back("3");
			Record r(vec);
			t.insert(r);
			d.evalDeleteQuery("SELECT {{School},{Number}} FROM {Table} WHERE {{School = TAMU} AND {Number <= 3}}");
			string s = "false";
			Table t2;
			t2 = d.getTables()[0];
			if(t2.getSize() == 1) s = "true";
			Assert::AreEqual<string>(s, "false");
		}

		// DeleteQuery Testings, AND
		TEST_METHOD(DeleteQueryTes6){
			Database d;
			Table t;
			t.add("School", Table::TYPE::STRING);
			t.add("Number", Table::TYPE::INT);
			vector<string> vec;
			vec.push_back("TAMU");
			vec.push_back("3");
			Record r(vec);
			t.insert(r);
			d.evalDeleteQuery("SELECT {{School},{Number}} FROM {Table} WHERE {{School = TAMU} OR {Number = 3}}");
			string s = "false";
			Table t2;
			t2 = d.getTables()[0];
			if(t2.getSize() == 1) s = "true";
			Assert::AreEqual<string>(s, "false");
		}
	};
}