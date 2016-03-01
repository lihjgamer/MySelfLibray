#include "timehelper.h"

namespace lihj
{	
	time_t CTimeHelper::Now()
	{
		return time(NULL);
	}

	tm CTimeHelper::Now(const time_t& time)
	{
		return *localtime(&time);
	}

	int CTimeHelper::Year(tm &time)
	{
		return time.tm_year + 1900;
	}

	int CTimeHelper::Year(time_t& time)
	{
		tm time1 = Now(time);
		return Year(time1);
	}

	int CTimeHelper::Month(tm &time)
	{
		return time.tm_mon + 1;
	}

	int CTimeHelper::Month(time_t& time)
	{
		tm time1 = Now(time);
		return Month(time1);
	}

	int CTimeHelper::Day(tm &time)
	{
		return time.tm_mday;
	}

	int CTimeHelper::Day(time_t& time)
	{
		tm time1 = Now(time);
		return Day(time1);
	}

	int CTimeHelper::Hour(tm &time)
	{
		return time.tm_hour;
	}

	int CTimeHelper::Hour(time_t& time)
	{
		tm time1 = Now(time);
		return Hour(time1);
	}

	int CTimeHelper::Minutes(tm &time)
	{
		return time.tm_min;
	}

	int CTimeHelper::Minutes(time_t& time)
	{
		tm time1 = Now(time);
		return Minutes(time1);
	}

	int CTimeHelper::Seconds(tm &time)
	{
		return time.tm_sec;
	}

	int CTimeHelper::Seconds(time_t& time)
	{
		tm time1 = Now(time);
		return Seconds(time1);
	}

	WeekDay CTimeHelper::Weekday(tm &time)
	{
		return (WeekDay)time.tm_wday;
	}

	WeekDay CTimeHelper::Weekday(time_t& time)
	{
		tm time1 = Now(time);
		return Weekday(time1);
	}

	char* CTimeHelper::DateFormat(const time_t& time)
	{
		return ctime(&time);
	}

	bool CTimeHelper::IsSameDay(const time_t& time1, const time_t& time2)
	{
		tm tm1 = Now(time1);
		tm tm2 = Now(time2);
		return IsSameDay(tm1, tm2);
	}

	bool CTimeHelper::IsSameDay(const time_t& time1, const tm& time2)
	{
		tm tm1 = Now(time1);
		return IsSameDay(tm1, time2);
	}

	bool CTimeHelper::IsSameDay(const tm& time1, const time_t& time2)
	{
		return IsSameDay(time2, time1);
	}

	bool CTimeHelper::IsSameDay(const tm& time1, const tm& time2)
	{
		return (
			time1.tm_year == time2.tm_year
			&& time1.tm_mon == time2.tm_mon
			&& time1.tm_mday == time2.tm_mday
			);
	}

	bool CTimeHelper::IsSameHour(const time_t& time1, const time_t& time2)
	{
		tm tm1 = Now(time1);
		tm tm2 = Now(time2);

		return tm1.tm_hour == tm2.tm_hour;
	}

	bool CTimeHelper::IsSameHour(const time_t& time1, const tm& time2)
	{
		tm tm1 = Now(time1);

		return tm1.tm_hour == time2.tm_hour;
	}

	bool CTimeHelper::IsSameHour(const tm& time1, const time_t& time2)
	{
		tm tm2 = Now(time2);

		return time1.tm_hour == tm2.tm_hour;
	}

	bool CTimeHelper::IsSameHour(const tm& time1, const tm& time2)
	{
		return time1.tm_min == time2.tm_min;
	}

	bool CTimeHelper::IsWeekday(WeekDay wd, const time_t& time1 /*= time(NULL)*/)
	{
		tm tm1 = Now(time1);
		return tm1.tm_wday == (int)wd;
	}

	bool CTimeHelper::IsWeekday(WeekDay wd, const tm& time1 )
	{
		return ((int)wd == time1.tm_wday);
	}
}
