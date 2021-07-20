#include "db_table_data_count_entity.h"

DbTableDataCountEntity::DbTableDataCountEntity(string dbName,
																			string tableName,
																			int rowCount,
																			double reservedPageCount_kb) {
	this->dbName_ = dbName;
	this->tableName_ = tableName;
	this->rowCount_ = rowCount;
	this->reservedPageCount_kb_ = reservedPageCount_kb;
}

string DbTableDataCountEntity::getDbName()
{
	return this->dbName_;
}

string DbTableDataCountEntity::getTableName()
{
	return this->tableName_;
}

int DbTableDataCountEntity::getRowCount()
{
	return this->rowCount_;
}

double DbTableDataCountEntity::getReservedPageCount_kb()
{
	return this->reservedPageCount_kb_;
}
