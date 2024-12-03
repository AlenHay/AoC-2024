#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm>

int task1(std::vector<int> &lc, std::vector<int> &rc) {
    int d = 0;
    std::sort(lc.begin(), lc.end());
    std::sort(rc.begin(), rc.end());

    for (int i = 0; i < std::min(lc.size(), rc.size()); ++i) {
        d += std::abs(lc[i] - rc[i]);
    }

    return d;
}

int task2(const std::vector<int> &lc, const std::vector<int> &rc) {
    int s = 0;
    std::unordered_map<int, int> rc_count;

    for (int re : rc) {
        rc_count[re]++;
    }

    for (int le : lc) {
        s += le * rc_count[le];
    }

    return s;
}

int main() {
    std::ifstream f("Day1/day1_input.txt");
    if (!f.is_open()) {
        std::cerr << "Error opening the file!" << std::endl;
        return -1;
    }

    std::vector<int> lc, rc;
    int l, r;
    while (f >> l >> r) {
        lc.push_back(l);
        rc.push_back(r);
    }
    f.close();

    int r1 = task1(lc, rc);
    int r2 = task2(lc, rc);

    std::cout << "Task 1: " << r1 << std::endl;
    std::cout << "Task 2: " << r2 << std::endl;

    return 0;
}