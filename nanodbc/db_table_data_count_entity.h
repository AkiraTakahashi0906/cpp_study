#ifndef INCLUDE_GUARD_DB_TABLE_DATA_COUNT_ENTITY_HPP
#define INCLUDE_GUARD_DB_TABLE_DATA_COUNT_ENTITY_HPP

#pragma once
#include <string>
using std::string;

class DbTableDataCountEntity
{
public:
	DbTableDataCountEntity(string dbName,
										 string tableName,
		                                 int rowCount,
		                                 double reservedPageCount_kb);
	string getDbName();
	string getTableName();
	int getRowCount();
	double getReservedPageCount_kb();

private:
	string dbName_;
	string tableName_;
	int rowCount_;
	double reservedPageCount_kb_;
};

#endif

