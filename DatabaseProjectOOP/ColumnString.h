#pragma once
#include "Column.h"

class ColumnString :
    public Column
{
private:
	std::vector<std::string> data_;

public:
	ColumnString();
	ColumnString(std::vector<std::string> data, std::string name);

	virtual void setData(std::vector<std::string> data) override;
	virtual void setDataToSize(std::vector<std::string>& data, const size_t& size) override;

	virtual std::string printData() const override;
	virtual size_t getDataSize() const override;

	virtual void addData(const std::string& newData) override;
	virtual Column* clone() const;

};

