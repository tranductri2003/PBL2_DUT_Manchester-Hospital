#pragma once
#include <iostream>
#include "User.h"
#include "Patient.h"
#include "Drug.h"
#include "../Structure/LinkedList.cpp"

using namespace std;

class Doctor : public User
{
public:
    // Constructor
    Doctor();
    Doctor(int, string, string, string);

    // Destructor
    ~Doctor();

    // Method
    // User getUserLoginInfo(string);
    // LinkedList<User> getAllUserLoginInfo();

    // Manage Patient
    void searchByPatientID();
    void searchByPatientName();
    void printAllPatient();
    void updatePatientById(int);
    void deletePatientById(int);

    // Manage Drug
    void addNewDrug();
    void updateDrugById(int);
    void deleteDrugById(int);

    // Manage Appointment
    void printAllAppointment();
    void printByMonthAppointment();
};
