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
	void convertNullToIntMIN(std::vector<std::string>& data);
	
	void copyFrom(const Table& other);
	void free();

public:

	Table() = default; // do i need to make it custom?
	~Table();
	Table(const Table& other);
	Table& operator=(const Table& other);

	
	Table(std::vector<Column*> columns, std::string tableName, std::string fileName);
	Table(const std::string& filename);

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

	void readFromFile(const std::string& fileName);

	void insertColumn(const std::string& name, const DataType& type);

	void addRow(const std::vector<std::string> rowData);


};

