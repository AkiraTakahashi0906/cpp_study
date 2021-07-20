#ifndef INCLUDE_GUARD_TIME_HELPER_HPP
#define INCLUDE_GUARD_TIME_HELPER_HPP

#pragma once
#include "nanodbc.h"
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

class TimeHelper
{
public:
	static nanodbc::date ToNanodbcDate(boost::gregorian::date gregorian_date);
	static nanodbc::timestamp ToNanodbcTimestamp(boost::posix_time::ptime ptime);
	static boost::gregorian::date ToGregorianDate(nanodbc::timestamp timestamp);
	static boost::posix_time::ptime ToPosixTime(nanodbc::timestamp timestamp);
};
#endif

