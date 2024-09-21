#include "ColumnDouble.h"

std::string ColumnDouble::doubleToString(double value) const
{
    char buffer[1024];
    snprintf(buffer, sizeof(buffer), "%g", value);
    return std::string(buffer);
}

ColumnDouble::ColumnDouble()
{
    setType(DataType::DOUBLE);
}

ColumnDouble::ColumnDouble(std::vector<double> data, std::string name)
{
    setType(DataType::DOUBLE);
    data_ = data;
    setName(name);
}

//overrites the current data
void ColumnDouble::setData(std::vector<std::string> data)
{
    if (data_.size() < data.size())
    {
        data_.resize(data.size());
    }
    for (size_t i = 0; i < data.size(); i++)
    {
        double value = std::stod(data[i]);
        data_[i] = value;
    }
}

void ColumnDouble::setDataToSize(std::vector<std::string>& data, const size_t& size)
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
        double value;
        bool flag = true;
        if (data[i].size() != 0)
        {
            for (size_t j = 0; j < data[i].size(); j++)
            {
                if (!(std::isdigit(data[i][j]) || data[i][j] == '.'))
                {
                    flag = false;
                }
            }
            if (flag)
            {
                value = std::stod(data[i]);
            }
            else
            {
                value = (double)INT_MIN;
            }
        }
        else
        {
            value = (double)INT_MIN;
        }
        data_[i] = value;
    }

}

std::string ColumnDouble::printData() const
{
    std::string printed;

    for (size_t i = 0; i < data_.size(); ++i)
    {
        if (data_[i] == (double)INT_MIN)
        {
            printed += "NULL";
        }
        else
        {
            printed += doubleToString(data_[i]);
        }
        if (i < data_.size() - 1) 
        {
            printed += ",";
        }
    }

    return printed;
}

size_t ColumnDouble::getDataSize() const
{
    return data_.size();
}

void ColumnDouble::addData(const std::string& newData)
{
    data_.push_back(std::stod(newData));
}

Column* ColumnDouble::clone() const
{
    return new ColumnDouble(*this);
}




