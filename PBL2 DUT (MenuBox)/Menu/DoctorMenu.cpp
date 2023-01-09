#pragma once
#include "Menu.h"
#include "../Management/PatientManagement.cpp"
#include "../Management/DrugManagement.cpp"
#include "../Business/Doctor.cpp"
#include <iostream>
#include <fstream>
using namespace std;

void DoctorMenu::main()
{
    system("cls");
    ifstream inFile("./Page/Doctor.txt");
    string line;
    while (getline(inFile, line))
    {
        cout << line << endl;
    }
    inFile.close();

    // cout << spaceLine << "1. Login\n";
    // cout << spaceLine << "2. Back \n";
    char data[200][200] =
        {
            "\t   Login",
            "\t   Back",
        };

    MenuBox MENU(2, data);
    int key = MENU.menu();
    switch (key)
    {
    case 1:
    {
        DoctorMenu::login();
        system("pause");
        break;
    }

    case 2:
        Home::menu();
        break;
    }
}

void DoctorMenu::login()
{
    system("cls");

    int id = -1;
    int time = 3;

    do
    {
        ifstream inFile("./Page/DoctorLogin.txt");
        string line;
        while (getline(inFile, line))
        {
            cout << line << endl;
        }
        inFile.close();

        // Break ESC
        string email = getEmailInput();
        string password = getPasswordInput("Password");
        if (email == "admin123@gmail.com" && password == (to_string(123456789)))
        {
            Doctor doctor;
            DoctorMenu::menu(doctor);
        }
        else
        {
            time--;
            if (time != 0)
            {
                printError("Wrong admin account, please enter again!");
                system("pause");
                system("cls");
            }
            else
            {
                printError("You have reached maximum login attempts, please try again later!");
                system("pause");
                DoctorMenu::main();
            }
        }
    } while (id = -1);
}

void DoctorMenu::menu(Doctor &doctor)
{
    system("cls");

    while (true)
    {
        int key = DoctorMenu::printTask();
        switch (key)
        {
        case 1:
        {
            DoctorMenu::drugManagement(doctor);
            system("pause");
            DoctorMenu::menu(doctor);
        }
        break;

        case 2:
        {
            DoctorMenu::patientManagement(doctor);
            system("pause");
            DoctorMenu::menu(doctor);
        }
        break;

        case 3:
        {
            DoctorMenu::appointmentManagement(doctor);
            system("pause");
            DoctorMenu::menu(doctor);
        }
        break;

        case 4:
        {
            DoctorMenu::saleDrugManagement(doctor);
            system("pause");
            DoctorMenu::menu(doctor);
        }
        break;

        case 5:
            Home::menu();
            break;
        }
    }
}
int DoctorMenu::printTask()
{
    ifstream inFile("./Page/DoctorMenu.txt");
    string line;
    while (getline(inFile, line))
    {
        cout << line << endl;
    }
    inFile.close();
    // cout << spaceLine << "1. Drug Management\n";
    // cout << spaceLine << "2. Patient Management\n";
    // cout << spaceLine << "3. Appointment Management\n";
    // cout << spaceLine << "4. Sale Drug Management\n";
    // cout << spaceLine << "5. Log out\n";

    char data[200][200] =
        {
            "\t  Drug Management",
            "\t  Patient Management",
            "\t  Appointment Management",
            "\t  Sale Drug Management",
            "\t  Log out",
        };

    MenuBox MENU(5, data);
    int key = MENU.menu();
    return key;
}

void DoctorMenu::drugManagement(Doctor &doctor)
{
    system("cls");
    ifstream inFile("./Page/DoctorDrugManagement.txt");
    string line;
    while (getline(inFile, line))
    {
        cout << line << endl;
    }
    inFile.close();
    // cout << spaceLine << "1. View all drugs available\n";
    // cout << spaceLine << "2. Add new drug\n";
    // cout << spaceLine << "3. Update drug information\n";
    // cout << spaceLine << "4. Search drug information\n";
    // cout << spaceLine << "5. Delete drug\n";
    // cout << spaceLine << "6. Back\n";
    char data[200][200] =
        {
            "\t  View all drugs available",
            "\t  Add new drug",
            "\t  Update drug information",
            "\t  Search drug information",
            "\t  Delete drug",
            "\t  Back",
        };

    MenuBox MENU(6, data);
    int key = MENU.menu();
    switch (key)
    {
    case 1:
    {
        doctor.printAllDrug();
        system("pause");
        DoctorMenu::drugManagement(doctor);
    }
    break;

    case 2:
    {
        doctor.addNewDrug();
        system("pause");
        DoctorMenu::drugManagement(doctor);
    }
    break;

    case 3:
    {
        int drugID = getIntInput("Enter the Drug ID you want to update");
        if (!isValidDrugId(drugID))
        {
            printError("Invalid Drug ID, please enter again!");
        }
        else
        {
            doctor.updateDrugById(drugID);
        }
        system("pause");
        DoctorMenu::drugManagement(doctor);
    }
    break;

    case 4:
    {
        DoctorMenu::searchDrug(doctor);
        system("pause");
        DoctorMenu::drugManagement(doctor);
    }
    break;

    case 5:
    {
        int drugID = getIntInput("Enter the Drug ID you want to delete");
        if (!isValidDrugId(drugID))
        {
            printError("Invalid drug ID, please enter again!");
        }
        else
        {
            doctor.deleteDrugById(drugID);
        }
        system("pause");
        DoctorMenu::drugManagement(doctor);
    }
    break;

    case 6:
        DoctorMenu::menu(doctor);
        break;
    }
}

void DoctorMenu::patientManagement(Doctor &doctor)
{
    system("cls");
    ifstream inFile("./Page/DoctorPatientManagement.txt");
    string line;
    while (getline(inFile, line))
    {
        cout << line << endl;
    }
    inFile.close();
    // cout << spaceLine << "1. View all Patients\n";
    // cout << spaceLine << "2. Search Patient information\n";
    // cout << spaceLine << "3. Update Patient information\n";
    // cout << spaceLine << "4. Delete Patient\n";
    // cout << spaceLine << "5. Back\n";
    char data[200][200] =
        {
            "\t  View all Patients",
            "\t  Search Patient information",
            "\t  Update Patient information",
            "\t  Delete Patient",
            "\t  Back",
        };

    MenuBox MENU(5, data);
    int key = MENU.menu();
    switch (key)
    {
    case 1:
    {
        LinkedList<Patient> patients = getAllPatient();
        printAllPatient(patients);
        system("pause");
        DoctorMenu::patientManagement(doctor);
    }
    break;

    case 2:
    {
        searchPatient(doctor);
        system("pause");
        DoctorMenu::patientManagement(doctor);
    }
    break;

    case 3:
    {
        int patientID = getIntInput("Enter the Patient ID you want to update");
        if (!isValidPatientID(patientID))
        {
            printError("Invalid Patient ID, please enter again!");
        }
        else
        {
            doctor.updatePatientById(patientID);
        }
        system("pause");
        DoctorMenu::patientManagement(doctor);
    }
    break;

    case 4:
    {
        int patientID = getIntInput("Enter the Patient ID you want to delete");
        if (!isValidPatientID(patientID))
        {
            printError("Invalid Patient ID, please enter again!");
        }
        else
        {
            doctor.deletePatientById(patientID);
        }
        system("pause");
        DoctorMenu::patientManagement(doctor);
    }
    break;

    case 5:
        DoctorMenu::menu(doctor);
        break;
    }
}
void DoctorMenu::appointmentManagement(Doctor &doctor)
{
    system("cls");
    ifstream inFile("./Page/DoctorAppointmentManagement.txt");
    string line;
    while (getline(inFile, line))
    {
        cout << line << endl;
    }
    inFile.close();
    // cout << spaceLine << "1. View Overall Schedule\n";
    // cout << spaceLine << "2. View By Month Schedule\n";
    // cout << spaceLine << "3. Back\n";

    char data[200][200] =
        {
            "\t  View Overall Schedule",
            "\t  View By Month Schedule",
            "\t  Back",
        };

    MenuBox MENU(3, data);
    int key = MENU.menu();
    switch (key)
    {
    case 1:
    {
        doctor.printAllAppointment();
        system("pause");
        DoctorMenu::appointmentManagement(doctor);
    }
    break;
    case 2:
    {
        doctor.printByMonthAppointment();
        system("pause");
        DoctorMenu::appointmentManagement(doctor);
    }
    break;
    case 3:
    {
        DoctorMenu::menu(doctor);
        break;
    }
    }
}

void DoctorMenu::saleDrugManagement(Doctor &doctor)
{
    system("cls");
    ifstream inFile("./Page/DoctorDrugSaleManagement.txt");
    string line;
    while (getline(inFile, line))
    {
        cout << line << endl;
    }
    inFile.close();
    // cout << spaceLine << "1. View drug sales\n";
    // cout << spaceLine << "2. Back\n";

    char data[200][200] =
        {
            "\t  View drug sales",
            "\t  Back",
        };

    MenuBox MENU(2, data);
    int key = MENU.menu();
    switch (key)
    {
    case 1:
    {
        LinkedList<Drug> drugs = getSaleManagement();
        printSaleTable(drugs);
        system("pause");
        DoctorMenu::saleDrugManagement(doctor);
    }
    break;

    case 2:
    {
        DoctorMenu::menu(doctor);
        break;
    }
    }
}

void DoctorMenu::searchDrug(Doctor &doctor)
{
    system("cls");
    ifstream inFile("./Page/DoctorSearchDrug.txt");
    string line;
    while (getline(inFile, line))
    {
        cout << line << endl;
    }
    inFile.close();
    // cout << spaceLine << "1. Search by ID\n";
    // cout << spaceLine << "2. Search by Name\n";
    // cout << spaceLine << "3. Back\n";
    char data[200][200] =
        {
            "\t  Search by ID",
            "\t  Search by Name",
            "\t  Back",
        };

    MenuBox MENU(3, data);
    int key = MENU.menu();
    switch (key)
    {
    case 1:
    {
        doctor.searchByDrugID();
        system("pause");
        DoctorMenu::searchDrug(doctor);
    }
    break;
    case 2:
    {
        doctor.searchByDrugName();
        system("pause");
        DoctorMenu::searchDrug(doctor);
    }
    break;

    case 3:
        DoctorMenu::drugManagement(doctor);
        break;
    }
}

void DoctorMenu::searchPatient(Doctor &doctor)
{
    system("cls");
    ifstream inFile("./Page/DoctorSearchPatient.txt");
    string line;
    while (getline(inFile, line))
    {
        cout << line << endl;
    }
    inFile.close();
    // cout << spaceLine << "1. Search by ID\n";
    // cout << spaceLine << "2. Search by Name\n";
    // cout << spaceLine << "3. Back\n";
    char data[200][200] =
        {
            "\t  Search by ID",
            "\t  Search by Name",
            "\t  Back",
        };

    MenuBox MENU(3, data);
    int key = MENU.menu();
    switch (key)
    {
    case 1:
    {
        doctor.searchByPatientID();
        system("pause");
        DoctorMenu::searchPatient(doctor);
    }
    break;

    case 2:
    {
        doctor.searchByPatientName();
        system("pause");
        DoctorMenu::searchPatient(doctor);
    }
    break;

    case 3:
        DoctorMenu::patientManagement(doctor);
        break;
    }
}
