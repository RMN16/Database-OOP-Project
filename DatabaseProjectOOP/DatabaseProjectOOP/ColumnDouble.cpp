#include "ColumnDouble.h"

std::string ColumnDouble::doubleToString(double value) const
{
    char buffer[1024];
    snprintf(buffer, sizeof(buffer), "%g", value);
    return std::string(buffer);
}

ColumnDouble::ColumnDouble()
{
    setType(DataTypes::DOUBLE);
}

ColumnDouble::ColumnDouble(std::vector<double> data, std::string name)
{
    setType(DataTypes::DOUBLE);
    data_ = data;
    setName(name);
}

void ColumnDouble::setData(std::vector<std::string> data)
{
    for (const auto& str : data)
    {
        double value = std::stod(str);
        data_.push_back(value);
    }
}



std::string ColumnDouble::printData() const
{
    std::string printed;

    for (size_t i = 0; i < data_.size(); ++i)
    {
        printed += doubleToString(data_[i]);
        if (i < data_.size() - 1) {
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
