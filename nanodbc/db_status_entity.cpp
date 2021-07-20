#include "db_status_entity.h"

db_status_entity::db_status_entity(int id,string name,bool is_deleted, double double_test, date date_test,ptime date_time_test)
{
	this->id = id;
	this->name = name;
	this->is_deleted = is_deleted;
	this->double_test = double_test;
	this->date_test = date_test;
	this->date_time_test = date_time_test;
}

int db_status_entity::get_id() {
	return this->id;
}

string db_status_entity::get_name() {
	return this->name;
}

bool db_status_entity::get_is_deleted() {
	return this->is_deleted;
}

double db_status_entity::get_double_test() {
	return this->double_test;
}

date db_status_entity::get_date_test() {
	return this->date_test;
}

ptime db_status_entity::get_date_time_test() {
	return this->date_time_test;
}


