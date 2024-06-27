#pragma once
#include <fstream>
#include <iostream>
#include "Table.h"

class AllTables :
    public Table
{
private:
    std::vector<Table> tables_;


    //helper functions
    std::vector<std::string> splitDataIntoAVectorOfStrings(const std::string& str);
    std::vector<size_t> findIndexes(const std::vector<std::string>& data, const std::string& value);
    void pagePrint(std::vector<std::vector<std::string>> data, std::vector<std::string> names) const;

   
    
public:
    std::vector<Table> getTables() const;


    size_t findTableIndex(std::string tableName);
    void addTable(Table table);

    void import(const char* filename);
    void showtables() const;
    void describe(std::string filename) const;
    void print(std::string filename) const;

    void Myexport(const char* name, const char* filename);


    void select(const size_t& column_n, const std::string& value, const std::string& tableName);
    void select_onto(Table resultTable, std::vector<size_t> columnsToAdd, const size_t& column_n, const std::string& value, const std::string& tableName);

    void addColumn(const std::string& tableName, const std::string& name, const DataTypes& type);

    void update(const std::string& tableName, const size_t& searchColumnN, const std::string& searchValue, const size_t& targetColumnN, const std::string& targethValue);

    void Mydelete(const std::string& tableName, const size_t& searchColumnN, const std::string& searchValue);

    void insert(std::string tableName, std::vector<std::string> columns);

    void help() const;
    void close();
    void save();
    void saveAs(const std::string& filenName);
    void exit();
    void open(const std::string& fileName);
};
