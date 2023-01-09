#pragma once
#include <iostream>
#include <string>
using namespace std;
class User
{
private:
    int _ID;
    string _Name;
    string _Email;
    string _Password;

public:
    // Constructor
    User();
    User(int, string);
    User(int, string, string);
    User(int, string, string, string);

    // Destructor
    ~User();

    // Get, Set User _Id
    int getID();
    void setID(int);

    // Get, Set User _Name
    string getName();
    void setName(string);

    // Get, Set User _Email
    string getEmail();
    void setEmail(string);

    // Get, Set User _Password
    string getPassword();
    void setPassword(string);

    void searchByDrugID();
    void searchByDrugName();
    void printAllDrug();
};