#pragma once
#include "Cart.h"
#include "../Management/DrugManagement.cpp"
#include "../Library/Table.cpp"
#include "../Library/Console.cpp"

Cart::Cart()
{
    this->_Total = 0;
}

Cart::~Cart()
{
}

LinkedList<int> Cart::DrugID()
{
    return this->_DrugID;
}

LinkedList<int> Cart::DrugQuantity()
{
    return this->_DrugQuantity;
}

int Cart::Total()
{
    int total = 0;
    for (int i = 0; i < this->_DrugID.length(); i++)
    {
        Drug Drug = getDrugFromDatabase(this->_DrugID.get(i));
        total += Drug.getPrice() * this->_DrugQuantity.get(i);
    }
    return total;
}

void Cart::addDrugtoCart(int id, int quantity)
{
    this->_DrugID.addLast(id);
    this->_DrugQuantity.addLast(quantity);
}

void Cart::emptyCart()
{
    this->_DrugID = LinkedList<int>();
    this->_DrugQuantity = LinkedList<int>();
    this->_Total = 0;
}
