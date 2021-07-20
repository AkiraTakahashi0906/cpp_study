#ifndef INCLUDE_GUARD_DB_STATUS_SQLSERVER_HPP
#define INCLUDE_GUARD_DB_STATUS_SQLSERVER_HPP
#pragma once

#include "sqlserver_helper.h"
#include "db_status_entity.h"
#include "db_backup_log_entity.h"

class db_status_sqlserver
{
public:
	vector<db_status_entity>GetDbStatus();
	vector<DbBackupLogEntity>GetDbBackupLogAll();
	void SaveDbStatus(db_status_entity db_status);
};
#endif

