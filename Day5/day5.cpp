#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>

using std::cin, std::cout, std::endl;
using std::string;
using std::unordered_set, std::unordered_map, std::vector, std::pair, std::queue;

unordered_map<int, unordered_set<int>> pageOrderingRuleParser(const vector<pair<int, int>> &page_ordering_rules) {
    unordered_map<int, unordered_set<int>> parsed_page_rules;

    for (const auto &rule: page_ordering_rules) {
        int first = rule.first;
        int second = rule.second;

        parsed_page_rules[first].insert(second);
    }

    return parsed_page_rules;
}

bool correctPageOrder(const unordered_map<int, unordered_set<int>> &parsed_page_rules, const vector<int> &update) {
    unordered_map<int, int> position_map;
    for (int i = 0; i < update.size(); ++i) {
        position_map[update[i]] = i;
    }

    for (const auto &rule: parsed_page_rules) {
        int first = rule.first;
        for (int second: rule.second) {
            if (position_map.find(first) != position_map.end() && position_map.find(second) != position_map.end()) {
                if (position_map[first] > position_map[second]) {
                    return false;
                }
            }
        }
    }
    return true;
}

int task1(const vector<pair<int, int>> &page_ordering_rules, const vector<vector<int>> &updates) {
    int middle_number_sum = 0;
    auto parsed_page_rules = pageOrderingRuleParser(page_ordering_rules);

    for (const auto &update: updates) {
        if (!update.empty() && correctPageOrder(parsed_page_rules, update)) {
            middle_number_sum += update[update.size() / 2];
        }
    }

    return middle_number_sum;
}

int main() {
    std::ifstream file("../Day5/day5_input.txt");
    if (!file.is_open()) {
        std::cerr << "Error opening the file!" << std::endl;
        return -1;
    }

    vector<pair<int, int>> page_ordering_rules;
    vector<vector<int>> updates;
    bool parsingRules = true;
    string line;

    while (std::getline(file, line)) {
        if (line.empty()) {
            parsingRules = false;
            continue;
        }

        std::stringstream ss(line);
        if (parsingRules) {
            int first, second;
            char delimiter = '|';
            ss >> first >> delimiter >> second;
            page_ordering_rules.emplace_back(first, second);
        } else {
            vector<int> update;
            string token;

            while (std::getline(ss, token, ',')) {
                update.push_back(std::stoi(token));
            }

            updates.push_back(update);
        }
    }

    file.close();

    cout << "Task 1: " << task1(page_ordering_rules, updates) << endl;

    return 0;
}
