#include"pch.h"

namespace {
	const int DAYS_BEFORE_MIONTH[] = { 0,31,59,90,120,151,181,212,243,173,304,334,365 };
}

istream& operator>>(istream& in, Date& date) {
	int year, month, day;
	char c1, c2;
	in >> year >> c1 >> month >> c2 >> day;
	if (c1 != '-' || c2 != '-')
		throw runtime_error("Bad time format");
	date = Date(year, month, day);
	return in;
}

ostream& operator<<(ostream& out, const Date& date) {
	out << date.getYear() << '-' << date.getMonth() << '-' << date.getDay();
	return out;
}

Date::Date(int year, int month, int day) :year(year), month(month), day(day) {
	if (day<0 || day>getMaxDay()) throw runtime_error("Invalid date");
	int years = year - 1;
	totalDays = years * 365 + years / 4 - years / 100 + years / 400
		+ DAYS_BEFORE_MIONTH[month - 1] + day;
	if (isLeapYear() && month > 2) {
		totalDays++;
	}
}

int Date::getMaxDay()const {
	if (isLeapYear() && month == 2) {
		return 29;
	}
	else {
		return DAYS_BEFORE_MIONTH[month] - DAYS_BEFORE_MIONTH[month - 1];
	}
}

void Date::show() const {
	cout << getYear() << '-' << getMonth() << "-" << getDay();
}