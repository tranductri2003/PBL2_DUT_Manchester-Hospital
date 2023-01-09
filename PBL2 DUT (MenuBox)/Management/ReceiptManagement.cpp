#pragma once
#include "../Library/Console.cpp"
#include "../Business/Drug.cpp"
#include "./PatientManagement.cpp"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstring>
using namespace std;

string lineReceiptFormat(string key, string info)
{
    string s = key;
    int n = 57 - key.length() - info.length();
    for (int i = 0; i < n; i++)
    {
        s += " ";
    }
    s = s + info;
    s = "|   " + s + "   |";
    return s;
}

string lineReceiptFormat(string qty, string item, string amount)
{
    string s = qty;
    int n = 6 - qty.length();
    for (int i = 0; i < n; i++)
    {
        s += " ";
    }
    s = s + item;
    int m = 57 - s.length() - amount.length();
    for (int i = 0; i < m; i++)
    {
        s += " ";
    }
    s = s + amount;
    s = "|   " + s + "   |";
    return s;
}

void printReceipt(int patientID, string recID)
{
    ifstream inFile("./Page/Receipt.txt");
    ifstream inFileRec("./Database/ReceiptDB/" + to_string(patientID) + "_" + recID + ".txt");

    string line;
    string lineRec;
    int firstIndex;

    for (int i = 0; i < 9; i++)
    {
        getline(inFile, line);
        cout << line << endl;
    }

    cout << lineReceiptFormat("No.", recID) << endl;

    getline(inFileRec, lineRec);
    cout << lineReceiptFormat("Terminal.", lineRec) << endl;
    getline(inFileRec, lineRec);
    int total = stoi(lineRec);

    for (int i = 0; i < 3; i++)
    {
        getline(inFile, line);
        cout << line << endl;
    }

    int quantity, drugID, amount;
    while (getline(inFileRec, lineRec))
    {
        firstIndex = lineRec.find_first_of(" ");
        quantity = stoi(lineRec.substr(0, firstIndex));
        drugID = stoi(lineRec.substr(firstIndex + 1));
        Drug drug = getDrugFromDatabase(drugID);
        amount = quantity * drug.getPrice();
        cout << lineReceiptFormat(to_string(quantity), drug.getName(), formatCurrency(amount)) << endl;
    }

    for (int i = 0; i < 1; i++)
    {
        getline(inFile, line);
        cout << line << endl;
    }

    cout << lineReceiptFormat("TOTAL AMOUNT", formatCurrency(total)) << endl;

    while (getline(inFile, line))
    {
        cout << line << endl;
    }

    inFileRec.close();
    inFile.close();
}

bool isValidReceiptID(string recID, Patient &patient)
{
    LinkedList<string> recs = patient.Rec();

    for (int i = 0; i < recs.length(); i++)
    {
        if (recs.get(i) == recID)
        {
            return true;
        }
    }
    return false;
}

void getReceiptFromDatabase(int patientID, int recID)
{
    ifstream inFile("./Page/Receipt.txt");
    ifstream inFileRec("./Database/ReceiptDB/" + to_string(patientID) + "_" + to_string(recID) + ".txt");

    string line;
    string lineRec;
    int firstIndex;

    for (int i = 0; i < 9; i++)
    {
        getline(inFile, line);
        cout << line << endl;
    }

    cout << lineReceiptFormat("No.", to_string(recID)) << endl;

    getline(inFileRec, lineRec);
    cout << lineReceiptFormat("Terminal.", lineRec) << endl;
    getline(inFileRec, lineRec);
    int total = stoi(lineRec);

    for (int i = 0; i < 3; i++)
    {
        getline(inFile, line);
        cout << line << endl;
    }

    int quantity, drugID, amount;
    while (getline(inFileRec, lineRec))
    {
        firstIndex = lineRec.find_first_of(" ");
        quantity = stoi(lineRec.substr(0, firstIndex));
        drugID = stoi(lineRec.substr(firstIndex + 1));
        Drug drug = getDrugFromDatabase(drugID);
        amount = quantity * drug.getPrice();
        cout << lineReceiptFormat(to_string(quantity), drug.getName(), formatCurrency(amount)) << endl;
    }

    for (int i = 0; i < 1; i++)
    {
        getline(inFile, line);
        cout << line << endl;
    }

    cout << lineReceiptFormat("TOTAL AMOUNT", formatCurrency(total)) << endl;

    while (getline(inFile, line))
    {
        cout << line << endl;
    }

    inFileRec.close();
    inFile.close();
}

void getAllPatientReceipts(Patient &patient)
{
    TextTable table;
    int n = patient.Rec().length();
    table.add("ID");
    table.add("Name");
    table.add("Receipt ID");
    table.add("Total");
    table.add("Datetime");
    table.endOfRow();

    int total = 0;
    for (int i = 0; i < n; i++)
    {
        table.add(to_string(patient.getID()));
        table.add(patient.getName());
        table.add(patient.Rec().get(i));
        table.add(formatCurrency(getReceiptTotal(patient.getID(), patient.Rec().get(i))));
        table.add(getReceiptDateTime(patient.getID(), patient.Rec().get(i)));
        table.endOfRow();
        total += getReceiptTotal(patient.getID(), patient.Rec().get(i));
    }
    table.add("");
    table.add("");
    table.add("Total amount");
    table.add(formatCurrency(total));
    table.add("");
    table.endOfRow();

    cout << table << endl;
}

void addReceiptToDatabase(int patientID, Cart _Cart, LinkedList<string> Rec)
{
    string recID = "REC#" + to_string(Rec.length() + 1);
    Rec.addLast(recID);

    string fileName = to_string(patientID) + "_" + recID + ".txt";
    string filePath = "./Database/ReceiptDB/" + fileName;
    ofstream outFilepatient("./Database/UserDB/PatientDB/patient_" + to_string(patientID) + ".txt", ios::app);
    outFilepatient << recID << endl;
    outFilepatient.close();

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
    printReceipt(patientID, recID);

    // _Cart.emptyCart();
}

void deleteReceiptFromDatabase(int patientID, string recID)
{
    string fileName = to_string(patientID) + "_" + recID + ".txt";
    string filePath = "./Database/ReceiptDB/" + fileName;

    char char_filePath[(filePath + fileName).length() + 1];
    strcpy(char_filePath, (filePath + fileName).c_str());

    int status = remove(char_filePath);

    if (status == 0)
    {
        printSuccess("Succesfully delete this Receipt!");
    }
    else
    {
        printError("Delete failed!");
    }
}
