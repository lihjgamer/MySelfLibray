#pragma once

#include <time.h>

namespace lihj
{
	typedef struct tm tm;

	typedef enum{
		WeekDay_Sunday,
		WeekDay_Monday,
		WeekDay_Tuesday,
		WeekDay_Wednesday,
		WeekDay_Thursday,
		WeekDay_Friday,
		WeekDay_Saturday,
	}WeekDay;

	class CTimeHelper
	{
	public:
		static time_t Now();
		static tm     Now(const time_t& time);

		static int Year(tm &time);
		static int Year(time_t& time);

		static int Month(tm &time);
		static int Month(time_t& time);

		static int Day(tm &time);
		static int Day(time_t& time);

		static int Hour(tm &time);
		static int Hour(time_t& time);

		static int Minutes(tm &time);
		static int Minutes(time_t& time);

		static int Seconds(tm &time);
		static int Seconds(time_t& time);

		static WeekDay Weekday(tm &time);
		static WeekDay Weekday(time_t& time);
	
		static char* DateFormat(const time_t& time);

		static bool IsSameDay(const time_t& time1, const time_t& time2);
		static bool IsSameDay(const time_t& time1, const tm&     time2);
		static bool IsSameDay(const tm&     time1, const time_t& time2);
		static bool IsSameDay(const tm&     time1, const tm&     time2);

		static bool IsSameHour(const time_t& time1, const time_t& time2);
		static bool IsSameHour(const time_t& time1, const tm&     time2);
		static bool IsSameHour(const tm&     time1, const time_t& time2);
		static bool IsSameHour(const tm&     time1, const tm&     time2);

		static bool IsWeekday(WeekDay wd, const time_t& time1 = time(NULL));
		static bool IsWeekday(WeekDay wd, const tm&     time1 );
	public:
		CTimeHelper(){}
		~CTimeHelper(){};
	};
}