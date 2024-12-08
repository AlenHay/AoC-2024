#include <iostream>
#include <fstream>
#include <regex>

int task1(const std::string &string) {
    int sum = 0;

    std::regex rule(R"(mul\((\d+),(\d+)\))");
    for (std::sregex_iterator i(string.begin(), string.end(), rule), end; i != end; ++i) {
        sum += std::stoi((*i)[1].str()) * std::stoi((*i)[2].str());
    }

    return sum;
}

int task2(const std::string &s) {
    int sum = 0;

    std::regex rule(R"((do\(\))|(don't\(\))|mul\((\d+),(\d+)\))");
    bool executable = true;
    for (std::sregex_iterator i(s.begin(), s.end(), rule), end; i != end; ++i) {
        if ((*i)[1].str() == "do()") {
            executable = true;
        } else if ((*i)[2].str() == "don't()") {
            executable = false;
        } else if (!(*i)[3].str().empty() && !(*i)[4].str().empty()) {
            if (executable) {
                sum += std::stoi((*i)[3].str()) * std::stoi((*i)[4].str());
            }
        }
    }

    return sum;
}

int main() {
    std::ifstream file("Day3/day3_input.txt");
    if (!file.is_open()) {
        std::cerr << "Error opening the file!" << std::endl;
        return -1;
    }

    std::ostringstream ss;
    std::string string;

    while (std::getline(file, string)) {
        ss << string;
    }
    file.close();
    string = ss.str();

    std::cout << "Task 1: " << task1(string) << std::endl;
    std::cout << "Task 2: " << task2(string) << std::endl;
}
