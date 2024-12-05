#include <iostream>
#include <fstream>
#include <regex>

int task1(const std::string &s) {
    int sum = 0;

    std::regex r(R"(mul\((\d+),(\d+)\))");
    for (std::sregex_iterator i(s.begin(), s.end(), r), end; i != end; ++i) {
        sum += std::stoi((*i)[1].str()) * std::stoi((*i)[2].str());
    }

    return sum;
}

int task2(const std::string &s) {
    int sum = 0;

    std::regex r(R"((do\(\))|(don't\(\))|mul\((\d+),(\d+)\))");
    bool d = true;
    for (std::sregex_iterator i(s.begin(), s.end(), r), end; i != end; ++i) {
        if ((*i)[1].str() == "do()") {
            d = true;
        } else if ((*i)[2].str() == "don't()") {
            d = false;
        } else if (!(*i)[3].str().empty() && !(*i)[4].str().empty()) {
            if (d) {
                sum += std::stoi((*i)[3].str()) * std::stoi((*i)[4].str());
            }
        }
    }

    return sum;
}

int main() {
    std::ifstream f("Day3/day3_input.txt");
    if (!f.is_open()) {
        std::cerr << "Error opening the file!" << std::endl;
        return -1;
    }

    std::ostringstream ss;
    std::string s;

    while (std::getline(f, s)) {
        ss << s;
    }

    s = ss.str();

    std::cout << "Task 1: " << task1(s) << std::endl;
    std::cout << "Task 2: " << task2(s) << std::endl;
}
