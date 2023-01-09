#pragma once
#include <iostream>
#include <string>
using namespace std;

class Calendar
{
private:
    int month;
    int year;

public:
    Calendar(int month, int year);
    int getDay(int date, int month, int year);
    void showCalendar(int month, int year);
    int getMonth();
    int getYear();
    void setMonth(int);
    void setYear(int);
};