#include "ColumnInt.h"

std::string ColumnInt::intToString(int value) const
{
    char buffer[50];
    snprintf(buffer, sizeof(buffer), "%d", value);
    return std::string(buffer);
}

ColumnInt::ColumnInt()
{
    setType(DataTypes::INT);
}

ColumnInt::ColumnInt(std::vector<int> data, std::string name)
{
    setType(DataTypes::INT);
    data_ = data;
    setName(name);
}

void ColumnInt::setData(std::vector<std::string> data)
{
    for (const auto& str : data)
    {
        int value = std::stoi(str);
        data_.push_back(value);
    }
}



std::string ColumnInt::printData() const
{
    std::string printed;

    for (size_t i = 0; i < data_.size(); ++i)
    {
        printed += intToString(data_[i]);
        if (i < data_.size() - 1) {
            printed += ",";
        }
    }

    return printed;
}

size_t ColumnInt::getDataSize() const
{
    return data_.size();
}

void ColumnInt::addData(const std::string& newData)
{
    data_.push_back(std::stoi(newData));
}
