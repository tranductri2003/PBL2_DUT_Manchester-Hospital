#pragma once
#include "User.h"
#include <iostream>
#include <string>
#include "../Management/DrugManagement.cpp"
using namespace std;

User::User()
{
    this->_ID = 0;
    this->_Name = "";
    this->_Email = "";
    this->_Password = "";
}

User::User(int id, string name)
{
    this->_ID = id;
    this->_Name = name;
}

User::User(int id, string email, string password)
{
    this->_ID = id;
    this->_Email = email;
    this->_Password = password;
}

User::User(int id, string name, string email, string password)
{
    this->_ID = id;
    this->_Name = name;
    this->_Email = email;
    this->_Password = password;
}

User::~User()
{
}

int User::getID()
{
    return this->_ID;
}

void User::setID(int id)
{
    this->_ID = id;
}

string User::getName()
{
    return this->_Name;
}

void User::setName(string name)
{
    this->_Name = name;
}

string User::getEmail()
{
    return this->_Email;
}

void User::setEmail(string email)
{
    this->_Email = email;
}

string User::getPassword()
{
    return this->_Password;
}

void User::setPassword(string password)
{
    this->_Password = password;
}

void User::searchByDrugID()
{
    searchByDrugsID();
}

void User::searchByDrugName()
{
    searchByDrugsName();
}

void User::printAllDrug()
{
    printAllDrugs();
}
