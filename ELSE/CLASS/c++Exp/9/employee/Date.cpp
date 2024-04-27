#include "date.h"
Date::Date(int year, int month, int day) : year_(year), month_(month), day_(day) {}
void Date::SetYear(int year) { year_ = year; }
void Date::SetMonth(int month) { month_ = month; }
void Date::SetDay(int day) { day_ = day; }
int Date::GetYear() const { return year_; }
int Date::GetMonth() const { return month_; }
int Date::GetDay() const { return day_; }
