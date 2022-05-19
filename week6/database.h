#pragma once
#include <string>
#include <map>
#include <vector>
#include <set>
#include "date.h"
#include "deque"
#include "tuple"
#include <utility>
#include "algorithm"
#include <memory>

using namespace std;


class Database{
public:
    void Add(const Date& date, const string& event);
    void Print(ostream& os) const;

	template <typename Predicate>
	int RemoveIf(const Predicate& predicate) {
		int count = 0;

		vector<Date> del_date; 
		for (auto& date_order : order_addition) {
			vector<string> new_events;
			for (auto& event : date_order.second) {
				if (predicate(date_order.first, event)) {
					date_event[date_order.first].erase(event);
					count++;
				} else {
					new_events.push_back(event);
				}
			}
			if (new_events.empty()) {
				del_date.push_back(date_order.first);
			} else {
				date_order.second = new_events;
			}
		}
		for (auto& date : del_date) {
			date_event.erase(date);
			order_addition.erase(date);
		}
		return count;
	}

    template <typename F>
    vector<pair<Date, string>> FindIf(const F& predicate) const{
        vector<pair<Date, string>> res;
        for(auto& date : order_addition){
            for(auto& event : date.second){
                if(predicate(date.first, event)){
                    res.push_back({date.first, event});
                }
            }
        }
        return res;
    }

    pair<Date, string> Last(const Date& date) const;

private:
    map <Date, set<string>> date_event;
    map <Date, vector<string>> order_addition;
};



