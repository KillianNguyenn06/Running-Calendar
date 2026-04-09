#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include "MyScheduleDay.h"
class MyCalendar
{
private: 
	unsigned short currentYear; 
	unsigned short currentMonth; 
	unsigned short currentDay; 
	unsigned short scheduledDay; 
	unsigned short scheduledMonth; 
	MyScheduleDay scheduleDays[12][31]; 
public: 
	MyCalendar()
	{
		currentDay = 1; 
		currentMonth = 1; 
		currentYear = 0001;
		scheduledDay = 1; 
		scheduledMonth = 1; 
	}
	int getDaysInMonth(int m, int y)
	{
		switch (m) 
		{
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10: 
		case 12: 
			return 31;
			break; 
		case 4: 
		case 6:
		case 9:
		case 11:
			return 30;
			break; 
		case 2:
			return ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0)) ? 29 : 28;
			break; 
		default: 
			return 0;
			break; 
		}
	}
	void setCurrentYear(int y)
	{
		currentYear = y; 
	}
	int getCurrentYear() const
	{
		return currentYear; 
	}
	void setCurrentMonth(int m)
	{
		currentMonth = m; 
	}
	int getCurrentMonth() const
	{
		return currentMonth; 
	}
	void setCurrentDay(int d)
	{
		currentDay = d; 
	}
	int getCurrentDay() const
	{
		return currentDay;
	}
	int getScheduledDay() const
	{
		return scheduledDay; 
	}
	int getScheduledMonth() const
	{
		return scheduledMonth; 
	}
	void setScheduledDay(int sd)
	{
		scheduledDay = sd; 
		//scheduledMonth = sm; 
	}
	void setScheduledMonth(int sm)
	{
		scheduledMonth = sm;
	}
	MyScheduleDay getScheduleDay(int sm, int sd) const
	{
		return scheduleDays[sm - 1][sd - 1]; 
	}
	bool isLeapYear() const //Check Leap Year
	{
		if (currentYear % 4 == 0)
		{
			if (currentYear % 100 == 0)
			{
				return currentYear % 400 == 0; 
			}
			return true; 
		}
		return false; 
	}
	
	MyCalendar operator++() //Pre-increment
	{
		if (currentMonth == 2)
		{
			if (isLeapYear())
			{
				if (currentDay == 29)
				{
					setCurrentDay(1);
					currentMonth++;
				}
				else
					setCurrentDay(++currentDay); 

			}
			else if (!isLeapYear())
			{
				if (currentDay == 28)
				{
					setCurrentDay(1);
					currentMonth++;
				}
				else
					setCurrentDay(++currentDay); 
			}
			else
				setCurrentDay(++currentDay);
		}
		else if (currentMonth == 1 || currentMonth == 3 || currentMonth == 5 || currentMonth == 7 || currentMonth == 8 || currentMonth == 10 || currentMonth == 12)
		{
			if (currentDay == 31)
			{
				setCurrentDay(1);
				currentMonth++;
			}
			else
				setCurrentDay(++currentDay);
		}
		else if (currentMonth == 4 || currentMonth == 6 || currentMonth == 9 || currentMonth == 11)
		{
			if (currentDay == 30)
			{
				setCurrentDay(1);
				currentMonth++;
			}
			else
				setCurrentDay(++currentDay);
		}

		if (currentMonth > 12)
		{
			setCurrentMonth(1);
			currentYear++;
		}

		return *this;

	}

	MyCalendar operator++(int) //Post-increment
	{
		MyCalendar temp = *this;
		if (currentMonth == 2)
		{
			if (isLeapYear())
			{
				if (currentDay == 29)
				{
					setCurrentDay(1);
					currentMonth++;
				}
				else
					setCurrentDay(++currentDay); 
			}
			else if (!isLeapYear())
			{
				if (currentDay == 28)
				{
					setCurrentDay(1);
					currentMonth++;
				}
				else
					setCurrentDay(++currentDay); 
			}
			else
				setCurrentDay(++currentDay);
		}
		else if (currentMonth == 1 || currentMonth == 3 || currentMonth == 5 || currentMonth == 7 || currentMonth == 8 || currentMonth == 10 || currentMonth == 12)
		{
			if (currentDay == 31)
			{
				setCurrentDay(1);
				currentMonth++;
			}
			else
				setCurrentDay(++currentDay);
		}
		else if (currentMonth == 4 || currentMonth == 6 || currentMonth == 9 || currentMonth == 11)
		{
			if (currentDay == 30)
			{
				setCurrentDay(1);
				currentMonth++;
			}
			else
				setCurrentDay(++currentDay);
		}

		if (currentMonth > 12)
		{
			setCurrentMonth(1);
			currentYear++;
		}
		return temp;
	}

	MyCalendar operator--()	//pre-decrement
	{
		if (currentMonth == 3)
		{
			if (isLeapYear())
			{
				if (currentDay == 1)
				{
					setCurrentDay(29);
					currentMonth--;
				}
				else
					setCurrentDay(--currentDay); 
			}
			else if (!isLeapYear())
			{
				if (currentDay == 1)
				{
					setCurrentDay(28);
					currentMonth--;
				}
				else
					setCurrentDay(--currentDay);
			}
			else
				setCurrentDay(--currentDay);
		}
		else if (currentMonth == 1 || currentMonth == 2 || currentMonth == 5 || currentMonth == 7 || currentMonth == 8 || currentMonth == 10 || currentMonth == 12)
		{
			if (currentDay == 1)
			{
				setCurrentDay(31);
				currentMonth--;
			}
			else
				setCurrentDay(--currentDay);
		}
		else if (currentMonth == 4 || currentMonth == 6 || currentMonth == 9 || currentMonth == 11)
		{
			if (currentDay == 1)
			{
				setCurrentDay(30);
				currentMonth--;
			}
			else
				setCurrentDay(--currentDay);
		}

		if (currentMonth < 1)
		{
			setCurrentMonth(12);
			currentYear--;
		}

		return *this;
	}

	MyCalendar operator--(int)   //post-decrement
	{
		MyCalendar temp = *this;
		if (currentMonth == 3)
		{
			if (isLeapYear())
			{
				if (currentDay == 1)
				{
					setCurrentDay(29);
					currentMonth--;
				}
				else
					setCurrentDay(--currentDay); 
			}
			else if (!isLeapYear())
			{
				if (currentDay == 1)
				{
					setCurrentDay(28);
					currentMonth--;
				}
				else
					setCurrentDay(--currentDay); 
			}
			else
				setCurrentDay(--currentDay);
		}
		else if (currentMonth == 1 || currentMonth == 2 || currentMonth == 5 || currentMonth == 7 || currentMonth == 8 || currentMonth == 10 || currentMonth == 12)
		{
			if (currentDay == 1)
			{
				setCurrentDay(31);
				currentMonth--;
			}
			else
				setCurrentDay(--currentDay);
		}
		else if (currentMonth == 4 || currentMonth == 6 || currentMonth == 9 || currentMonth == 11)
		{
			if (currentDay == 1)
			{
				setCurrentDay(30);
				currentMonth--;
			}
			else
				setCurrentDay(--currentDay);
		}

		if (currentMonth < 1)
		{
			setCurrentMonth(12);
			currentYear--;
		}

		return temp;
	}

	string getDateFormat() const
	{
		string monthName[13] = { "unknown", "January", "February", "March", "April",
	"May", "June" , "July", "August", "September", "October" , "November",
	"December" };
		return monthName[currentMonth] + " " + to_string(currentDay) + ", " + to_string(currentYear);
	}

	string getDateNumberFormat() const
	{
		return to_string(currentMonth) + "/" + to_string(currentDay) + "/" + to_string(currentYear); 
	}

	MyCalendar jumpForward(int n)
	{
		for (int i = 0; i < n; i++)
		{
			if (currentMonth == 2)
			{
				if (isLeapYear())
				{
					if (currentDay == 29)
					{
						setCurrentDay(1);
						currentMonth++;
					}
					else
						setCurrentDay(++currentDay);

				}
				else if (!isLeapYear())
				{
					if (currentDay == 28)
					{
						setCurrentDay(1);
						currentMonth++;
					}
					else
						setCurrentDay(++currentDay);
				}
				else
					setCurrentDay(++currentDay);
			}
			else if (currentMonth == 1 || currentMonth == 3 || currentMonth == 5 || currentMonth == 7 || currentMonth == 8 || currentMonth == 10 || currentMonth == 12)
			{
				if (currentDay == 31)
				{
					setCurrentDay(1);
					currentMonth++;
				}
				else
					setCurrentDay(++currentDay);
			}
			else if (currentMonth == 4 || currentMonth == 6 || currentMonth == 9 || currentMonth == 11)
			{
				if (currentDay == 30)
				{
					setCurrentDay(1);
					currentMonth++;
				}
				else
					setCurrentDay(++currentDay);
			}

			if (currentMonth > 12)
			{
				setCurrentMonth(1);
				currentYear++;
			}
		}
		return *this;
	}

	MyCalendar jumpBackward(int n)
	{
		for (int i = 0; i < n; i++)
		{
			if (currentMonth == 3)
			{
				if (isLeapYear())
				{
					if (currentDay == 1)
					{
						setCurrentDay(29);
						currentMonth--;
					}
					else
						setCurrentDay(--currentDay);

				}
				else if (!isLeapYear())
				{
					if (currentDay == 1)
					{
						setCurrentDay(28);
						currentMonth--;
					}
					else
						setCurrentDay(--currentDay);
				}
				else
					setCurrentDay(--currentDay);
			}
			else if (currentMonth == 1 || currentMonth == 2 || currentMonth == 5 || currentMonth == 7 || currentMonth == 8 || currentMonth == 10 || currentMonth == 12)
			{
				if (currentDay == 1)
				{
					setCurrentDay(31);
					currentMonth--;
				}
				else
					setCurrentDay(--currentDay);
			}
			else if (currentMonth == 4 || currentMonth == 6 || currentMonth == 9 || currentMonth == 11)
			{
				if (currentDay == 1)
				{
					setCurrentDay(30);
					currentMonth--;
				}
				else
					setCurrentDay(--currentDay);
			}

			if (currentMonth < 1)
			{
				setCurrentMonth(12);
				currentYear--;
			}
		}

		return *this; 
	}

	friend ostream& operator<< (ostream&, const MyCalendar&);
};

ostream& operator<<(ostream& out, const MyCalendar& obj)
{
	out << obj.getDateNumberFormat(); 

	return out; 
}


