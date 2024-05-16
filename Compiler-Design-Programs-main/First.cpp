#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <cctype>

using namespace std;

// Global data structure to store the First sets
unordered_map<char, unordered_set<char>> firstSet;

// Function to calculate First set
void calculateFirst(char nonTerminal, const vector<string> &productions) {
    if (firstSet.find(nonTerminal) != firstSet.end()) {
        // First set already calculated for this non-terminal
        return;
    }

    // Create a set to store the First set for the current non-terminal
    unordered_set<char> first;

    // Loop through productions to find productions for the current non-terminal
    for (const string &production : productions) {
        if (production[0] == nonTerminal) {
            
            if (production.size() == 1) { // Handle epsilon production
                first.insert('#');
            } else if (!isupper(production[2])) { // If the next symbol is a terminal, add it to the First set
                first.insert(production[2]);
            } else { // If the next symbol is a non-terminal, recursively calculate its First set
                calculateFirst(production[2], productions);
                const auto &nextFirst = firstSet[production[2]]; // Merge the First set of the next non-terminal with the current First set
                first.insert(nextFirst.begin(), nextFirst.end());
            }
        }
    }

    firstSet[nonTerminal] = first;
}

int main() {
    vector<string> productions = {
        "E=TR", 
        "R=+TR", 
        "R=#", 
        "T=FY", 
        "Y=*FY", 
        "Y=#", 
        "F=(E)", 
        "F=i"
    };

    // Calculate First set for each non-terminal in the grammar
    for (const string &production : productions) {
        calculateFirst(production[0], productions);
    }

    // Print First sets for each non-terminal
    for (const auto &pair : firstSet) {
        cout << "First(" << pair.first << ") = { ";
        for (char terminal : pair.second) {
            cout << terminal << " ";
        }
        cout << "}\n";
    }

    return 0;
}
