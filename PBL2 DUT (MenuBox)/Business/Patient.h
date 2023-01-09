#pragma once
#include "User.cpp"
#include "Cart.cpp"
#include "../Structure/LinkedList.cpp"
class Patient : public User
{
private:
    Cart _Cart;
    LinkedList<string> _Rec;
    // string _Problem;

public:
    // Constructor
    Patient();
    Patient(int, string, string, string, LinkedList<string> = LinkedList<string>());

    // Destructor
    ~Patient();

    // // Get, Set Patient _Problem
    // string getProblem();
    // void setProblem(string);

    // Info
    void displayInfo();
    void updateInfo();

    // Get patient item in Cart
    Cart &getCart();

    // Get list of receipt ID
    LinkedList<string> Rec();

    // Set list of receipt ID
    void setRec(LinkedList<string>);

    void newPatient();

    void purchase();
    void searchByReceiptID(int);
    // void searchByCompName(string);
    void printALLPatientReceipts();
    // void printReceipt(int);
    void addNewReceipt();
    void deleteReceiptById(string);

    void bookAnAppointment();
    void printMedicalHistory();
};
