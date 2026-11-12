#include "Utils.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cctype>

using namespace std;

namespace {

string trim(const string &s) {
    const char *ws = " \t\r\n";
    size_t start = s.find_first_not_of(ws);
    if (start == string::npos) return "";
    size_t end = s.find_last_not_of(ws);
    return s.substr(start, end - start + 1);
}

string toLower(string s) {
    for (size_t i = 0; i < s.size(); i++)
        s[i] = (char)tolower((unsigned char)s[i]);
    return s;
}

void stripBOM(string &s) {
    if (s.size() >= 3 && (unsigned char)s[0] == 0xEF &&
        (unsigned char)s[1] == 0xBB && (unsigned char)s[2] == 0xBF)
        s.erase(0, 3);
}

vector<string> parseCsvLine(const string &line) {
    vector<string> fields;
    string cur;
    bool inQuotes = false;

    for (size_t i = 0; i < line.size(); i++) {
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

string quoteField(const string &s) {
    if (s.find_first_of(",\"\r\n") == string::npos) return s;
    string out = "\"";
    for (size_t i = 0; i < s.size(); i++) {
        if (s[i] == '"') out += "\"\"";
        else out += s[i];
    }
    out += "\"";
    return out;
}

bool isHeaderLine(const string &line) {
    vector<string> f = parseCsvLine(line);
    return !f.empty() && toLower(trim(f[0])) == "sbd";
}

}

bool Utils::loadFromFile(const string &filename, LinkedList &list, HashTable &table) {
    ifstream inFile(filename);
    string line;
    int loadedCount = 0;
    int validRows = 0;
    int duplicateCount = 0;
    int invalidCount = 0;
    bool firstLine = true;

    if (!inFile.is_open()) {
        cout << "[!] Khong the mo file du lieu: " << filename << "\n";
        return false;
    }

    while (getline(inFile, line)) {
        if (firstLine) {
            stripBOM(line);
            firstLine = false;
            if (isHeaderLine(line)) continue;
        }

        if (trim(line).empty()) continue;

        vector<string> f = parseCsvLine(line);

        if (f.size() < 5) {
            invalidCount++;
            continue;
        }

        string sbd      = trim(f[0]);
        string hoTen    = trim(f[1]);
        string gioiTinh = trim(f[2]);
        string ngaySinh = trim(f[3]);
        string queQuan  = trim(f[4]);

        for (size_t i = 5; i < f.size(); i++)
            queQuan += ", " + trim(f[i]);

        if (sbd.empty()) {
            invalidCount++;
            continue;
        }

        if (list.find(sbd) != nullptr) {
            cout << "[!] Bo qua SBD trung: " << sbd << "\n";
            duplicateCount++;
            continue;
        }

        validRows++;

        Candidate c(sbd, hoTen, gioiTinh, ngaySinh, queQuan);

        list.insertTail(c);
        table.insert(c);
        loadedCount++;
    }

    inFile.close();

    if (loadedCount == 0 || validRows == 0) {
        cout << "[!] File " << filename << " khong co ban ghi hop le nao.\n";
        return false;
    }

    cout << "[+] Da doc thanh cong " << loadedCount << " thi sinh tu file " << filename << "\n";
    if (duplicateCount > 0)
        cout << "    (Bo qua " << duplicateCount << " dong trung SBD)\n";
    if (invalidCount > 0)
        cout << "    (Bo qua " << invalidCount << " dong sai dinh dang)\n";
    return true;
}

bool Utils::saveToFile(const string &filename, const LinkedList &list) {
    ofstream outFile(filename);
    Node* p = list.getHead();

    if (!outFile.is_open()) {
        cout << "[!] Khong the tao hoac mo file de ghi: " << filename << "\n";
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
    cout << "[+] Da luu toan bo " << list.getCount() << " thi sinh ra file " << filename << " thanh cong!\n";
    return true;
}
