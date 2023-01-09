#pragma once
#include "../Business/Drug.h"
#include "../Business/Drug.cpp"
#include "../Structure/LinkedList.cpp"
#include "../Library/Console.cpp"
#include "../Library/Table.cpp"
#include <fstream>
#include <string>
#include <iostream>
#include <cstring>
using namespace std;

bool isValidDrugId(int drugID)
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

void addDrugToDatabase(Drug &drug)
{
    // generate file path
    // start from main.cpp
    string fileName = to_string(drug.getID()) + ".txt";
    string filePath = "./Database/DrugDB/" + fileName;

    // create file in database
    ofstream outFile(filePath);
    // outFile << computer.ID() << endl;
    outFile << drug.getID() << endl;
    outFile << drug.getName() << endl;
    outFile << drug.getDisease() << endl;
    outFile << drug.getQuantity() << endl;
    outFile << drug.getPrice() << endl;
    outFile << drug.getSale() << endl;
    outFile << drug.getDescription() << endl;

    if (!isValidDrugId(drug.getID()))
    {
        ofstream outFileDrugId("./Database/DrugDB/drug_ID.txt", ios::app);
        outFileDrugId << drug.getID() << endl;
        outFileDrugId.close();
    }

    // close ofstream
    outFile.close();
}

void addNewDrugToDataBase()
{
    cout << spaceLineChoice + "New drug:\n";
    string name = getStringInput("Name");
    string disease = getStringInput("Desease");
    int quantity = getIntInput("Quantity");
    int price = getIntInput("Price");
    int sale = getIntInput("Sale");
    string description = getStringInput("Description");

    // Create new drug object
    Drug drug = Drug(getLastDrugId(), name, disease, quantity, price, sale, description);

    // Save to database
    addDrugToDatabase(drug);

    // Update new drug id range
    updateLine("./Database/lastID.txt", 0, getLastDrugId());

    // Generate sale and write to sale file
    ofstream outFilesale("./Database/saleSummary.txt", ios::app);
    outFilesale << drug.getID() << " " << drug.getSale() << endl;
    outFilesale.close();
}

Drug getDrugFromDatabase(int drugID)
{
    string fileName = to_string(drugID) + ".txt";
    string filePath = "./Database/DrugDB/" + fileName;

    ifstream inFile(filePath);
    string line;

    string name;
    string disease;
    int quantity;
    int price;
    int sale;
    string description;

    getline(inFile, line);
    drugID = stoi(line);

    getline(inFile, line);
    name = line;

    getline(inFile, line);
    disease = line;

    getline(inFile, line);
    quantity = stoi(line);

    getline(inFile, line);
    price = stoi(line);

    getline(inFile, line);
    sale = stoi(line);

    getline(inFile, line);
    description = line;

    return Drug(drugID, name, disease, quantity, price, sale, description);
}
void deleteDrugFromDatabase(int drugID)
{
    string filePath = "./Database/DrugDB/";
    string fileName = to_string(drugID) + ".txt";

    // char char_filePath[(filePath + fileName).length() + 1];
    // strcpy(char_filePath, (filePath + fileName).c_str());

    int status = remove((filePath + fileName).c_str());

    if (status == 0)
    {
        printSuccess("Succesfully delete this Drug!");
        eraseFileLine(filePath + "drug_ID.txt", to_string(drugID));
        eraseFileLine("./Database/saleSummary.txt", drugID);
    }
    else
    {
        printError("Delete failed!");
    }
}

void updateDrugInDatabase(int drugID)
{
    Drug drug = getDrugFromDatabase(drugID);
    string filePath = "./Database/DrugDB/";
    string fileName = to_string(drugID) + ".txt";

    char char_filePath[(filePath + fileName).length() + 1];
    strcpy(char_filePath, (filePath + fileName).c_str());

    int status = remove(char_filePath);

    string name = updateComponent("Name", drug.getName());
    string disease = updateComponent("Disease", drug.getDisease());
    int quantity = updateIntComponent("Quantity", drug.getQuantity());
    int price = updateIntComponent("Price", drug.getPrice());
    int sale = updateIntComponent("Sale", drug.getSale());
    string description = updateComponent("Description", drug.getDescription());

    drug.setID(drugID);
    drug.setName(name);
    drug.setDisease(disease);
    drug.setQuantity(quantity);
    drug.setPrice(price);
    drug.setSale(sale);
    drug.setDescription(description);

    addDrugToDatabase(drug);
    printSuccess("Succesfully update!");
}

LinkedList<Drug> getAllDrug()
{
    LinkedList<Drug> drugs;

    ifstream inFile("./Database/DrugDB/drug_ID.txt");
    if (!inFile.is_open())
    {
        printError("Error open file drug_ID.txt");
    }
    string x;

    // Create a new drug object
    // Get each drug from database then add it to the list of drugs
    while (getline(inFile, x))
    {
        Drug drug = getDrugFromDatabase(stoi(x));
        drugs.addLast(drug);
    }

    inFile.close();
    return drugs;
}

void printDrug(Drug drug)
{
    TextTable table;

    table.add("ID");
    table.add("Name");
    table.add("Disease");
    table.add("Quantity");
    table.add("Price");
    table.add("Description");
    table.endOfRow();

    table.add(to_string(drug.getID()));
    table.add(drug.getName());
    table.add(drug.getDisease());
    table.add(to_string(drug.getQuantity()));
    table.add(formatCurrency(drug.getPrice()));
    table.add(drug.getDescription());
    table.endOfRow();

    cout << table << endl;
}

void printAllDrugs(LinkedList<Drug> drugs = getAllDrug())
{

    TextTable table;

    table.add("ID");
    table.add("Name");
    table.add("Disease");
    table.add("Quantity");
    table.add("Price");
    table.add("Description");
    table.endOfRow();

    for (int i = 0; i < drugs.length(); i++)
    {
        Drug drug = drugs.get(i);
        table.add(to_string(drug.getID()));
        table.add(drug.getName());
        table.add(drug.getDisease());
        table.add(to_string(drug.getQuantity()));
        table.add(formatCurrency(drug.getPrice()));
        table.add(drug.getDescription());
        table.endOfRow();
    }

    cout << table << endl;
}

void searchByDrugsID()
{
    int id = getIntInput("Enter ID");
    if (!isValidDrugId(id))
    {
        printError("Invalid ID, please enter again!");
    }
    else
    {
        Drug drug = getDrugFromDatabase(id);
        printDrug(drug);
    }
}

LinkedList<Drug> searchByDrugCase(string toSearch)
{
    LinkedList<Drug> res;
    LinkedList<Drug> drugs = getAllDrug();

    for (int i = 0; i < drugs.length(); i++)
    {
        if (findCaseInsensitive(drugs.get(i).getName(), toSearch) != string::npos)
        {
            res.addLast(drugs.get(i));
        }
    }
    return res;
}

void searchByDrugsName()
{
    string name = getStringInput("Enter name: ");
    LinkedList<Drug> drugs = searchByDrugCase(name);

    if (drugs.length())
    {
        printSuccess("Succesfully search!");
        printAllDrugs(drugs);
    }
    else
    {
        printError("Invalid Name, please enter again!");
    }
}
void updateDrugQuantityInDatabase(int id, int quantity)
{
    updateLine("./Database/DrugDB/" + to_string(id) + ".txt", 3, quantity);
}
void updateSale(int drugID, int amount)
{
    ifstream inFile("./Database/saleSummary.txt");

    string sale, line;
    int firstIndex;
    while (getline(inFile, line))
    {
        firstIndex = line.find_first_of(" ");
        if (stoi(line.substr(0, firstIndex)) == drugID)
        {
            break;
        }
    }

    inFile.close();

    Drug drug = getDrugFromDatabase(drugID);

    int new_sale = drug.getSale() + amount;
    updateLine("./Database/saleSummary.txt", line, line.substr(0, firstIndex + 1) + to_string(new_sale));
    updateLine("./Database/DrugDB/" + to_string(drugID) + ".txt", 5, new_sale);
}

LinkedList<Drug> getSaleManagement()
{
    ifstream inFile("./Database/saleSummary.txt");
    LinkedList<Drug> drugs;

    string line;
    int firstIndex;
    while (getline(inFile, line))
    {
        firstIndex = line.find_first_of(" ");
        int drugID = stoi(line.substr(0, firstIndex));
        int sale = stoi(line.substr(firstIndex + 1));
        Drug drug = getDrugFromDatabase(drugID);
        drugs.addLast(Drug(drug.getID(), drug.getName(), drug.getDisease(), drug.getQuantity(), drug.getPrice(), drug.getSale(), drug.getDescription()));
    }

    inFile.close();

    return drugs;
}
void printSaleTable(LinkedList<Drug> drugs = getSaleManagement())
{
    TextTable table;

    table.add("ID");
    table.add("Name");
    table.add("Price");
    table.add("Total sale");
    table.endOfRow();

    double total = 0;

    for (int i = 0; i < drugs.length(); i++)
    {
        Drug drug = drugs.get(i);
        table.add(to_string(drug.getID()));
        table.add(drug.getName());
        table.add(formatCurrency(drug.getPrice()));
        table.add(formatCurrency(drug.getSale() * drug.getPrice()));
        table.endOfRow();
        total += drug.getSale() * drug.getPrice();
    }

    table.add("");
    table.add("");
    table.add("Total");
    table.add(formatCurrency(total));
    table.endOfRow();

    cout << table << "\n";
}
