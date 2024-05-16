```c
#include<iostream>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
using namespace std;

int vars,terms,i,j,k,m,rep,count,temp=-1;
char var[10],term[10],lead[10][10]; // Arrays to store variables, terminals, and leading set
struct grammar
{
    int prodno;
    char lhs,rhs[20][20];
}gram[50]; // Structure to hold grammar rules

void get()
{
    cout<<"\nLEADING SET COMPUTATION\n";
    cout<<"\nEnter the no. of variables : ";
    cin>>vars;
    cout<<"\nEnter the variables : \n";
    for(i=0;i<vars;i++)
    {
        cin>>gram[i].lhs; // Input variables
        var[i]=gram[i].lhs; // Store variables in var array
    }
    cout<<"\nEnter the no. of terminals : ";
    cin>>terms;
    cout<<"\nEnter the terminals : ";
    for(j=0;j<terms;j++)
        cin>>term[j]; // Input terminals
    cout<<"\nPRODUCTION DETAILS\n";
    for(i=0;i<vars;i++)
    {
        cout<<"\nEnter the no. of production of "<<gram[i].lhs<<":";
        cin>>gram[i].prodno; // Input production numbers for each variable
        for(j=0;j<gram[i].prodno;j++)
        {
            cout<<gram[i].lhs<<"->";
            cin>>gram[i].rhs[j]; // Input production rules
        }
    }
}

void leading()
{
    // Calculation of leading set
    for(i=0;i<vars;i++)
    {
        for(j=0;j<gram[i].prodno;j++)
        {
            for(k=0;k<terms;k++)
            {
                if(gram[i].rhs[j][0]==term[k])
                    lead[i][k]=1; // Mark the first terminal in the production as leading
                else
                {
                    if(gram[i].rhs[j][1]==term[k])
                        lead[i][k]=1; // Mark the second terminal if exists, as leading
                }
            }
        }
    }
    // Iterate to calculate transitive closure
    for(rep=0;rep<vars;rep++)
    {
        for(i=0;i<vars;i++)
        {
            for(j=0;j<gram[i].prodno;j++)
            {
                for(m=1;m<vars;m++)
                {
                    if(gram[i].rhs[j][0]==var[m])
                    {
                        temp=m;
                        goto out;
                    }
                }
                out:
                for(k=0;k<terms;k++)
                {
                    if(lead[temp][k]==1)
                        lead[i][k]=1; // Update leading set based on transitive closure
                }
            }
        }
    }
}

void display_leading()
{
    // Display leading set for each variable
    for(i=0;i<vars;i++)
    {
        cout<<"\nLEADING("<<gram[i].lhs<<") = ";
        for(j=0;j<terms;j++)
        {
            if(lead[i][j]==1)
                cout<<term[j]<<","; // Print leading terminals for the current variable
        }
    }
}

int main()
{
    get();
    leading();
    display_leading();
    return 0;
}
```
![image](https://github.com/PriyanshiNegi01/CD/assets/121029180/6da7b1bd-191c-4dec-b395-dc4078d9c789)
