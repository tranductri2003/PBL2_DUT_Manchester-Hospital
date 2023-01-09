#pragma once
#include <iostream>
using namespace std;
#include "../Business/Patient.h"
#include "../Business/Doctor.h"

class Home
{
public:
    static void printTask();
    static void login();
    static void signUp();
    static void menu();
};

class PatientMenu
{
public:
    static void printTask();                          // In ra console các chức năng
    static void searchDrug(Patient &);                // Tìm kiếm thông tin thuốc
    static void purchaseDrug(Patient &);              // Mua bán thuốc
    static void orderDrugHistory(Patient &);          // Lịch sử mua bán thuốc
    static void bookAppointment(Patient &);           // Đặt lịch hẹn
    static void viewMedicalHistory(Patient &); // Xem lịch sử khám
    static void menu(Patient &);                      // Thực hiện các chức năng menu, switchcase
    static void login();
    static void signUp();
    static void main();
};

class DoctorMenu
{
public:
    static void printTask();                     // In ra console các chức năng
    static void searchDrug(Doctor &);            // Tìm kiếm thông tin thuốc
    static void drugManagement(Doctor &);        // Xem, thêm, cập nhật, xóa,...
    static void searchPatient(Doctor &);         // Tìm theo tên, ID
    static void patientManagement(Doctor &);     // Thêm, xóa, cập nhật, tìm kiếm
    static void appointmentManagement(Doctor &); // Xem lịch tổng quát, xem ngày chi tiết, thống kê doanh thu trong tháng
    static void saleDrugManagement(Doctor &);    // Lịch sử mua bán thuốc
    static void menu(Doctor &);                  // Thực hiện các chức năng menu, switchcase
    static void login();
    static void main();
};