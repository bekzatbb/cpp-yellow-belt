#pragma once
#include "string"
#include "sstream"
#include "iomanip"
#include "iostream"
#include "vector"
using namespace std;

#include <memory>

class Date {
public:
    Date(int new_year, int new_month, int new_day);
    int GetYear() const {return year;};
    int GetMonth() const {return month;};
    int GetDay() const {return day;};

private:
    int year, month, day;
};

bool operator < (const Date& lhs, const Date& rhs);

ostream& operator<<(ostream& stream, const Date& date);

bool operator==(const Date& lhs, const Date& rhs);

bool operator != (const Date& lhs, const Date& rhs);

bool operator <=(const Date& lhs, const Date& rhs);

bool operator >= (const Date& lhs, const Date& rhs);

bool operator > (const Date& lhs, const Date& rhs);

ostream& operator<<(ostream& os, const vector<pair<Date, string>>& T);

ostream& operator<<(ostream& os, const pair<Date, string> & P);

Date ParseDate(istream& date);