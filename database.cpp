#include <iostream>
#include <map>
#include <set>
#include <sstream>

using namespace std;
class Date {
public:
    explicit Date(string& input) {
        stringstream ss;
        char separator1, separator2;
        int i_year, i_month, i_day;
        ss << input;
        ss >> i_year >> separator1 >> i_month >> separator2 >> i_day;

        if (ss.fail() || !ss.eof() || separator1 != '-' || separator2 != '-') {
            throw domain_error("Wrong date format: " + input);
        }

        if (i_month > 12 || i_month < 1) {
            throw domain_error("Month value is invalid: " + to_string(i_month));
        }
        if (i_day > 31 || i_day < 1) {
            throw domain_error("Day value is invalid: " + to_string(i_day));
        }

        year = i_year;
        month = i_month;
        day = i_day;
    }

    int GetYear() const {
        return year;
    }

    int GetMonth() const {
        return month;
    }

    int GetDay() const {
        return day;
    }

private:
    int year;
    int month;
    int day;
};

bool operator<(const Date& lhs, const Date& rhs) {
    if (rhs.GetYear() == lhs.GetYear()) {
        if (rhs.GetMonth() == lhs.GetMonth()) {
            return lhs.GetDay() < rhs.GetDay();
        }
        return lhs.GetMonth() < rhs.GetMonth();
    }
    return lhs.GetYear() < rhs.GetYear();
}

class Database {
public:
    void AddEvent(const Date& date, const string& event) {
        m[date].insert(event);
    }

    bool DeleteEvent(const Date& date, const string& event) {
        if (m.count(date) && m[date].count(event)) {
            m[date].erase(event);
            return true;
        }
        return false;
    }

    int DeleteDate(const Date& date) {
        int cnt = m[date].size();
        if (cnt > 0) {
            m.erase(date);
        }
        return cnt;
    }

    set<string> Find(const Date& date) const {
        if (m.count(date)) {
            return m.at(date);
        }
        return {};
    }

    void Print() const {
        for (const auto& [key, value] : m) {
            string d = (key.GetDay() < 10) ? ("0" + to_string(key.GetDay())) : to_string(key.GetDay());
            string m = (key.GetMonth() < 10) ? ("0" + to_string(key.GetMonth())) : to_string(key.GetMonth());
            string y = "";
            if (key.GetYear() < 10) {
                y += "000";
            } else if (key.GetYear() < 100) {
                y += "00";
            } else if (key.GetYear() < 1000) {
                y += "0";
            }
            y += to_string(key.GetYear());
            for (const auto& line : value) {
                cout << y + "-" + m + "-" + d + " " + line << endl;
            }
        }
    }

private:
    map<Date, set<string>> m;
};

int main() {
    Database db;

    string line;
    while (getline(cin, line)) {
        try {
            if (line.empty()) {
                continue;
            }

            stringstream ss;
            ss << line;
            string command;
            ss >> command;

            if (command == "Add") {
                string date_str, event;
                ss >> date_str >> event;

                if (ss.fail()) {
                    cout << "Wrong date format: " << date_str << endl;
                    continue;
                }
                Date date(date_str);
                db.AddEvent(date, event);
            } else if (command == "Del") {
                string date_str, event;
                ss >> date_str >> event;
                Date date = Date(date_str);
                if (event.empty()) {
                    int deleted = db.DeleteDate(date);
                    cout << "Deleted " + to_string(deleted) + " events" << endl;
                } else {
                    if (db.DeleteEvent(date, event)) {
                        cout << "Deleted successfully" << endl;
                    } else {
                        cout << "Event not found" << endl;
                    }
                }
            } else if (command == "Find") {
                string date_str;
                ss >> date_str;
                const Date &date = Date(date_str);
                for (const auto &item: db.Find(date)) {
                    cout << item << endl;
                }

            } else if (command == "Print") {
                db.Print();
            } else {
                cout << "Unknown command: " << command << endl;
                return 0;
            }

        } catch (domain_error &error) {
            cout << error.what() << endl;
            return 0;
        }
    }

    return 0;
}
