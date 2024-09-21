#pragma once
#include "Column.h"

class ColumnInt :
     public Column
{
private:
	std::vector<int> data_;


	std::string intToString(int value) const;

public:
	ColumnInt();
	ColumnInt(std::vector<int> data, std::string name);

	virtual void setData(std::vector<std::string> data) override;
	virtual void setDataToSize(std::vector<std::string>& data, const size_t& size) override;

	virtual std::string printData() const override;
	virtual size_t getDataSize() const override;

	virtual void addData(const std::string& newData) override;
	virtual Column* clone() const;
	
};

