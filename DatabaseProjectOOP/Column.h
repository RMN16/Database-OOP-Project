#pragma once
#include <string>
#include <vector>

enum DataType
{
    UNDEFINED = -1,
    INT = 0,
    DOUBLE = 1,
    STRING = 2
};


class Column {
private:
    std::string name_;
    DataType type_ = DataType::UNDEFINED;

public:

    Column() = default;
    Column(const std::string& name, DataType type);
    virtual ~Column() = default;

    std::string getName() const;
    DataType getType() const;

    virtual void setName(std::string name);
    virtual void setType(DataType type);
    
    virtual void setData(std::vector<std::string> data) = 0; //overrites the current data
    virtual void setDataToSize(std::vector<std::string>& data, const size_t& size) = 0; // like setData, but it checks for invalid sizes

    virtual Column* clone() const = 0;
    virtual std::string printData() const = 0; // data11,data12,data13,...,data1n
    virtual size_t getDataSize() const = 0; // returns the number of data rows
    virtual void addData(const std::string& newData) = 0;

};

