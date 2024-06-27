#include "ColumnString.h"

ColumnString::ColumnString()
{
	
	setType(DataTypes::STRING);
}

ColumnString::ColumnString(std::vector<std::string> data, std::string name)
{
	setType(DataTypes::STRING);
	data_ = data;
	setName(name);
}

void ColumnString::setData(std::vector<std::string> data)
{
	data_ = data;
}

std::string ColumnString::printData() const
{
	std::string printed;

	for (size_t i = 0; i < data_.size(); i++)
	{
		printed.append(data_[i]);
		printed.append(",");
	}

	return printed;

}

size_t ColumnString::getDataSize() const
{
	return data_.size();
}

void ColumnString::addData(const std::string& newData)
{
	data_.push_back(newData);
}
