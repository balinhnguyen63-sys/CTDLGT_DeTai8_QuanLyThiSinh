
#include "Utils.h"
#include <iostream>
#include <fstream>
#include <sstream>
 
namespace {
std::string trim(const std::string &s) {
    const char *ws = " \t\r\n";
    std::size_t start = s.find_first_not_of(ws);
    if (start == std::string::npos) return "";
    std::size_t end = s.find_last_not_of(ws);
    return s.substr(start, end - start + 1);
}
}
 
bool Utils::loadFromFile(const std::string &filename, LinkedList &list, HashTable &table) {
    std::ifstream inFile(filename);
    std::string line;
    std::string sbd, hoTen, gioiTinh, ngaySinh, queQuan;
    int loadedCount = 0;
 
    if (!inFile.is_open()) {
        std::cout << "[!] Khong the mo file du lieu: " << filename << "\n";
        return false;
    }
 
    std::getline(inFile, line);
 
    while (std::getline(inFile, line)) {
        if (trim(line).empty()) continue;
 
        std::stringstream ss(line);
 
        sbd.clear(); hoTen.clear(); gioiTinh.clear(); ngaySinh.clear(); queQuan.clear();
 
        std::getline(ss, sbd, ',');
        std::getline(ss, hoTen, ',');
        std::getline(ss, gioiTinh, ',');
        std::getline(ss, ngaySinh, ',');
        std::getline(ss, queQuan, ',');
 
        sbd = trim(sbd);
        hoTen = trim(hoTen);
        gioiTinh = trim(gioiTinh);
        ngaySinh = trim(ngaySinh);
        queQuan = trim(queQuan);
 
        if (sbd.empty()) continue;
 
        Candidate c(sbd, hoTen, gioiTinh, ngaySinh, queQuan);
 
        list.insertTail(c);
        table.insert(c);
        loadedCount++;
    }
 
    inFile.close();
    std::cout << "[+] Da doc thanh cong " << loadedCount << " thi sinh tu file " << filename << "\n";
    return true;
}
 
bool Utils::saveToFile(const std::string &filename, const LinkedList &list) {
    std::ofstream outFile(filename);
    Node* p = list.getHead();
 
    if (!outFile.is_open()) {
        std::cout << "[!] Khong the tao hoac mo file de ghi: " << filename << "\n";
        return false;
    }
 
    outFile << "SBD,HoTen,GioiTinh,NgaySinh,QueQuan\n";
 
    while (p != nullptr) {
        outFile << p->data.getSBD() << ","
                << p->data.getHoTen() << ","
                << p->data.getGioiTinh() << ","
                << p->data.getNgaySinh() << ","
                << p->data.getQueQuan() << "\n";
        p = p->next;
    }
 
    outFile.close();
    std::cout << "[+] Da luu toan bo " << list.getCount() << " thi sinh ra file " << filename << " thanh cong!\n";
    return true;
}
