#include "AllTables.h"
#pragma warning(disable:4996)


std::vector<Table> AllTables::getTables() const
{
	return tables_;
}

size_t AllTables::findTableIndex(std::string tableName)
{
	size_t tableIndex = -1;
	for (size_t i = 0; i < tables_.size(); i++)
	{
		if (tableName == tables_[i].getTableName())
		{
			tableIndex = i;
			break;
		}
	}
	return tableIndex;
}

void AllTables::addTable(Table table)
{
	tables_.push_back(table);
}


const size_t BUFF_SIZE = 1024;
void AllTables::import(const char* filename)
{
	//add the table name in the catalogue
	const char* tablename = nullptr;
	for (size_t i = 0; i < tables_.size(); i++)
	{
		if (tables_[i].getFileName() == filename)
		{
			std::string tablenameStr = tables_[i].getTableName();
			tablename = tablenameStr.c_str();

			break;
		}
	}
	// check if the if statement in the for loop has passed
	// if not retrun 
	if (tablename == nullptr)
	{
		return;
	}


	//check if filename already exists
	std::ifstream catalogueI("catalogue.txt");
	if (!catalogueI.is_open())
	{
		throw "Catalogue not found - ifstream";
	}

	char tableBuff[BUFF_SIZE];
	char fileBuff[BUFF_SIZE];
	while (!catalogueI.eof())
	{
		catalogueI >> tableBuff;
		catalogueI >> fileBuff;

		if (strcmp(tablename, tableBuff) == 0)
		{
			throw std::invalid_argument("Table name already exists");
		}
		if (strcmp(filename, fileBuff) == 0)
		{
			throw std::invalid_argument("File name already exists");
		}
	}
	catalogueI.close();

	//add the new table in the catalogue
	std::ofstream catalogueO("catalogue.txt", std::ios::app);
	if (!catalogueO.is_open())
	{
		throw "Catalogue not found - ifstream";
	}

	catalogueO << tablename << " " << filename << '\n';
	catalogueO.close();
}
void AllTables::showtables() const
{
	std::ifstream catalogueI("catalogue.txt");
	if (!catalogueI.is_open())
	{
		throw "Catalogue not found - ifstream";
	}

	char buff[BUFF_SIZE];
	while (!catalogueI.eof())
	{

		catalogueI >> buff;
		std::cout << buff << '\n';

		catalogueI >> buff;
	}

	catalogueI.close();
}

void AllTables::describe(std::string filename) const
{
	int numOfTypes[3] = { 0 }; // 0- int, 1-double, 2-string

	std::ifstream file(filename);
	if (!file.is_open())
	{
		throw "File is not opened";
	}

	std::string line;
	while (std::getline(file, line))
	{
		size_t firstComma = line.find(',');

		switch (line[firstComma + 1])
		{
		case '0': numOfTypes[0]++; break;
		case '1': numOfTypes[1]++; break;
		case '2': numOfTypes[2]++; break;
		default: break;
		}
	}

	std::cout << "Number of Integer types: " << numOfTypes[0] << std::endl;
	std::cout << "Number of Double types: " << numOfTypes[1] << std::endl;
	std::cout << "Number of String types: " << numOfTypes[2] << std::endl;

	file.close();
}

const size_t PAGE_SIZE = 10;
void AllTables::pagePrint(std::vector<std::vector<std::string>> data, std::vector<std::string> names) const
{
	size_t pageIndex = 0;
	//Find the longest row if all rows are not of equal length
	size_t max_rows = 0;
	for (size_t i = 0; i < data.size(); i++) {
		if (data[i].size() > max_rows) {
			max_rows = data[i].size();
		}
	}
	size_t numberOfPages = max_rows / PAGE_SIZE;

	std::string str;
	do
	{
		for (int i = 0; i < names.size(); i++)
		{
			std::cout << names[i] << " ";
		}
		std::cout << std::endl;


		for (size_t i = pageIndex * PAGE_SIZE; i < max_rows && i < (pageIndex * PAGE_SIZE) + PAGE_SIZE; i++) {
			for (size_t j = 0; j < data.size(); j++) {
				if (i < data[j].size()) {
					std::cout << data[j][i] << " ";
				}
				else {
					std::cout << "  "; // Fill in empty space if row has fewer elements
				}
			}
			std::cout << std::endl;
		}

		std::cout << "--------------------------------------page " << pageIndex << " [next/prev/exit]--------------------------------------" << std::endl;
		std::cin >> str;
		if (str == "next")
		{
			pageIndex++;
		}
		else if (str == "prev" && pageIndex > 0)
		{
			pageIndex--;
		}


	} while ((str == "next" || str == "prev") && pageIndex < numberOfPages); // if we write something different we exit the print
}

void AllTables::print(std::string filename) const
{
	std::ifstream file(filename);
	if (!file.is_open())
	{
		throw "File is not opened";
	}

	//Idea
	// 1. put the first colum in a vector
	// 2. put the data in a vector or vectors
	// 3. print pages

	std::string line;
	std::vector<std::string> names;
	std::vector<std::vector<std::string>> data;

	while (std::getline(file, line))
	{
		size_t posiotion = 0;
		std::string word;

		// Read the name
		posiotion = line.find(',');
		if (posiotion != std::string::npos) //if it's not the end of the string
		{
			word = line.substr(0, posiotion);
			names.push_back(word);
			line.erase(0, posiotion + 1);
		}

		// Skip the type
		posiotion = line.find(',');
		if (posiotion != std::string::npos) //if it's not the end of the string
		{
			line.erase(0, posiotion + 1);
		}

		// Read the data
		std::vector<std::string> row;
		while ((posiotion = line.find(',')) != std::string::npos)
		{
			word = line.substr(0, posiotion);
			row.push_back(word);
			line.erase(0, posiotion + 1);
		}
		row.push_back(line);
		data.push_back(row); // it has 2 empty members at the end
	}
	file.close();

	
	pagePrint(data,names);

}


void AllTables::Myexport(const char* name, const char* filename) // "export" word makes the program fail
{
	for (size_t i = 0; i < tables_.size(); i++)
	{
		std::string tablenameStr = tables_[i].getTableName();
		const char* tablename = tablenameStr.c_str();

		if (strcmp(name, tablename) == 0)
		{
			std::string filenameStr = tables_[i].getFileName();
			const char* filenameOfTable = filenameStr.c_str();
			if (strcmp(filename, filenameOfTable) == 0)
			{
				tables_[i].insertIntoFile();
			}
		}
	}
}

//split the data into a vector of words so that i can find the matching values better
std::vector<std::string>  AllTables::splitDataIntoAVectorOfStrings(const std::string& str)
{
	std::vector<std::string> words;
	std::string word;

	for (char ch : str)
	{
		if (ch == ',')
		{
			if (!word.empty())
			{
				words.push_back(word);
				word.clear();
			}
		}
		else
		{
			word += ch;
		}
	}
	if (!word.empty())
	{
		words.push_back(word);
	}
	return words;
}
std::vector<size_t>  AllTables::findIndexes(const std::vector<std::string>& data, const std::string& value)
{
	std::vector<size_t> result;
	for (size_t i = 0; i < data.size(); i++)
	{
		if (data[i] == value)
		{
			result.push_back(i);
		}
	}
	return result;
}


void AllTables::select(const size_t&  column_n,const std::string& value, const std::string& tableName)
{
	size_t tableIndex = findTableIndex(tableName);
	
	 
	Table searchedTable = tables_[tableIndex];
	
	std::vector<std::string> names; // get the names of the columns
	for (size_t i = 0; i < searchedTable.getColumns().size(); i++)
	{
		names.push_back(searchedTable.getColumns()[i]->getName());
	}
	
	//parse through the data and save the index of the values that match
	std::string columnData = searchedTable.getColumns()[column_n - 1]->printData();
	
	std::vector<size_t> matchingValueIndexes;
	matchingValueIndexes = findIndexes(splitDataIntoAVectorOfStrings(columnData), value);


	std::vector<std::string> dataColums;
	for (size_t i = 0; i < searchedTable.getSize(); i++)
	{
		dataColums.push_back(searchedTable.getColumns()[i]->printData());
	}
	//now we have a vector filled with the data of the table

	std::vector<std::vector<std::string>> splitTableData;
	for (size_t i = 0; i < dataColums.size(); i++)
	{
		std::vector<std::string> splitData = splitDataIntoAVectorOfStrings(dataColums[i]);
		splitTableData.push_back(splitData);
	}
	// now we should have a vector with all the data of the table but it is split
	
	std::vector<std::vector<std::string>> sortedTableData;
	
	
		for (size_t i = 0; i < splitTableData.size(); i++)
		{
			std::vector<std::string> temp;
			for (size_t j = 0; j < splitTableData[i].size(); j++)
			{
				for (size_t k = 0; k < matchingValueIndexes.size(); k++)
				{		
					if (j == matchingValueIndexes[k])
					{
						temp.push_back(splitTableData[i][j]);
					}
				}
			}
			sortedTableData.push_back(temp);
		}
	

	

	pagePrint(sortedTableData, names);

}
//yes i coppied all of the select function in select_onto // yes i know it is wrong // i didnt have time
void AllTables::select_onto(Table resultTable, std::vector<size_t> columnsToAdd, const size_t& column_n, const std::string& value, const std::string& tableName)
{
	size_t tableIndex = findTableIndex(tableName);

	Table searchedTable = tables_[tableIndex];

	std::vector<std::string> names; // get the names of the columns
	for (size_t i = 0; i < searchedTable.getColumns().size(); i++)
	{
		names.push_back(searchedTable.getColumns()[i]->getName());
	}

	std::vector<DataTypes> types;
	for (size_t i = 0; i < searchedTable.getColumns().size(); i++)
	{
		types.push_back(searchedTable.getColumns()[i]->getType());
	}

	//parse through the data and save the index of the values that match
	std::string columnData = searchedTable.getColumns()[column_n - 1]->printData();

	std::vector<size_t> matchingValueIndexes;
	matchingValueIndexes = findIndexes(splitDataIntoAVectorOfStrings(columnData), value);


	std::vector<std::string> dataColums;
	for (size_t i = 0; i < searchedTable.getSize(); i++)
	{
		dataColums.push_back(searchedTable.getColumns()[i]->printData());
	}
	//now we have a vector filled with the data of the table

	std::vector<std::vector<std::string>> splitTableData;
	for (size_t i = 0; i < dataColums.size(); i++)
	{
		std::vector<std::string> splitData = splitDataIntoAVectorOfStrings(dataColums[i]);
		splitTableData.push_back(splitData);
	}
	// now we should have a vector with all the data of the table but it is split

	std::vector<std::vector<std::string>> sortedTableData;


	for (size_t i = 0; i < splitTableData.size(); i++)
	{
		std::vector<std::string> temp;
		for (size_t j = 0; j < splitTableData[i].size(); j++)
		{
			for (size_t k = 0; k < matchingValueIndexes.size(); k++)
			{
				if (j == matchingValueIndexes[k])
				{
					temp.push_back(splitTableData[i][j]);
				}
			}
		}
		sortedTableData.push_back(temp);
	}
	//now we have a vector with all of the filtered rows
	

	// primer:						row
	// sortedTableData[0]: column [0]Dragan, [1]Maria
	// sortedTableData[1]:        [0]45	   , [1]42
	// sortedTableData[2]:		  [0]4	   , [1]4
	// sortedTableData[3]:		  [0]500.24, [1]535.92
	// 
	// meanwhile:
	// matchingValueIndexes = {1, 2} // we start from 0
	// 
	// so:
	// if the columnsToAdd vector contain 1 and/or 2 we add 
	// basically if: matchingValueIndexes[i] == columnsToAdd[j]; where have for(i) {for(j)}
	// we do this:
	// for(k)
	//	finalData += sortedTableData[i][k]
	// 
	//



	std::vector<std::vector<std::string>> finalData;
	std::vector<std::string> finalNames;
	std::vector<DataTypes> finalTypes;
	for (size_t i = 0; i < matchingValueIndexes.size(); i++)
	{
		for (size_t j = 0; j < columnsToAdd.size(); j++)
		{
			if (matchingValueIndexes[i] == columnsToAdd[j])
			{
				std::vector<std::string> finalDataMember;
				for (size_t k = 0; k < sortedTableData.size(); k++)
				{
					finalDataMember.push_back(sortedTableData[i][k]);

				}
				finalData.push_back(finalDataMember);
				finalNames.push_back(names[columnsToAdd[j]]);
				finalTypes.push_back(types[columnsToAdd[j]]);
			}
		}
	}
	// finalData is the filtred data that we will use
	//
	// primer:						row
	// finalData[0]: column [0]Dragan, [1]Maria
	// finalData[1]:        [0]45	 , [1]42
	// finalData[3]:		[0]500.24, [1]535.92
	// finalData[4]:		[0]500.24, [1]535.92
	// finalData[5]:		[0]45    , [1]42
	// 
	// now we need to turn it into a column data type
	
	std::ofstream file(resultTable.getFileName());
	if (!file.is_open())
	{
		throw "File not opened";
	}

	for (size_t i = 0; i < finalData.size(); i++)
	{
		file << finalNames[i] << "," << finalTypes[i] << ",";
		for (size_t j = 0; j < finalData[i].size(); j++)
		{
			file << finalData[i][j] << ",";
		}
		file << std::endl;
	}
	file.close();

	resultTable.readFromFile(resultTable.getFileName());

}

void AllTables::addColumn(const std::string& tableName, const std::string& name, const DataTypes& type)
{
	size_t tableIndex = findTableIndex(tableName);

	tables_[tableIndex].insertColumn(name,type);

}

void AllTables::update(const std::string& tableName, const size_t& searchColumnN, const std::string& searchValue, const size_t& targetColumnN, const std::string& targethValue)
{
	size_t tableIndex = findTableIndex(tableName);

	//find the indexes of the matching rows of the searchColumn
	//go to the targetColumn and change the value of the rows with matching indexes
	
	std::string searchColumnData = tables_[tableIndex].getColumns()[searchColumnN]->printData();
	//now we have a string with the data of the searched column

	std::vector<size_t> matchingSearchValueIndexes;
	matchingSearchValueIndexes = findIndexes(splitDataIntoAVectorOfStrings(searchColumnData), searchValue);

	std::vector<std::string> changedTargetData; // final product

	std::string targetColumnData = tables_[tableIndex].getColumns()[targetColumnN]->printData();
	std::vector<std::string> splitTargetData = splitDataIntoAVectorOfStrings(targetColumnData);


	for (size_t i = 0; i < matchingSearchValueIndexes.size(); i++)
	{
		for (size_t j = 0; j < splitTargetData.size(); j++)
		{
			if (matchingSearchValueIndexes[i] == j)
			{
				changedTargetData[j] = targethValue;
			}
			else
			{
				changedTargetData[j] = splitTargetData[j];
			}
		}
	}

	tables_[tableIndex].setDataInAColumn(changedTargetData, targetColumnN);

}

void AllTables::Mydelete(const std::string& tableName, const size_t& searchColumnN, const std::string& searchValue)
{
	size_t tableIndex = findTableIndex(tableName);

	std::string searchColumnData = tables_[tableIndex].getColumns()[searchColumnN]->printData();
	std::vector<std::string> splitData = splitDataIntoAVectorOfStrings(searchColumnData);
	//now we have a string vector with the data of the searched column

	std::vector<size_t> matchingSearchValueIndexes;
	matchingSearchValueIndexes = findIndexes(splitDataIntoAVectorOfStrings(searchColumnData), searchValue);
	
	std::vector<std::string> changedData; // final product

	for (size_t i = 0; i < matchingSearchValueIndexes.size(); i++)
	{
		for (size_t j = 0; j < splitData.size(); j++)
		{
			if (matchingSearchValueIndexes[i] == j)
			{
				if (tables_[tableIndex].getColumns()[searchColumnN]->getType() == DataTypes::STRING)
				{
					changedData[j] = "NULL";
				}
				else if (tables_[tableIndex].getColumns()[searchColumnN]->getType() == DataTypes::INT || tables_[tableIndex].getColumns()[searchColumnN]->getType() == DataTypes::DOUBLE)
				{
					changedData[j] = "0";
				}
			}
			else
			{
				changedData[j] = splitData[j];
			}
		}
	}

	tables_[tableIndex].setDataInAColumn(changedData, searchColumnN);

	



}

void AllTables::insert(std::string tableName, std::vector<std::string> columns)
{
	size_t tableIndex = findTableIndex(tableName);

	tables_[tableIndex].addRow(columns);

}

void AllTables::help() const
{
	std::cout << "Supported commands:" << std::endl;
	std::cout << "import <file name> - Add a new table from a file" << std::endl;
	std::cout << "showtables - Show a list of all table names" << std::endl;
	std::cout << "describe <name> - Show column types of a table" << std::endl;
	std::cout << "print <name> - Print all rows of a table" << std::endl;
	std::cout << "export <name> <file name> - Export table to a text file" << std::endl;
	std::cout << "select <column-n> <value> <table name> - Select rows by column value" << std::endl;
	std::cout << "select_onto <result_table> [<column_1>, <column_2>, ...] <column-n> <value> <table name> - Select rows and save to a new table" << std::endl;
	std::cout << "addcolumn <table name> <column name> <column type> - Add a new column to a table" << std::endl;
	std::cout << "update <table name> <search column n> <search value> <target column n> <target value> - Update rows by column value" << std::endl;
	std::cout << "delete <table name> <search column n> <search value> - Delete rows by column value" << std::endl;
	std::cout << "insert <table name> <column 1> … <column n> - Insert a new row" << std::endl;
	std::cout << "close - Close the current database" << std::endl;
	std::cout << "save - Save the current database" << std::endl;
	std::cout << "save as <new file name> - Save the current database as a new file" << std::endl;
	std::cout << "help - Show this help message" << std::endl;
	std::cout << "exit - Exit the application" << std::endl;
}

void AllTables::close()
{
	std::cout << "Do you want to save before closing? (yes/no)" << std::endl;
	std::string answer;
	std::cin >> answer;
	if (answer == "yes")
	{
		save();
	}
	std::cout << "Closing" << std::endl;

	tables_.clear();
}

void AllTables::save()
{
	for (size_t i = 0; i < tables_.size(); i++)
	{
		tables_[i].saveToFile(tables_[i].getFileName());
	}
}

void AllTables::saveAs(const std::string& filenName)
{
	std::cout << "What table do you want to save in" << filenName << std::endl;
	std::string answer;
	std::cin >> answer;

	size_t tableIndex = findTableIndex(answer);
	if (tableIndex < 0)
	{
		std::cout << "This table doesn't exist. Try again: " << std::endl;
		answer.clear();
		std::cin >> answer;
	}

	//tables_[tableIndex].setFileName(filenName);
	tables_[tableIndex].saveToFile(filenName);

}

void AllTables::exit()
{
	std::cout << "Do you want to save before exiting? (yes/no)" << std::endl;
	std::string answer;
	std::cin >> answer;
	if (answer == "yes")
	{
		save();
	}
	std::cout << "Exiting" << std::endl;
	std::exit(0);
}

void AllTables::open(const std::string& fileName) // needs fixing
{
	std::ifstream file(fileName);
	if (!file.is_open()) 
	{
		// File does not exist, create a new empty file
		std::ofstream newFile(fileName);
		if (!newFile.is_open()) 
		{
			std::cerr << "Error creating file: " << fileName << std::endl;
			return;
		}
		newFile.close();
		std::cout << "Successfully created and opened " << fileName << std::endl;
	}
	else 
	{
		std::cout << "Successfully opened " << fileName << std::endl;
	}
	


}

