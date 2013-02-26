#include "Table.h"
#include "Record.h"
#include "Database.h"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
//#include <./boost/test/unit_test.hpp>

//BOOST_AUTO_TEST_CASE( my_test )
int main()
{
    Database * test_db = new Database();
	Table * test_table1 = new Table();
	Table * test_table2 = new Table();

    printf("test is %d\n", test_db != NULL );
	printf("test is %d\n", test_table1 != NULL);
	printf("test is %d\n", test_table2 != NULL);
	
	test_db->addTable(*test_table1, "Table 1");

	printf("test is %d\n",test_db->listTables().size() == 1);
	printf("test is %d\n",test_db->listTables().front() == "Table 1");
	test_db->dropTable("Table 2");
	printf("test is %d\n",test_db->listTables().size() == 1);
	test_db->dropTable("Table 1");
	printf("test is %d\n",test_db->listTables().size() == 0);

	test_db->addTable(*test_table2, "Table 2");

	printf("test is %d\n",test_db->listTables().size() == 1);
	printf("test is %d\n",test_db->listTables().front() == "Table 2");

	Table * test_table3 = new Table();
	printf("test is %d\n",test_table3->getAttributes().size() == 0);

	test_table3->addAttribute("key", Table::Type::INT);
	test_table3->addAttribute("fName", Table::Type::string);
	test_table3->addAttribute("lName", Table::Type::string);
	test_table3->addAttribute("bogus", Table::Type::FLOAT);
	printf("test is %d\n",test_table3->deleteAttribute("BOGUS"));

	test_db->addTable(*test_table3, "Table 3");
	printf("test is %d\n",test_db->listTables().size() == 2);
	printf("test is %d\n",test_table3->getAttributes().size() == 4);
	printf("test is %d\n",test_db->getTables().back().getAttributes().size() == 4);

	Table myTestTable = test_db->getTables().back();

	printf("test is %d\n",myTestTable.getAttributes().size() == 4);
	printf("test is %d\n",myTestTable.renameAttribute("bogus", "unreal"));
	printf("test is %d\n",myTestTable.getAttributes().size() == 4);
	printf("test is %d\n",!myTestTable.deleteAttribute("bogus"));
	printf("test is %d\n",myTestTable.deleteAttribute("unreal"));	
	printf("test is %d\n",myTestTable.getAttributes().size() == 3);
	printf("test is %d\n",myTestTable.getSize() == 0);
	printf("test is %d\n",myTestTable.getCount("fName") == 0);

	test_table3->addAttribute("num", Table::Type::FLOAT);

	Record test_record1 = Record();
	test_record1.modifyRecordEntry(0, "1"); // should be key?
	test_record1.modifyRecordEntry(1, "brent"); // should be fName?
	test_record1.modifyRecordEntry(2, "walther"); // should be lName?
	test_record1.modifyRecordEntry(3, "12.12");

	Record test_record2 = Record();
	test_record2.modifyRecordEntry(0, "2"); // should be key?
	test_record2.modifyRecordEntry(1, ""); // should be fName?
	test_record2.modifyRecordEntry(2, "person"); // should be lName?
	test_record2.modifyRecordEntry(3, "14.14");

	Record test_record3 = Record();
	test_record3.modifyRecordEntry(0, "3"); // should be key?
	test_record3.modifyRecordEntry(1, "another"); // should be fName?
	test_record3.modifyRecordEntry(2, "test"); // should be lName?
	test_record3.modifyRecordEntry(3, "");

	Record test_record4 = Record();
	test_record4.modifyRecordEntry(0, "4"); // should be key?
	test_record4.modifyRecordEntry(1, "good"); // should be fName?
	test_record4.modifyRecordEntry(2, "guygreg"); // should be lName?
	test_record4.modifyRecordEntry(3, " 13.13");

	printf("test is %d\n",(*test_record1.accessRecordEntry(0)).compare("1") == 0);
	printf("test is %d\n",(*test_record1.accessRecordEntry(2)).compare("walther") == 0);
	printf("test is %d\n",test_record1.accessRecordEntry(4) == NULL);

	myTestTable.insertRecord(test_record1);
	myTestTable.insertRecord(test_record2);
	myTestTable.insertRecord(test_record3);

	printf("test is %d\n",test_db->getTables().back().getSize() == 3);
	printf("test is %d\n",test_db->getTables().back().getSum("num") == 36.36);
	printf("test is %d\n",test_db->getTables().back().getCount("fName") == 2);
	printf("test is %d\n",test_db->getTables().back().getCount("lName") == 3);
	printf("test is %d\n",test_db->getTables().back().getMin("num") == 12.12);
	printf("test is %d\n",test_db->getTables().back().getMax("num") == 14.14);

	myTestTable.insertRecord(test_record3);
	printf("test is %d\n",test_db->getTables().back().getSize() == 4);
	printf("test is %d\n",test_db->getTables().back().getSum("num") == 49.49);
	printf("test is %d\n",test_db->getTables().back().getCount("fName") == 3);
	printf("test is %d\n",test_db->getTables().back().getCount("lName") == 4);
	printf("test is %d\n",test_db->getTables().back().getMin("num") == 12.12);
	printf("test is %d\n",test_db->getTables().back().getMax("num") == 14.14);

	Table combined_test_table = test_table3->crossJoin(*test_table3, *test_table2);

	printf("test is %d\n",combined_test_table.getSize() == test_table3->getSize());

	Record test_record5 = Record();
	test_record5.modifyRecordEntry(0, "5"); // should be key?
	test_record5.modifyRecordEntry(1, "marshall"); // should be fName?
	test_record5.modifyRecordEntry(2, "mathers"); // should be lName?
	test_record5.modifyRecordEntry(3, "1.11");

	test_table2->insertRecord(test_record5);
	combined_test_table = test_table3->crossJoin(*test_table3, *test_table2);

	printf("test is %d\n",combined_test_table.getSize() != (*test_table3).getSize());
	printf("test is %d\n",combined_test_table.getSize() == 5);	
	printf("test is %d\n",test_db->getTables().back().getSum("num") == 50.60);
	printf("test is %d\n",test_db->getTables().back().renameAttribute("num", "aNumber"));
	printf("test is %d\n",test_db->getTables().back().getSum("aNumber") == 50.60);
	printf("test is %d\n",test_db->getTables().back().getSum("num") == 0);

	std::list<std::string> attributeList = std::list<std::string>();
	attributeList.push_back("fName");
	attributeList.push_back("lName");

	std::list<std::string> attributeList2 = std::list<std::string>();
	attributeList.push_back("fName");
	attributeList.push_back("aNumber");

	printf("test is %d\n",test_db->query(attributeList,"Table3","1==1").getSize() == 5);
	printf("test is %d\n",test_db->query(attributeList,"Table3","1==0").getSize() == 0);
	printf("test is %d\n",test_db->query(attributeList2,"Table3","key >= 2 AND key < 2").getSize() == 5);
	printf("test is %d\n",test_db->query(attributeList2,"Table3","key >= 2").getSize() == 4);
	printf("test is %d\n",test_db->query(attributeList2,"Table3","key > 2").getSize() == 3);
	printf("test is %d\n",test_db->query(attributeList2,"Table3","key <= 2").getSize() == 2);
	printf("test is %d\n",test_db->query(attributeList2,"Table3","key < 2").getSize() == 1);
	printf("test is %d\n",test_db->query(attributeList2,"Table3","fName != \"brent\" OR lName != \"mathers\"").getSize() == 3);
	printf("test is %d\n",test_db->query(attributeList2,"Table3","fName != \"brent\" AND lName != \"mathers\"").getSize() == 3);
	printf("test is %d\n",test_db->query(attributeList2,"Table3","NOT fName == \"brent\" AND NOT lName == \"mathers\"").getSize() == 3);

	test_db->deleteRecord("Table3", "key < 2");
	printf("test is %d\n",test_db->query(attributeList2,"Table3","fName != \"brent\" OR lName != \"mathers\"").getSize() == 3);
	printf("test is %d\n",test_db->query(attributeList2,"Table3","fName != \"brent\" AND lName != \"mathers\"").getSize() == 3);
	printf("test is %d\n",test_db->query(attributeList2,"Table3","NOT fName == \"brent\" AND NOT lName == \"mathers\"").getSize() == 3);	
	printf("test is %d\n",test_db->query(attributeList2,"Table3","key < 2").getSize() == 0);
	printf("test is %d\n",test_db->query(attributeList2,"Table3","fName == \"brent\"").getSize() == 0);

	test_db->addTable(test_db->query(attributeList2,"Table3","fName != \"brent\" OR lName != \"mathers\""), "myQuery");
	printf("test is %d\n",test_db->listTables().size() == 3);
	test_db->dropTable("myQuery");
	printf("test is %d\n",test_db->listTables().size() == 2);

	Record *test_rd1 = new Record();

	test_rd1->modifyRecordEntry(1, "N");
	test_rd1->modifyRecordEntry(2, "WHATISTHAT>>??");
	test_rd1->modifyRecordEntry(4, "WHATISTHIS>>?");
	test_rd1->modifyRecordEntry(3, "IMPOSSIBLE");

	Table * test_table9000 = new Table();
	test_db->addTable(*test_table9000, "Table9000");
	test_db->addTable(*test_table9000, "Table9000");
	test_db->dropTable("Table9000");	
	test_db->dropTable("Table9000");	
	printf("test is %d\n",test_db->listTables().size() == 2);
}