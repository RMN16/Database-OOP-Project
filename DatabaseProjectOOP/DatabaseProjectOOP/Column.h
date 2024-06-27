#pragma once
#include <string>
#include <vector>

enum DataTypes
{
    UNDEFINED = -1,
    INT = 0,
    DOUBLE = 1,
    STRING = 2
};


class Column {
private:
    std::string name_;
    DataTypes type_ = DataTypes::UNDEFINED;

public:

    Column() = default;
    Column(const std::string& name, DataTypes type);
    virtual ~Column() = default;

    std::string getName() const;
    DataTypes getType() const;

    
    //virtual void setData(void* newData) = 0;

    virtual void setName(std::string name);
    virtual void setType(DataTypes type);
    
    virtual void setData(std::vector<std::string> data) = 0;
    virtual std::string printData() const = 0; // data11,data12,data13,...,data1n
    virtual size_t getDataSize() const = 0; // returns the number of data rows
    virtual void addData(const std::string& newData) = 0;




};

