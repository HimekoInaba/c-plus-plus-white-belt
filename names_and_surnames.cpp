#include <string>
#include <map>
#include <vector>
#include <algorithm>

class Person {
public:
    Person(std::string first_name, std::string last_name, int year_of_birth) {
        this->year_of_birth = year_of_birth;
        this->first_name_map[year_of_birth] = first_name;
        this->last_name_map[year_of_birth] = last_name;
    }

    void ChangeFirstName(int year, const std::string &first_name) {
        if (year >= this->year_of_birth) {
            first_name_map[year] = first_name;
        }
    }

    void ChangeLastName(int year, const std::string &last_name) {
        if (year >= this->year_of_birth) {
            last_name_map[year] = last_name;
        }
    }

    std::string GetFullName(int year) const {
        if (year < year_of_birth) {
            return "No person";
        }

        std::string first_name = FindLatestFirstName(year);
        std::string last_name = FindLatestLastName(year);
        if (first_name == UNKNOWN && last_name == UNKNOWN) {
            return "Incognito";
        } else if (last_name == UNKNOWN) {
            return first_name + " with unknown last name";
        } else if (first_name == UNKNOWN) {
            return last_name + " with unknown first name";
        } else {
            return first_name + " " + last_name;
        }
    }

    std::string GetFullNameWithHistory(int year) const {
        if (year < year_of_birth) {
            return "No person";
        }

        std::vector<std::string> first_names = FindLatestFirstNameWithHistory(year);
        std::vector<std::string> last_names = FindLatestLastNameWithHistory(year);
        if (first_names.size() == 0 && last_names.size() == 0) {
            return "Incognito";
        } else if (first_names.size() == 0) {
            return ConstructHistory(last_names) + " with unknown first name";
        } else if (last_names.size() == 0) {
            return ConstructHistory(first_names) + " with unknown last name";
        } else {
            return ConstructHistory(first_names) + " " + ConstructHistory(last_names);
        }
    }

private:
    const std::string UNKNOWN = "unknown";
    int year_of_birth;
    std::map<int, std::string> first_name_map;
    std::map<int, std::string> last_name_map;

    std::string ConstructHistory(std::vector<std::string> v) const {
        if (v.size() == 1) {
            return v[0];
        } else {
            std::string res = v[0] + " (";
            for (int i = 1; i < v.size(); ++i) {
                res += v[i] + ", ";
            }
            res = res.substr(0, res.length() - 1);
            res[res.length() - 1] = ')';
            return res;
        }
    }

    std::string FindLatestFirstName(int year) const {
        std::string res = UNKNOWN;
        for (const auto& [key, val] : first_name_map) {
            if (key <= year) {
                res = val;
            }
        }
        return res;
    }

    std::vector<std::string> FindLatestFirstNameWithHistory(int year) const {
        std::string prev = "";
        std::vector<std::string> v;
        for (auto iter = first_name_map.rbegin(); iter != first_name_map.rend(); ++iter) {
            auto key = iter->first;
            std::string val = iter->second;
            if (key <= year && val != prev) {
                prev = val;
                v.push_back(val);
            }
        }
        return v;
    }

    std::string FindLatestLastName(int year) const {
        std::string res = UNKNOWN;
        for (const auto& [key, val] : last_name_map) {
            if (key <= year) {
                res = val;
            }
        }
        return res;
    }

    std::vector<std::string> FindLatestLastNameWithHistory(int year) const {
        std::vector<std::string> v;
        std::string prev = "";
        for (auto iter = last_name_map.rbegin(); iter != last_name_map.rend(); ++iter) {
            auto key = iter->first;
            std::string val = iter->second;
            if (key <= year && val != prev) {
                prev = val;
                v.push_back(val);
            }
        }
        return v;
    }
};
