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

        if (patient.Rec().length() != 0)
        {
            cout << "\n\n\n\n\n\n\n\n\n";

            patient.printALLPatientReceipts();
            // cout << spaceLine << "1. View receipt details by ID\n";
            // cout << spaceLine << "2. Back\n";
            char data[200][200] =
                {
                    "\t   View receipt details by ID",
                    "\t   Back",
                };

            MenuBox MENU(2, data);
            int key = MENU.menu();
            switch (key)
            {
            case 1:
            {
                string recID = getStringInput("Enter the receipt ID you want to view details");
                while (!isValidReceiptID(recID, patient))
                {
                    printError("Invalid receipt ID, please enter again!");
                    recID = getStringInput("Enter the receipt ID you want to view details");
                }
                cout << endl;
                // Handle Exception
                printReceipt(patient.getID(), recID);
            }
            break;

            case 2:
                break;
            }
        }
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
        table.add("ID");
        table.add("Name");
        table.add("Email");
        table.endOfRow();
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

    bool existDay = false;
    for (int i = 0; i < appointments.length(); i++)
    {
        string x = appointments.get(i);
        int posSpace = x.find(" ");
        string ngay = (x.substr(0, posSpace));
        int id = stoi((x.substr(posSpace + 1, x.length())));

        if (isValidPatientID(id))
        {
            existDay = true;
            table.add(to_string(i + 1));
            table.add(ngay);
            table.add(getPatientFromDatabase(id).getName());
            table.endOfRow();
        }
    }
    if (existDay == false)
    {
        printError("You have no appointment!");
    }
    else
    {
        cout << table << endl;
    }
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