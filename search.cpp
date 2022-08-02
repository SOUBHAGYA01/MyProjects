//Mini Search Engine project by Soubhagya Kumar Dash
#include <fstream>
#include <stdio.h>
#include <iostream>
#include <conio.h>
#include <bits/stdc++.h>
using namespace std;
int main()
{
    char ch;
    char file[56];
    char name[78];
    char a[25];
    FILE *fp;
    system("clear");
    cout << "                               ENTER FILE NAME TO SEARCH\n\n"
         << endl;
    cin >> a;
    sprintf(file, "%s", a);
    fp = fopen(file, "r");
    if (fp == NULL)
    {
        printf("sorry");
        getch();
    }
    else
    {
        while ((ch = fgetc(fp)) != EOF)
            cout << ch;
        getch();
    }

    fclose(fp);
    return 0;
}
