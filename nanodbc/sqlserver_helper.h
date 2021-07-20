#ifndef INCLUDE_GUARD_SQLSERVER_HELPER_HPP
#define INCLUDE_GUARD_SQLSERVER_HELPER_HPP
#pragma once
#include <iostream>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/any.hpp>
#include <boost/foreach.hpp>
#include "nanodbc.h"
#include "time_helper.h"
#include <vector>
#include <string>

using std::string;
using std::vector;

struct SqlParameter {
	int parameter_number;
    boost::any value;
};

class SqlserverHelper
{
public:
    nanodbc::result Query(const nanodbc::string sql , vector<SqlParameter> parameters);
	void execute_transaction(const nanodbc::string sql, vector<SqlParameter> parameters);
	void execute_transaction(vector<std::pair<std::string, vector<SqlParameter>>> querys);
private:
	nanodbc::result bind_parameter(nanodbc::connection *connection, vector<SqlParameter> *parameters, const nanodbc::string sql);
	const char* _connection_string = "DRIVER={SQL Server};SERVER=DESKTOP-8B0KCU1\\SQLEXPRESS;DATABASE=KGWS;UID=python;PWD=akira;";
};
#endif

