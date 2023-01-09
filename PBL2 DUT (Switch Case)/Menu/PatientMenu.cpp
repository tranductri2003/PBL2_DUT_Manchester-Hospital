#pragma once
#include "Menu.h"
#include "../Management/PatientManagement.cpp"
#include "../Management/DrugManagement.cpp"
#include "../Management/UserManagement.cpp"
#include "../Library/Console.cpp"
#include <iostream>
using namespace std;

void PatientMenu::main()
{
    system("cls");
    ifstream inFile("./Page/Patient.txt");
    string line;
    while (getline(inFile, line))
    {
        cout << line << endl;
    }
    inFile.close();
    cout << spaceLine << "1. Login\n";
    cout << spaceLine << "2. Sign Up\n";
    cout << spaceLine << "3. Back\n";
    int key = getKey(3);
    switch (key)
    {
    case 1:
    {
        PatientMenu::login();
        system("pause");
        break;
    }

    case 2:
    {
        PatientMenu::signUp();
        system("pause");
        break;
    }

    case 3:
        Home::menu();
        break;
    }
}
void PatientMenu::login()
{
    system("cls");

    int time = 3;
    int id = -1;
    do
    {
        ifstream inFile("./Page/PatientLogin.txt");
        string line;
        while (getline(inFile, line))
        {
            cout << line << endl;
        }
        inFile.close();
        string email = getEmailInput();
        string password = getPasswordInput("Password");

        id = findUser(email, password);
        if (id == -1)
        {
            time--;
            if (time != 0)
            {
                printError("Invalid email/password, please enter again!");
                system("pause");
                system("cls");
            }
            else
            {
                printError("You have reached maximum login attempts, please try again later!");
                system("pause");
                PatientMenu::main();
            }
        }
        else
        {
            Patient patient = getPatientFromDatabase(id);
            PatientMenu::menu(patient);
        }
    } while (id = -1);
}
void PatientMenu::signUp()
{
    system("cls");
    ifstream inFile("./Page/PatientSignUp.txt");
    string line;
    while (getline(inFile, line))
    {
        cout << line << endl;
    }
    inFile.close();
    Patient patient = addNewPatient();
    PatientMenu::menu(patient);
}
void PatientMenu::menu(Patient &patient)
{
    system("cls");
    PatientMenu::printTask();

    while (true)
    {
        int key = getKey(9);
        switch (key)
        {
        case 1:
        {
            patient = getPatientFromDatabase(patient.getID()); // PatientManagement,user
            printPatient(patient);                             // PatientManagement
            system("pause");
            PatientMenu::menu(patient);
        }
        break;

        case 2:
        {
            updatePatientInDatabase(patient.getID()); // PatientManagement
            system("pause");
            PatientMenu::menu(patient);
        }
        break;

        case 3:
        {
            orderDrugHistory(patient);
            system("pause");
            PatientMenu::menu(patient);
        }
        break;

        case 4:
        {
            patient.printAllDrug(); // Business/User
            system("pause");
            PatientMenu::menu(patient);
        }
        break;

        case 5:
        {
            searchDrug(patient);
            system("pause");
            PatientMenu::menu(patient);
        }
        break;

        case 6:
        {
            purchaseDrug(patient);
            system("pause");
            PatientMenu::menu(patient);
        }
        break;

        case 7:
        {
            bookAppointment(patient);
            system("pause");
            PatientMenu::menu(patient);
        }
        break;

        case 8:
        {
            viewMedicalHistory(patient);
            system("pause");
            PatientMenu::menu(patient);
        }
        break;

        case 9:
            Home::menu();
            break;
        }
    }
}

void PatientMenu::printTask()
{
    system("cls");
    ifstream inFile("./Page/PatientMenu.txt");
    string line;
    while (getline(inFile, line))
    {
        cout << line << endl;
    }
    inFile.close();
    cout << spaceLine << "1. Account information\n";
    cout << spaceLine << "2. Update account information\n";
    cout << spaceLine << "3. View your drug order history\n";
    cout << spaceLine << "4. View all drugs\n";
    cout << spaceLine << "5. Search drug information\n";
    cout << spaceLine << "6. Purchase drug\n";
    cout << spaceLine << "7. Book an appointment\n";
    cout << spaceLine << "8. View medical history\n";
    cout << spaceLine << "9. Log out\n";
}

void PatientMenu::purchaseDrug(Patient &patient)
{
    system("cls");

    patient.printAllDrug();

    int drugID, drugQuantity, newDrugQuantity;
    string request;

    do
    {
        drugID = getIntInput("Please enter the Drug ID that you want to purchase");
        while (!isValidDrugId(drugID))
        {
            printError("Invalid Drug ID, please enter again!");
            drugID = getIntInput("Please enter the Drug ID that you want to purchase");
        }
        Drug Drug = getDrugFromDatabase(drugID);
        drugQuantity = getIntInput("Please enter the quantity you want to purchase");
        while (drugQuantity > Drug.getQuantity() || drugQuantity < 1)
        {
            printError("Invalid Drug quantity, please enter again!");
            drugQuantity = getIntInput("Please enter the quantity you want to purchase");
        }
        newDrugQuantity = Drug.getQuantity() - drugQuantity;
        updateDrugQuantityInDatabase(drugID, newDrugQuantity);
        updateSale(Drug.getID(), drugQuantity);
        patient.getCart().addDrugtoCart(drugID, drugQuantity);
        request = getYesNoInput(spaceLineChoice + "Do you want to purchase another Drug (y/n)");
    } while (request == "y" || request == "Y");

    patient.purchase();
}

void PatientMenu::searchDrug(Patient &patient)
{
    system("cls");
    ifstream inFile("./Page/DoctorSearchDrug.txt");
    string line;
    while (getline(inFile, line))
    {
        cout << line << endl;
    }
    inFile.close();
    cout << spaceLine << "1. Search by ID\n";
    cout << spaceLine << "2. Search by Name\n";
    cout << spaceLine << "3. Back\n";
    int key = getKey(3);
    switch (key)
    {
    case 1:
    {
        patient.searchByDrugID();
        system("pause");
        PatientMenu::searchDrug(patient);
    }
    break;
    case 2:
    {
        patient.searchByDrugName();
        system("pause");
        PatientMenu::searchDrug(patient);
    }
    break;

    case 3:
        PatientMenu::menu(patient);
        break;
    }
}
void PatientMenu::bookAppointment(Patient &patient)
{
    system("cls");
    ifstream inFile("./Page/PatientSchedule.txt");
    string line;
    while (getline(inFile, line))
    {
        cout << line << endl;
    }
    inFile.close();
    patient.bookAnAppointment();
}
void PatientMenu::viewMedicalHistory(Patient &patient)
{
    system("cls");
    ifstream inFile("./Page/PatientSchedule.txt");
    string line;
    while (getline(inFile, line))
    {
        cout << line << endl;
    }
    inFile.close();

    patient.printMedicalHistory();
}
void PatientMenu::orderDrugHistory(Patient &patient)
{
    system("cls");
    if (patient.Rec().length() == 0)
    {
        printError("You haven't purchased anything!");
        system("pause");
        PatientMenu::menu(patient);
    }
    else
    {
        system("cls");
        patient.printALLPatientReceipts();
        cout << spaceLine << "1. View receipt details by ID\n";
        cout << spaceLine << "2. Back\n";
        int key = getKey(2);
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
            system("pause");
            orderDrugHistory(patient);
        }
        break;

        case 2:
            PatientMenu::menu(patient);
            break;
        }
    }
}
