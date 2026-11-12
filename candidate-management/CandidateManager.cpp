#include "CandidateManager.h"
#include "Sorter.h"
#include "RoomAllocator.h"
#include "Utils.h"
#include <cctype>
#include <iostream>
#include <limits>
#include <string>

using namespace std;

namespace {
string trim(const string &s) {
    const char *ws = " \t\r\n";
    size_t start = s.find_first_not_of(ws);
    if (start == string::npos) return "";
    size_t end = s.find_last_not_of(ws);
    return s.substr(start, end - start + 1);
}

string normalizeGender(const string &raw) {
    string ascii;
    for (unsigned char c : raw) {
        if (c < 0x80) {
            ascii += (char)tolower(c);
        }
    }
    ascii = trim(ascii);
    if (ascii == "nam") return "Nam";
    if (ascii == "nu") return "Nu";
    return "";
}

bool isValidDate(const string &s) {
    if (s.size() != 10 || s[2] != '/' || s[5] != '/') return false;
    for (size_t i = 0; i < s.size(); ++i) {
        if (i == 2 || i == 5) continue;
        if (!isdigit((unsigned char)s[i])) return false;
    }

    int day = stoi(s.substr(0, 2));
    int month = stoi(s.substr(3, 2));
    int year = stoi(s.substr(6, 4));
    if (year < 1900 || year > 2100 || month < 1 || month > 12) return false;

    static const int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int maxDay = daysInMonth[month - 1];
    bool leapYear = (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
    if (month == 2 && leapYear) maxDay = 29;

    return day >= 1 && day <= maxDay;
}
} 

// Nguyen Ba Linh: Khoi tao he thong quan ly thi sinh

CandidateManager::CandidateManager() {
    if (!Utils::loadFromFile("input.txt", candidateList, hashTable)) {
        initSampleData();
    }
}

CandidateManager::~CandidateManager() {
    candidateList.clear();
    hashTable.clear();
}

void CandidateManager::initSampleData() {
    Candidate samples[] = {
        Candidate("TS001", "Nguyen Ba Linh", "Nam", "15/08/2004", "TP. Ho Chi Minh"),
        Candidate("TS002", "Hoang The Anh", "Nam", "20/01/2004", "Ha Noi"),
        Candidate("TS003", "Tran Nhat Anh", "Nam", "10/05/2004", "Da Nang"),
        Candidate("TS004", "Nguyen Huu Cuong", "Nam", "12/12/2004", "Nghe An"),
        Candidate("TS005", "Pham Khanh Hung", "Nam", "03/04/2004", "Dong Nai"),
        Candidate("TS006", "Dao Quang Thang", "Nam", "18/09/2004", "Binh Duong"),
        Candidate("TS007", "Le Thi Mai", "Nu", "22/11/2004", "Can Tho"),
        Candidate("TS008", "Tran Van Binh", "Nam", "05/02/2004", "Hai Phong"),
        Candidate("TS009", "Vo Hoang Giang", "Nam", "14/07/2004", "Quang Nam"),
        Candidate("TS010", "Nguyen Thuy Dung", "Nu", "09/09/2004", "Hue")
    };

    for (const auto &c : samples) {
        candidateList.insertTail(c);
        hashTable.insert(c);
    }
}

// Hoang The Anh: Them thi sinh moi va cap nhat thong tin thi sinh

bool CandidateManager::addCandidate() {
    string sbd, hoTen, gioiTinh, ngaySinh, queQuan;

    cout << "\n--- THEM THI SINH MOI ---\n";
    cout << "Nhap Ma Du Thi / SBD (vi du: TS099): ";
    cin >> sbd;
    sbd = trim(sbd);

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (sbd.empty()) {
        cout << "[!] Ma du thi khong duoc de trong!\n";
        return false;
    }

    // Kiem tra trung SBD ngay sau khi nhap
    if (candidateList.find(sbd) != nullptr ||
        hashTable.searchBySBD(sbd) != nullptr) {
        cout << "[!] Loi: Ma du thi " << sbd
             << " da ton tai trong he thong!\n";
        return false;
    }

    cout << "Nhap Ho va Ten: ";
    getline(cin, hoTen);
    hoTen = trim(hoTen);
    if (hoTen.empty()) {
        cout << "[!] Ho va Ten khong duoc de trong!\n";
        return false;
    }

    cout << "Nhap Gioi Tinh (Nam/Nu): ";
    getline(cin, gioiTinh);
    string gioiTinhChuan = normalizeGender(gioiTinh);
    if (gioiTinhChuan.empty()) {
        cout << "[!] Gioi tinh khong hop le (chi nhan Nam hoac Nu)!\n";
        return false;
    }

    cout << "Nhap Ngay Sinh (dd/mm/yyyy): ";
    getline(cin, ngaySinh);
    ngaySinh = trim(ngaySinh);
    if (!isValidDate(ngaySinh)) {
        cout << "[!] Ngay sinh khong hop le (dinh dang dd/mm/yyyy)!\n";
        return false;
    }

    cout << "Nhap Que Quan: ";
    getline(cin, queQuan);
    queQuan = trim(queQuan);

    Candidate newCandidate(sbd, hoTen, gioiTinhChuan, ngaySinh, queQuan);

    candidateList.insertTail(newCandidate);
    hashTable.insert(newCandidate);

    cout << "[+] Da them thi sinh " << hoTen
         << " (SBD: " << sbd << ") thanh cong!\n";

    return true;
}

bool CandidateManager::updateCandidate() {
    string sbd;
    string newHoTen, newGioiTinh, newNgaySinh, newQueQuan;
    Node* pTarget = nullptr;

    cout << "\n--- CAP NHAT THONG TIN THI SINH ---\n";
    cout << "Nhap SBD thi sinh can cap nhat: ";
    cin >> sbd;
    sbd = trim(sbd);

    pTarget = candidateList.find(sbd);

    if (pTarget == nullptr) {
        cout << "[!] Khong tim thay thi sinh co SBD: "
             << sbd << "\n";
        return false;
    }

    cout << "\nThong tin hien tai cua thi sinh:\n";
    pTarget->data.displayRow();

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "\nNhap Ho Ten moi (de trong neu giu nguyen): ";
    getline(cin, newHoTen);
    newHoTen = trim(newHoTen);

    cout << "Nhap Gioi Tinh moi (de trong neu giu nguyen): ";
    getline(cin, newGioiTinh);
    newGioiTinh = trim(newGioiTinh);

    cout << "Nhap Ngay Sinh moi (dd/mm/yyyy, de trong neu giu nguyen): ";
    getline(cin, newNgaySinh);
    newNgaySinh = trim(newNgaySinh);

    cout << "Nhap Que Quan moi (de trong neu giu nguyen): ";
    getline(cin, newQueQuan);
    newQueQuan = trim(newQueQuan);

    string gioiTinhChuan;
    if (!newGioiTinh.empty()) {
        gioiTinhChuan = normalizeGender(newGioiTinh);
        if (gioiTinhChuan.empty()) {
            cout << "[!] Gioi tinh khong hop le (chi nhan Nam hoac Nu)!\n";
            return false;
        }
    }

    if (!newNgaySinh.empty() && !isValidDate(newNgaySinh)) {
        cout << "[!] Ngay sinh khong hop le (dinh dang dd/mm/yyyy)!\n";
        return false;
    }

    char oldFirstLetter = pTarget->data.getFirstLetterOfName();

    if (!newHoTen.empty()) pTarget->data.setHoTen(newHoTen);
    if (!gioiTinhChuan.empty()) pTarget->data.setGioiTinh(gioiTinhChuan);
    if (!newNgaySinh.empty()) pTarget->data.setNgaySinh(newNgaySinh);
    if (!newQueQuan.empty()) pTarget->data.setQueQuan(newQueQuan);

    hashTable.remove(sbd, oldFirstLetter);
    hashTable.insert(pTarget->data);

    cout << "\n[+] Cap nhat thong tin thi sinh thanh cong!\n";

    return true;
}

void CandidateManager::searchBySBD() {
    string sbd;
    Node* result = nullptr;

    cout << "\n--- TRA CUU THI SINH THEO SO BAO DANH ---\n";
    cout << "Nhap So Bao Danh: ";
    cin >> sbd;
    sbd = trim(sbd);

    result = hashTable.searchBySBD(sbd);
    if (result == nullptr) {
        result = candidateList.find(sbd);
    }

    if (result != nullptr) {
        cout << "\n[+] Tim thay thi sinh:\n";
        result->data.displayRow();
    }
    else {
        cout << "[-] Khong tim thay thi sinh co SBD: " << sbd << "\n";
    }
}

void CandidateManager::searchByName() {
    string name;

    cout << "\n--- TRA CUU THI SINH THEO TEN ---\n";
    cout << "Nhap ten thi sinh can tim: ";

    getline(cin, name);

    hashTable.searchByName(name);
}

bool CandidateManager::deleteCandidate() {
    string sbd;
    Node* pTarget = nullptr;

    cout << "\n--- XOA THI SINH KHOI HE THONG ---\n";
    cout << "Nhap SBD thi sinh can xoa: ";
    cin >> sbd;
    sbd = trim(sbd);

    pTarget = candidateList.find(sbd);

    if (pTarget == nullptr) {
        cout << "Khong tim thay thi sinh co SBD: " << sbd << "\n";
        return false;
    }

    char firstLetter = pTarget->data.getFirstLetterOfName();

    candidateList.remove(sbd);
    hashTable.remove(sbd, firstLetter);

    cout << "Da xoa thi sinh " << sbd << " thanh cong!\n";

    return true;
}

// Nguyen Ba Linh: Giao dien menu va dieu phoi he thong

void CandidateManager::displayAll() const {
    cout << "\n=======================================================================\n";
    cout << "               DANH SACH TOAN BO THI SINH (LINKED LIST)                \n";
    cout << "=======================================================================\n";
    candidateList.display();
}

void CandidateManager::displayHashTable() const {
    hashTable.displayAll();
}

void CandidateManager::sortCandidates() {
    Sorter::sortByNameAZ(candidateList);
    Sorter::sortBuckets(hashTable);
}

void CandidateManager::allocateExamRooms() {
    int numRooms;
    cout << "Nhap so luong phong thi can phan chia (n > 0): ";
    if (!(cin >> numRooms) || numRooms <= 0 || numRooms > 10000) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "[!] So phong khong hop le! Vui long nhap so tu 1 den 10000.\n";
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    RoomAllocator::allocateRooms(candidateList, hashTable, numRooms);
}

void CandidateManager::loadData() {
    string filename;
    cout << "Nhap ten file can doc (mac dinh: input.txt): ";
    getline(cin, filename);
    filename = trim(filename);
    if (filename.empty()) filename = "input.txt";

    LinkedList newList;
    HashTable newTable;

    if (!Utils::loadFromFile(filename, newList, newTable)) {
        cout << "[!] Khong nap duoc du lieu. Danh sach cu duoc giu nguyen.\n";
        return;
    }

    candidateList = newList;
    hashTable = newTable;

    cout << "[+] Da thay the danh sach bang " << candidateList.getCount()
         << " thi sinh tu file " << filename << ".\n";
}

void CandidateManager::saveData() {
    string filename;
    cout << "Nhap ten file can luu (mac dinh: candidates_out.txt): ";
    getline(cin, filename);
    filename = trim(filename);
    if (filename.empty()) filename = "candidates_out.txt";
    Utils::saveToFile(filename, candidateList);
}

void CandidateManager::showMenu() const {
    cout << "\n=======================================================================\n";
    cout << "  CHUONG TRINH QUAN LY THI SINH - DE TAI 8 (HASH TABLE & LINKED LIST)  \n";
    cout << "  NHOM 4 - GVHD: ThS. BUI VAN THUONG - TRUONG NHOM: NGUYEN BA LINH     \n";
    cout << "=======================================================================\n";
    cout << "  1. Hien thi danh sach tat ca thi sinh (Linked List)\n";
    cout << "  2. Xem Bang bam thi sinh dang bang tra 26 nhom A-Z (Hash Table)\n";
    cout << "  3. Them thi sinh moi (Hoang The Anh)\n";
    cout << "  4. Cap nhat thong tin thi sinh (Hoang The Anh)\n";
    cout << "  5. Tra cuu thi sinh theo So Bao Danh (Tran Nhat Anh)\n";
    cout << "  6. Tra cuu thi sinh theo Ten tren Bang bam (Tran Nhat Anh)\n";
    cout << "  7. Xoa thi sinh khoi he thong (Tran Nhat Anh)\n";
    cout << "  8. Sap xep danh sach thi sinh theo Ten tang dan A-Z (Nguyen Huu Cuong)\n";
    cout << "  9. Phan chia thi sinh vao n phong thi toi uu xac suat (Pham Khanh Hung)\n";
    cout << " 10. Doc du lieu thi sinh tu file input.txt (Dao Quang Thang)\n";
    cout << " 11. Luu danh sach thi sinh ra file TXT (Dao Quang Thang)\n";
    cout << "  0. Thoat chuong trinh\n";
    cout << "=======================================================================\n";
    cout << "Lua chon cua ban [0-11]: ";
}

void CandidateManager::run() {
    int choice = -1;
    while (choice != 0) {
        showMenu();
        if (!(cin >> choice)) {
            if (cin.eof()) break; 
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "[!] Lua chon khong hop le! Vui long nhap so tu 0 den 11.\n";

            choice = -1;
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                displayAll();
                break;
            case 2:
                displayHashTable();
                break;
            case 3:
                addCandidate();
                break;
            case 4:
                updateCandidate();
                break;
            case 5:
                searchBySBD();
                break;
            case 6:
                searchByName();
                break;
            case 7:
                deleteCandidate();
                break;
            case 8:
                sortCandidates();
                break;
            case 9:
                allocateExamRooms();
                break;
            case 10:
                loadData();
                break;
            case 11:
                saveData();
                break;
            case 0:
                cout << "\n[!] Cam on ban da su dung chuong trinh! Tam biet.\n";
                break;
            default:
                cout << "[!] Lua chon khong ton tai! Vui long chon lai tu 0 den 11.\n";
                break;
        }
    }
}
