#include <fstream>
#include <iostream>
#include <stdexcept>
#include "DataBase.h"


#pragma warning(disable:4996)

//
// TODO:
// -add null compatability - DO CHECKS 
// -fix spacing with null - DO CHECKS
// -fix open - DONE
// -fix save, save as, exit comands - DO CHECKS
// -add first line of file to be the table name cmpatibility - DONE
// -fix the examples - DO CHECKS 
// 
// -handle exeptions everywhere DONE?
// 
// -add big 4 to the Table class. Have somme questions
// 
// -make it possible to do write a full command in one line
// 
//
// -posible upgrade. Have checks for invalid tablename formats. 
//					 If the first line isnt the tablename use the name of the file as a tablename and have a std::cerr for example
// -posible upgrade. Update funtion that removes or adds tables from the project object into the catalogue.
// 
// 
//





int main()
{
//	Table apartment;
//	apartment.readFromFile("Apartment.txt");

//	Table shop;
//	shop.readFromFile("Shop.txt");


	DataBase project;

	//project.print("Work.txt");

	bool flag = true;
	std::string command;
	std::string openedFile;
	do
	{
		std::cout << "Write commands:" << std::endl;
		std::cin >> command;

		

		if (command == "open") 
		{
			std::cout << "What file do you want to open: " << std::endl;
			std::cin >> openedFile;

			project.open(openedFile);
		}
		else if (command == "save")
		{
			project.save();
		}
		else if (command == "saveAs") 
		{
			std::cout << "Where do you want to save as: " << std::endl;
			std::string answer;
			std::cin >> answer;

			project.saveAs(answer);
		}
		else if (command == "help") 
		{
			project.help();
		}
		else if (command == "close")
		{
			project.close();
		}
		else if (command == "import") 
		{
			/*std::cout << "What file do you want to import into the catalogue: " << std::endl;
			std::cout << "(if \"demo\" is written it will default to Apartment.txt for a demo)" << std::endl;
			std::string answer;
			std::cin >> answer;
			
			if (answer == "demo")
			{
				project.import("Apartment.txt");
			}
			else
			{
				project.import(answer);
			}*/
			
			if (openedFile.empty())
			{
				std::cout << "No file opened!" << std::endl;
			}
			else
			{
				project.import(openedFile);
			}

		}
		else if (command == "showtables") 
		{
			project.showtables();
		}
		else if (command == "describe") 
		{
			/*std::cout << "Which file do you want to describe : " << std::endl;

			std::cout << "(if \"demo\" is written it will default to Apartment.txt for a demo)" << std::endl;
			std::string answer;
			std::cin >> answer;

			if (answer == "demo")
			{
				project.describe("Apartment.txt");
			}
			else
			{
				project.describe(answer);
			}*/

			if (openedFile.empty())
			{
				std::cout << "No file opened!" << std::endl;
			}
			else
			{
				project.describe(openedFile);
			}

		}
		else if (command == "print") 
		{
			/*std::cout << "Which file do you want to print : " << std::endl;

			std::cout << "(if \"demo\"  is written it will default to Work.txt for a demo)" << std::endl;
			std::string answer;
			std::cin >> answer;

			if (answer == "demo")
			{
				project.print("Work.txt");
			}
			else
			{
				project.print(answer);
			}*/

			if (openedFile.empty())
			{
				std::cout << "No file opened!" << std::endl;
			}
			else
			{
				project.print(openedFile);
			}

		}
		else if (command == "export")
		{

			/*std::cout << "Which table do you want to export : " << std::endl;

			std::cout << "(if \"demo\"  is written in table it will default to Shop.txt for a demo)" << std::endl;
			std::string answerTable;
			std::cin >> answerTable;*/
			std::cout << "Which file do you want to export to: " << std::endl;
			std::string answerFile;
			std::cin >> answerFile;

			/*if (answerFile == "demo")
			{
				project.Myexport("Shop","Shop.txt");
			}
			else
			{
				project.Myexport(answerTable.c_str(), answerFile.c_str());
			}*/

			std::string answerTable = project.getTables().back().getTableName();
			if (openedFile.empty())
			{
				std::cout << "No file opened!" << std::endl;
			}
			else
			{
				project.Myexport(answerTable,answerFile);
			}

		}
		else if (command == "select") 
		{			
			/*std::cout << "Which table do you want to select: " << std::endl;
			std::cout << "(if \"demo\"  is written in table it will default to Apartment.txt for a demo)" << std::endl;
			std::string answerTable = project.getTables().back().getTableName();
			std::cin >> answerTable;
			*/
			std::cout << "Which column do you want to select: " << std::endl;
			size_t answerCol;
			std::cin >> answerCol;

			std::cout << "What value do you want to select: " << std::endl;
			std::string answerVal;
			std::cin >> answerVal;

			/*if (answerTable == "demo")
			{
				project.select(3, "4", "Apartment");
			}
			else
			{
				project.select(answerCol, answerVal, answerTable);
			}*/
			
			std::string answerTable = project.getTables().back().getTableName();
			if (openedFile.empty())
			{
				std::cout << "No file opened!" << std::endl;
			}
			else
			{
				project.select(answerCol,answerVal,answerTable);
			}

		}
		else if (command == "select_onto") 
		{
			/*std::cout << "Which table do you want to select: " << std::endl;
			std::cout << "(if \"demo\"  is written in table it will default to Apartment.txt for a demo)" << std::endl;
			std::string answerTable;
			std::cin >> answerTable;*/

			std::cout << "How manny columns do you want to select: " << std::endl;
			size_t length;
			std::cin >> length;

			std::cout << "Which columns do you want to select: " << std::endl;
			std::vector<size_t> answerCol;
			for (size_t i = 0; i < length; i++)
			{
				size_t answer;
				std::cin >> answer;
				answerCol.push_back(answer);
			}
			
			std::cout << "What is the number of the column you want to filter in: " << std::endl;
			size_t answerColN;
			std::cin >> answerColN;

			std::cout << "What value do you want to select: " << std::endl;
			std::string answerVal;
			std::cin >> answerVal;

			/*if (answerTable == "demo")
			{
				Table forthFloor;
				project.select_onto(forthFloor, { 1,3,4 }, 3, "4", "Apartment.txt");
			}
			else
			{
				Table resultTable;
				project.select_onto(resultTable, answerCol,answerColN,answerVal,answerTable);
			}*/

			std::string answerTable = project.getTables().back().getTableName();
			if (openedFile.empty())
			{
				std::cout << "No file opened!" << std::endl;
			}
			else
			{
				Table resultTable;
				resultTable.setTableName("result_table");
				resultTable.setFileName("resultTable.txt");
				project.select_onto(resultTable, answerCol, answerColN, answerVal, answerTable);
			}

		}
		else if (command == "addcolumn") //
		{			
			/*std::cout << "Which table do you want to add a column in: " << std::endl;
			std::cout << "(if \"demo\"  is written in table it will default to Shop.txt for a demo)" << std::endl;
			std::string answerTable;
			std::cin >> answerTable;*/

			std::cout << "What is the name of the new column: "  << std::endl;
			std::string answerColName;
			std::cin >> answerColName;

			std::cout << "What is the type of the new column(int/double/string): " << std::endl;
			std::string answerType;
			std::cin >> answerType;
			DataType type;
			if (answerType == "int")
			{
				type = DataType::INT;
			}
			else if (answerType == "double")
			{
				type = DataType::DOUBLE;
			}
			else if (answerType == "string")
			{
				type = DataType::STRING;
			}

			/*if (answerTable == "demo")
			{
				project.addColumn("Shop","Type(Veg/Fruit)",DataType::STRING);
			}
			else
			{
				project.addColumn(answerTable,answerColName,type);
			}*/

			std::string answerTable = project.getTables().back().getTableName();
			if (openedFile.empty())
			{
				std::cout << "No file opened!" << std::endl;
			}
			else
			{
				project.addColumn(answerTable, answerColName, type);
			}

		}
		else if (command == "update")
		{
			/*std::cout << "Which table do you want to update: " << std::endl;
			std::cout << "(if \"demo\"  is written in table it will default to Apartment.txt for a demo)" << std::endl;
			std::string answerTable;
			std::cin >> answerTable;*/

			std::cout << "What is the column number do you want to filter in: " << std::endl;
			size_t answerColN;
			std::cin >> answerColN;

			std::cout << "What value do you want to filter by: " << std::endl;
			std::string answerVal;
			std::cin >> answerVal;

			std::cout << "What is the column number do you want to put in: " << std::endl;
			size_t answerColT;
			std::cin >> answerColT;

			std::cout << "What value do you want to put: " << std::endl;
			std::string answerValT;
			std::cin >> answerValT;

			/*if (answerTable == "demo")
			{
				project.update("Apartment", 3,"6",3,"4");
			}
			else
			{				
				project.update(answerTable, answerColN, answerVal, answerColT, answerValT);
			}*/

			std::string answerTable = project.getTables().back().getTableName();
			if (openedFile.empty())
			{
				std::cout << "No file opened!" << std::endl;
			}
			else
			{
				project.update(answerTable, answerColN, answerVal, answerColT, answerValT);
			}


		}
		else if (command == "delete")
		{
		/*	std::cout << "Which table do you want to select: " << std::endl;
			std::cout << "(if \"demo\"  is written in table it will default to Apartment.txt for a demo)" << std::endl;
			std::string answerTable;
			std::cin >> answerTable;*/

			std::cout << "What is the column number do you want to delete in: " << std::endl;
			size_t answerColN;
			std::cin >> answerColN;

			std::cout << "What value do you want to delete by: " << std::endl;
			std::string answerVal;
			std::cin >> answerVal;

			/*if (answerTable == "demo")
			{
				project.Mydelete("Apartment", 3, "4");
			}
			else
			{
				project.Mydelete(answerTable, answerColN, answerVal);
			}*/

			std::string answerTable = project.getTables().back().getTableName();
			if (openedFile.empty())
			{
				std::cout << "No file opened!" << std::endl;
			}
			else
			{
				project.Mydelete(answerTable, answerColN, answerVal);
			}

		}
		else if (command == "insert")
		{
			/*std::cout << "Which table do you want to select: " << std::endl;
			std::cout << "(if \"demo\" is written in table it will default to Shop.txt for a demo)" << std::endl;
			std::string answerTable;
			std::cin >> answerTable;*/

			std::string answerTable = project.getTables().back().getTableName();

			size_t tableIndex = project.findTableIndex(answerTable);
			size_t rowCount = project.getTables()[tableIndex].getSize();
			std::cout << "You have " <<  rowCount  << " rows." << std::endl;;

			std::cout << "Write your rows: " << std::endl;
			std::vector<std::string> answerCol;
			std::string temp;
			for (size_t i = 0; i < rowCount; i++)
			{
				std::cin >> temp;
				answerCol.push_back(temp);
			}


			/*if (answerTable == "demo")
			{
				project.insert("Shop",{"Lime","43","7.99","13"});
			}
			else
			{
				project.insert(answerTable, answerCol);
			}*/

			if (openedFile.empty())
			{
				std::cout << "No file opened!" << std::endl;
			}
			else
			{
				project.insert(answerTable, answerCol);
			}

		}
		else if (command == "exit")
		{
		flag = false;
		project.exit();
		}
		else
		{
		std::cout << "This command doesn't exist." << std::endl;
		}
		
	} while (flag);


	

}


