#include "sqlserver_helper.h"

nanodbc::result SqlserverHelper::Query(const nanodbc::string sql, vector<SqlParameter> parameters) {
	nanodbc::connection connection = nanodbc::connection(_connection_string);
    nanodbc::result results = bind_parameter(&connection, &parameters, sql);
	return results;
}

void SqlserverHelper::execute_transaction(const nanodbc::string sql, vector<SqlParameter> parameters)
{
	nanodbc::connection connection = nanodbc::connection(_connection_string);
	nanodbc::transaction transaction = nanodbc::transaction(connection);
	bind_parameter(&connection, &parameters, sql);
	transaction.commit();
}

void SqlserverHelper::execute_transaction(vector<std::pair<std::string, vector<SqlParameter>>> querys)
{
	nanodbc::connection connection = nanodbc::connection(_connection_string);
	nanodbc::transaction transaction = nanodbc::transaction(connection);
	std::string sql;
	vector<SqlParameter> param;
	for (auto itr = querys.begin(); itr != querys.end(); ++itr) {
		sql = itr._Ptr->first;
		param = itr._Ptr->second;
		bind_parameter(&connection, &param,sql);
	}
	transaction.commit();
}

nanodbc::result SqlserverHelper::bind_parameter(
																		  nanodbc::connection* connection,
																		  vector<SqlParameter>* parameters,
																		  const nanodbc::string sql)
{
	nanodbc::statement statement = nanodbc::statement(*connection);
	nanodbc::prepare(statement, sql);
	BOOST_FOREACH(auto & x, *parameters) {
		if (x.value.type() == typeid(int)) {
			statement.bind(x.parameter_number, boost::any_cast<int>(&x.value));
		}
		else if (x.value.type() == typeid(std::string)) {
			statement.bind(x.parameter_number, boost::any_cast<std::string>(&x.value)->c_str());
		}
		else if (x.value.type() == typeid(double)) {
			statement.bind(x.parameter_number, boost::any_cast<double>(&x.value));
		}
		else if (x.value.type() == typeid(bool)) {
			int param;
			param = *boost::any_cast<bool>(&x.value);
			statement.bind(x.parameter_number, &param);
		}
		else if (x.value.type() == typeid(boost::gregorian::date)) {
			boost::gregorian::date date = boost::any_cast<boost::gregorian::date>(x.value);
			nanodbc::date nanodbc_date = TimeHelper::ToNanodbcDate(date);
			statement.bind(x.parameter_number, &nanodbc_date);
		}
		else if (x.value.type() == typeid(boost::posix_time::ptime)) {
			boost::posix_time::ptime date = boost::any_cast<boost::posix_time::ptime>(x.value);
			nanodbc::timestamp nanodbc_timestamp = TimeHelper::ToNanodbcTimestamp(date);
			statement.bind(x.parameter_number, &nanodbc_timestamp);
		}
		else if (x.value.type() == typeid(nullptr_t)) {
			statement.bind_null(x.parameter_number);
		}
		else {
			throw std::exception("sqlparameter:error!");
		}
	}
	return nanodbc::execute(statement);
}



