// Eliminating Left Recursion from the given grammar productions
#include <iostream>
#include <cstring>
#define SIZE 10

using namespace std;

int main() {
    char non_terminal;
    char beta[SIZE], alpha[SIZE];
    int num;
    char production[10][SIZE];
    int index = 3; /* starting of the string following "->" */
    
    cout << "Enter the number of Productions: ";
    cin >> num;
    cout << "Enter the grammar as E->E-A:\n";
    
    for(int i = 0; i < num; i++) {
        cin >> production[i];
    }
    
    for(int i = 0; i < num; i++) {
        cout << "\nGRAMMAR: " << production[i];
        non_terminal = production[i][0];
        
        if (non_terminal == production[i][index]) {
            int j = 0, k = 0;
            index += 2; // Skip non-terminal and "->"
            
            while (production[i][index] != '|' && production[i][index] != '\0') {
                beta[j++] = production[i][index++];
            }
            beta[j] = '\0'; // Null-terminate beta
            
            if (production[i][index] == '|') {
                index++; // Skip '|'
                
                while (production[i][index] != '\0') {
                    alpha[k++] = production[i][index++];
                }
            }
            alpha[k] = '\0'; // Null-terminate alpha
            
            cout << " is left recursive.\n";
            cout << "Grammar without left recursion:\n";
            cout << non_terminal << "->" << beta << non_terminal << "\'\n";
            cout << non_terminal << "\'->" << alpha << non_terminal << "\'|E\n";
        } else {
            cout << " is not left recursive.\n";
        }
    }
    return 0;
}
