#include "date.h"
#include <string>
#include "utility"
#include "set"
#include <iomanip>

using namespace std;

Date::Date(int new_year, int new_month, int new_day) {
 
    if( new_year < 0 || new_year > 9999){
        throw runtime_error("Year value is invalid: " + to_string(new_year));
    } else year = new_year;
    if (new_month < 1 || new_month > 12) {
        throw runtime_error("Month value is invalid: " + to_string(new_month));
    }
    else month = new_month;

    if (new_day < 1 || new_day > 31) {
        throw runtime_error("Day value is invalid: " + 

to_string

(new_day));
    }
    else day = new_day;
}
bool operator < (const Date& lhs, const Date& rhs) {
    if (lhs.GetYear() == rhs.GetYear()) {
        if (lhs.GetMonth() == rhs.GetMonth()) {
            if (lhs.GetDay() < rhs.GetDay()) {
                return 1;
            }
            else return 0;
        }
        else if (lhs.GetMonth() < rhs.GetMonth()) {
            return 1;
        }
        else return 0;
    }
    return lhs.GetYear() < rhs.GetYear();
}

ostream& operator<<(ostream& stream, const Date& date) {
    stream << setw(4) << setfill('0') << date.GetYear() <<
           "-" << setw(2) << setfill('0') << date.GetMonth() <<
           "-" << setw(2) << setfill('0') << date.GetDay();
    return stream;
}

bool operator==(const Date& lhs, const Date& rhs){
    vector<int> left = {lhs.GetYear() , lhs.GetMonth(), lhs.GetDay()};
    vector<int> right = {rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()};
    return left == right;
}

bool operator != (const Date& lhs, const Date& rhs){
    vector<int> left = {lhs.GetYear() , lhs.GetMonth(), lhs.GetDay()};
    vector<int> right = {rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()};
    return left != right;
}

bool operator <= (const Date& lhs, const Date& rhs){
    vector<int> left = {lhs.GetYear() , lhs.GetMonth(), lhs.GetDay()};
    vector<int> right = {rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()};
    return left <= right;
}

bool operator >= (const Date& lhs, const Date& rhs){
    vector<int> left = {lhs.GetYear() , lhs.GetMonth(), lhs.GetDay()};
    vector<int> right = {rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()};
    return left >= right;
}

bool operator > (const Date& lhs, const Date& rhs){
    vector<int> left = {lhs.GetYear() , lhs.GetMonth(), lhs.GetDay()};
    vector<int> right = {rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()};
    return left > right;
}

ostream& operator<<(ostream& os, const vector<pair<Date, string>> &T){
    os << setfill('0');
    for(const auto& item : T){
        os << item.first <<  " " << item.second;
    }
    return os;
}
ostream& operator<<(ostream& os, const pair<Date, string> & P){
    os << setfill('0');
    os << P.first << " "<< P.second;
    return os;
}



Date ParseDate(istream& date) {  /* stringstream ss(date); */
    int year, month, day;
    date >> year;
    if (date.peek() != '-') {
        throw runtime_error("Wrong date format: check_year " /*+ date*/);
    }
    date.ignore();
    date >> month;
    if (date.peek() != '-') {
        throw runtime_error("Wrong date format: check_month " /*+ date"*/);
    }
    date.ignore();
    //ss >> day;
    if (!(date >> day)) { //если в поток не считалось вернет 0
        throw runtime_error("Wrong date format: check_day" /*+ "date"*/);
    }


    return Date(year, month, day);
}