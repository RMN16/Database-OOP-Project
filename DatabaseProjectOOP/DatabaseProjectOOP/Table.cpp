#include <fstream>
#include "Table.h"

Table::Table(std::vector<Column*> columns, std::string tableName, std::string fileName)
{
	columns_ = columns;
	tableName_ = tableName;
	filename_ = fileName;
	size_ = columns.size();
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
		throw "File not opened";
	}

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
		throw "File not opened";
	}

	for (size_t i = 0; i < columns_.size(); i++)
	{
		file << columns_[i]->getName() << "," << columns_[i]->getType() << "," << columns_[i]->printData() << std::endl;
	}
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

void Table::readFromFile(std::string fileName)
{
	std::ifstream file(fileName);

	if (!file.is_open())
	{
		throw "File not opened";
	}

	filename_ = fileName;
	size_t dot = filename_.find_last_of('.');
	tableName_ = filename_.substr(0, dot);

	std::vector<std::string> names;
	std::vector<std::string> types;
	std::vector<std::vector<std::string>> data;

	//filing the vectors
	std::string line;
	while (std::getline(file, line)) {
		std::string name;
		std::string type;
		std::vector<std::string> dataRow;

		splitLine(line, name, type, dataRow);

		names.push_back(name);
		types.push_back(type);
		data.push_back(dataRow);
	}
	file.close();

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
		columns_[i]->setName(names[i]);

		if (types[i] == "0")
		{
			columns_[i]->setType(DataTypes::INT);
		}
		else if (types[i] == "1")
		{
			columns_[i]->setType(DataTypes::DOUBLE);
		}
		else if (types[i] == "2")
		{
			columns_[i]->setType(DataTypes::STRING);
		}
		else
		{
			columns_[i]->setType(DataTypes::UNDEFINED);
		}

		columns_[i]->setData(data[i]);
	}


}

void Table::insertColumn(const std::string& name, const DataTypes& type)
{
	Column* newCol;

	if (type == DataTypes::INT)
	{
		std::vector<int> data;
		newCol = new ColumnInt(data, name);
	}
	else if (type == DataTypes::DOUBLE)
	{
		std::vector<double> data;
		newCol = new ColumnDouble(data, name);
	}
	else if (type == DataTypes::STRING)
	{
		std::vector<std::string> data;
		newCol = new ColumnString(data, name);
	}
	columns_.push_back(newCol);
	
	size_++;
}

void Table::addRow(const std::vector<std::string> rowData)
{
	size_++;
	for (size_t i = 0; i < columns_.size(); i++)
	{
		columns_[i]->addData(rowData[i]);
	}

}


