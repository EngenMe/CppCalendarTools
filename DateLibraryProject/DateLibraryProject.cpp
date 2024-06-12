#include <iostream>

#include "clsDate.h";
#include "clsPeriod.h";

int main()
{
	clsDate date;

	date.DisplayDate();

	std::cout << "Week Day Name: " << date.WeekDayName() << std::endl;

	date.PrintMonthCalendar();

	//date.PrintYearCalendar();

	std::cout << "How many days from the begining of the year: " << date.DaysFromTheBeginingOfTheYear() <<
		std::endl;

	std::cout << "Date after adding days: \n";
	date.AddDays(365);
	date.DisplayDate();

	std::string str_date = "10/6/2024";
	std::cout << "Is today before given date " << str_date << ": " <<
		(date.IsDateBeforeDate2(clsDate(str_date)) ? "Yes" : "No") << std::endl;

	std::cout << "Is date equal: " << (date.IsDateEqualDate2(clsDate(str_date)) ? "Yes" : "No") << std::endl;

	std::cout << "Is last day in month: " << (date.IsLastDayInMonth() ? "Yes" : "No") << std::endl;
	std::cout << "Is last month in year: " << (date.IsLastMonthInYear() ? "Yes" : "No") << std::endl;

	clsDate date1("12/6/2002");
	clsDate date2;
	std::cout << "Dates before swapping:\n";
	date1.DisplayDate();
	date2.DisplayDate();
	clsDate::SwapDates(date1, date2);
	std::cout << "Dates after swapping:\n";
	date1.DisplayDate();
	date2.DisplayDate();

	std::cout << "Difference between both dates: " << clsDate::CalculateDateDifference(date1, date2) <<
		std::endl;

	clsDate my_age("1/10/1995");
	clsDate this_date;
	std::cout << "My age in days = " << this_date.CalculateAgeInDays(my_age) << std::endl;

	std::cout << "My age - 1 year (substraction): \n";
	my_age.SubstractDays(365);
	my_age.DisplayDate();

	date.IncreaseDateByOneWeek();
	std::cout << "Date Increased By one week: \n";
	date.DisplayDate();

	date.IncreaseDateByNWeeks(16);
	std::cout << "Date Increased By N weeks: \n";
	date.DisplayDate();

	//date.day = 31;
	//date.month = 10;
	//date.year = 2024;
	date.IncreaseDateByOneMonth();
	std::cout << "Date Increased By one month: \n";
	date.DisplayDate();

	date.IncreaseDateByNMonths(12);
	std::cout << "Date Increased By N months: \n";
	date.DisplayDate();

	//date.DecreaseDateByNMiliniums(2);
	//std::cout << "Date Decreased by 2 miliniums: \n";
	//date.DisplayDate();

	date = clsDate();
	date.DisplayDate();
	std::cout << "Is a end of week: " << (date.IsEndOfWeek() ? "Yes" : "No") << std::endl;
	std::cout << "Is a weekend: " << (date.IsWeekEnd() ? "Yes" : "No") << std::endl;
	std::cout << "Is a business day: " << (date.IsBusinessDay() ? "Yes" : "No") << std::endl;

	std::cout << "Days until end of week: " << date.DaysUntilTheEndOfWeek() << std::endl;
	std::cout << "Days until end of month: " << date.DaysUntilTheEndOfMonth() << std::endl;
	std::cout << "Days until end of year: " << date.DaysUntilTheEndOfYear() << std::endl;

	std::cout << "How many business days until next month: " <<
		date.HowManyBusinessDays(clsDate::IncreaseDateByOneMonth(date)) << std::endl;
	std::cout << "How many weekend days until next month: " <<
		date.HowManyWeekendDays(clsDate::IncreaseDateByOneMonth(date)) << std::endl;

	std::cout << "Vacation return date after 23 of annual leave:\n";
	date.CalculateVacationReturnDate(23).DisplayDate();

	clsPeriod::clsDate period1_start_date("2/1/2020");
	clsPeriod::clsDate period1_end_date("1/11/2020");
	clsPeriod::clsDate period2_start_date("1/3/2020");
	clsPeriod::clsDate period2_end_date("1/10/2020");
	clsPeriod period1(period1_start_date, period1_end_date);
	clsPeriod period2(period2_start_date, period2_end_date);
	std::cout << "Are periods overlapped: " << (period1.IsOverLapWith(period2) ? "Yes" : "No") << std::endl;
	std::cout << "Period 1:\n";
	std::cout << "Start date: ";
	period1_start_date.DisplayDate();
	std::cout << "End date: ";
	period1_end_date.DisplayDate();
	std::cout << "Period 2:\n";
	std::cout << "Start date: ";
	period2_start_date.DisplayDate();
	std::cout << "End date: ";
	period2_end_date.DisplayDate();

	return 0;
}