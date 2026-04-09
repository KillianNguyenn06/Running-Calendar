#include <iostream>
#include <vector>
#include <cmath> 
#include <ctime>
#include <string>
#include <cctype>
#include <iomanip>
#include <cstring>
#include <fstream>
#include "input.h"
#include "MyUnit.h"
#include "MyCalendar.h"
#include "MyScheduleDay.h"
using namespace std; 

void currentYear(MyCalendar& calendar); 
void currentMonth(MyCalendar& calendar);
void currentDay(MyCalendar& calendar);
void currentCalendar(MyCalendar& calendar); 
void scheduleAndReport(MyCalendar& calendar, MyScheduleDay(&scheduleDays)[12][31]);
void displayYearSchedule(MyCalendar& calendar, MyScheduleDay(&scheduleDays)[12][31]);
void displayMonthSchedule(MyCalendar& calendar, MyScheduleDay(&scheduleDays)[12][31]);
void displayDaySchedule(MyCalendar& calendar, MyScheduleDay(&scheduleDays)[12][31]);
string DaySuffix(int day); 
string getYearInWords(int year); 
void Zellercongruence(int day, int month, int year);
void initializeWithCurrentDate(MyCalendar& calendar); 
void syncSystemDate(MyCalendar& calendar);
void saveCalendar(MyCalendar& calendar, MyScheduleDay(&scheduleDays)[12][31]);
void restoreCalendar(MyCalendar& calendar, MyScheduleDay(&scheduleDays)[12][31]);
void table(MyCalendar& calendar, MyScheduleDay(&scheduleDays)[12][31]);

void table(MyCalendar& calendar, MyScheduleDay(&scheduleDays)[12][31])
{
	string monthName[13] = { "unknown", "January", "February", "March", "April",
	"May", "June" , "July", "August", "September", "October" , "November",
	"December" };
	string awareness[13] = { "Unknown",
		"New Year and National Blood Donor Month", // January
		"Black History Month and Heart Awareness", // February
		"Women's History Month",                   // March
		"Earth Day and Financial Literacy Month",  // April
		"Mental Health Awareness Month",           // May
		"Pride Month",                             // June
		"Independence Day and Disability Awareness", // July
		"Back to School and Family Fun Month",     // August
		"Suicide Prevention Awareness Month",      // September
		"Breast Cancer Awareness Month",           // October
		"Veterans Day and Diabetes Awareness Month", // November
		"Holiday Season and Human Rights Month"    // December
	};
	cout << "\n\t" << string(80, char(196)); 
	cout << "\n\t Current year  : " << calendar.getCurrentYear() << " - " << getYearInWords(calendar.getCurrentYear()) << "  (" << (calendar.isLeapYear() ? "leap" : "non-leap") << ")"; 
	cout << "\n\t" << string(80, char(196)); 
	cout << "\n\t Current month : " << calendar.getCurrentMonth() << " - " << monthName[calendar.getCurrentMonth()];
	cout << "\n\t Awareness     : " << awareness[calendar.getCurrentMonth()]; 
	cout << "\n\t" << string(80, char(196)); 
	cout << "\n\t Current day   : " << calendar.getCurrentDay() << DaySuffix(calendar.getCurrentDay()) << " - "; Zellercongruence(calendar.getCurrentDay(), calendar.getCurrentMonth(), calendar.getCurrentYear());
	cout << "\n\t               : " << scheduleDays[calendar.getScheduledMonth() - 1][calendar.getScheduledDay() - 1].getDescription();
	cout << "\n\t" << string(80, char(196)); 
}

int main()
{
	char option = char(); 
	MyCalendar calendar; 
	MyScheduleDay scheduleDay; 
	MyScheduleDay scheduleDays [12][31]; 
	initializeWithCurrentDate(calendar); 
	do
	{
		system("cls");  
		table(calendar, scheduleDays);
		//cout << "\n\t" << calendar.getDateNumberFormat(); 
		cout << "\t"; 
		//Zellercongruence(calendar.getCurrentDay(), calendar.getCurrentMonth(), calendar.getCurrentYear());
		cout << endl; 
		cout << "\t\tMyCalender - OOP implementation";
		cout << "\n\t" << string(70, char(205));
		cout << "\n\t\tA. Setting Current Year";
		cout << "\n\t\tB. Setting Current Month";
		cout << "\n\t\tC. Setting Current Day";
		cout << "\n\t\tD. Setting Current Calendar";
		cout << "\n\t\tE. Schedule and Report Dates";
		cout << "\n\t" << string(70, char(196));
		cout << "\n\t\tF. Sync to system's date";
		cout << "\n\t\tG. Save calendar to file";
		cout << "\n\t\tH. Restore calendar from file";
		cout << "\n\t" << string(70, char(196));
		cout << "\n\t\tX. Exit";
		cout << "\n\t" << string(70, char(205));
		option = toupper(inputChar("\n\t\tOption: ", "ABCDEX"));
		switch (option)
		{
		case 'A':
			currentYear(calendar);
			break;
		case 'B':
			currentMonth(calendar); 
			break;
		case 'C':
			currentDay(calendar); 
			break;
		case 'D':
			currentCalendar(calendar);
			break;
		case 'E':
			scheduleAndReport(calendar, scheduleDays); 
			break;
		case 'F':
			syncSystemDate(calendar);
			break;
		case 'G':
			saveCalendar(calendar, scheduleDays);
			break;
		case 'H':
			restoreCalendar(calendar, scheduleDays);
			break;
		case 'X':
			exit(0);
			break; 
		default:
			cout << "\n\t\tERROR: Invalid Option!" << endl;
			break;
		}
		system("pause"); 
	} while (option != 'X');

	return 0; 
}
string getYearInWords(int year)
{
	vector<string> ones = { "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
	vector<string> teens = { "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen" };
	vector<string> tens = { "", "", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety" };
	vector<string> thousands = { "", "one thousand", "two thousand", "three thousand", "four thousand",
								 "five thousand", "six thousand", "seven thousand", "eight thousand", "nine thousand" };

	string yearInWords;

	// Handle thousands place
	if (year >= 1000) {
		int thousandPlace = year / 1000;
		yearInWords += thousands[thousandPlace] + " ";
		year %= 1000;
	}

	// Handle hundreds place
	if (year >= 100) {
		int hundreds = year / 100;
		yearInWords += ones[hundreds] + " hundred ";
		year %= 100;
	}

	// Handle tens and ones place
	if (year >= 10 && year < 20) {
		yearInWords += teens[year - 10];
	}
	else {
		if (year >= 20) {
			int tensPlace = year / 10;
			yearInWords += tens[tensPlace] + " ";
			year %= 10;
		}
		if (year > 0) {
			yearInWords += ones[year];
		}
	}

	return yearInWords;
}
void initializeWithCurrentDate(MyCalendar& calendar)
{
	time_t now = time(nullptr);
	tm localTime;

	// Get the current local time
	localtime_s(&localTime, &now);

	// Set the MyCalendar object with the current date
	calendar.setCurrentYear(localTime.tm_year + 1900);
	calendar.setCurrentMonth(localTime.tm_mon + 1);  // tm_mon is 0-11
	calendar.setCurrentDay(localTime.tm_mday);
}
void Zellercongruence(int day, int month, int year)
{
	if (month == 1) {
		month = 13;
		year--;
	}
	if (month == 2) {
		month = 14;
		year--;
	}
	int q = day;
	int m = month;
	int k = year % 100;
	int j = year / 100;
	int h
		= q + 13 * (m + 1) / 5 + k + k / 4 +
		j / 4 + 5 * j;
	h = h % 7;
	switch (h) {
	case 0:
		cout << "Saturday";
		break;
	case 1:
		cout << "Sunday";
		break;
	case 2:
		cout  << "Monday";
		break;
	case 3:
		cout << "Tuesday";
		break;
	case 4:
		cout << "Wednesday";
		break;
	case 5:
		cout << "Thursday";
		break;
	case 6:
		cout << "Friday";
		break;
	}
}
void currentYear(MyCalendar& calendar)
{ 
	do
	{
		system("cls"); 
		cout << "\n\tCurrent year: " << calendar.getCurrentYear() << " - " << getYearInWords(calendar.getCurrentYear()) << "  (" << (calendar.isLeapYear() ? "leap" : "non-leap") << ")";
		cout << "\n\n\tCalendar - Current Year Menu";
		cout << "\n\t" << string(70, char(205));
		cout << "\n\t1. Set Current Year";
		cout << "\n\t" << string(70, char(196));
		cout << "\n\t0. Return";
		cout << "\n\t" << string(70, char(205)); 
		switch (inputInteger("\n\tOption: ", 0, 1))
		{
		case 0:
			return;
			break;
		case 1:
			calendar.setCurrentYear(inputInteger("\n\tEnter a year (1...9999): ", 1, 9999)); 
			if (!calendar.isLeapYear() && calendar.getCurrentMonth() == 2 && calendar.getCurrentDay() == 29)  //LOGIC ERROR NOTED IN NOTEBOOK
				calendar.setCurrentDay(28); 
			break;
		default:
			cout << "\n\tERROR: Invalid Option!";
			break;
		}
		system("pause");
	} while (true); 
}

void currentMonth(MyCalendar& calendar)
{
	string monthName[13] = { "unknown", "January", "February", "March", "April",
		"May", "June" , "July", "August", "September", "October" , "November",
		"December" };
	do
	{
		system("cls");
		cout << "\n\tCurrent Month: "<< calendar.getCurrentMonth() << " - " << monthName[calendar.getCurrentMonth()]; 
		cout << "\n\n\tCalendar - Current Month Menu";
		cout << "\n\t" << string(70, char(205));
		cout << "\n\t1. Set Current Month";
		cout << "\n\t" << string(70, char(196));
		cout << "\n\t0. Return";
		cout << "\n\t" << string(70, char(205));
		switch (inputInteger("\n\tOption: ", 0, 1))
		{
		case 0:
			return;
			break;
		case 1:
			calendar.setCurrentMonth(inputInteger("\n\tEnter a month (1...12): ", 1, 12));
			break;
		default:
			cout << "\n\tERROR: Invalid Option!";
			break;
		}
		system("pause");
	} while (true);
}
void currentDay(MyCalendar& calendar)
{
	do
	{
		system("cls");
		cout << "\n\tCurrent Day: " << calendar.getCurrentDay() << DaySuffix(calendar.getCurrentDay()); 
		cout << "\n\n\tCalendar - Current Day Menu";
		cout << "\n\t" << string(70, char(205));
		cout << "\n\t1. Set Current Day";
		cout << "\n\t" << string(70, char(196));
		cout << "\n\t0. Return";
		cout << "\n\t" << string(70, char(205));
		switch (inputInteger("\n\tOption: ", 0, 1))
		{
		case 0:
			return;
			break;
		case 1:
			switch (calendar.getCurrentMonth())
			{
			case 2: 
				if (calendar.isLeapYear())
					calendar.setCurrentDay(inputInteger("\n\tEnter a day (1...29): ", 1, 29));
				else
					calendar.setCurrentDay(inputInteger("\n\tEnter a day (1...28): ", 1, 28)); 
				break; 
			case 1:
			case 3:
			case 5:
			case 7:
			case 8:
			case 10:
			case 12:
				calendar.setCurrentDay(inputInteger("\n\tEnter a day (1...31): ", 1, 31)); 
				break; 
			default: 
				calendar.setCurrentDay(inputInteger("\n\tEnter a day (1...30): ", 1, 30));
			}
			break;
		default:
			cout << "\n\tERROR: Invalid Option!";
			break;
		}
		system("pause");
	} while (true);
}

void currentCalendar(MyCalendar& calendar)
{
	string monthName[13] = { "unknown", "January", "February", "March", "April",
		"May", "June" , "July", "August", "September", "October" , "November",
		"December" };
	int num = 0; 
	do
	{
		system("cls");
		cout << "\n\t";
		Zellercongruence(calendar.getCurrentDay(), calendar.getCurrentMonth(), calendar.getCurrentYear());
		cout << ", " << monthName[calendar.getCurrentMonth()] << " " << calendar.getCurrentDay() << DaySuffix(calendar.getCurrentDay()) << ", " << calendar.getCurrentYear() << endl;
		cout << "\t" << calendar << endl;
		cout << "\n\tMy Calendar Menu"; 
		cout << "\n\t" << string(70, char(205)); 
		cout << "\n\t 1. ++ (pre-increment)"; 
		cout << "\n\t 2. ++ (post-inrement)"; 
		cout << "\n\t 3. jump forward (+n)"; 
		cout << "\n\t" << string(70, char(196)); 
		cout << "\n\t-1. -- (pre-decrement)"; 
		cout << "\n\t-2. -- (post-decrement)"; 
		cout << "\n\t-3. jump backward (-n)"; 
		cout << "\n\t" << string(70, char(196)); 
		cout << "\n\t0. Return"; 
		cout << "\n\t" << string(70, char(205)); 
		switch (inputInteger("\n\tOption: ", -3, 3))
		{
		case 1: 
			cout << "\n\tPre-increment:(++)" << endl; 
			++calendar;
			cout << "\n\t";
			Zellercongruence(calendar.getCurrentDay(), calendar.getCurrentMonth(), calendar.getCurrentYear());
			cout << ", " << monthName[calendar.getCurrentMonth()] << " " << calendar.getCurrentDay() << DaySuffix(calendar.getCurrentDay()) << ", " << calendar.getCurrentYear() << endl;
			cout << "\t" << calendar << endl; 
			break; 
		case 2: 
			cout << "\n\tPost-increment:(++)" << endl; 
			cout << "\n\t"; 
			Zellercongruence(calendar.getCurrentDay(), calendar.getCurrentMonth(), calendar.getCurrentYear()); 
			cout << ", " << monthName[calendar.getCurrentMonth()] << " " << calendar.getCurrentDay() << DaySuffix(calendar.getCurrentDay()) << ", " << calendar.getCurrentYear() << endl;
			cout << "\t" << calendar << endl; 
			calendar++;
			break; 
		case 3:
			num = inputInteger("\n\tEnter an integer (n): ", true);
			cout << "\n\tJump forward(" << num << ")" << endl; 
			calendar.jumpForward(num); 
			break; 
		case -1: 
			cout << "\n\tPre-decrement:(--)" << endl; 
			--calendar;
			cout << "\n\t";
			Zellercongruence(calendar.getCurrentDay(), calendar.getCurrentMonth(), calendar.getCurrentYear());
			cout << ", " << monthName[calendar.getCurrentMonth()] << " " << calendar.getCurrentDay() << DaySuffix(calendar.getCurrentDay()) << ", " << calendar.getCurrentYear() << endl;
			cout << "\t" << calendar<< endl; 
			break; 
		case -2: 
			cout << "\n\tPost-decrement:(--)" << endl; 
			cout << "\n\t";
			Zellercongruence(calendar.getCurrentDay(), calendar.getCurrentMonth(), calendar.getCurrentYear());
			cout << ", " << monthName[calendar.getCurrentMonth()] << " " << calendar.getCurrentDay() << DaySuffix(calendar.getCurrentDay()) << ", " << calendar.getCurrentYear() << endl;
			cout << "\t" << calendar << endl; 
			calendar--;
			break; 
		case -3:
			num = inputInteger("\n\tEnter an integer (n): ", true);
			cout << "\n\tJump backward(" << num << ")" << endl;
			calendar.jumpBackward(num); 
			break; 
		case 0: 
			return; 
			break; 
		default: 
			cout << "\n\tERROR: Invalid Option!" << endl; 
			break; 
		}
		system("pause"); 
	}
	while (true); 
}

void scheduleAndReport(MyCalendar& calendar, MyScheduleDay(&scheduleDays)[12][31])
{
	MyCalendar originalCalendar = calendar;
	bool change = false; 
	bool scheduled = false; 
	char choice; 
	char R = 'R'; 
	char A = 'A'; 
	char H = 'H'; 
	char P = 'P';
	do
	{
		system("cls");
		string monthName[13] = { "unknown", "January", "February", "March", "April",
		"May", "June" , "July", "August", "September", "October" , "November",
		"December" };
		if (change)
		{
			cout << "\n\tMonth       : " << monthName[calendar.getScheduledMonth()];
			cout << "\n\tDay         : " << calendar.getScheduledDay() << DaySuffix(calendar.getScheduledDay()); 
		}
		else
		{
			cout << "\n\tMonth       : " << monthName[calendar.getCurrentMonth()];
			cout << "\n\tDay         : " << calendar.getCurrentDay() << DaySuffix(calendar.getCurrentDay()); 
		}
		cout << "\n\tType        : " << scheduleDays[calendar.getScheduledMonth() - 1][calendar.getScheduledDay() - 1].getType();
		cout << "\n\tDescription : " << scheduleDays[calendar.getScheduledMonth() - 1][calendar.getScheduledDay() - 1].getDescription() << endl;

		cout << "\n\n\tScheduling Date";
		cout << "\n\t" << string(70, char(205));
		cout << "\n\t1. Schedule a date";
		cout << "\n\t2. Unschedule a date";
		cout << "\n\t" << string(70, char(196));
		cout << "\n\t3. Display year schedules";
		cout << "\n\t4. Display month schedules";
		cout << "\n\t5. Display day schedule";
		cout << "\n\t" << string(70, char(196));
		cout << "\n\t0. Return";
		cout << "\n\t" << string(70, char(196)); 
		switch (inputInteger("\n\tOption: ", 0, 5))
		{
		case 1:
			calendar.setScheduledMonth(inputInteger("\n\tSpecify a month(1...12) : ", 1, 12)); 
			switch (calendar.getScheduledMonth())
			{
			case 2:
				if (calendar.isLeapYear())
					calendar.setScheduledDay(inputInteger("\n\tSpecify a day (1...29): ", 1, 29));
				else
					calendar.setScheduledDay(inputInteger("\n\tSpecify a day (1...28): ", 1, 28));
				break;
			case 1:
			case 3:
			case 5:
			case 7:
			case 8:
			case 10:
			case 12:
				calendar.setScheduledDay(inputInteger("\n\tSpecify a day (1...31): ", 1, 31));
				break;
			default:
				calendar.setScheduledDay(inputInteger("\n\tSpecify a day (1...30): ", 1, 30));
			}
			for (int month = 0; month < 12; month++)
			{
				scheduled = false; 
				int daysInMonth = calendar.getDaysInMonth(month + 1, calendar.getCurrentYear());
				for (int day = 0; day < daysInMonth; day++)
				{
					if (scheduleDays[calendar.getScheduledMonth() - 1][calendar.getScheduledDay() - 1].getDescription() != "unschedule")
						scheduled = true; 
					break; 
				}
			}
			change = true; 
			scheduleDays[calendar.getScheduledMonth() - 1][calendar.getScheduledDay() - 1].setDescription(inputString("\n\tEnter a description     : ", true));
			do
			{
				choice = toupper(inputChar("\n\tSpecify a type (R-return, A-Awareness, H-holiday or P-personal): ",true));  //SOME REASON NOT VALIDATING INPUT
				switch (choice)
				{
				case 'R':
					calendar = originalCalendar;
					cout << "\n\tDate has NOT been scheduled or resheduled." << endl;
					change = false;
					break;
				case 'H':
				case 'A':
				case 'P':
					change = true;
					break;
				default:
					cout << "\n\tERROR: Invalid option." << endl;
					
				}
			} while (choice != 'R' && choice != 'A' && choice != 'H' && choice != 'P');
			/*if (scheduleDays[calendar.getScheduledMonth() - 1][calendar.getScheduledDay() - 1].getType() == 'R')
			{
				calendar = originalCalendar; 
				cout << "\n\tDate has NOT been scheduled or resheduled" << endl; 
				change = false; 
				break; 
			}*/
			scheduleDays[calendar.getScheduledMonth() - 1][calendar.getScheduledDay() - 1].setType(choice); 
			calendar.getScheduleDay(calendar.getScheduledMonth(), calendar.getScheduledDay()) = scheduleDays[calendar.getScheduledMonth() - 1][calendar.getScheduledDay() - 1];
			if (scheduled)
			{
				cout << "\n\tWARNING: Overwrite the existing scheduled date!" << endl; 
			}
			
			if(change)
			cout << "\n\tSUCCESS: Date has successfully been scheduled." << endl; 
			break;
		case 2:
			calendar.setScheduledMonth(inputInteger("\n\tSpecify a month(1...12) : ", 1, 12));
			switch (calendar.getScheduledMonth())
			{
			case 2:
				if (calendar.isLeapYear())
					calendar.setScheduledDay(inputInteger("\n\tSpecify a day (1...29): ", 1, 29));
				else
					calendar.setScheduledDay(inputInteger("\n\tSpecify a day (1...28): ", 1, 28));
				break;
			case 1:
			case 3:
			case 5:
			case 7:
			case 8:
			case 10:
			case 12:
				calendar.setScheduledDay(inputInteger("\n\tSpecify a day (1...31): ", 1, 31));
				break;
			default:
				calendar.setScheduledDay(inputInteger("\n\tSpecify a day (1...30): ", 1, 30));
			}
			if (scheduleDays[calendar.getScheduledMonth() - 1][calendar.getScheduledDay() - 1].getDescription() != "unschedule" && scheduleDays[calendar.getScheduledMonth() - 1][calendar.getScheduledDay() - 1].getType() != 'U')
			{
				scheduleDays[calendar.getScheduledMonth() - 1][calendar.getScheduledDay() - 1].setDescription("unschedule");
				scheduleDays[calendar.getScheduledMonth() - 1][calendar.getScheduledDay() - 1].setType('U');
				cout << "\n\tSUCCESS: Date has successfully been unscheduled." << endl;
			}
			else
				cout << "\n\tWARNING: Date has NOT been unscheduled." << endl; 
			break;
		case 3:
			displayYearSchedule(calendar, scheduleDays);
			break;
		case 4:
			displayMonthSchedule(calendar, scheduleDays);
			break;
		case 5:
			displayDaySchedule(calendar, scheduleDays);
			break;
		case 0:
			return;
			break;
		default:
			cout << "\n\tERROR: Invalid Option!";
			break;
		}
		system("pause");
	} while (true); 
}
string DaySuffix(int day) 
{
	if (day >= 11 && day <= 13)
	{
		return "th";
	}

	switch (day % 10)
	{
	case 1: return "st";
	case 2: return "nd";
	case 3: return "rd";
	default: return "th";
	}
}

void displayYearSchedule(MyCalendar& calendar, MyScheduleDay(&scheduleDays)[12][31])	
{
	string monthName[13] = { "unknown", "January", "February", "March", "April",
		"May", "June" , "July", "August", "September", "October" , "November",
		"December" };
	for (int month = 0; month < 12; month++)
	{
		cout<< "\n\t" << left << setw(10) << monthName[month + 1] << " : "; 
		bool scheduled = false; 
		int daysInMonth = calendar.getDaysInMonth(month + 1, calendar.getCurrentYear());
		for (int day = 0; day < daysInMonth; day++)
		{
			//MyScheduleDay currentSchedule = calendar.getScheduleDay(month, day);
			if (scheduleDays[month][day].getDescription() != "unschedule")
			{
				scheduled = true; 
				cout << "\n\t\t   " << day + 1 << DaySuffix(day + 1) << " - " << scheduleDays[month][day].getDescription();
			}
		}
		if(!scheduled)
			cout << right << setw(30) << "No scheduled dates for the month." << endl;
	}
	cout << "\n";
}

void displayMonthSchedule(MyCalendar& calendar, MyScheduleDay(&scheduleDays)[12][31])			
{
	string monthName[13] = { "unknown", "January", "February", "March", "April",
		"May", "June" , "July", "August", "September", "October" , "November",
		"December" };
	int month = 0; 
	month = inputInteger("\n\tSpecify a month (1...12) : ", 1, 12); 
	cout << "\n\t" << left << setw(8) << monthName[month] << " : ";
	bool scheduled = false;
	int daysInMonth = calendar.getDaysInMonth(month, calendar.getCurrentYear());
	for (int day = 0; day < daysInMonth; day++)
	{
		if (scheduleDays[month - 1][day].getDescription() != "unschedule")
		{
			scheduled = true;
			cout << "\n\t\t   " << day + 1 << DaySuffix(day + 1) << " - " << scheduleDays[month - 1][day].getDescription();
		}
	}
	if (!scheduled)
	{
		cout << right << setw(30) << "No scheduled dates for the month." << endl;
	}
	cout << "\n";
}

void displayDaySchedule(MyCalendar& calendar, MyScheduleDay(&scheduleDays)[12][31])			

{
	string monthName[13] = { "unknown", "January", "February", "March", "April",
		"May", "June" , "July", "August", "September", "October" , "November",
		"December" };

	int searchDay = 0; 
	int searchMonth = 0; 
	searchMonth = inputInteger("\n\tSpecify a month (1...12) : ", 1, 12); 
	switch (searchMonth)
	{
	case 2:
		if (calendar.isLeapYear())
			searchDay = inputInteger("\n\tEnter a day (1...29): ", 1, 29);
		else
			searchDay = inputInteger("\n\tEnter a day (1...28): ", 1, 28);
		break;
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		searchDay = inputInteger("\n\tEnter a day (1...31): ", 1, 31);
		break;
	default:
		searchDay = inputInteger("\n\tEnter a day (1...30): ", 1, 30);
	}

	if (scheduleDays[searchMonth - 1][searchDay - 1].getDescription() != "unschedule")
	{
		cout << "\n\t" << left << setw(8) << monthName[searchMonth] << " : ";
		cout << "\n\t\t   " << searchDay << DaySuffix(searchDay) << " - " << scheduleDays[searchMonth - 1][searchDay - 1].getDescription();
	}
	else
	{
		cout << "\n\t" << left << setw(8) << monthName[searchMonth] << " : ";
		cout << "\n\t\t   " << searchDay << DaySuffix(searchDay) << " - " << scheduleDays[searchMonth - 1][searchDay - 1].getDescription();
	}
	cout << "\n"; 
}

void syncSystemDate(MyCalendar& calendar)
{
	initializeWithCurrentDate(calendar); 
	
}

void saveCalendar(MyCalendar& calendar, MyScheduleDay(&scheduleDays)[12][31])
{
	fstream outFile; 
	string filename = to_string(calendar.getCurrentYear()) + ".DAT"; 

	outFile.open(filename, ios::out | ios::binary);

	int currentYear = calendar.getCurrentYear();
	int currentMonth = calendar.getCurrentMonth();
	int currentDay = calendar.getCurrentDay();

	outFile.write(reinterpret_cast<char*>(&currentYear), sizeof(int));
	outFile.write(reinterpret_cast<char*>(&currentMonth), sizeof(int));
	outFile.write(reinterpret_cast<char*>(&currentDay), sizeof(int));

	for (int month = 0; month < 12; month++)
	{
		int daysInMonth = calendar.getDaysInMonth(month + 1, calendar.getCurrentYear());
		for (int day = 0; day < daysInMonth; day++)
		{
			outFile.write(reinterpret_cast<char*>(&scheduleDays[month][day]), sizeof(MyScheduleDay)); 
		}
	}

	cout << "\n\tSUCCESS: File, " << filename << ", has been saved." << endl; 

	outFile.close(); 
}

void restoreCalendar(MyCalendar& calendar, MyScheduleDay(&scheduleDays)[12][31])
{
	string filename = inputString("\n\tEnter a binary (.DAT) calendar filename: ", false); 

	fstream inFile; 
	inFile.open(filename, ios::in | ios::binary); 
	if (inFile.fail())
	{
		cout << "\n\tERROR: Cannot open file, " << filename << "." << endl; 
		return; 
	}

	int fileYear, fileMonth, fileDay = 1; 
	inFile.read(reinterpret_cast<char*>(&fileYear), sizeof(int));
	inFile.read(reinterpret_cast<char*>(&fileMonth), sizeof(int));
	inFile.read(reinterpret_cast<char*>(&fileDay), sizeof(int));

	// Set the read date into the calendar
	calendar.setCurrentYear(fileYear);
	calendar.setCurrentMonth(fileMonth);
	calendar.setCurrentDay(fileDay);

	for (int month = 0; month < 12; month++)
	{
		int daysInMonth = calendar.getDaysInMonth(month + 1, calendar.getCurrentYear());
		for (int day = 0; day < daysInMonth; day++)
		{
			inFile.read(reinterpret_cast<char*>(&scheduleDays[month][day]), sizeof(MyScheduleDay)); 
		}
	}

	cout << "\n\tSUCCESS: Restored calendar from " << filename << endl; 

	inFile.close(); 
}