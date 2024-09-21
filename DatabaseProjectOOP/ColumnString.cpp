#include "ColumnString.h"

ColumnString::ColumnString()
{
	
	setType(DataType::STRING);
}

ColumnString::ColumnString(std::vector<std::string> data, std::string name)
{
	setType(DataType::STRING);
	data_ = data;
	setName(name);
}

//overrites the current data
void ColumnString::setData(std::vector<std::string> data)
{
	data_ = data;
}

void ColumnString::setDataToSize(std::vector<std::string>& data, const size_t& size)
{
	if (data.size() < size)
	{
		for (size_t i = 0; i < (size - data.size()); i++)
		{
			data.push_back("NULL");
		}
	}
	data_ = data;
}

std::string ColumnString::printData() const
{
	std::string printed;

	for (size_t i = 0; i < data_.size(); i++)
	{
		printed.append(data_[i]);
		if (i+1 != data_.size())
		{
			printed.append(",");
		}
		
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

Column* ColumnString::clone() const
{
	return new ColumnString(*this);
}
