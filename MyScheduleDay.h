#pragma once
#include <cstring>
#include <iostream>
#include "MyUnit.h"
class MyScheduleDay :  public MyUnit
{
private: 
	char type; 
public: 
	MyScheduleDay()
	{
		type = 'U';
	}
	void setType(char t)
	{
		type = t; 
	}
	char getType() const
	{
		return type; 
	}
	friend ostream& operator << (ostream&, const MyScheduleDay&); 
};

ostream& operator << (ostream& out, const MyScheduleDay& obj)
{
	out << "\n\tType: " << obj.getType(); 
	return out; 
}
