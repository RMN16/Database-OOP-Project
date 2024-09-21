#include "DataBase.h"
#pragma warning(disable:4996)


std::vector<Table> DataBase::getTables() const
{
	return tables_;
}

int DataBase::findTableIndex(const std::string& tableName)
{
	int tableIndex = -1;
	for (int i = 0; i < tables_.size(); i++)
	{
		if (tableName == tables_[i].getTableName())
		{
			tableIndex = i;
			break;
		}
	}
	
	if (tableIndex == -1)
	{
		std::cerr << "Table doesn't exist in the database." << std::endl;
	}
	
	return tableIndex;
}

void DataBase::addTable(Table table)
{
	tables_.push_back(table);
}

void DataBase::import(const std::string& filename)
{
	
	//check if filename already exists
	std::ifstream catalogueI("catalogue.txt");
	if (!catalogueI.is_open())
	{
		std::cerr << "Failed to open the catalogue - ifstream" << std::endl;
		return;
	}

	std::string tableBuff;
	std::string fileBuff;
	std::string line;
	while (std::getline(catalogueI, line))
	{
		size_t commaPositionInLine = line.find(',');
		if (commaPositionInLine != std::string::npos)
		{
			tableBuff = line.substr(0, commaPositionInLine);
			fileBuff = line.substr(commaPositionInLine + 1);
		}

		try
		{
			if (filename == fileBuff)
			{
				std::cerr << filename << std::endl;
			}
		}
		catch (const std::string& err)
		{
			std::cout << "File/Table already exists in the catalogue" << std::endl;
			return;
		}

	}
	catalogueI.close();

	//read the name of the table
	std::ifstream file(filename);
	if (!file.is_open())
	{
		std::cerr << "Failed to open the file - ifstream" << std::endl;
		return;
	}
	std::string tablename;

	if (!std::getline(file, tablename))
	{
		if (file.eof())
		{
			std::cout << "No name for the table found. Using filename as tablename." << std::endl;
			size_t dotPosition = filename.find_last_of('.');
			tablename = filename.substr(0, dotPosition);
		}
		else if (file.fail())
		{
			std::cout << "Failed to read file. Using filename as tablename." << std::endl;
			size_t dotPosition = filename.find_last_of('.');
			tablename = filename.substr(0, dotPosition);
		}
	}
	file.close();

	//add the new table in the catalogue
	std::ofstream catalogueO("catalogue.txt", std::ios::app);
	if (!catalogueO.is_open())
	{
		std::cerr << "Failed to open the catalogue - ofstream" << std::endl;
		return;
	}

	catalogueO << tablename << "," << filename << '\n';
	catalogueO.close();

	//create a Table object in the Database
	Table newTable;
	newTable.readFromFile(filename);

	tables_.push_back(newTable);
}

void DataBase::showtables() const
{
	std::ifstream catalogueI("catalogue.txt");
	if (!catalogueI.is_open())
	{
		std::cerr << "Catalogue not found!" << std::endl;
		return;
	}

	std::string line;
	while (std::getline(catalogueI, line))
	{
		size_t commaPositionInLine = line.find(',');
		if (commaPositionInLine != std::string::npos)
		{
			std::string table = line.substr(0, commaPositionInLine);
			std::cout << table << std::endl;
		}
	}

	catalogueI.close();
}

void DataBase::describe(std::string filename) const
{
	int numOfTypes[3] = { 0 }; // 0- int, 1-double, 2-string

	std::ifstream file(filename);
	if (!file.is_open())
	{
		std::cerr << "Failed to open the file - ifstream" << std::endl;
		return;
	}


	std::string line;
	std::getline(file, line); // skip the first line which is the name of the table

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
void DataBase::pagePrint(std::vector<std::vector<std::string>> data, std::vector<std::string> names) const
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

void DataBase::print(std::string filename) const
{
	std::ifstream file(filename);
	if (!file.is_open())
	{
		std::cerr << "Failed to open the file - ifstream" << std::endl;
		return;
	}

	//Idea
	// 1. put the first colum in a vector
	// 2. put the data in a vector or vectors
	// 3. print pages

	std::string line;
	std::vector<std::string> names;
	std::vector<std::vector<std::string>> data;

	std::getline(file, line); // skip the first line which is the name of the table
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


void DataBase::Myexport(const std::string& name, const std::string& filename) // "export" word makes the program fail
{
	for (size_t i = 0; i < tables_.size(); i++)
	{
		std::string tablename = tables_[i].getTableName();
		
		if (name == tablename)
		{
			tables_[i].saveToFile(filename);
			break;
		}
	}
}

//split the data into a vector of words so that i can find the matching values better
std::vector<std::string>  DataBase::splitDataIntoAVectorOfStrings(const std::string& str)
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
std::vector<size_t>  DataBase::findIndexes(const std::vector<std::string>& data, const std::string& value)
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


void DataBase::select(const size_t&  column_n,const std::string& value, const std::string& tableName)
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


void DataBase::select_onto(Table resultTable, std::vector<size_t> columnsToAdd, const size_t& column_n, const std::string& value, const std::string& tableName)
{
	try
	{
		findTableIndex(tableName);
	}
	catch (std::invalid_argument err)
	{
		std::cout << err.what() << std::endl;
		return;
	}
	size_t tableIndex = findTableIndex(tableName);

	Table searchedTable = tables_[tableIndex];

	std::vector<std::string> names; // get the names of the columns
	for (size_t i = 0; i < searchedTable.getColumns().size(); i++)
	{
		names.push_back(searchedTable.getColumns()[i]->getName());
	}

	std::vector<DataType> types;
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
	

	// example:					   row
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
	std::vector<DataType> finalTypes;
	for (size_t i = 0; i < matchingValueIndexes.size(); i++)
	{
		for (size_t j = 0; j < columnsToAdd.size(); j++)
		{
			std::vector<std::string> finalDataMember;
			for (size_t k = 0; k < sortedTableData[columnsToAdd[j] - 1].size(); ++k)
			{
				finalDataMember.push_back(sortedTableData[columnsToAdd[j] - 1][k]);
			}

			finalData.push_back(finalDataMember);
			finalNames.push_back(names[columnsToAdd[j] - 1]);
			finalTypes.push_back(types[columnsToAdd[j] - 1]);
			
		}
	}
	// finalData is the filtred data that we will use
	//
	// example:				row
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
		std::cerr << "File not opened - ofstream" << std::endl;
		return;
	}

	file << resultTable.getTableName() << std::endl;

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

void DataBase::addColumn(const std::string& tableName, const std::string& name, const DataType& type)
{
	int tableIndex;
	try
	{
		tableIndex = findTableIndex(tableName);
	}
	catch (const std::invalid_argument& err)
	{
		std::cout << err.what() <<" Please enter a valid table name!" << std::endl;
		return;
	}
	
	tables_[tableIndex].insertColumn(name,type);

}

void DataBase::update(const std::string& tableName, const size_t& searchColumnN, const std::string& searchValue, const size_t& targetColumnN, const std::string& targethValue)
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

void DataBase::Mydelete(const std::string& tableName, const size_t& searchColumnN, const std::string& searchValue) //delete is a saved word
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
				if (tables_[tableIndex].getColumns()[searchColumnN]->getType() == DataType::STRING)
				{
					changedData[j] = "NULL";
				}
				else if (tables_[tableIndex].getColumns()[searchColumnN]->getType() == DataType::INT || tables_[tableIndex].getColumns()[searchColumnN]->getType() == DataType::DOUBLE)
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

void DataBase::insert(std::string tableName, std::vector<std::string> columns)
{
	size_t tableIndex = findTableIndex(tableName);

	try
	{
		tables_[tableIndex].addRow(columns);
	}
	catch (const std::invalid_argument& err)
	{
		std::cout << err.what() << "Please enter valid arguments!" << std::endl;
	}
}

void DataBase::help() const
{
	std::cout << "Supported commands:" << std::endl;
	std::cout << "import <file name> - Add a new table from a file;" << std::endl;
	std::cout << "showtables - Show a list of all table names;" << std::endl;
	std::cout << "describe <table name> - Shows the column type counts of a table;" << std::endl;
	std::cout << "print <table name> - Print all rows of a table;" << std::endl;
	std::cout << "export <table name> <file name> - Export table to a text file;" << std::endl;
	std::cout << "select <column-n> <value> <table name> - Select rows by column value;" << std::endl;
	std::cout << "select_onto <result_table> [<column_1>, <column_2>, ...] <column-n> <value> <table name> - Select rows and save to a new table;" << std::endl;
	std::cout << "addcolumn <table name> <column name> <column type> - Adds an empty column to a table;" << std::endl;
	std::cout << "update <table name> <search column n> <search value> <target column n> <target value> - Update rows by column value;" << std::endl;
	std::cout << "delete <table name> <search column n> <search value> - Delete rows by column value;" << std::endl;
	std::cout << "insert <table name> <column 1> … <column n> - Insert a new row;" << std::endl;
	std::cout << "close - Close all the tables in the current database;" << std::endl;
	std::cout << "save - Save the current database;" << std::endl;
	std::cout << "saveAs <new file name> - Saves the current table to a new file;" << std::endl;
	std::cout << "help - Shows supported commands;" << std::endl;
	std::cout << "exit - Exit the application." << std::endl;
}

void DataBase::close()
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

void DataBase::save() //make save add the filenames in the catalogue
{
	std::cout << "Sving tables..";
	for (size_t i = 0; i < tables_.size(); i++)
	{
		std::cout << ".";
		tables_[i].saveToFile(tables_[i].getFileName());
	}

	std::cout << std::endl << "Saving new tables into the catalogue.." << std::endl;
	
	//fancy code to stop the import function from printing errors
	std::ofstream nullStream("/dev/null");
	std::streambuf* coutBuf = std::cout.rdbuf(); // Save old buffer
	std::cout.rdbuf(nullStream.rdbuf());         // Redirect cout to /dev/null

	for (size_t i = 0; i < tables_.size(); i++)
	{
		import(tables_[i].getFileName());
	}
	
	std::cout.rdbuf(coutBuf);

}

void DataBase::saveAs(const std::string& filenName)
{
	std::cout << "What table do you want to save in: " << filenName << std::endl;
	std::string answer;
	std::cin >> answer;
	size_t tableIndex;
	bool flag = true;
	while (flag)
	{
		try
		{
			tableIndex = findTableIndex(answer);
		}
		catch (std::invalid_argument err)
		{
			std::cout << err.what() <<" Try again: " << std::endl;
			answer.clear();
			std::cin >> answer;
			continue;
		}
		flag = false;
	
		
	}

	//tables_[tableIndex].setFileName(filenName);
	tables_[tableIndex].saveToFile(filenName);

}

void DataBase::exit()
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

void DataBase::open(const std::string& filename)
{
	//check if filename if in the catalogue
	std::ifstream catalogueI("catalogue.txt");
	if (!catalogueI.is_open())
	{
		std::cerr << "Failed to open the file - ifstream" << std::endl;
		return;
	}

	std::string fileBuff;
	bool exists = false;

	std::string line;
	while (std::getline(catalogueI, line))
	{
		size_t commaPositionInLine = line.find(',');
		if (commaPositionInLine != std::string::npos)
		{
			fileBuff = line.substr(commaPositionInLine + 1);
		}

		if (filename == fileBuff)
		{
			exists = true;
			break;
		}
	}
	catalogueI.close();
	
	
	if (!exists) // if the file name has not been found create an empty table
	{
		Table emptyTable(filename);
		tables_.push_back(emptyTable);
		return;
	}

	//create the table and add it to the database
	Table newTable(filename);
	tables_.push_back(newTable);
	std::cout << "File " << filename << " opened." << std::endl;

}

