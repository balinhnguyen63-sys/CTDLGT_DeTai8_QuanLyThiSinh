#pragma once
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

// Nguyen Ba Linh: Mo hinh du lieu Thi sinh (Candidate)

class Candidate {
private:
    string sbd;       // Ma du thi / So bao danh (duy nhat)
    string hoTen;     // Ho va ten thi sinh
    string gioiTinh;  // Gioi tinh (Nam / Nu)
    string ngaySinh;  // Ngay sinh (dd/mm/yyyy)
    string queQuan;   // Que quan / Noi sinh

public:
    // Constructors
    Candidate();
    Candidate(const string &sbd, const string &hoTen,
              const string &gioiTinh, const string &ngaySinh,
              const string &queQuan);

    // Getters
    string getSBD() const;
    string getHoTen() const;
    string getGioiTinh() const;
    string getNgaySinh() const;
    string getQueQuan() const;

    // Setters
    void setSBD(const string &sbd);
    void setHoTen(const string &hoTen);
    void setGioiTinh(const string &gioiTinh);
    void setNgaySinh(const string &ngaySinh);
    void setQueQuan(const string &queQuan);

    // Phuong thuc phuc vu Bang bam & Sap xep
    string getFirstName() const;         // Trich xuat Ten (tu cuoi cung trong ho ten)
    char getFirstLetterOfName() const;   // Lay chu cai dau tien cua ten (A-Z) de bam bang tra

    // Hien thi thong tin thi sinh
    void displayRow() const;             // In dang dong trong bang
};
