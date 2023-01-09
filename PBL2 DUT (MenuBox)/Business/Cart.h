#pragma once
#include "../Structure/LinkedList.cpp"
#include "./Drug.h"
#include "./Drug.cpp"

class Cart
{
private:
    LinkedList<int> _DrugID;
    LinkedList<int> _DrugQuantity;
    int _Total;

public:
    // Constructor
    Cart();

    // Destructor
    ~Cart();

    // Get list of drug ID
    LinkedList<int> DrugID();

    // Get list of drug Quantity
    LinkedList<int> DrugQuantity();

    // Add drug to cart
    void addDrugtoCart(int, int = 1);

    // Set cart to Null for next purchase
    void emptyCart();

    // Set Total //Calculate total amount (money) in cart
    int Total();
};