#include "Patient.h"
#include "Appointment.cpp"
#include "Drug.cpp"
#include "../Management/DrugManagement.cpp"
#include "../Management/ReceiptManagement.cpp"
#include "../Management/AppointmentManagement.cpp"
#include <iostream>
using namespace std;

Patient::Patient() : User(0, "", "", "")
{
    this->_Rec = LinkedList<string>();
    this->_Cart = Cart();
}

Patient::Patient(int id, string name, string email, string password, LinkedList<string> recs) : User(id, name, email, password)
{
    this->_Rec = recs;
    this->_Cart = Cart();
}

Patient::~Patient()
{
}

Cart &Patient::getCart()
{
    return this->_Cart;
}

LinkedList<string> Patient::Rec()
{
    return this->_Rec;
}

void Patient::setRec(LinkedList<string> recs)
{
    this->_Rec = recs;
}

void Patient::purchase()
{
    string recID = "REC#" + to_string(this->_Rec.length() + 1);
    this->_Rec.addLast(recID);

    string fileName = to_string(this->getID()) + "_" + recID + ".txt";
    string filePath = "./Database/ReceiptDB/" + fileName;
    ofstream outFilePatient("./Database/UserDB/PatientDB/PATIENT_" + to_string(this->getID()) + ".txt", ios::app);
    outFilePatient << recID << endl;
    outFilePatient.close();

    ofstream outFile(filePath);

    string date = currentDateTime();
    outFile << date << endl;
    outFile << _Cart.Total() << endl;

    for (int i = 0; i < _Cart.DrugID().length(); i++)
    {
        outFile << _Cart.DrugQuantity().get(i) << " ";
        outFile << _Cart.DrugID().get(i) << endl;
    }

    outFile.close();
    system("cls");
    printReceipt(this->getID(), recID);

    _Cart.emptyCart();
}

void Patient::searchByReceiptID(int id)
{
    getReceiptFromDatabase(this->getID(), id);
}

void Patient::printALLPatientReceipts()
{
    getAllPatientReceipts(*this);
}

void Patient::addNewReceipt()
{
    addReceiptToDatabase(this->getID(), this->_Cart, this->_Rec);
}

void Patient::deleteReceiptById(string id)
{
    deleteReceiptFromDatabase(this->getID(), id);
}

void Patient ::bookAnAppointment()
{
    int year, month;
    string choose;
    do
    {
        system("cls");
        ifstream inFile("./Page/PatientSchedule.txt");
        string line;
        while (getline(inFile, line))
        {
            cout << line << endl;
        }
        inFile.close();

        year = getIntInput("Which year do you want to schedule a medical appointment? ");
        month = getMonthInput("Which month do you want to schedule a medical appointment? ");
        int date;
        Calendar calendar(month, year);
        calendar.showCalendar(month, year);
        cout << endl;
        date = getDateInput("Which date do you want to schedule a medical appointment? ", month, year);
        if (isFreeDate(date, month, year) == -1)
        {
            addNewDayToDataBase(date, month, year, getID());
            printSuccess("Succesfully book an appointment!");

            ofstream outFilePatient("./Database/UserDB/PatientDB/PATIENT_" + to_string(this->getID()) + ".txt", ios::app);
            string name = to_string(date) + "/" + to_string(month) + "/" + to_string(year);
            outFilePatient << name << endl;
            outFilePatient.close();
        }
        else
        {
            printError("Invalid date!");
        }
        choose = getYesNoInput("Continue?");
    } while (choose == "y" || choose == "Y");
}

void Patient::printMedicalHistory()
{
    system("cls");
    ifstream inFile("./Page/PatientSchedule.txt");
    string line;
    while (getline(inFile, line))
    {
        cout << line << endl;
    }
    inFile.close();

    TextTable table;

    table.add("Num");
    table.add("Date");
    table.endOfRow();
    LinkedList<string> appointments = getAllAppointmentOfID(this->getID());

    for (int i = 0; i < appointments.length(); i++)
    {
        string ngay = appointments.get(i);

        table.add(to_string(i + 1));
        table.add(ngay);
        table.endOfRow();
    }

    cout << table << endl;
}