#pragma once

#include <iostream>

#include "clsDate.h";

class clsPeriod : public clsDate
{
public:
    clsPeriod::clsDate start_date;
	clsPeriod::clsDate end_date;

	clsPeriod(clsPeriod::clsDate start_date, clsPeriod::clsDate end_date)
	{
		this->start_date = start_date;
		this->end_date = end_date;
	}

    static bool IsOverlapPeriods(clsPeriod period1, clsPeriod period2)
    {
        if (clsDate::IsDate1BeforeDate2(period2.end_date, period1.start_date) || 
            clsDate::IsDate1BeforeDate2(period1.end_date, period2.start_date))
            return false;
        
        return true;
    }

    bool IsOverLapWith(clsPeriod period2)
    {
        return IsOverlapPeriods(*this, period2);
    }
};

