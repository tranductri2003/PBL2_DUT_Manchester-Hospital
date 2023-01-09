#pragma once
#include "../Business/Appointment.h"
#include "../Business/Appointment.cpp"
#include "../Library/Console.cpp"
#include "../Library/Table.cpp"
#include <fstream>
#include <string>
#include <iostream>
#include <cstring>
#include <direct.h>

using namespace std;

bool isValidDate(int drugID)
{
    ifstream inFile("./Database/DrugDB/drug_ID.txt");
    string x;
    while (getline(inFile, x))
    {
        if (stoi(x) == drugID)
        {
            return true;
        }
    }
    inFile.close();
    return false;
}

int isFreeDate(int date, int month, int year)
{
    int *check = new int[32];
    for (int i = 0; i < 32; i++)
        check[i] = -1;

    string fileName = to_string(year) + "." + to_string(month) + ".txt";
    string pathName = "./Database/AppointmentDB/" + fileName;

    ifstream inFile(pathName);
    string x;
    while (getline(inFile, x))
    {
        int posSpace = x.find(" ");
        int ngay = stoi((x.substr(0, posSpace)));
        int id = stoi((x.substr(posSpace + 1, x.length())));

        check[ngay] = id;
    }
    inFile.close();

    return check[date];
}

void addNewDayToDataBase(int date, int month, int year, int ID)
{
    string fileName = to_string(year) + "." + to_string(month) + ".txt";
    string pathName = "./Database/AppointmentDB/" + fileName;
    fstream outFile(pathName, fstream::app);
    outFile << date << " " << ID << endl;
    outFile.close();

    string path = "./Database/AppointmentDB/AppointmentDB.txt";
    fstream outNewFile(path, fstream::app);
    string name = to_string(date) + "/" + to_string(month) + "/" + to_string(year);
    outNewFile << name << " " << ID << endl;
    outNewFile.close();
}

LinkedList<string> getAllAppointment()
{
    LinkedList<string> appointments;

    ifstream inFile("./Database/AppointmentDB/AppointmentDB.txt");
    if (!inFile.is_open())
    {
        printError("Error open file drug_ID.txt");
    }
    string x;

    // Create a new drug object
    // Get each drug from database then add it to the list of drugs
    while (getline(inFile, x))
    {
        appointments.addLast(x);
    }

    inFile.close();
    return appointments;
}

LinkedList<string> getAllAppointmentOfID(int ID)
{
    LinkedList<string> appointments;

    ifstream inFile("./Database/AppointmentDB/AppointmentDB.txt");
    if (!inFile.is_open())
    {
        printError("Error open file drug_ID.txt");
    }
    string x;

    // Create a new drug object
    // Get each drug from database then add it to the list of drugs
    while (getline(inFile, x))
    {
        int posSpace = x.find(" ");
        string ngay = (x.substr(0, posSpace));
        int id = stoi((x.substr(posSpace + 1, x.length())));

        if (id == ID)
            appointments.addLast(ngay);
    }

    inFile.close();
    return appointments;
}