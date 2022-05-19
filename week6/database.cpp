#include "database.h"
#include "algorithm"
using namespace std;

void Database::Add(const Date &date, const string &event) {
    if (date_event.count(date) > 0 && 
        date_event[date].count(event) == 1 ) {; 
    } else {
        date_event[date].insert(event);
        order_addition[date].push_back(event);
    }
}

void Database::Print(ostream& os) const {
	for (auto& date : order_addition) {
		for (auto& event : date.second) {
			os << date.first << " ";
			os << event;
			os << endl;
		}
	}
}




pair<Date, string> Database::Last(const Date& date) const{
	auto upper = order_addition.upper_bound(date);
	if (upper == order_addition.begin() || order_addition.empty()) { throw invalid_argument("no_date"); }
	--upper;
	return {upper->first, upper->second.back()};
}