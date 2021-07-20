#ifndef INCLUDE_GUARD_DB_BACKUP_LOG_ENTITY_HPP
#define INCLUDE_GUARD_DB_BACKUP_LOG_ENTITY_HPP

#pragma once
#include <string>
#include <optional>
#include <boost/date_time/gregorian/gregorian.hpp>
using std::string;
using boost::gregorian::date;

class DbBackupLogEntity
{
public:
	DbBackupLogEntity(string dbName,date createDate,date fullBackupDate);
	string Get_dbName();
	date Get_createDate();
	std::optional<date> Get_fullBackupDate();
	string Get_displayFullBackupDate();
	string Get_displayCreateDate();

private:
	string dbName_;
	date createDate_;
	date fullBackupDate_;
	string displayBackupDate_;
};

#endif

