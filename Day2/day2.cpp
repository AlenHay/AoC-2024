#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iterator>

bool isSafe(std::vector<int> r) {
    bool is_incr = r[0] <= r[1];

    for (int i = 1; i < r.size(); ++i) {
        int diff = r[i] - r[i - 1];
        if (abs(diff) < 1 || abs(diff) > 3) {
            return false;
        }
        if ((is_incr && diff < 0) || (!is_incr && diff > 0)) {
            return false;
        }
    }

    return true;
}

int task1(const std::vector<std::vector<int>> &rs) {
    int safe_r = 0;

    for (const auto &r: rs) {
        if (isSafe(r)) {
            safe_r++;
        }
    }

    return safe_r;
}

int task2(const std::vector<std::vector<int>> &rs) {
    int safe_r = 0;

    for (const auto &r: rs) {
        if (isSafe(r)) {
            safe_r++;
            continue;
        }
        bool is_dumpable = true;
        for (int i = 0; i < r.size() && is_dumpable; ++i) {
            std::vector<int> modified_report = r;
            modified_report.erase(modified_report.begin() + i);

            if (isSafe(modified_report)) {
                safe_r++;
                is_dumpable = false;
            }
        }
    }

    return safe_r;
}

int main() {
    std::ifstream f("Day2/day2_input.txt");
    if (!f.is_open()) {
        std::cerr << "Error opening the file!" << std::endl;
        return -1;
    }

    std::vector<std::vector<int>> rs;
    std::string s;
    while (std::getline(f, s)) {
        std::istringstream ss(s);
        std::vector<int> temp_r((std::istream_iterator<int>(ss)), std::istream_iterator<int>());
        rs.push_back(temp_r);
    }

    std::cout << "Task 1: " << task1(rs) << std::endl;
    std::cout << "Task 2: " << task2(rs) << std::endl;
}