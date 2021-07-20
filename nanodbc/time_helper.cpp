#include "time_helper.h"

nanodbc::date TimeHelper::ToNanodbcDate(boost::gregorian::date gregorian_date) {
	nanodbc::date nanodbc_date{ (int)gregorian_date.year(),
											      (int)gregorian_date.month(),
											      (int)gregorian_date.day() };
	return nanodbc_date;
}

nanodbc::timestamp TimeHelper::ToNanodbcTimestamp(boost::posix_time::ptime ptime)
{
	nanodbc::timestamp nanodbc_timestamp{ (int)ptime.date().year(),
																	(int)ptime.date().month(),
																	(int)ptime.date().day(),
																	(short)ptime.time_of_day().hours(),
																	(short)ptime.time_of_day().minutes(),
																	(short)ptime.time_of_day().seconds() };
	return nanodbc_timestamp;
}

boost::gregorian::date TimeHelper::ToGregorianDate(nanodbc::timestamp timestamp)
{
	boost::gregorian::date date(timestamp.year, timestamp.month, timestamp.day);
	return date;
}

boost::posix_time::ptime TimeHelper::ToPosixTime(nanodbc::timestamp timestamp)
{
	boost::gregorian::date date = TimeHelper::ToGregorianDate(timestamp);
	boost::posix_time::time_duration time_duration(boost::posix_time::hours(timestamp.hour) + boost::posix_time::minutes(timestamp.min) + boost::posix_time::seconds(timestamp.sec));
	boost::posix_time::ptime pt(date, time_duration);
	return pt;
}

