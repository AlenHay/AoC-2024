#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm>

int task1(std::vector<int> &left_column, std::vector<int> &right_column) {
    int distance = 0;
    std::sort(left_column.begin(), left_column.end());
    std::sort(right_column.begin(), right_column.end());

    for (int i = 0; i < std::min(left_column.size(), right_column.size()); ++i) {
        distance += std::abs(left_column[i] - right_column[i]);
    }

    return distance;
}

int task2(const std::vector<int> &left_column, const std::vector<int> &right_column) {
    int similarity_score = 0;
    std::unordered_map<int, int> right_column_count;

    for (int location_id: right_column) {
        right_column_count[location_id]++;
    }

    for (int location_id: left_column) {
        similarity_score += location_id * right_column_count[location_id];
    }

    return similarity_score;
}

int main() {
    std::ifstream file("Day1/day1_input.txt");
    if (!file.is_open()) {
        std::cerr << "Error opening the file!" << std::endl;
        return -1;
    }

    std::vector<int> left_column, right_column;
    int left, right;
    while (file >> left >> right) {
        left_column.push_back(left);
        right_column.push_back(right);
    }
    file.close();

    std::cout << "Task 1: " << task1(left_column, right_column) << std::endl;
    std::cout << "Task 2: " << task2(left_column, right_column) << std::endl;

    return 0;
}