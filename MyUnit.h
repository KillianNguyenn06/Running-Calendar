#pragma once
#include<cstring>
#include<iostream>
using namespace std;
class MyUnit
{
private:
	unsigned short value;
	char description[100];
public:
	MyUnit()
	{
		value = 0;
		strncpy_s(description, "unschedule", 99);
	}
	void setValue(int n)
	{
		value = n;
	}
	int getValue() const
	{
		return value;
	}
	void setDescription(string d)
	{
		strncpy_s(description, d.c_str(), 99);
	}
	string getDescription() const
	{
		return description;
	}
	friend ostream& operator<<(ostream&, const MyUnit&);
};
ostream& operator<<(ostream& out, const MyUnit& obj)
{
	out << "\nvalue: " << obj.getValue();
	out << "\ndescription: " << obj.getDescription();
	return out;
}
