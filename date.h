#include"pch.h"
#ifndef DATE_H
#define DATE_H
#include<iostream>
class Date {
private:
	int year;
	int month;
	int day;
	int totalDays;
public:
	Date() {}
	Date(int year, int month, int day);
	//static Date read();
	int getYear() const { return year; }
	int getMonth() const { return month; }
	int getDay() const { return day; }
	int getMaxDay() const;
	bool isLeapYear() const {
		return year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
	}
	void show() const;
	int operator- (const Date& date) const {
		return totalDays - date.totalDays;
	}

	bool operator<(const Date& date) const {
		return totalDays < date.totalDays;
	}
};

std::istream& operator>>(std::istream& in, Date& dat);
std::ostream& operator<<(std::ostream& out, const Date& date);

#endif