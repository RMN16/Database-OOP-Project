#include "ColumnInt.h"

std::string ColumnInt::intToString(int value) const
{
    char buffer[50];
    snprintf(buffer, sizeof(buffer), "%d", value);
    return std::string(buffer);
}

ColumnInt::ColumnInt()
{
    setType(DataType::INT);
}

ColumnInt::ColumnInt(std::vector<int> data, std::string name)
{
    setType(DataType::INT);
    data_ = data;
    setName(name);
}

//overrites the current data
void ColumnInt::setData(std::vector<std::string> data)
{
    if (data_.size() < data.size())
    {
        data_.resize(data.size());
    }
    for (size_t i = 0; i < data.size(); i++)
    {
        int value = std::stoi(data[i]);
        data_[i] = value;
    }
}

void ColumnInt::setDataToSize(std::vector<std::string>& data, const size_t& size)
{
    if (data.size() < size)
    { 
        data.resize(size);
    }
    if (data_.size() < data.size())
    {
        data_.resize(data.size());
    }

    for (size_t i = 0; i < data.size(); i++)
    {
        int value;
        bool flag = true;
        if (data[i].size() != 0) // .epty() breaks the code for some reason
        {
            for (size_t j = 0; j < data[i].size(); j++)
            {
                if (!std::isdigit(data[i][j]))
                {
                    flag = false;
                }
            }
            if (flag)
            {
                value = std::stoi(data[i]);
            }
            else
            {
                value = INT_MIN;
            }
        }
        else
        {
            value = INT_MIN;
        }
        data_[i] = value;
    }
}



std::string ColumnInt::printData() const
{
    std::string printed;

    for (size_t i = 0; i < data_.size(); ++i)
    {
        if (data_[i] == INT_MIN)
        {
            printed += "NULL";
        }
        else
        {
            printed += intToString(data_[i]);
        }
        if (i < data_.size() - 1) 
        {
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

Column* ColumnInt::clone() const
{
    return new ColumnInt(*this);
}
