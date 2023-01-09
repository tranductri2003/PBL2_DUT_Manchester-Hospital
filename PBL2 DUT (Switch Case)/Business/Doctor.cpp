#pragma once
#include "Doctor.h"
#include "../Management/PatientManagement.cpp"
#include "../Management/DrugManagement.cpp"
#include "../Management/AppointmentManagement.cpp"

Doctor::Doctor() : User()
{
}

Doctor::Doctor(int id, string name, string email, string password) : User(id, name, email, password)
{
}

Doctor::~Doctor()
{
}

void Doctor::searchByPatientID()
{
    int id = getIntInput("Enter ID");
    if (!isValidPatientID(id))
    {
        printError("Invalid ID!");
    }
    else
    {
        cout << endl;

        Patient patient = getPatientFromDatabase(id);

        TextTable table;

        table.add("ID");
        table.add("Name");
        table.add("Email");
        table.endOfRow();

        table.add(to_string(patient.getID()));
        table.add(patient.getName());
        table.add(patient.getEmail());
        table.endOfRow();

        cout << table << endl;
    }
}

void Doctor::searchByPatientName()
{
    string name = getStringInput("Enter name");
    LinkedList<Patient> patients = getPatientNameFromDatabase(name);
    if (patients.length() > 0)
    {
        cout << endl;

        TextTable table;

        for (int i = 0; i < patients.length(); i++)
        {
            table.add("ID");
            table.add("Name");
            table.add("Email");
            table.endOfRow();

            Patient patient = patients.get(i);

            cout << patient.getID();
            table.add(to_string(patient.getID()));
            table.add(patient.getName());
            table.add(patient.getEmail());
            table.endOfRow();
        }

        cout << table << endl;
    }
    else
    {
        printError("Invalid name!");
    }
}

void Doctor::printAllPatient()
{
    TextTable table;

    table.add("ID");
    table.add("Name");
    table.add("Email");
    table.endOfRow();
    LinkedList<Patient> patients = getAllPatient();
    for (int i = 0; i < patients.length(); i++)
    {
        Patient patient = patients.get(i);
        table.add(to_string(patient.getID()));
        table.add(patient.getName());
        table.add(patient.getEmail());
        table.endOfRow();
    }

    cout << table << endl;
}

void Doctor::updatePatientById(int id)
{
    if (!isValidPatientID(id))
    {
        printError("Invalid ID!");
    }
    else
    {
        updatePatientInDatabase(id);
    }
}

void Doctor::deletePatientById(int id)
{
    if (!isValidPatientID(id))
    {
        printError("Invalid ID!");
    }
    else
    {
        deletePatientFromDatabase(id);
    }
}

void Doctor::addNewDrug()
{
    addNewDrugToDataBase();
}

void Doctor::updateDrugById(int id)
{
    if (!isValidDrugId(id))
    {
        printError("Invalid ID, please enter again!");
    }
    else
    {
        updateDrugInDatabase(id);
    }
}

void Doctor::deleteDrugById(int id)
{
    if (!isValidDrugId(id))
    {
        printError("Invalid ID, please enter again!");
    }
    else
    {
        deleteDrugFromDatabase(id);
    }
}

void Doctor::printAllAppointment()
{
    system("cls");
    ifstream inFile("./Page/DoctorAppointmentManagement.txt");
    string line;
    while (getline(inFile, line))
    {
        cout << line << endl;
    }
    inFile.close();

    TextTable table;

    table.add("Num");
    table.add("Date");
    table.add("Name");
    table.endOfRow();
    LinkedList<string> appointments = getAllAppointment();

    for (int i = 0; i < appointments.length(); i++)
    {
        string x = appointments.get(i);
        int posSpace = x.find(" ");
        string ngay = (x.substr(0, posSpace));
        int id = stoi((x.substr(posSpace + 1, x.length())));

        table.add(to_string(i + 1));
        table.add(ngay);
        table.add(getPatientFromDatabase(id).getName());
        table.endOfRow();
    }

    cout << table << endl;
}

void Doctor::printByMonthAppointment()
{
    int year, month;
    string choose;
    do
    {
        system("cls");
        ifstream inFile("./Page/DoctorAppointmentManagement.txt");
        string line;
        while (getline(inFile, line))
        {
            cout << line << endl;
        }
        inFile.close();

        year = getIntInput("Which year do you want to view appointment? ");
        month = getMonthInput("Which month do you want to view appointment? ");
        Calendar calendar(month, year);
        calendar.showCalendar(month, year);
        cout << endl;
        choose = getYesNoInput("Continue?");
    } while (choose == "y" || choose == "Y");
}