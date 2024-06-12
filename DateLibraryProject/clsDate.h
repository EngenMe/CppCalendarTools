#pragma warning(disable : 4996)
#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <algorithm>

#include "clsString.h";

class clsDate
{
private:
	enum _enDateFormat
	{
		dd_mm_yy,
		mm_dd_yy,
		dd_month_yy
	};

	std::vector <std::string> _v_month_names = 
	{
		"",
		"January",
		"February",
		"March",
		"April",
		"May",
		"June",
		"July",
		"August",
		"September",
		"October",
		"November",
		"December"
	};
	std::vector <std::string> _v_week_days = 
	{
			"Sunday",
			"Monday",
			"Tuesday",
			"Wednesday",
			"Thursday",
			"Friday",
			"Saturday"
	};
	std::vector <std::string> _v_weekend_days =
	{
		"Saturday",
		"Sunday"
	};

	std::string _GetStNdRd(short day)
	{
		if (day == 1 || day == 21 || day == 31)
			return "st";
		else if (day == 2 || day == 22)
			return "nd";
		else if (day == 3 || day == 23)
			return "rd";
		else
			return "th";
	}

	bool _IsLeap(short year)
	{
		return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
	}

	short _HowManyDaysInYear(short year)
	{
		return _IsLeap(year) ? 365 : 364;
	}
	short _HowManyDaysInMonth(short month, bool is_leap)
	{
		short arr_month_days[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		return (month == 2) ? (is_leap ? 29 : 28) : arr_month_days[month - 1];
	}

	clsDate _GetDateFromDayOrderInYear(short day_order_in_year, short year)
	{
		clsDate date;

		date._year = year;
		date._is_leap = _IsLeap(_year);
		date._month = 1;
		date._day = day_order_in_year;

		while (true)
		{
			short how_many_days_in_month = _HowManyDaysInMonth(date._month, date._is_leap);

			if (date._day >= how_many_days_in_month)
			{
				date._day -= how_many_days_in_month;
				date._month++;
			}
			else
				break;
		}

		return date;
	}

	bool _IsValidDate(short day, short month, short year, bool is_leap)
	{
		if (year < 0 ||
			month < 0 || month > 12 ||
			day < 0 || day > _HowManyDaysInMonth(month, is_leap))
		{
			std::cerr << "Error: Invalid date!" << std::endl;
			exit(EXIT_FAILURE); 
			return false;
		}

		return true;
	}

	short _DayOfWeekOrder(clsDate date)
	{
		short a, y, m;
		a = (14 - date._month) / 12;
		y = date._year - a;
		m = date._month + (12 * a) - 2;
		return (date._day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
	}

	short _CalculateHowManyYearsInDays(int& days, short current_year)
	{
		short how_many_years = 0;
		short how_many_days_in_year = _HowManyDaysInYear(current_year);

		while (days >= how_many_days_in_year)
		{
			how_many_years++;
			days -= how_many_days_in_year;
			how_many_days_in_year = _HowManyDaysInYear(++current_year);
		}

		return how_many_years;
	}

	bool _IsElementInVect(std::string element, std::vector <std::string> vec)
	{
		for (std::string s : vec)
		{
			if (s == element)
				return true;
		}
		
		return false;
	}

	short _FindIndex(std::string element, std::vector <std::string> vec)
	{
		for (short i = 0; i < vec.size(); i++)
		{
			if (vec[i] == element)
				return i;
		}

		return -1;
	}

	short _day;
	short _month;
	short _year;
	bool _is_leap;
	bool _is_valid_date;

public:
	clsDate()
	{
		time_t t = time(0); tm* now = localtime(&t); 
		_day = now->tm_mday;   
		_month = now->tm_mon + 1;
		_year = now->tm_year + 1900;
		_is_leap = _IsLeap(_year);
	}
	clsDate(std::string str_date)
	{
		std::vector <std::string> v_str_date = clsString::Split(str_date, "/");
		_day = stoi(v_str_date[0]);
		_month = stoi(v_str_date[1]);
		_year = stoi(v_str_date[2]);
		_is_leap = _IsLeap(_year);
		_is_valid_date = _IsValidDate(_day, _month, _year, _is_leap);
	}
	clsDate(short day, short month, short year)
	{
		_day = day;
		_month = month;
		_year = year;
		_is_leap = _IsLeap(_year);
		_is_valid_date = _IsValidDate(_day, _month, _year, _is_leap);
	}
	clsDate(short day_order_in_year, short year)
	{
		clsDate date = _GetDateFromDayOrderInYear(day_order_in_year, year);
		_day = date._day;
		_month = date._month;
		_year = date._year;
		_is_leap = date._is_leap;
		_is_valid_date = _IsValidDate(_day, _month, _year, _is_leap);
	}

	static clsDate GetSystemDate()
	{
		return clsDate();
	}

	void SetDay(short day)
	{
		_day = day;
	}
	void SetMonth(short month)
	{
		_month = month;
	}
	void SetYear(short year)
	{
		_year = year;
		_is_leap = _IsLeap(_year);
	}

	short GetDay()
	{
		return _day;
	}
	short GetMonth()
	{
		return _month;
	}
	short GetYear()
	{
		return _year;
	}
	bool GetIsLeap()
	{
		return _is_leap;
	}
	bool GetIsValidDate()
	{
		return _IsValidDate(_day, _month, _year, _is_leap);
	}

	__declspec(property(get = GetDay, put = SetDay)) short day;
	__declspec(property(get = GetMonth, put = SetMonth)) short month;
	__declspec(property(get = GetYear, put = SetYear)) short year;
	__declspec(property(get = GetIsLeap)) bool is_leap;
	__declspec(property(get = GetIsValidDate)) bool is_valid_date;

	static void DisplayDate(clsDate date, _enDateFormat en_date_format = _enDateFormat::dd_month_yy)
	{
		std::cout << "Date: ";

		switch (en_date_format)
		{
		case _enDateFormat::dd_mm_yy:
			std::cout << date.day << "/" << date.month << "/" << date.year << std::endl;
			break;
		case _enDateFormat::mm_dd_yy:
			std::cout << date.month << "/" << date.month << "/" << date.year << std::endl;
			break;
		default:
			std::cout << date.day << date._GetStNdRd(date.day) << " " <<
				date._v_month_names[date.month] << " " << date.year << std::endl;
		}
	}
	void DisplayDate(_enDateFormat en_date_format = _enDateFormat::dd_month_yy)
	{
		DisplayDate(*this);
	}

	static std::string WeekDayName(clsDate date)
	{
		return date._v_week_days[date._DayOfWeekOrder(date)];
	}
	std::string WeekDayName()
	{
		return WeekDayName(*this);
	}

	static void PrintMonthCalendar(short month, short year)
	{
		clsDate date;

		int current = date._DayOfWeekOrder(clsDate(1, month, year));
		int number_of_days = date._HowManyDaysInMonth(month, date._IsLeap(year));

		printf("\n  _______________%s_______________\n\n", date._v_month_names[month].substr(0, 3).c_str());

		printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");

		int i;
		for (i = 0; i < current; i++)
			printf("     ");
		for (int j = 1; j <= number_of_days; j++)
		{
			printf("%5d", j);

			if (++i == 7)
			{
				i = 0;
				printf("\n");
			}
		}
		printf("\n  _________________________________\n");
	}
	void PrintMonthCalendar()
	{
		PrintMonthCalendar(this->_month, this->_year);
	}

	static void PrintYearCalendar(int year)
	{
		printf("\n  _________________________________\n\n");
		printf("           Calendar - %d\n", year);
		printf("  _________________________________\n");

		for (int i = 1; i <= 12; i++)
		{
			PrintMonthCalendar(i, year);
		}
	}
	void PrintYearCalendar()
	{
		PrintYearCalendar(this->_year);
	}

	static short DaysFromTheBeginingOfTheYear(clsDate date)
	{
		short total_days = 0;

		if (date._month == 1)
			return date._day;

		for (short i = 1; i < date._month; i++)
		{
			total_days += date._HowManyDaysInMonth(i, date._is_leap);
		}

		return total_days + date._day;
	}
	short DaysFromTheBeginingOfTheYear()
	{
		return DaysFromTheBeginingOfTheYear(*this);
	}

	static clsDate AddDays(int days, clsDate date)
	{
		date._day += days;

		while (date._day > date._HowManyDaysInMonth(date._month, date._is_leap))
		{
			date._day -= date._HowManyDaysInMonth(date._month, date._is_leap);
			date._month++;
			if (date.month > 12)
			{
				date._month = 1;
				date._year++;
				date._is_leap = date._IsLeap(date._year);
			}
		}

		return date;
	}
	void AddDays(int days)
	{
		*this = AddDays(days, *this);
	}

	static clsDate SubstractDays(int days, clsDate date)
	{
		date._day -= days;

		while (date._day <= 0)
		{
			date._month--;
			if (date.month < 1)
			{
				date._month = 12;
				date._year--;
				date._is_leap = date._IsLeap(date._year);
			}
			date._day += date._HowManyDaysInMonth(date._month, date._is_leap);
		}

		return date;
	}
	void SubstractDays(int days)
	{
		*this = SubstractDays(days, *this);
	}

	static bool IsDate1BeforeDate2(clsDate date1, clsDate date2)
	{
		if (date1.year < date2.year) 
		{
			return true;
		}
		else if (date1.year == date2.year) 
		{
			if (date1.month < date2.month) 
			{
				return true;
			}
			else if (date1.month == date2.month) 
			{
				if (date1.day < date2.day) 
				{
					return true;
				}
			}
		}
		return false;
	}
	bool IsDateBeforeDate2(clsDate date2)
	{
		return IsDate1BeforeDate2(*this, date2);
	}

	static bool IsDate1EqualDate2(clsDate date1, clsDate date2)
	{
		return (date1._year == date2._year && date1._month == date2._month && date1._day == date2._day);
	}
	bool IsDateEqualDate2(clsDate date2)
	{
		return IsDate1EqualDate2(*this, date2);
	}

	static bool IsLastDayInMonth(clsDate date)
	{
		return date._day == date._HowManyDaysInMonth(date._month, date._is_leap);
	}
	bool IsLastDayInMonth()
	{
		return IsLastDayInMonth(*this);
	}

	static bool IsLastMonthInYear(clsDate date)
	{
		return date._month == 12;
	}
	bool IsLastMonthInYear()
	{
		return IsLastMonthInYear(*this);
	}

	static void SwapDates(clsDate& date1, clsDate& date2)
	{
		clsDate temp_date;
		temp_date = date1;
		date1 = date2;
		date2 = temp_date;
	}

	static int CalculateDateDifference(clsDate date1, clsDate date2) {
		if (date1._year == date2._year && date1._month == date2._month) {
			return abs(date1.day - date2.day);
		}

		clsDate min_date = IsDate1BeforeDate2(date1, date2) ? date1 : date2;
		clsDate max_date = IsDate1BeforeDate2(date1, date2) ? date2 : date1;

		int days = min_date._HowManyDaysInMonth(min_date._month, min_date._is_leap) - min_date._day;

		min_date._month++;
		while (min_date._year < max_date._year ||
			(min_date._year == max_date._year && min_date._month < max_date._month)) 
		{
			days += min_date._HowManyDaysInMonth(min_date._month, min_date._is_leap);
			min_date._month++;
			if (min_date._month > 12) {
				min_date._month = 1;
				min_date._year++;
				min_date._is_leap = min_date._IsLeap(min_date._year);
			}
		}

		days += max_date._day;

		return days;
	}

	int CalculateAgeInDays(clsDate age)
	{
		return CalculateDateDifference(*this, age);
	}

	static clsDate IncreaseDateByOneWeek(clsDate date)
	{
		date.AddDays(7);

		return date;
	}
	void IncreaseDateByOneWeek()
	{
		*this = IncreaseDateByOneWeek(*this);
	}

	static clsDate IncreaseDateByNWeeks(clsDate date, short n_weeks)
	{
		date.AddDays(7 * n_weeks);

		return date;
	}
	void IncreaseDateByNWeeks(short n_weeks)
	{
		*this = IncreaseDateByNWeeks(*this, n_weeks);
	}

	static clsDate IncreaseDateByOneMonth(clsDate date)
	{
		date._month++;

		if (date._month > 12)
		{
			date._year++;
			date._is_leap = date._IsLeap(date._year);
			date._month = 1;
		}

		short how_many_days_in_month = date._HowManyDaysInMonth(date._month, date._is_leap);
		if (date._day > how_many_days_in_month)
		{
			date._day -= how_many_days_in_month;
			date._month++;
		}

		return date;
	}
	void IncreaseDateByOneMonth()
	{
		*this = IncreaseDateByOneMonth(*this);
	}

	static clsDate IncreaseDateByNMonths(clsDate date, short n_months)
	{
		for (int i = 1; i <= n_months; i++)
		{
			date.IncreaseDateByOneMonth();
		}

		return date;
	}
	void IncreaseDateByNMonths(short n_months)
	{
		*this = IncreaseDateByNMonths(*this, n_months);
	}

	static clsDate IncreaseDateByOneYear(clsDate date)
	{
		date._year++;
		
		return date;
	}
	void IncreaseDateByOneYear()
	{
		*this = IncreaseDateByOneYear(*this);
	}

	static clsDate IncreaseDateByNYears(clsDate date, short n_years)
	{
		date._year += n_years;

		return date;
	}
	void IncreaseDateByNYears(short n_years)
	{
		*this = IncreaseDateByNYears(*this, n_years);
	}

	static clsDate IncreaseDateByOneDecade(clsDate date)
	{
		date._year += 10;

		return date;
	}
	void IncreaseDateByOneDecade()
	{
		*this = IncreaseDateByOneDecade(*this);
	}

	static clsDate IncreaseDateByNDecades(clsDate date, short n_decades)
	{
		date._year += 10 * n_decades;

		return date;
	}
	void IncreaseDateByNDecades(short n_decades)
	{
		*this = IncreaseDateByNDecades(*this, n_decades);
	}

	static clsDate IncreaseDateByOneCentury(clsDate date)
	{
		date._year += 100;
		
		return date;
	}
	void IncreaseDateByOneCentury()
	{
		*this = IncreaseDateByOneCentury(*this);
	}

	static clsDate IncreaseDateByNCenturies(clsDate date, short n_centuries)
	{
		date._year += 100 * n_centuries;

		return date;
	}
	void IncreaseDateByNCenturies(short n_centuries)
	{
		*this = IncreaseDateByNCenturies(*this, n_centuries);
	}

	static clsDate IncreaseDateByOneMilinium(clsDate date)
	{
		date._year += 1000;

		return date;
	}
	void IncreaseDateByOneMilinium()
	{
		*this = IncreaseDateByOneMilinium(*this);
	}

	static clsDate IncreaseDateByNMiliniums(clsDate date, short n_miliniums)
	{
		date.year += 1000 * n_miliniums;

		return date;
	}
	void IncreaseDateByNMiliniums(short n_miliniums)
	{
		*this = IncreaseDateByNMiliniums(*this, n_miliniums);
	}

	static clsDate DecreaseDateByOneWeek(clsDate date)
	{
		date.SubstractDays(7);
	}
	void DecreaseDateByOneWeek()
	{
		*this = DecreaseDateByOneWeek(*this);
	}

	static clsDate DecreaseDateByNWeeks(clsDate date, short n_weeks)
	{
		date.SubstractDays(7 * n_weeks);
	}
	void DecreaseDateByNWeeks(short n_weeks)
	{
		*this = DecreaseDateByNWeeks(*this, n_weeks);
	}

	static clsDate DecreaseDateByOneMonth(clsDate date)
	{
		date._month--;

		if (date._month < 1)
		{
			date._year--;
			date._is_leap = date._IsLeap(date._year);
			date._month = 12;
		}

		short how_many_days_in_month = date._HowManyDaysInMonth(date._month, date._is_leap);
		if (date._day > how_many_days_in_month)
		{
			date._day -= how_many_days_in_month;
			date._month++;
		}

		return date;
	}
	void DecreaseDateByOneMonth()
	{
		*this = DecreaseDateByOneMonth(*this);
	}

	static clsDate DecreaseDateByNMonths(clsDate date, short n_months)
	{
		for (int i = 1; i <= n_months; i++)
		{
			date.DecreaseDateByOneMonth();
		}

		return date;
	}
	void DecreaseDateByNMonths(short n_months)
	{
		*this = DecreaseDateByNMonths(*this, n_months);
	}

	static clsDate DecreaseDateByOneYear(clsDate date)
	{
		date._year--;

		return date;
	}
	void DecreaseDateByOneYear()
	{
		*this = DecreaseDateByOneYear(*this);
	}

	static clsDate DecreaseDateByNYears(clsDate date, short n_years)
	{
		date._year -= n_years;

		return date;
	}
	void DecreaseDateByNYears(short n_years)
	{
		*this = DecreaseDateByNYears(*this, n_years);
	}

	static clsDate DecreaseDateByOneDecade(clsDate date)
	{
		date._year -= 10;

		return date;
	}
	void DecreaseDateByOneDecade()
	{
		*this = DecreaseDateByOneDecade(*this);
	}

	static clsDate DecreaseDateByNDecades(clsDate date, short n_decades)
	{
		date._year -= 10 * n_decades;

		return date;
	}
	void DecreaseDateByNDecades(short n_decades)
	{
		*this = DecreaseDateByNDecades(*this, n_decades);
	}

	static clsDate DecreaseDateByOneCentury(clsDate date)
	{
		date._year -= 100;

		return date;
	}
	void DecreaseDateByOneCentury()
	{
		*this = DecreaseDateByOneCentury(*this);
	}

	static clsDate DecreaseDateByNCenturies(clsDate date, short n_centuries)
	{
		date._year -= 100 * n_centuries;

		return date;
	}
	void DecreaseDateByNCenturies(short n_centuries)
	{
		*this = DecreaseDateByNCenturies(*this, n_centuries);
	}

	static clsDate DecreaseDateByOneMilinium(clsDate date)
	{
		date._year -= 1000;

		return date;
	}
	void DecreaseDateByOneMilinium()
	{
		*this = DecreaseDateByOneMilinium(*this);
	}

	static clsDate DecreaseDateByNMiliniums(clsDate date, short n_miliniums)
	{
		date.year -= 1000 * n_miliniums;

		return date;
	}
	void DecreaseDateByNMiliniums(short n_miliniums)
	{
		*this = DecreaseDateByNMiliniums(*this, n_miliniums);
	}

	static bool IsEndOfWeek(clsDate date)
	{
		return date.WeekDayName() == date._v_week_days.back();
	}
	bool IsEndOfWeek()
	{
		return IsEndOfWeek(*this);
	}

	static bool IsWeekEnd(clsDate date)
	{
		return date._IsElementInVect(date.WeekDayName(), date._v_weekend_days);
	}
	bool IsWeekEnd()
	{
		return IsWeekEnd(*this);
	}

	static bool IsBusinessDay(clsDate date)
	{
		return !date.IsWeekEnd();
	}
	bool IsBusinessDay()
	{
		return IsBusinessDay(*this);
	}

	static short DaysUntilTheEndOfWeek(clsDate date)
	{
		return date._FindIndex(date.WeekDayName(), date._v_week_days);
	}
	short DaysUntilTheEndOfWeek()
	{
		return DaysUntilTheEndOfWeek(*this);
	}

	static short DaysUntilTheEndOfMonth(clsDate date)
	{
		clsDate end_of_month_date = clsDate
		(
			date._HowManyDaysInMonth(date._month, date._is_leap),
			date._month,
			date._year
		);

		return date.CalculateDateDifference(date, end_of_month_date);
	}
	short DaysUntilTheEndOfMonth()
	{
		return DaysUntilTheEndOfMonth(*this);
	}

	static short DaysUntilTheEndOfYear(clsDate date)
	{
		return clsDate::CalculateDateDifference(date, clsDate(31, 12, date._year));
	}
	short DaysUntilTheEndOfYear()
	{
		return DaysUntilTheEndOfYear(*this);
	}

	static short HowManyBusinessDays(clsDate starting_date, clsDate ending_date)
	{
		short counter = 0;

		while (clsDate::IsDate1BeforeDate2(starting_date, ending_date))
		{
			if (clsDate::IsBusinessDay(starting_date))
				counter++;

			starting_date.AddDays(1);
		}

		return counter;
	}
	short HowManyBusinessDays(clsDate ending_date)
	{
		return HowManyBusinessDays(*this, ending_date);
	}

	static short HowManyWeekendDays(clsDate starting_date, clsDate ending_date)
	{
		short counter = 0;

		while (clsDate::IsDate1BeforeDate2(starting_date, ending_date))
		{
			if (clsDate::IsWeekEnd(starting_date))
				counter++;

			starting_date.AddDays(1);
		}

		return counter;
	}
	short HowManyWeekendDays(clsDate ending_date)
	{
		return HowManyWeekendDays(*this, ending_date);
	}

	static clsDate CalculateVacationReturnDate(clsDate starting_date, short vacation_days)
	{
		while (vacation_days >= 0)
		{
			starting_date.AddDays(1);

			if (starting_date.IsBusinessDay())
				vacation_days--;
		}

		return starting_date;
	}
	clsDate CalculateVacationReturnDate(short vacation_days)
	{
		return CalculateVacationReturnDate(*this, vacation_days);
	}
};

