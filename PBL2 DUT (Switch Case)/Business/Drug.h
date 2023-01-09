#pragma once
#include <iostream>
#include <string>
using namespace std;

class Drug
{
private:
    int _ID;
    string _Name;
    string _Disease;
    int _Quantity;
    int _Price;
    int _Sale;
    string _Description;
public:
    // Constructor
    Drug();
    Drug(int, string, string, int, int, int, string);
    Drug(const Drug&);

    // Overloading the assignment operator
    Drug& operator = (const Drug&);

    // Destructor
    ~Drug();

    // Get, Set Drug_ID
    int getID();
    void setID(int);

    // Get, Set Drug_Name
    string getName();
    void setName(string);

    // Get, Set Drug_Disease
    string getDisease();
    void setDisease(string);

    // Get, Set Drug_Quantity
    int getQuantity();
    void setQuantity(int);

    // Get, Set Drug_Price
    int getPrice();
    void setPrice(int);

    // Get, Set Drug_Sale
    int getSale();
    void setSale(int);

    // Get, Set Drug_Description
    string getDescription();
    void setDescription(string);
};