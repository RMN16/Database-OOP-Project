#include <fstream>
#include <iostream>
#include "Table.h"

Table::Table(std::vector<Column*> columns, std::string tableName, std::string fileName)
{
	columns_ = columns;
	tableName_ = tableName;
	filename_ = fileName;
	size_ = columns.size();
}

Table::Table(const std::string& filename)
{
	readFromFile(filename);
}

void Table::setTableName(const std::string tablename)
{
	tableName_ = tablename;
}
void Table::setFileName(const std::string filename)
{
	filename_ = filename;
}
void Table::setColumns(const std::vector<Column*> columns)
{
	columns_ = columns;
}

void Table::setDataInAColumn(std::vector<std::string> data, const size_t& index)
{
	columns_[index]->setData(data);
}


std::string Table::getTableName() const
{
	return tableName_;
}
size_t Table::getSize() const
{
	return size_;
}
std::string Table::getFileName() const
{
	return filename_;
}
std::vector<Column*> Table::getColumns() const
{
	return columns_;
}

void Table::insertIntoFile() const
{
	std::ofstream file(filename_, std::ios::app);

	if (!file.is_open())
	{
		std::cerr << "File not opened" << std::endl;
	}

	file << tableName_ << std::endl;

	for (size_t i = 0; i < columns_.size(); i++)
	{
		file << columns_[i]->getName() << "," << columns_[i]->getType() << "," << columns_[i]->printData() << std::endl;
	}

}

void Table::saveToFile(const std::string fileName) const
{
	std::ofstream file(fileName);

	if (!file.is_open())
	{
		std::cerr << "Failed to open the file - ofstream" << std::endl;
		return;
	}

	if (columns_.size() == 0)
	{
		file.close();
		return;
	}

	file << tableName_ << std::endl;

	for (size_t i = 0; i < columns_.size(); i++)
	{
		file << columns_[i]->getName() << "," << columns_[i]->getType() << "," << columns_[i]->printData() << std::endl;
	}
	file.close();
}

//helper function that puts the name, type and data into different variables 
void Table::splitLine(const std::string& line, std::string& name, std::string& type, std::vector<std::string>& data) {
	size_t pos = 0;
	size_t prev_pos = 0;

	pos = line.find(',', prev_pos);
	if (pos != std::string::npos) {
		name = line.substr(prev_pos, pos - prev_pos);
		prev_pos = pos + 1;
	}

	pos = line.find(',', prev_pos);
	if (pos != std::string::npos) {
		type = line.substr(prev_pos, pos - prev_pos);
		prev_pos = pos + 1;
	}

	while ((pos = line.find(',', prev_pos)) != std::string::npos) {
		data.push_back(line.substr(prev_pos, pos - prev_pos));
		prev_pos = pos + 1;
	}
	data.push_back(line.substr(prev_pos));
}

void Table::convertNullToIntMIN(std::vector<std::string>& dataRow)
{
	for (size_t i = 0; i < dataRow.size(); i++)
	{
		if (dataRow[i] == "NULL")
		{
			dataRow[i] = INT_MIN;
		}
	}
}

void Table::copyFrom(const Table& other)
{
	size_ = other.size_;
	tableName_ = other.tableName_;
	filename_ = other.filename_;

	for (size_t i = 0; i < size_; i++)
	{
		Column* newObj = other.columns_[i]->clone();
		columns_.push_back(newObj);
	}
}

void Table::free()
{
	tableName_.clear();
	filename_.clear();
	for (size_t i = 0; i < size_; i++)
	{
		delete columns_[i];
	}
	columns_.clear(); // nessasary?
	size_ = 0;

}

//Table::Table()
//{
//}

Table::~Table()
{
	free();
}

Table::Table(const Table& other)
{
	copyFrom(other);
}

Table& Table::operator=(const Table& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

void Table::readFromFile(const std::string& fileName)
{
	//if the file doens't exist we create it
	std::ofstream fileO(fileName,std::ios::app);
	fileO.close();

	std::ifstream file(fileName);
	if (!file.is_open())
	{
		std::cerr << "Failed to open the file - ifstream" << std::endl;
		return;
	}

	filename_ = fileName;
	
	//first line is the name of the table
	std::getline(file,tableName_);
	if (file.peek() == std::ifstream::traits_type::eof()) //check if the file is empty
	{
		return;
	}

	std::vector<std::string> names;
	std::vector<std::string> types;
	std::vector<std::vector<std::string>> data;

	//filing the vectors
	std::string line;
	do 
	{
		std::getline(file, line);

		std::string name;
		std::string type;
		std::vector<std::string> dataRow;

		if (line.empty())
		{
			break;
		}
		splitLine(line, name, type, dataRow);

		names.push_back(name);
		types.push_back(type);
		data.push_back(dataRow);

	} while (file.good());
	file.close();

	//make NULL into INT_MIN for the int and double types // DBL_MIN can't be cast into const char*
	for (size_t i = 0; i < data.size(); i++)
	{
		if (types[i] == "0" || types[i] == "1")
		{
			convertNullToIntMIN(data[i]);
		}
	}


	//find the longest vector so that we dont end up with missing data
	size_ = names.size();
	if (size_ < types.size())
	{
		size_ = types.size();
	}
	else if (size_ < data.size())
	{
		size_ = data.size();
	}

	
	for (size_t i = 0; i < size_; i++)
	{
		
		if (types[i] == "0")
		{
			columns_.push_back(new ColumnInt());
		}
		else if (types[i] == "1")
		{
			columns_.push_back(new ColumnDouble());
		}
		else if (types[i] == "2")
		{
			columns_.push_back(new ColumnString());
		}
		else
		{
			throw std::runtime_error("Undefined data type"); // should it be std::cerr
		}

		columns_[i]->setName(names[i]);
		columns_[i]->setDataToSize(data[i],size_);
	}

}

void Table::insertColumn(const std::string& name, const DataType& type)
{
	Column* newCol;
	size_++;

	if (type == DataType::INT)
	{
		std::vector<int> data;
		for (size_t i = 0; i < size_; i++) // adding the null values in the object
		{
			data.push_back(0);
		}

		newCol = new ColumnInt(data, name);
	}
	else if (type == DataType::DOUBLE)
	{
		std::vector<double> data;
		for (size_t i = 0; i < size_; i++)// adding the null values in the object
		{
			data.push_back(0);
		}
		newCol = new ColumnDouble(data, name);
	}
	else if (type == DataType::STRING)
	{
		std::vector<std::string> data;
		for (size_t i = 0; i < size_; i++)// adding the null values in the object
		{
			data.push_back("NULL");
		}
		newCol = new ColumnString(data, name);
	}
	columns_.push_back(newCol);
	
	

	

}

void Table::addRow(const std::vector<std::string> rowData)
{
	size_++;
	for (size_t i = 0; i < columns_.size(); i++)
	{
		try
		{
			columns_[i]->addData(rowData[i]);

		}
		catch (const std::out_of_range& err)
		{
			size_--;
			std::cout << err.what();
			throw std::invalid_argument("Your rows have invalid types in them");
		}
	}

}


