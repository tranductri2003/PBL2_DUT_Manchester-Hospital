#pragma once
#include "Drug.h"
#include <fstream>
#include <iostream>
using namespace std;

Drug::Drug()
{
    this->_ID = 0;
    this->_Name = " ";
    this->_Disease = " ";
    this->_Quantity = 0;
    this->_Price = 0;
    this->_Sale = 0;
    this->_Description = " ";
}

Drug::Drug(int id, string name, string disease, int quantity, int price , int sale, string description)
{
    this->_ID = id;
    this->_Name = name;
    this->_Disease = disease;
    this->_Quantity = quantity;
    this->_Price = price;
    this->_Sale = sale;
    this->_Description = description;
}

Drug::Drug(const Drug& drug)
{
    this->_ID = drug._ID;
    this->_Name = drug._Name;
    this->_Disease = drug._Disease;
    this->_Quantity = drug._Quantity;
    this->_Price = drug._Price;
    this->_Sale = drug._Sale;
    this->_Description = drug._Description;
}

Drug& Drug::operator = (const Drug& drug)
{
    this->_ID = drug._ID;
    this->_Name = drug._Name;
    this->_Disease = drug._Disease;
    this->_Quantity = drug._Quantity;
    this->_Price = drug._Price;
    this->_Sale = drug._Sale;
    this->_Description = drug._Description;
    return *this;
}

Drug::~Drug()
{

}

int Drug::getID()
{
    return this->_ID;
}

void Drug::setID(int id)
{
    this->_ID = id;
}

string Drug::getName()
{
    return this->_Name;
}

void Drug::setName(string name)
{
    this->_Name = name;
}

string Drug::getDisease()
{
    return this->_Disease;
}

void Drug::setDisease(string disease)
{
    this->_Disease = disease;
}

int Drug::getQuantity()
{
    return this->_Quantity;
}

void Drug::setQuantity(int quantity)
{
    this->_Quantity = quantity;
}

int Drug::getPrice()
{
    return this->_Price;
}

void Drug::setPrice(int price)
{
    this->_Price = price;
}

int Drug::getSale()
{
    return this->_Sale;
}

void Drug::setSale(int sale)
{
    this->_Sale = sale;
}

string Drug::getDescription()
{
    return this->_Description;
}

void Drug::setDescription(string description)
{
    this->_Description = description;
}