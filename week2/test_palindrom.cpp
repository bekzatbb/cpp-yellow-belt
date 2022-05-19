#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
    os << "{";
    bool first = true;
    for (const auto& kv : m) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << kv.first << ": " << kv.second;
    }
    return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
    if (t != u) {
        ostringstream os;
        os << "Assertion failed: " << t << " != " << u;
        if (!hint.empty()) {
            os << " hint: " << hint;
        }
        throw runtime_error(os.str());
    }
}

void Assert(bool b, const string& hint) {
    AssertEqual(b, true, hint);
}

class TestRunner {
public:
    template <class TestFunc>
    void RunTest(TestFunc func, const string& test_name) {
        try {
            func();
            cerr << test_name << " OK" << endl;
        }
        catch (exception & e) {
            ++fail_count;
            cerr << test_name << " fail: " << e.what() << endl;
        }
        catch (...) {
            ++fail_count;
            cerr << "Unknown exception caught" << endl;
        }
    }

    ~TestRunner() {
        if (fail_count > 0) {
            cerr << fail_count << " unit tests failed. Terminate" << endl;
            exit(1);
        }
    }

private:
    int fail_count = 0;
};

bool IsPalindrome(const string& str) {
    // Вы можете вставлять сюда различные реализации функции,
    // чтобы проверить, что ваши тесты пропускают корректный код
    // и ловят некорректный
    for (int i = 0; i < str.size() / 2; ++i) {
        if (str[i] != str[str.size() - i - 1]) {
            return false;
        }
    }
    return true;
}

void EmptyString() {
    AssertEqual(IsPalindrome(""), 1);
    AssertEqual(IsPalindrome("  "), 1);
    AssertEqual(IsPalindrome(" "), 1);
    AssertEqual(IsPalindrome("       "), 1);

}

void oneSymbol() {
    AssertEqual(IsPalindrome("a"), 1);
    AssertEqual(IsPalindrome("A"), 1);
}

void Palindrome_with_space() {
    AssertEqual(IsPalindrome("m a a m"), 1);
    AssertEqual( IsPalindrome(" m a  a m "), 1);
    AssertEqual(IsPalindrome("    a    "), 1);
}

void evenPalindrome() {
    AssertEqual(IsPalindrome("poop"), 1);
    AssertEqual(IsPalindrome("  ABA  "), 1);
    AssertEqual(IsPalindrome("Madam"), 0);
}

void oddPalindrome() {
    AssertEqual(IsPalindrome("pokop"), 1);
    AssertEqual(IsPalindrome("baobab"), 0);
    AssertEqual(IsPalindrome(" ABA") , 0);
}

void even_not_a_Palindrome() {
    AssertEqual(IsPalindrome("damn"), 0);
    AssertEqual(IsPalindrome(" a ba"), 0);
    AssertEqual(IsPalindrome("777777"), 1);

}

void odd_not_a_Palindrome() {
    AssertEqual(IsPalindrome("damnj"), 0);
    AssertEqual(IsPalindrome("ad"), 0);
}



int main() {
    TestRunner runner;
    // добавьте сюда свои тесты
    runner.RunTest(EmptyString, "EmptyString is Palindrome");
    runner.RunTest(oneSymbol, "One Symbol is Palindrome");
    runner.RunTest(Palindrome_with_space, "Palindrome_with_space");
    runner.RunTest(evenPalindrome, "evenPalindrome");
    runner.RunTest(oddPalindrome, "oddPalindrome");
    runner.RunTest(even_not_a_Palindrome, "even_not_a_Palindrome");
    runner.RunTest(odd_not_a_Palindrome, "odd_not_a_Palindrome");
    return 0;
}