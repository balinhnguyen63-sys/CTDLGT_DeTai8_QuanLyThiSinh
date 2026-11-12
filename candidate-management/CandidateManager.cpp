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
    string s = trim(raw);
    for (char &c : s) {
        c = (char)tolower((unsigned char)c);
    }
    if (s == "nam") return "Nam";
    if (s == "nu") return "Nu";
    return "";
}

bool laNamNhuan(int nam) {
    return (nam % 400 == 0) || (nam % 4 == 0 && nam % 100 != 0);
}

int soNgayTrongThang(int thang, int nam) {
    switch (thang) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            return 31;
        case 4: case 6: case 9: case 11:
            return 30;
        case 2:
            return laNamNhuan(nam) ? 29 : 28;
        default:
            return 0;
    }
}

bool kiemTraNgayHopLe(int ngay, int thang, int nam) {
    if (nam < 1900 || nam > 2100) return false;
    if (thang < 1 || thang > 12) return false;
    if (ngay < 1 || ngay > soNgayTrongThang(thang, nam)) return false;
    return true;
}

string dinhDangNgay(int ngay, int thang, int nam) {
    string sNgay = (ngay < 10 ? "0" : "") + to_string(ngay);
    string sThang = (thang < 10 ? "0" : "") + to_string(thang);
    return sNgay + "/" + sThang + "/" + to_string(nam);
}

// Doc mot dong; tra ve false khi gap EOF.
bool docDong(string &line) {
    if (!getline(cin, line)) return false;
    return true;
}

bool chiChuaChuCaiVaKhoangTrang(const string &s) {
    if (s.empty()) return false;
    for (unsigned char c : s) {
        if (!isalpha(c) && c != ' ') return false;
    }
    return true;
}

bool chuoiThanhSo(const string &s, int &value) {
    if (s.empty() || s.size() > 9) return false;
    value = 0;
    for (char c : s) {
        if (!isdigit((unsigned char)c)) return false;
        value = value * 10 + (c - '0');
    }
    return true;
}

// Nhap 1-10 chu so cua SBD, tu dong them tien to "TS".
// Neu nhap it hon 3 chu so thi tu them so 0 o dau cho du 3.
bool nhapSBD(const string &nhac, string &sbd) {
    while (true) {
        cout << nhac;
        string line;
        if (!docDong(line)) return false;
        line = trim(line);

        bool hopLe = !line.empty() && line.size() <= 10;
        for (char c : line) {
            if (!isdigit((unsigned char)c)) hopLe = false;
        }
        if (!hopLe) {
            cout << "[!] SBD phai gom tu 1 den 10 chu so! Nhap lai.\n";
            continue;
        }

        while (line.size() < 3) {
            line = "0" + line;
        }

        sbd = "TS" + line;
        return true;
    }
}

// Nhap Ho va ten dem. duocDeTrong = true dung cho chuc nang cap nhat.
bool nhapHoDem(string &hoDem, bool duocDeTrong) {
    while (true) {
        cout << (duocDeTrong
            ? "Nhap Ho va ten dem moi (de trong neu giu nguyen): "
            : "Nhap Ho va ten dem: ");
        string line;
        if (!docDong(line)) return false;

        line = trim(line);
        if (line.empty()) {
            if (duocDeTrong) {
                hoDem = "";
                return true;
            }
            cout << "[!] Ho va ten dem khong duoc de trong! Nhap lai.\n";
            continue;
        }
        if (!chiChuaChuCaiVaKhoangTrang(line)) {
            cout << "[!] Ho va ten dem chi duoc chua chu cai va khoang trang! Nhap lai.\n";
            continue;
        }
        hoDem = line;
        return true;
    }
}

// Nhap Ten rieng. Ten chi duoc la mot tu.
bool nhapTen(string &ten, bool duocDeTrong) {
    while (true) {
        cout << (duocDeTrong
            ? "Nhap Ten moi (de trong neu giu nguyen): "
            : "Nhap Ten: ");
        string line;
        if (!docDong(line)) return false;

        line = trim(line);
        if (line.empty()) {
            if (duocDeTrong) {
                ten = "";
                return true;
            }
            cout << "[!] Ten khong duoc de trong! Nhap lai.\n";
            continue;
        }
        if (line.find(' ') != string::npos) {
            cout << "[!] Ten chi duoc la mot tu, khong chua khoang trang! Nhap lai.\n";
            continue;
        }
        if (!chiChuaChuCaiVaKhoangTrang(line)) {
            cout << "[!] Ten chi duoc chua chu cai! Nhap lai.\n";
            continue;
        }
        ten = line;
        return true;
    }
}

// Nhap gioi tinh. duocDeTrong = true dung cho chuc nang cap nhat.
bool nhapGioiTinh(string &gioiTinh, bool duocDeTrong) {
    while (true) {
        cout << (duocDeTrong
            ? "Nhap Gioi Tinh moi (Nam/Nu, de trong neu giu nguyen): "
            : "Nhap Gioi Tinh (Nam/Nu): ");
        string line;
        if (!docDong(line)) return false;

        line = trim(line);
        if (line.empty() && duocDeTrong) {
            gioiTinh = "";
            return true;
        }

        string chuan = normalizeGender(line);
        if (!chuan.empty()) {
            gioiTinh = chuan;
            return true;
        }
        cout << "[!] Gioi tinh khong hop le (chi nhan Nam hoac Nu)! Nhap lai.\n";
    }
}

// Nhap ngay/thang/nam rieng, sai thi nhap lai tu ngay.
bool nhapNgaySinh(string &ngaySinh, bool duocDeTrong) {
    while (true) {
        cout << (duocDeTrong
            ? "Nhap ngay sinh moi (1-31, de trong neu giu nguyen): "
            : "Nhap ngay sinh (1-31): ");
        string sNgay;
        if (!docDong(sNgay)) return false;

        sNgay = trim(sNgay);
        if (sNgay.empty()) {
            if (duocDeTrong) {
                ngaySinh = "";
                return true;
            }
            cout << "[!] Ngay sinh khong duoc de trong! Nhap lai.\n";
            continue;
        }

        int ngay = 0, thang = 0, nam = 0;
        if (!chuoiThanhSo(sNgay, ngay)) {
            cout << "[!] Ngay sinh phai la so tu 1 den 31! Nhap lai.\n";
            continue;
        }

        cout << "Nhap thang sinh (1-12): ";
        string sThang;
        if (!docDong(sThang)) return false;
        if (!chuoiThanhSo(trim(sThang), thang)) {
            cout << "[!] Thang sinh phai la so tu 1 den 12! Nhap lai tu ngay.\n";
            continue;
        }

        cout << "Nhap nam sinh (vi du 2004): ";
        string sNam;
        if (!docDong(sNam)) return false;
        if (!chuoiThanhSo(trim(sNam), nam)) {
            cout << "[!] Nam sinh phai la so! Nhap lai tu ngay.\n";
            continue;
        }

        if (!kiemTraNgayHopLe(ngay, thang, nam)) {
            cout << "[!] Ngay thang nam sinh khong hop le! Nhap lai tu ngay.\n";
            continue;
        }

        ngaySinh = dinhDangNgay(ngay, thang, nam);
        return true;
    }
}

// Nhap que quan. duocDeTrong = true dung cho chuc nang cap nhat.
bool nhapQueQuan(string &queQuan, bool duocDeTrong) {
    while (true) {
        cout << (duocDeTrong
            ? "Nhap Que Quan moi (de trong neu giu nguyen): "
            : "Nhap Que Quan: ");
        string line;
        if (!docDong(line)) return false;

        line = trim(line);
        if (line.empty()) {
            if (duocDeTrong) {
                queQuan = "";
                return true;
            }
            cout << "[!] Que quan khong duoc de trong! Nhap lai.\n";
            continue;
        }
        queQuan = line;
        return true;
    }
}
} // namespace

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

    // Nhap SBD: 1-10 chu so, tu them "TS", khong duoc trung.
    while (true) {
        if (!nhapSBD("Nhap SBD (1-10 chu so, vi du: 030): ", sbd)) return false;
        if (candidateList.find(sbd) != nullptr ||
            hashTable.searchBySBD(sbd) != nullptr) {
            cout << "[!] Loi: Ma du thi " << sbd
                 << " da ton tai trong he thong! Nhap so khac.\n";
            continue;
        }
        break;
    }

    string hoDem, ten;
    if (!nhapHoDem(hoDem, false)) return false;
    if (!nhapTen(ten, false)) return false;
    hoTen = hoDem + " " + ten;

    if (!nhapGioiTinh(gioiTinh, false)) return false;
    if (!nhapNgaySinh(ngaySinh, false)) return false;
    if (!nhapQueQuan(queQuan, false)) return false;

    Candidate newCandidate(sbd, hoTen, gioiTinh, ngaySinh, queQuan);

    candidateList.insertTail(newCandidate);
    hashTable.insert(newCandidate);

    cout << "[+] Da them thi sinh " << hoTen
         << " (SBD: " << sbd << ") thanh cong!\n";

    return true;
}

bool CandidateManager::updateCandidate() {
    string sbd;
    string newHoTen, newHoDem, newTen;
    string newGioiTinh, newNgaySinh, newQueQuan;
    Node* pTarget = nullptr;

    cout << "\n--- CAP NHAT THONG TIN THI SINH ---\n";

    if (!nhapSBD("Nhap SBD thi sinh can cap nhat (1-10 chu so): ", sbd)) return false;

    pTarget = candidateList.find(sbd);

    if (pTarget == nullptr) {
        cout << "[!] Khong tim thay thi sinh co SBD: "
             << sbd << "\n";
        return false;
    }

    cout << "\nThong tin hien tai cua thi sinh:\n";
    pTarget->data.displayRow();

    // Tach ho ten cu de giu lai phan khong doi khi chi sua mot trong hai phan.
    string oldHoTen = pTarget->data.getHoTen();
    string oldHoDem, oldTen;
    size_t lastSpace = oldHoTen.find_last_of(" \t");
    if (lastSpace == string::npos) {
        oldTen = oldHoTen;
    }
    else {
        oldHoDem = trim(oldHoTen.substr(0, lastSpace));
        oldTen = trim(oldHoTen.substr(lastSpace + 1));
    }

    if (!nhapHoDem(newHoDem, true)) return false;
    if (!nhapTen(newTen, true)) return false;

    bool doiTen = !newHoDem.empty() || !newTen.empty();
    if (doiTen) {
        string hoDemCuoi = newHoDem.empty() ? oldHoDem : newHoDem;
        string tenCuoi = newTen.empty() ? oldTen : newTen;
        newHoTen = hoDemCuoi.empty() ? tenCuoi : (hoDemCuoi + " " + tenCuoi);
    }

    if (!nhapGioiTinh(newGioiTinh, true)) return false;
    if (!nhapNgaySinh(newNgaySinh, true)) return false;
    if (!nhapQueQuan(newQueQuan, true)) return false;

    char oldFirstLetter = pTarget->data.getFirstLetterOfName();

    if (doiTen) pTarget->data.setHoTen(newHoTen);
    if (!newGioiTinh.empty()) pTarget->data.setGioiTinh(newGioiTinh);
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
    if (!nhapSBD("Nhap SBD can tim (1-10 chu so): ", sbd)) return;

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
    if (!nhapSBD("Nhap SBD thi sinh can xoa (1-10 chu so): ", sbd)) return false;

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
    cout << "  5. Tra cuu theo SBD - biet ma thi tim ma (Tran Nhat Anh)\n";
    cout << "  6. Tra cuu theo Ten - hien danh sach ten phu hop (Tran Nhat Anh)\n";
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
