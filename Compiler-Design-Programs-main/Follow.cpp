#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include <cctype>

using namespace std;

unordered_map<char, unordered_set<char>> firstSet;
unordered_map<char, unordered_set<char>> followSet;
unordered_map<char, vector<string>> productions;

// Function to calculate First set
void calculateFirst(char nonTerminal) {
    if (firstSet.find(nonTerminal) != firstSet.end()) {
        // First set already calculated for this non-terminal
        return;
    }

    unordered_set<char> first;

    for (const string& production : productions[nonTerminal]) {
        if (!isupper(production[0])) {
            first.insert(production[0]);
        } else {
            calculateFirst(production[0]);
            const auto& nextFirst = firstSet[production[0]];
            first.insert(nextFirst.begin(), nextFirst.end());
        }
    }

    firstSet[nonTerminal] = first;
}

// Function to calculate Follow set
void calculateFollow(char nonTerminal) {
    if (followSet.find(nonTerminal) != followSet.end()) {
        // Follow set already calculated for this non-terminal
        return;
    }

    unordered_set<char> follow;

    if (nonTerminal == 'E') {
        follow.insert('$');
    }

    for (const auto& prodPair : productions) {
        char nt = prodPair.first;
        for (const string& production : prodPair.second) {
            for (size_t i = 0; i < production.size(); ++i) {
                if (production[i] == nonTerminal) {
                    if (i < production.size() - 1) {
                        char next = production[i + 1];
                        if (!isupper(next)) {
                            follow.insert(next);
                        } else {
                            calculateFirst(next);
                            const auto& nextFirst = firstSet[next];
                            follow.insert(nextFirst.begin(), nextFirst.end());
                            if (nextFirst.count('#') > 0) {
                                follow.erase('#');
                                calculateFollow(nt);
                                const auto& nextFollow = followSet[nt];
                                follow.insert(nextFollow.begin(), nextFollow.end());
                            }
                        }
                    } else {
                        if (nt != nonTerminal) {
                            calculateFollow(nt);
                            const auto& nextFollow = followSet[nt];
                            follow.insert(nextFollow.begin(), nextFollow.end());
                        }
                    }
                }
            }
        }
    }

    followSet[nonTerminal] = follow;
}

int main() {
    productions['E'] = {"TR"};
    productions['R'] = {"+TR", "#"};
    productions['T'] = {"FY"};
    productions['Y'] = {"*FY", "#"};
    productions['F'] = {"(E)", "i"};

    for (const auto& prodPair : productions) {
        char nt = prodPair.first;
        calculateFirst(nt);
        calculateFollow(nt);
    }

    // Print Follow sets for each non-terminal
    for (const auto& followPair : followSet) {
        cout << "Follow(" << followPair.first << ") = { ";
        for (char terminal : followPair.second) {
            cout << terminal << " ";
        }
        cout << "}\n";
    }

    return 0;
}
