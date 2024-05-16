```c
#include<iostream>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
using namespace std;

int vars, terms, i, j, k, m, rep, count, temp = -1;
char var[10], term[10], trail[10][10]; // Arrays to store variables, terminals, and trailing set
struct grammar
{
    int prodno;
    char lhs, rhs[20][20];
} gram[50]; // Structure to hold grammar rules

void get()
{
    cout << "\nTRAILING SET COMPUTATION\n";
    cout << "\nEnter the no. of variables : ";
    cin >> vars;
    cout << "\nEnter the variables : \n";
    for (i = 0; i < vars; i++)
    {
        cin >> gram[i].lhs; // Input variables
        var[i] = gram[i].lhs; // Store variables in var array
    }
    cout << "\nEnter the no. of terminals : ";
    cin >> terms;
    cout << "\nEnter the terminals : ";
    for (j = 0; j < terms; j++)
        cin >> term[j]; // Input terminals
    cout << "\nPRODUCTION DETAILS\n";
    for (i = 0; i < vars; i++)
    {
        cout << "\nEnter the no. of production of " << gram[i].lhs << ":";
        cin >> gram[i].prodno; // Input production numbers for each variable
        for (j = 0; j < gram[i].prodno; j++)
        {
            cout << gram[i].lhs << "->";
            cin >> gram[i].rhs[j]; // Input production rules
        }
    }
}

void trailing()
{
    // Calculation of trailing set
    for (i = 0; i < vars; i++)
    {
        for (j = 0; j < gram[i].prodno; j++)
        {
            count = 0;
            while (gram[i].rhs[j][count] != '\x0')
                count++;
            for (k = 0; k < terms; k++)
            {
                if (gram[i].rhs[j][count - 1] == term[k])
                    trail[i][k] = 1; // Mark the last terminal in the production as trailing
                else
                {
                    if (gram[i].rhs[j][count - 2] == term[k])
                        trail[i][k] = 1; // Mark the second-to-last terminal if exists, as trailing
                }
            }
        }
    }
    // Iterate to calculate transitive closure
    for (rep = 0; rep < vars; rep++)
    {
        for (i = 0; i < vars; i++)
        {
            for (j = 0; j < gram[i].prodno; j++)
            {
                count = 0;
                while (gram[i].rhs[j][count] != '\x0')
                    count++;
                for (m = 1; m < vars; m++)
                {
                    if (gram[i].rhs[j][count - 1] == var[m])
                        temp = m;
                }
                for (k = 0; k < terms; k++)
                {
                    if (trail[temp][k] == 1)
                        trail[i][k] = 1; // Update trailing set based on transitive closure
                }
            }
        }
    }
}

void display_trailing()
{
    // Display trailing set for each variable
    for (i = 0; i < vars; i++)
    {
        cout << "\nTRAILING(" << gram[i].lhs << ") = ";
        for (j = 0; j < terms; j++)
        {
            if (trail[i][j] == 1)
                cout << term[j] << ","; // Print trailing terminals for the current variable
        }
    }
}

int main()
{
    get();
    trailing();
    display_trailing();
    return 0;
}
```
![image](https://github.com/PriyanshiNegi01/CD/assets/121029180/a0a0df1f-913c-4bda-971f-bcf01bcb2d49)
