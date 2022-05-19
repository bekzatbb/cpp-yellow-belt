#include "condition_parser.h" 
#include "database.h" 
#include "date.h" 
#include "node.h" 
#include <sstream>
#include "algorithm"
#include <iostream>
#include <stdexcept>
#include "date.h"
#include "condition_parser.h"
#include "database.h"
#include "test_runner.h"
using namespace std;

void TestParseEvent();
void TestDate();
void TestAdd();


int DoRemove (Database& db, const string& str);
void TestDbRemoveIf();
void TestDbLast();


string ParseEvent(istream& is) {
  // Реализуйте эту функцию
  string event;
  getline(is, event);
  auto it_b = find_if(event.begin(), event.end(),[](char s){
      return !isspace(s);
  });
  return string(it_b, event.end());
}

void TestAll();

int main() {

    TestAll();
	Database db;


    for (string line; getline(cin, line);) {
        istringstream is(line);

        string command;
        is >> command;
        if (command == "Add") {
            const auto date = ParseDate(is);
            const auto event = ParseEvent(is);
            db.Add(date, event);
        } else if (command == "Print") {
            db.Print(cout);
        } else if (command == "Del") {
            auto condition = ParseCondition(is);
            auto predicate = [condition](const Date &date, const string &event) {
                return condition->Evaluate(date, event);
            };
          int count = db.RemoveIf(predicate);
          cout << "Removed " << count << " entries" << endl;
        }
        else if (command == "Find") {
          auto condition = ParseCondition(is);
          auto predicate = [condition](const Date& date, const string& event) {
            return condition->Evaluate(date, event);
          };
          const auto entries = db.FindIf(predicate);
          for (const auto& entry : entries) {
            cout << entry << endl;
          }
          cout << "Found " << entries.size() << " entries" << endl;
        } else if (command == "Last") {
          try {
              cout << db.Last(ParseDate(is)) << endl;
          } catch (invalid_argument&) {
              cout << "No entries" << endl;
          }
        } else if (command.empty()) {
          continue;
        } else {
          throw logic_error("Unknown command: " + command);
        }
      }

            return 0;
}

void TestDbRemoveIf() {
	{
		Database db;
		db.Add({ 2017, 1, 1 }, "new year");
		db.Add({ 2017, 1, 7 }, "xmas");
		AssertEqual(0, DoRemove(db, R"(event == "something")"), "Remove nothing");
		AssertEqual(1, DoRemove(db, R"(date == "2017-01-01")"), "Remove by date");
		ostringstream out;
		db.Print(out);
		AssertEqual("2017-01-07 xmas\n", out.str(), "Remove by date, left");
	}
	{
		Database db;
		db.Add({ 2017, 1, 1 }, "new year");
		db.Add({ 2017, 1, 7 }, "xmas");
		AssertEqual(1, DoRemove(db, R"(event == "xmas")"), "Remove by event");
		ostringstream out;
		db.Print(out);
		AssertEqual("2017-01-01 new year\n", out.str(), "Remove by event, left");
	}
	{
		Database db;
		db.Add({ 2017, 1, 1 }, "new year");
		db.Add({ 2017, 1, 7 }, "xmas");
		db.Add({ 2017, 1, 7 }, "new year");
		AssertEqual(2, DoRemove(db, R"(event == "new year")"), "Multiple remove by event");
		ostringstream out;
		db.Print(out);
		AssertEqual("2017-01-07 xmas\n", out.str(), "Multiple remove by event, left");
	}
}

void TestDbLast() {
	Database db;
	db.Add({ 2017, 1, 1 }, "new year");
	db.Add({ 2017, 1, 7 }, "xmas");
	{
		try {
			db.Last({ 2016, 12, 31 });
			Assert(false, "last, found no entries");
		}
		catch (...) {
			Assert(true, "last, found no entries");

		}
	}
	{
		ostringstream os;
		os << db.Last({ 2017, 1, 2 });
		AssertEqual("2017-01-01 new year", os.str(), "greater than date");
	}
	{
		ostringstream os;
		os << db.Last({ 2017, 1, 1 });
		AssertEqual("2017-01-01 new year", os.str(), "eq to date");
	}
	{
		ostringstream os;
		os << db.Last({ 2017, 1, 10 });
		AssertEqual("2017-01-07 xmas", os.str(), "greater than max date");
	}
}

void TestParseEvent() {
  {
    istringstream is("event");
    AssertEqual(ParseEvent(is), "event", "Parse event without leading spaces");
  }

  {
    istringstream is("   sport event ");
    AssertEqual(ParseEvent(is), "sport event ", "Parse event with leading spaces");
  }

  {
      istringstream is("sport   event ");
      AssertEqual(ParseEvent(is), "sport   event ", "Parse event with middle spaces");
  }

  {
    istringstream is("  first event  \n  second event");
    vector<string> events;
    events.push_back(ParseEvent(is));
    events.push_back(ParseEvent(is));
    AssertEqual(events, vector<string>{"first event  ", "second event"}, "Parse multiple events");
  }
}

void TestDate() {
    {
        istringstream is("2017-6-25");
        auto p = ParseDate(is);
        Date d(2017, 06, 25);
        AssertEqual(p, d, "simple data");
    }

}

void TestAdd(){
    {
        Database db;
        istringstream is("2017-6-25");
        auto p = ParseDate(is);
        db.Add(p,"Singin song");
        db.Add(p, "Dancing dance");
        db.Add(p, "Sitting sit");
        db.Add(p, "Dancing dance");
        ostringstream out;
        db.Print(out);
        AssertEqual("2017-06-25 Singin song\n"
                    "2017-06-25 Dancing dance\n"
                    "2017-06-25 Sitting sit\n",
                out.str(),"db with repeats");
    }
    {
        Database db;
        istringstream is("2012-6-5");
        auto p = ParseDate(is);
        db.Add(p,"Dancing dance");
        db.Add(p, "Singing song");
        ostringstream out;
        db.Print(out);
        AssertEqual("2012-06-05 Dancing dance\n"
                    "2012-06-05 Singing song\n",
                    out.str(),"reverse");
    }
}


void TestAll() {
    TestRunner tr;
    tr.RunTest(TestParseEvent, "TestParseEvent");
    tr.RunTest(TestDate, "TestDate");
    tr.RunTest(TestDbRemoveIf, "TestRemoveif");
	tr.RunTest(TestDbLast, "TestDbLast");
	tr.RunTest(TestAdd, "TestAdd");
	tr.RunTest(TestParseCondition, "TestParseCondition");
}

int DoRemove (Database& db, const string& str) {
    istringstream is (str);
    auto condition = ParseCondition(is);
    auto predicate = [condition](const Date &date, const string &event) {
        return condition->Evaluate(date, event);
    };
    return db.RemoveIf(predicate);
}
