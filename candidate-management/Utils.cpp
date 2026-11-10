#include "Utils.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cctype>
 
namespace {
 
std::string trim(const std::string &s) {
    const char *ws = " \t\r\n";
    std::size_t start = s.find_first_not_of(ws);
    if (start == std::string::npos) return "";
    std::size_t end = s.find_last_not_of(ws);
    return s.substr(start, end - start + 1);
}
 
std::string toLower(std::string s) {
    for (std::size_t i = 0; i < s.size(); i++)
        s[i] = (char)std::tolower((unsigned char)s[i]);
    return s;
}
 
void stripBOM(std::string &s) {
    if (s.size() >= 3 && (unsigned char)s[0] == 0xEF &&
        (unsigned char)s[1] == 0xBB && (unsigned char)s[2] == 0xBF)
        s.erase(0, 3);
}
 
std::vector<std::string> parseCsvLine(const std::string &line) {
    std::vector<std::string> fields;
    std::string cur;
    bool inQuotes = false;
 
    for (std::size_t i = 0; i < line.size(); i++) {
        char ch = line[i];
        if (inQuotes) {
            if (ch == '"') {
                if (i + 1 < line.size() && line[i + 1] == '"') {
                    cur += '"';
                    i++;
                } else {
                    inQuotes = false;
                }
            } else {
                cur += ch;
            }
        } else {
            if (ch == '"') inQuotes = true;
            else if (ch == ',') { fields.push_back(cur); cur.clear(); }
            else cur += ch;
        }
    }
    fields.push_back(cur);
    return fields;
}
 
std::string quoteField(const std::string &s) {
    if (s.find_first_of(",\"\r\n") == std::string::npos) return s;
    std::string out = "\"";
    for (std::size_t i = 0; i < s.size(); i++) {
        if (s[i] == '"') out += "\"\"";
        else out += s[i];
    }
    out += "\"";
    return out;
}
 
bool isHeaderLine(const std::string &line) {
    std::vector<std::string> f = parseCsvLine(line);
    return !f.empty() && toLower(trim(f[0])) == "sbd";
}
 
}
 
bool Utils::loadFromFile(const std::string &filename, LinkedList &list, HashTable &table) {
    std::ifstream inFile(filename);
    std::string line;
    int loadedCount = 0;
    int validRows = 0;
    int duplicateCount = 0;
    int invalidCount = 0;
    bool firstLine = true;
 
    if (!inFile.is_open()) {
        std::cout << "[!] Khong the mo file du lieu: " << filename << "\n";
        return false;
    }
 
    while (std::getline(inFile, line)) {
        if (firstLine) {
            stripBOM(line);
            firstLine = false;
            if (isHeaderLine(line)) continue;
        }
 
        if (trim(line).empty()) continue;
 
        std::vector<std::string> f = parseCsvLine(line);
 
        if (f.size() < 5) {
            invalidCount++;
            continue;
        }
 
        std::string sbd      = trim(f[0]);
        std::string hoTen    = trim(f[1]);
        std::string gioiTinh = trim(f[2]);
        std::string ngaySinh = trim(f[3]);
        std::string queQuan  = trim(f[4]);
 
        for (std::size_t i = 5; i < f.size(); i++)
            queQuan += ", " + trim(f[i]);
 
        if (sbd.empty()) {
            invalidCount++;
            continue;
        }
 
        validRows++;
 
        if (list.find(sbd) != nullptr) {
            std::cout << "[!] Bo qua SBD trung: " << sbd << "\n";
            duplicateCount++;
            continue;
        }
 
        Candidate c(sbd, hoTen, gioiTinh, ngaySinh, queQuan);
 
        list.insertTail(c);
        table.insert(c);
        loadedCount++;
    }
 
    inFile.close();
 
    if (validRows == 0) {
        std::cout << "[!] File " << filename << " khong co ban ghi hop le nao.\n";
        return false;
    }
 
    std::cout << "[+] Da doc thanh cong " << loadedCount << " thi sinh tu file " << filename << "\n";
    if (duplicateCount > 0)
        std::cout << "    (Bo qua " << duplicateCount << " dong trung SBD)\n";
    if (invalidCount > 0)
        std::cout << "    (Bo qua " << invalidCount << " dong sai dinh dang)\n";
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
        outFile << quoteField(p->data.getSBD()) << ","
                << quoteField(p->data.getHoTen()) << ","
                << quoteField(p->data.getGioiTinh()) << ","
                << quoteField(p->data.getNgaySinh()) << ","
                << quoteField(p->data.getQueQuan()) << "\n";
        p = p->next;
    }
 
    outFile.close();
    std::cout << "[+] Da luu toan bo " << list.getCount() << " thi sinh ra file " << filename << " thanh cong!\n";
    return true;
}
