#pragma once
#include "ColumnInt.h"
#include "ColumnDouble.h"
#include "ColumnString.h"



class Table

{
private: 
	std::vector<Column*> columns_;
	std::string tableName_;
	size_t size_ = 0;

	std::string filename_;


	void splitLine(const std::string& line, std::string& name, std::string& type, std::vector<std::string>& data);

public:
	Table() = default;
	Table(std::vector<Column*> columns, std::string tableName, std::string fileName);

	void setTableName(const std::string tablename);
	void setFileName(const std::string filename);
	void setColumns(const std::vector<Column*> columns);

	void setDataInAColumn(std::vector<std::string> data, const size_t& index);

	std::string getTableName() const;
	size_t getSize() const;
	std::string getFileName() const;
	std::vector<Column*> getColumns() const;

	void insertIntoFile() const;
	void saveToFile(const std::string fileName) const;

	void readFromFile(std::string fileName);

	void insertColumn(const std::string& name, const DataTypes& type);

	void addRow(const std::vector<std::string> rowData);


};

