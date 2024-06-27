#include "Column.h"


Column::Column(const std::string& name, DataTypes type)
    : name_(name), type_(type)
{

}

std::string Column::getName() const
{
    return name_;
}

DataTypes Column::getType() const
{
    return type_;
}

void Column::setName(std::string name)
{
    name_ = name;
}

void Column::setType(DataTypes type)
{
    type_ = type;
}
