#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iterator>

bool isSafe(std::vector<int> report) {
    bool is_increasing = report[0] <= report[1];

    for (int i = 1; i < report.size(); ++i) {
        int diff = report[i] - report[i - 1];
        if (abs(diff) < 1 || abs(diff) > 3) {
            return false;
        }
        if ((is_increasing && diff < 0) || (!is_increasing && diff > 0)) {
            return false;
        }
    }

    return true;
}

int task1(const std::vector<std::vector<int>> &reports) {
    int safe_reports = 0;

    for (const auto &r: reports) {
        if (isSafe(r)) {
            safe_reports++;
        }
    }

    return safe_reports;
}

int task2(const std::vector<std::vector<int>> &reports) {
    int safe_reports = 0;

    for (const auto &report: reports) {
        if (isSafe(report)) {
            safe_reports++;
            continue;
        }
        bool is_dumpable = true;
        for (int i = 0; i < report.size() && is_dumpable; ++i) {
            std::vector<int> modified_report = report;
            modified_report.erase(modified_report.begin() + i);

            if (isSafe(modified_report)) {
                safe_reports++;
                is_dumpable = false;
            }
        }
    }

    return safe_reports;
}

int main() {
    std::ifstream file("Day2/day2_input.txt");
    if (!file.is_open()) {
        std::cerr << "Error opening the file!" << std::endl;
        return -1;
    }

    std::vector<std::vector<int>> reports;
    std::string string_report;
    while (std::getline(file, string_report)) {
        std::istringstream ss(string_report);
        reports.emplace_back((std::istream_iterator<int>(ss)), std::istream_iterator<int>());
    }
    file.close();

    std::cout << "Task 1: " << task1(reports) << std::endl;
    std::cout << "Task 2: " << task2(reports) << std::endl;
}