#include "Column.h"


Column::Column(const std::string& name, DataType type)
    : name_(name), type_(type)
{

}

std::string Column::getName() const
{
    return name_;
}

DataType Column::getType() const
{
    return type_;
}

void Column::setName(std::string name)
{
    name_ = name;
}

void Column::setType(DataType type)
{
    type_ = type;
}
