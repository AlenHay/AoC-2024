#include <iostream>
#include <fstream>
#include <vector>

int task1(const std::vector<std::vector<char>> &word_search) {
    int count = 0;

    int directions[8][2] = {
            {0,  1},
            {1,  0},
            {0,  -1},
            {-1, 0},
            {1,  1},
            {-1, -1},
            {1,  -1},
            {-1, 1},
    };

    const std::string word = "XMAS";
    for (int i = 0; i < word_search.size(); ++i) {
        for (int j = 0; j < word_search[i].size(); ++j) {
            if (word_search[i][j] == 'X') {
                for (auto &direction: directions) {
                    bool valid = true;
                    for (int k = 0; k < word.length(); ++k) {
                        int ni = i + k * direction[0];
                        int nj = j + k * direction[1];
                        if (ni < 0 || ni >= word_search.size() ||
                            nj < 0 || nj >= word_search[i].size() ||
                            word_search[ni][nj] != word[k]) {
                            valid = false;
                            break;
                        }
                    }
                    count += valid;
                }
            }
        }
    }

    return count;
}

int task2(const std::vector<std::vector<char>> &word_search) {
    int count = 0;

    const int directions[2][2] = {
            {1, 1},
            {1, -1},
    };

    for (int i = 1; i < word_search.size() - 1; ++i) {
        for (int j = 1; j < word_search[i].size() - 1; ++j) {
            if (word_search[i][j] == 'A') {
                int valid = true;
                for (const auto &direction: directions) {
                    int ni = i + direction[0];
                    int nj = j + direction[1];
                    int mi = i - direction[0];
                    int mj = j - direction[1];
                    if (word_search[ni][nj] == 'A' || word_search[mi][mj] == 'A' ||
                        word_search[ni][nj] == 'X' || word_search[mi][mj] == 'X' ||
                        word_search[ni][nj] == word_search[mi][mj]) {
                        valid = false;
                        break;
                    }
                }
                count += valid;
            }
        }
    }

    return count;
}

int main() {
    std::ifstream file("Day4/day4_input.txt");
    if (!file.is_open()) {
        std::cerr << "Error opening the file!" << std::endl;
        return -1;
    }

    std::vector<std::vector<char>> word_search;
    std::string string;

    while (std::getline(file, string)) {
        word_search.emplace_back(string.begin(), string.end());
    }
    file.close();

    std::cout << "Task 1: " << task1(word_search) << std::endl;
    std::cout << "Task 2: " << task2(word_search) << std::endl;
}