#pragma once
#include "Appointment.h"
#include "../Management/AppointmentManagement.cpp"
#include <fstream>
#include <iostream>
using namespace std;

Calendar::Calendar(int month, int year)
{
    this->month = month;
    this->year = year;
}

int Calendar::getDay(int date, int month, int year)
{
    int monthc, yearc, centuryc, centuryx, lyearc, day;
    if (month == 1)
    {
        monthc = 0;
    }
    else if (month == 2)
    {
        monthc = 3;
    }
    else if (month == 3)
    {
        monthc = 3;
    }
    else if (month == 4)
    {
        monthc = 6;
    }
    else if (month == 5)
    {
        monthc = 1;
    }
    else if (month == 6)
    {
        monthc = 4;
    }
    else if (month == 7)
    {
        monthc = 6;
    }
    else if (month == 8)
    {
        monthc = 2;
    }
    else if (month == 9)
    {
        monthc = 5;
    }
    else if (month == 10)
    {
        monthc = 0;
    }
    else if (month == 11)
    {
        monthc = 3;
    }
    else if (month == 12)
    {
        monthc = 5;
    }

    yearc = (year + (year / 4)) % 7;

    centuryx = (year - (year % 100));

    if (centuryx == 1700)
    {
        centuryc = 4;
    }
    else if (centuryx == 1800)
    {
        centuryc = 2;
    }
    else if (centuryx == 1900)
    {
        centuryc = 0;
    }
    else if (centuryx == 2000)
    {
        centuryc = 6;
    }
    else if (centuryx == 2100)
    {
        centuryc = 4;
    }
    else if (centuryx == 2200)
    {
        centuryc = 8;
    }
    else if (centuryx == 2300)
    {
        centuryc = 0;
    }

    lyearc = 0;

    if ((year % 4 == 0 && year % 100 != 0) || (year % 4 == 0 && year % 100 == 0 && year % 400 == 0))
    {
        if (month == 1 || month == 2)
        {
            lyearc = 1;
        }
    }

    day = (yearc - lyearc + date + monthc + centuryc) % 7;

    return day;
}

void Calendar::showCalendar(int month, int year)
{
    // int red = 67, black = 37;
    int red = 12, black = 10;

    int iday = getDay(1, month, year);
    int calendar[6][6] = {0};
    int lday = 1, i, j, flag = 0;

    cout << "\nCalculator of Month: " << month << " / " << year << endl;
    cout << ("\n____________________________________________________________________________________");
    cout << ("\n|   Sunday  |  Monday   |  Tuesday  | Wednesday | Thursday  |  Friday   | Saturday  |");
    cout << ("\n|___________|___________|___________|___________|___________|___________|___________|\n");

    int k;

    for (i = 0; i <= 6; i++)
    {
        for (k = 0; k <= 2; k++)
        {
            for (j = 1; j <= 7; j++)
            {
                int l = 1;

                if (iday == 0 && i == 0 && j < 7)
                {
                    cout << ("|___________");
                }

                else if (j < iday && i == 0 && iday != 0)
                {
                    cout << ("|___________");
                }
                else
                {
                    calendar[i][j - l] = lday;
                    if (k == 1)
                    {
                        if (calendar[i][j - l] % 10 == calendar[i][j - l])
                        {
                            if (j == 7)
                            {
                                cout << "|     ";
                                if (isFreeDate(calendar[i][j - l], month, year) == -1)
                                    printLineColor(to_string(calendar[i][j - l]), black);
                                else
                                    printLineColor(to_string(calendar[i][j - l]), red);
                                cout << "     |";
                            }
                            else
                            {
                                cout << "|     ";
                                if (isFreeDate(calendar[i][j - l], month, year) == -1)
                                    printLineColor(to_string(calendar[i][j - l]), black);
                                else
                                    printLineColor(to_string(calendar[i][j - l]), red);
                                cout << "     ";
                            }
                        }
                        else
                        {
                            if (j == 7)
                            {
                                cout << "|     ";
                                if (isFreeDate(calendar[i][j - l], month, year) == -1)
                                    printLineColor(to_string(calendar[i][j - l]), black);
                                else
                                    printLineColor(to_string(calendar[i][j - l]), red);
                                cout << "    |";
                            }
                            else
                            {
                                cout << "|     ";
                                if (isFreeDate(calendar[i][j - l], month, year) == -1)
                                    printLineColor(to_string(calendar[i][j - l]), black);
                                else
                                    printLineColor(to_string(calendar[i][j - l]), red);
                                cout << "    ";
                            }
                        }
                        lday++;

                        if (lday > 30 && (month == 4 || month == 6 || month == 9 || month == 11))
                        {
                            flag = 1;
                            break;
                        }
                        if (lday > 31 && (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12))
                        {
                            flag = 1;
                            break;
                        }
                        else if (lday > 28 && month == 2)
                        {
                            flag = 1;
                            break;
                        }
                    }

                    else if (k == 2)
                    {
                        if (j == 7)
                        {
                            cout << ("|___________|");
                        }
                        else
                        {
                            cout << ("|___________");
                        }
                    }
                    else
                    {
                        if (j == 7)
                        {
                            cout << ("|           |");
                        }
                        else
                            cout << ("|           ");
                    }
                }
            }
            cout << endl;
        }
        if (flag == 1)
        {
            break;
        }
    }
}

int Calendar::getMonth()
{
    return this->month;
}

int Calendar::getYear()
{
    return this->year;
}

void Calendar::setMonth(int month)
{
    this->month = month;
}

void Calendar::setYear(int year)
{
    this->year = year;
}