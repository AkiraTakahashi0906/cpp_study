#ifndef INCLUDE_GUARD_DB_STATUS_ENTITY_HPP
#define INCLUDE_GUARD_DB_STATUS_ENTITY_HPP

#pragma once
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <string>

using std::string;
using boost::posix_time::ptime;
using boost::gregorian::date;

class db_status_entity
{
public:
	db_status_entity(int id,string name,bool is_deleted, double double_test, date date_test,ptime date_time_test);
	int get_id();
	string get_name();
	bool get_is_deleted();
	double get_double_test();
	date get_date_test();
	ptime get_date_time_test();
protected:
	int id;
	string name;
	bool is_deleted;
	double double_test;
	date date_test;
	ptime date_time_test;
};
#endif

