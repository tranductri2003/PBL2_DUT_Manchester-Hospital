#pragma once
#include <fstream>
#include "Menu.h"
#include "./PatientMenu.cpp"
#include "./DoctorMenu.cpp"

void Home::printTask()
{
    ifstream inFile("./Page/MainPage.txt");
    string line;
    while (getline(inFile, line))
    {
        cout << line << endl;
    }
    inFile.close();
    cout << spaceLine << "1. Doctor\n";
    cout << spaceLine << "2. Patient\n";
    cout << spaceLine << "3. Exit\n";
}

void Home::menu()
{
    system("cls");
    Home::printTask();

    int key = getKey(3);
    switch (key)
    {
    case 1:
        DoctorMenu::main();
        system("pause");
        break;

    case 2:
        PatientMenu::main();
        system("pause");
        break;

    case 3:
        exit(0);
        break;
    }
}