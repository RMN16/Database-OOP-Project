#include <fstream>
#include <iostream>
#include <stdexcept>
#include "AllTables.h"


#pragma warning(disable:4996)

/*
catalogue.txt - big file with all the tables, must be created/opened at start of program

catalogue.txt file looks like this:
	tablename1 filename1
	tablename2 filename2
	tablename3 filename3
		...
	tablenameN filenameN

*/


//const size_t BUFF_SIZE = 1024;
//void import(const char* tablename, const char* filename)
//{
//	//check if tablename or filename already exists
//	std::ifstream catalogueI("catalogue.txt");
//	if (!catalogueI.is_open())
//	{
//		throw "Catalogue not found - ifstream"; 
//	}
//
//	char tableBuff[BUFF_SIZE];
//	char fileBuff[BUFF_SIZE];
//	while (!catalogueI.eof()) 
//	{
//		catalogueI >> tableBuff;
//		catalogueI >> fileBuff;
//
//		if (strcmp(tablename,tableBuff) == 0)
//		{
//			throw std::invalid_argument("Table name already exists");
//		}
//		if (strcmp(filename, fileBuff) == 0)
//		{
//			throw std::invalid_argument("File name already exists");
//		}
//	}
//	catalogueI.close();
//
//	//add the new table in the catalogue
//	std::ofstream catalogueO("catalogue.txt", std::ios::app); 
//	if (!catalogueO.is_open())
//	{
//		throw "Catalogue not found - ifstream";
//	}
//	
//	catalogueO << tablename << " " << filename << '\n';
//	catalogueO.close();
//}
//void showtables() //const
//{
//	std::ifstream catalogueI("catalogue.txt");
//	if (!catalogueI.is_open())
//	{
//		 throw "Catalogue not found - ifstream";
//	}
//
//	char buff[BUFF_SIZE];
//	while (!catalogueI.eof())
//	{
//		
//		catalogueI >> buff;
//		std::cout << buff << '\n';
//
//		catalogueI >> buff;
//	}
//
//	catalogueI.close();
//}
//
////
////How a table looks in a file:
//// 
//// name1,type1,data11,data12,data13,....,data1n
//// name2,type2,data21,data22,data23,....,data2n
//// name3,type3,data31,data32,data33,....,data3n
////  .......
//// 
////
//
//
//void describe(std::string filename)
//{
//	int numOfTypes[3] = { 0 }; // 0- int, 1-double, 2-string
//
//	std::ifstream file(filename);
//	if (!file.is_open())
//	{
//		throw "File is not opened";
//	}
//
//	std::string line;
//	while (std::getline(file,line))
//	{
//		size_t firstComma = line.find(',');
//		
//		switch (line[firstComma + 1])
//		{
//		case '0': numOfTypes[0]++; break;
//		case '1': numOfTypes[1]++; break;
//		case '2': numOfTypes[2]++; break;
//		default: break;
//		}
//	}
//
//	std::cout << "Number of Integer types: "<< numOfTypes[0] << std::endl;
//	std::cout << "Number of Double types: " << numOfTypes[1] << std::endl;
//	std::cout << "Number of String types: " << numOfTypes[2] << std::endl;
//	
//	file.close();
//}
//
//const size_t PAGE_SIZE = 10;
//void print(std::string filename)
//{
//	std::ifstream file(filename);
//	if (!file.is_open())
//	{
//		throw "File is not opened";
//	}
//
//	//Idea
//	// 1. put the first colum in a vector
//	// 2. put the data in a vector or vectors
//	// 3. print pages
//
//	std::string line;
//	std::vector<std::string> names;
//	std::vector<std::vector<std::string>> data;
//
//	while (std::getline(file, line))
//	{
//		size_t posiotion = 0;
//		std::string token;
//
//		// Read the name
//		posiotion = line.find(',');
//		if (posiotion != std::string::npos) //if it's not the end of the string
//		{
//			token = line.substr(0, posiotion);
//			names.push_back(token);
//			line.erase(0, posiotion + 1);
//		}
//
//		// Skip the type
//		posiotion = line.find(',');
//		if (posiotion != std::string::npos) //if it's not the end of the string
//		{
//			line.erase(0, posiotion + 1);
//		}
//
//		// Read the data
//		std::vector<std::string> row;
//		while ((posiotion = line.find(',')) != std::string::npos) 
//		{
//			token = line.substr(0, posiotion);
//			row.push_back(token);
//			line.erase(0, posiotion + 1);
//		}
//		row.push_back(line);
//		data.push_back(row); // it has 2 empty members at the end
//	}
//	file.close();
//
//
//	//The printing part 
//	size_t pageIndex = 0;
//	//Find the longest row if all rows are not of equal length
//	size_t max_rows = 0;
//	for (size_t i = 0; i < data.size(); i++) {
//		if (data[i].size() > max_rows) {
//			max_rows = data[i].size();
//		}
//	}
//	size_t numberOfPages = max_rows / PAGE_SIZE;
//
//	std::string str = "Y";
//	while (str == "Y" && pageIndex < numberOfPages)
//	{
//		for (int i = 0; i < names.size(); i++)
//		{
//			std::cout << names[i] << " ";
//		}
//		std::cout << std::endl;
//		
//		for (size_t i = pageIndex * PAGE_SIZE; i < max_rows && i < (pageIndex * PAGE_SIZE) + PAGE_SIZE; i++) {
//			for (size_t j = 0; j < data.size(); j++) {
//				if (i < data[j].size()) {
//					std::cout << data[j][i] << " ";
//				}
//				else {
//					std::cout << "  "; // Fill in empty space if row has fewer elements
//				}
//			}
//			std::cout << std::endl;
//		}
//		pageIndex++;
//		std::cout << "--------------------------------------page " << pageIndex << " next page? [Y/N]--------------------------------------" << std::endl;
//		std::cin >> str;
//
//	}
//
//}



int main()
{
	std::vector<std::string> Apartment_residentNameData = { "Ivan","Dragan","Maria","Nikol" };
	ColumnString* Apartment_ResidentName = new ColumnString(Apartment_residentNameData,"ResidentName");
	
	std::vector<int> Apartment_numberData = { 42,45,50,66 };
	ColumnInt* Apartment_Number = new ColumnInt(Apartment_numberData, "Number");

	std::vector<int> Apartment_floorData = { 5,4,4,6 };
	ColumnInt* Apartment_Floor = new ColumnInt(Apartment_floorData, "Floor");
	
	std::vector<double> Apartment_rentData = { 450.99,500.24,535.92,600 };
	ColumnDouble* Apartment_Rent = new ColumnDouble(Apartment_rentData, "Rent");

	std::vector<Column*> apartmentData = { Apartment_ResidentName,Apartment_Number,Apartment_Floor,Apartment_Rent };

	Table apartment(apartmentData, "Apartment", "Apartment.txt");




	std::vector<std::string> Shop_productNameData = { "Bannana","Apple","Orange","Lemon" };
	ColumnString* Shop_Name = new ColumnString(Shop_productNameData, "ProductName");

	std::vector<int> Shop_productIDData = { 10,11,22,42 };
	ColumnInt* Shop_ID = new ColumnInt(Shop_productIDData, "ID");

	std::vector<int> Shop_soldData = { 522,402,402,60 };
	ColumnInt* Shop_sold = new ColumnInt(Shop_soldData, "Number sold");

	std::vector<double> Shop_priceData = { 5.99,3.20,4.92,2 };
	ColumnDouble* Shop_price = new ColumnDouble(Shop_priceData, "Price");

	std::vector<Column*> shopData = { Shop_Name,Shop_ID,Shop_sold,Shop_price };

	Table shop(shopData, "Shop", "Shop.txt");




	AllTables project;
	project.addTable(apartment);
	project.addTable(shop);

	std::ifstream catalogue("catalogue.txt");
	if (!catalogue.is_open())
	{
		throw "File not opened";
	}
	
	
	bool flag = true;
	std::string command;

		do
		{
			std::cout << "Write commands:" << std::endl;
			std::cin >> command;

			if (command == "open")
			{
				std::cout << "What file do you want to open: " << std::endl;
				std::string answer;
				std::cin >> answer;

				project.open(answer);
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
				std::cout << "What file do you want to import into the catalogue: " << std::endl;
				std::cout << "(if nothing is written it will default to Apartment.txt for a demo)" << std::endl;
				std::string answer;
				std::cin >> answer;
				
				if (answer.empty())
				{
					project.import("Apartment.txt");
				}
				else
				{
					project.import(answer.c_str());
				}
				
			}
			else if (command == "showtables")
			{
				project.showtables();
			}
			else if (command == "describe")
			{
				std::cout << "Which table do you want to describe : " << std::endl;

				std::cout << "(if nothing is written it will default to Apartment.txt for a demo)" << std::endl;
				std::string answer;
				std::cin >> answer;

				if (answer.empty())
				{
					project.describe("Apartment.txt");
				}
				else
				{
					project.describe(answer);
				}
			}
			else if (command == "print")
			{
				std::cout << "Which table do you want to print : " << std::endl;

				std::cout << "(if nothing is written it will default to Work.txt for a demo)" << std::endl;
				std::string answer;
				std::cin >> answer;

				if (answer.empty())
				{
					project.print("Work.txt");
				}
				else
				{
					project.print(answer);
				}
				

			}
			else if (command == "export")
			{

				std::cout << "Which table do you want to export : " << std::endl;

				std::cout << "(if nothing is written in table it will default to Shop.txt for a demo)" << std::endl;
				std::string answerTable;
				std::cin >> answerTable;
				std::string answerFile;
				std::cin >> answerFile;

				if (answerFile.empty())
				{
					project.Myexport("Shop","Shop.txt");
				}
				else
				{
					project.Myexport(answerTable.c_str(), answerFile.c_str());
				}

			}
			else if (command == "select")
			{
				
				
				std::cout << "(if nothing is written in table it will default to Apartment.txt for a demo)" << std::endl;
				
				std::cout << "Which table do you want to select: " << std::endl;
				std::string answerTable;
				std::cin >> answerTable;
				
				std::cout << "Which column do you want to select: " << std::endl;
				size_t answerCol;
				std::cin >> answerCol;

				std::cout << "What value do you want to select: " << std::endl;
				std::string answerVal;
				std::cin >> answerVal;

				if (answerTable.empty())
				{
					project.select(3, "4", "Apartment");
				}
				else
				{
					project.select(answerCol, answerVal, answerTable);
				}
				
			}
			else if (command == "select_onto")
			{
				std::cout << "(if nothing is written in table it will default to Apartment.txt for a demo)" << std::endl;

				std::cout << "Which table do you want to select: " << std::endl;
				std::string answerTable;
				std::cin >> answerTable;

				std::cout << "How manny columns do you want to select: " << std::endl;
				size_t length;
				std::cin >> length;

				std::cout << "Which columns do you want to select: " << std::endl;
				std::vector<size_t> answerCol;
				for (size_t i = 0; i < length; i++)
				{
					std::cin >> answerCol[i];
				}
				
				std::cout << "What is the column number do you want to filter in: " << std::endl;
				size_t answerColN;
				std::cin >> answerColN;

				std::cout << "What value do you want to select: " << std::endl;
				std::string answerVal;
				std::cin >> answerVal;

				if (answerTable.empty())
				{
					Table forthFloor;
					project.select_onto(forthFloor, { 1,3,4 }, 3, "4", "Apartment.txt");
				}
				else
				{
					Table resultTable;
					project.select_onto(resultTable, answerCol,answerColN,answerVal,answerTable);
				}

			}
			else if (command == "addcolumn")
			{

				std::cout << "(if nothing is written in table it will default to Shop.txt for a demo)" << std::endl;

				std::cout << "Which table do you want to add a column in: " << std::endl;
				std::string answerTable;
				std::cin >> answerTable;

				std::cout << "What is the name of the new column: "  << std::endl;
				std::string answerColName;
				std::cin >> answerColName;

				std::cout << "What is the type of the new column(int/double/string): " << std::endl;
				std::string answerType;
				std::cin >> answerType;
				DataTypes type;
				if (answerType == "int")
				{
					type = DataTypes::INT;
				}
				else if (answerType == "double")
				{
					type = DataTypes::DOUBLE;
				}
				else if (answerType == "string")
				{
					type = DataTypes::STRING;
				}


				if (answerTable.empty())
				{
					Table forthFloor;
					project.addColumn("Shop","Type(Veg/Fruit)",DataTypes::STRING);
				}
				else
				{
					Table resultTable;
					project.addColumn(answerTable,answerColName,type);
				}

			}
			else if (command == "update")
			{
				std::cout << "(if nothing is written in table it will default to Apartment.txt for a demo)" << std::endl;

				std::cout << "Which table do you want to update: " << std::endl;
				std::string answerTable;
				std::cin >> answerTable;

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

				if (answerTable.empty())
				{
					project.update("Apartment", 3,"6",3,"4");
				
				}
				else
				{
					
					project.update(answerTable, answerColN, answerVal, answerColT, answerValT);
				}

			}
			else if (command == "delete")
			{
				std::cout << "(if nothing is written in table it will default to Apartment.txt for a demo)" << std::endl;

				std::cout << "Which table do you want to select: " << std::endl;
				std::string answerTable;
				std::cin >> answerTable;

				std::cout << "What is the column number do you want to delete in: " << std::endl;
				size_t answerColN;
				std::cin >> answerColN;

				std::cout << "What value do you want to delete by: " << std::endl;
				std::string answerVal;
				std::cin >> answerVal;

				if (answerTable.empty())
				{
					project.Mydelete("Apartment", 3, "4");
				}
				else
				{
					project.Mydelete(answerTable, answerColN, answerVal);
				}

			}
			else if (command == "insert")
			{
				std::cout << "(if nothing is written in table it will default to Shop.txt for a demo)" << std::endl;

				std::cout << "Which table do you want to select: " << std::endl;
				std::string answerTable;
				std::cin >> answerTable;

				size_t tableIndex = project.findTableIndex(answerTable);
				size_t rowCount = project.getTables()[tableIndex].getSize();
				std::cout << "You have " <<  rowCount  << " rows." << std::endl;;

				std::cout << "Which table do you want to select: " << std::endl;
				std::vector<std::string> answerCol;
				std::cin >> answerTable;
				for (size_t i = 0; i < rowCount; i++)
				{

				}


				if (answerTable.empty())
				{
					project.insert("Shop",{"Lime","43","30","7.99"});
				}
				else
				{
					project.insert(answerTable, answerCol);
				}

			}

			if (command == "exit")
			{
				flag = false;
				project.exit();
			}
		} while (flag);

}


