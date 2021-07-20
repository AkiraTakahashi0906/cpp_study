#include "db_backup_log_entity.h"

DbBackupLogEntity::DbBackupLogEntity(string dbName, date createDate, date fullBackupDate)
{
	this->dbName_ = dbName;
	this->createDate_ = createDate;
	this->fullBackupDate_ = fullBackupDate;
}

string DbBackupLogEntity::Get_dbName()
{
	return this->dbName_;
}

date DbBackupLogEntity::Get_createDate()
{
	return this->createDate_;
}

std::optional<date> DbBackupLogEntity::Get_fullBackupDate()
{
	return this->fullBackupDate_;
}

string DbBackupLogEntity::Get_displayFullBackupDate()
{
	string date = boost::gregorian::to_iso_extended_string(fullBackupDate_);
	if (date=="1900-01-01") {
		return "DBNULL";
	}
	else {
		return date;
	}
}

string DbBackupLogEntity::Get_displayCreateDate()
{
	return boost::gregorian::to_iso_extended_string(createDate_);
}
