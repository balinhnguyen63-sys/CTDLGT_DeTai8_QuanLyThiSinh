#include "CandidateManager.h"
#include "Sorter.h"
#include "RoomAllocator.h"
#include "Utils.h"
#include <cctype>
#include <iostream>
#include <limits>
#include <string>

namespace {
std::string trim(const std::string &s) {
    const char *ws = " \t\r\n";
    std::size_t start = s.find_first_not_of(ws);
    if (start == std::string::npos) return "";
    std::size_t end = s.find_last_not_of(ws);
    return s.substr(start, end - start + 1);
}

// Chuẩn hóa giới tính: chấp nhận Nam/Nữ/Nu (kể cả chữ có dấu UTF-8).
// Bỏ các byte không phải ASCII nên "Nữ"/"nữ" đều thành "nu".
std::string normalizeGender(const std::string &raw) {
    std::string ascii;
    for (unsigned char c : raw) {
        if (c < 0x80) {
            ascii += static_cast<char>(std::tolower(c));
        }
    }
    ascii = trim(ascii);
    if (ascii == "nam") return "Nam";
    if (ascii == "nu") return "Nu";
    return "";
}

// Kiểm tra ngày sinh đúng định dạng dd/mm/yyyy và có thật trên lịch.
bool isValidDate(const std::string &s) {
    if (s.size() != 10 || s[2] != '/' || s[5] != '/') return false;
    for (std::size_t i = 0; i < s.size(); ++i) {
        if (i == 2 || i == 5) continue;
        if (!std::isdigit(static_cast<unsigned char>(s[i]))) return false;
    }

    int day = std::stoi(s.substr(0, 2));
    int month = std::stoi(s.substr(3, 2));
    int year = std::stoi(s.substr(6, 4));
    if (year < 1900 || year > 2100 || month < 1 || month > 12) return false;

    static const int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int maxDay = daysInMonth[month - 1];
    bool leapYear = (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
    if (month == 2 && leapYear) maxDay = 29;

    return day >= 1 && day <= maxDay;
}
} // namespace

// ============================================================================
// DỰ ÁN CTDL&GT: ĐỀ TÀI SỐ 8 - QUẢN LÝ DANH SÁCH THÍ SINH
// GIẢNG VIÊN HƯỚNG DẪN: ThS. BÙI VĂN THƯỢNG - LỚP: 012012400212 - NHÓM 4
// KIẾN TRÚC & ĐIỀU PHỐI HỆ THỐNG: NGUYỄN BÁ LINH (TRƯỞNG NHÓM - MSSV: 044207007737)
// ============================================================================

CandidateManager::CandidateManager() {
    // Khởi tạo hệ thống
    // Thử nạp dữ liệu từ input.txt, nếu chưa có thì nạp dữ liệu mẫu ban đầu
    if (!Utils::loadFromFile("input.txt", candidateList, hashTable)) {
        initSampleData();
    }
}

CandidateManager::~CandidateManager() {
    candidateList.clear();
    hashTable.clear();
}

// Nạp dữ liệu mẫu ban đầu để kiểm thử hệ thống bảng băm và danh sách liên kết
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

// ============================================================================
// PHẦN VIỆC CỦA THÀNH VIÊN: HOÀNG THẾ ANH
// NHIỆM VỤ: Thêm thí sinh mới (kiểm tra trùng SBD) & Cập nhật thông tin thí sinh
// KIẾN TRÚC ÁP DỤNG: Chương 2 (Tìm kiếm tuyến tính) & Chương 4 (DSLK thêm cuối)
// ============================================================================

bool CandidateManager::addCandidate() {
    std::string sbd, hoTen, gioiTinh, ngaySinh, queQuan;
    Node* pCheck = nullptr;

    std::cout << "\n--- THEM THI SINH MOI ---\n";
    std::cout << "Nhap Ma Du Thi / SBD (vi du: TS099): ";
    std::cin >> sbd;
    sbd = trim(sbd);

    if (sbd.empty()) {
        std::cout << "[!] Ma du thi khong duoc de trong!\n";
        return false;
    }

    pCheck = candidateList.find(sbd);
    if (pCheck != nullptr) {
        std::cout << "[!] Loi: Ma du thi " << sbd
                  << " da ton tai trong he thong!\n";
        return false;
    }
    if (hashTable.searchBySBD(sbd) != nullptr) {
        std::cout << "[!] Loi: Ma du thi " << sbd
                  << " da ton tai trong Bang bam!\n";
        return false;
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Nhap Ho va Ten: ";
    std::getline(std::cin, hoTen);
    hoTen = trim(hoTen);
    if (hoTen.empty()) {
        std::cout << "[!] Ho va Ten khong duoc de trong!\n";
        return false;
    }

    std::cout << "Nhap Gioi Tinh (Nam/Nu): ";
    std::getline(std::cin, gioiTinh);
    std::string gioiTinhChuan = normalizeGender(gioiTinh);
    if (gioiTinhChuan.empty()) {
        std::cout << "[!] Gioi tinh khong hop le (chi nhan Nam hoac Nu)!\n";
        return false;
    }

    std::cout << "Nhap Ngay Sinh (dd/mm/yyyy): ";
    std::getline(std::cin, ngaySinh);
    ngaySinh = trim(ngaySinh);
    if (!isValidDate(ngaySinh)) {
        std::cout << "[!] Ngay sinh khong hop le (dinh dang dd/mm/yyyy)!\n";
        return false;
    }

    std::cout << "Nhap Que Quan: ";
    std::getline(std::cin, queQuan);
    queQuan = trim(queQuan);

    Candidate newCandidate(sbd, hoTen, gioiTinhChuan, ngaySinh, queQuan);
    candidateList.insertTail(newCandidate);
    hashTable.insert(newCandidate);

    std::cout << "[+] Da them thi sinh " << hoTen
              << " (SBD: " << sbd << ") thanh cong!\n";

    return true;
}

bool CandidateManager::updateCandidate() {

    std::string sbd;
    std::string newHoTen, newGioiTinh, newNgaySinh, newQueQuan;
    Node* pTarget = nullptr;

    std::cout << "\n--- CAP NHAT THONG TIN THI SINH ---\n";
    std::cout << "Nhap SBD thi sinh can cap nhat: ";
    std::cin >> sbd;

    pTarget = candidateList.find(sbd);

    if (pTarget == nullptr) {
        std::cout << "[!] Khong tim thay thi sinh co SBD: "
                  << sbd << "\n";
        return false;
    }

    std::cout << "\nThong tin hien tai cua thi sinh:\n";
    pTarget->data.displayRow();

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "\nNhap Ho Ten moi (de trong neu giu nguyen): ";
    std::getline(std::cin, newHoTen);
    newHoTen = trim(newHoTen);

    std::cout << "Nhap Gioi Tinh moi (de trong neu giu nguyen): ";
    std::getline(std::cin, newGioiTinh);
    newGioiTinh = trim(newGioiTinh);

    std::cout << "Nhap Ngay Sinh moi (dd/mm/yyyy, de trong neu giu nguyen): ";
    std::getline(std::cin, newNgaySinh);
    newNgaySinh = trim(newNgaySinh);

    std::cout << "Nhap Que Quan moi (de trong neu giu nguyen): ";
    std::getline(std::cin, newQueQuan);
    newQueQuan = trim(newQueQuan);

    // Kiem tra TAT CA du lieu moi truoc khi ghi de (tranh sua nua chung)
    std::string gioiTinhChuan;
    if (!newGioiTinh.empty()) {
        gioiTinhChuan = normalizeGender(newGioiTinh);
        if (gioiTinhChuan.empty()) {
            std::cout << "[!] Gioi tinh khong hop le (chi nhan Nam hoac Nu)!\n";
            return false;
        }
    }

    if (!newNgaySinh.empty() && !isValidDate(newNgaySinh)) {
        std::cout << "[!] Ngay sinh khong hop le (dinh dang dd/mm/yyyy)!\n";
        return false;
    }

    // Luu chu cai dau CU (truoc khi doi ten) de xoa dung bucket trong HashTable
    char oldFirstLetter = pTarget->data.getFirstLetterOfName();

    if (!newHoTen.empty()) pTarget->data.setHoTen(newHoTen);
    if (!gioiTinhChuan.empty()) pTarget->data.setGioiTinh(gioiTinhChuan);
    if (!newNgaySinh.empty()) pTarget->data.setNgaySinh(newNgaySinh);
    if (!newQueQuan.empty()) pTarget->data.setQueQuan(newQueQuan);

    // HashTable luu BAN SAO cua Candidate, nen sau BAT KY thay doi nao
    // (ten, gioi tinh, ngay sinh, que quan) deu phai xoa ban cu va chen ban moi.
    hashTable.remove(sbd, oldFirstLetter);
    hashTable.insert(pTarget->data);

    std::cout << "\n[+] Cap nhat thong tin thi sinh thanh cong!\n";

    return true;
}

void CandidateManager::searchBySBD() {
    std::string sbd;
    Node* result = nullptr;

    std::cout << "\n--- TRA CUU THI SINH THEO SO BAO DANH ---\n";
    std::cout << "Nhap So Bao Danh: ";
    std::cin >> sbd;

    // Tim trong Bang bam truoc, neu khong co tim trong Danh sach lien ket
    result = hashTable.searchBySBD(sbd);
    if (result == nullptr) {
        result = candidateList.find(sbd);
    }

    if (result != nullptr) {
        std::cout << "\n[+] Tim thay thi sinh:\n";
        result->data.displayRow();
    }
    else {
        std::cout << "[-] Khong tim thay thi sinh co SBD: " << sbd << "\n";
    }
}
   


void CandidateManager::searchByName() {
    std::string name;

    std::cout << "\n--- TRA CUU THI SINH THEO TEN ---\n";
    std::cout << "Nhap ten thi sinh can tim: ";

    // run() da bo newline sau lua chon menu, nen doc thang ca dong ten
    std::getline(std::cin, name);

    hashTable.searchByName(name);
}


bool CandidateManager::deleteCandidate() {
    std::string sbd;
    Node* pTarget = nullptr;

    std::cout << "\n--- XOA THI SINH KHOI HE THONG ---\n";
    std::cout << "Nhap SBD thi sinh can xoa: ";
    std::cin >> sbd;

    pTarget = candidateList.find(sbd);

    if (pTarget == nullptr) {
        std::cout << "Khong tim thay thi sinh co SBD: " << sbd << "\n";
        return false;
    }

    char firstLetter = pTarget->data.getFirstLetterOfName();

    candidateList.remove(sbd);
    hashTable.remove(sbd, firstLetter);

    std::cout << "Da xoa thi sinh " << sbd << " thanh cong!\n";

    return true;
}
   

// ============================================================================
// PHẦN VIỆC CỦA TRƯỞNG NHÓM: NGUYỄN BÁ LINH
// GIAO DIỆN MENU, ĐIỀU PHỐI VÀ LIÊN KẾT CÁC MODULE TOÀN HỆ THỐNG
// ============================================================================

void CandidateManager::displayAll() const {
    std::cout << "\n=======================================================================\n";
    std::cout << "               DANH SACH TOAN BO THI SINH (LINKED LIST)                \n";
    std::cout << "=======================================================================\n";
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
    std::cout << "Nhap so luong phong thi can phan chia (n > 0): ";
    if (!(std::cin >> numRooms) || numRooms <= 0 || numRooms > 10000) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "[!] So phong khong hop le! Vui long nhap so tu 1 den 10000.\n";
        return;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    RoomAllocator::allocateRooms(candidateList, hashTable, numRooms);
}

void CandidateManager::loadData() {
    std::string filename;
    std::cout << "Nhap ten file can doc (mac dinh: input.txt): ";
    std::getline(std::cin, filename);
    filename = trim(filename);
    if (filename.empty()) filename = "input.txt";

    // Nạp vào vùng tạm trước: nếu file lỗi thì giữ nguyên dữ liệu đang có,
    // nếu thành công mới thay thế (tránh cộng dồn 30 -> 60 -> 90 và tránh mất dữ liệu).
    LinkedList newList;
    HashTable newTable;

    if (!Utils::loadFromFile(filename, newList, newTable)) {
        std::cout << "[!] Khong nap duoc du lieu. Danh sach cu duoc giu nguyen.\n";
        return;
    }

    candidateList = newList;
    hashTable = newTable;

    std::cout << "[+] Da thay the danh sach bang " << candidateList.getCount()
              << " thi sinh tu file " << filename << ".\n";
}

void CandidateManager::saveData() {
    std::string filename;
    std::cout << "Nhap ten file can luu (mac dinh: candidates_out.txt): ";
    std::getline(std::cin, filename);
    filename = trim(filename);
    if (filename.empty()) filename = "candidates_out.txt";
    Utils::saveToFile(filename, candidateList);
}

void CandidateManager::showMenu() const {
    std::cout << "\n=======================================================================\n";
    std::cout << "  CHUONG TRINH QUAN LY THI SINH - DE TAI 8 (HASH TABLE & LINKED LIST)  \n";
    std::cout << "  NHOM 4 - GVHD: ThS. BUI VAN THUONG - TRUONG NHOM: NGUYEN BA LINH     \n";
    std::cout << "=======================================================================\n";
    std::cout << "  1. Hien thi danh sach tat ca thi sinh (Linked List)\n";
    std::cout << "  2. Xem Bang bam thi sinh dang bang tra 26 nhom A-Z (Hash Table)\n";
    std::cout << "  3. Them thi sinh moi (Hoang The Anh)\n";
    std::cout << "  4. Cap nhat thong tin thi sinh (Hoang The Anh)\n";
    std::cout << "  5. Tra cuu thi sinh theo So Bao Danh (Tran Nhat Anh)\n";
    std::cout << "  6. Tra cuu thi sinh theo Ten tren Bang bam (Tran Nhat Anh)\n";
    std::cout << "  7. Xoa thi sinh khoi he thong (Tran Nhat Anh)\n";
    std::cout << "  8. Sap xep danh sach thi sinh theo Ten tang dan A-Z (Nguyen Huu Cuong)\n";
    std::cout << "  9. Phan chia thi sinh vao n phong thi toi uu xac suat (Pham Khanh Hung)\n";
    std::cout << " 10. Doc du lieu thi sinh tu file input.txt (Dao Quang Thang)\n";
    std::cout << " 11. Luu danh sach thi sinh ra file TXT (Dao Quang Thang)\n";
    std::cout << "  0. Thoat chuong trinh\n";
    std::cout << "=======================================================================\n";
    std::cout << "Lua chon cua ban [0-11]: ";
}

void CandidateManager::run() {
    int choice = -1;
    while (choice != 0) {
        showMenu();
        if (!(std::cin >> choice)) {
            if (std::cin.eof()) break; // Thoat neu gap EOF hoac dong luong nhap
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "[!] Lua chon khong hop le! Vui long nhap so tu 0 den 11.\n";
            continue;
        }

        // Bỏ ký tự newline còn lại sau khi nhập số, để các hàm dùng getline
        // (đọc/ghi file) nhận đúng đường dẫn người dùng nhập.
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

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
                std::cout << "\n[!] Cam on ban da su dung chuong trinh! Tam biet.\n";
                break;
            default:
                std::cout << "[!] Lua chon khong ton tai! Vui long chon lai tu 0 den 11.\n";
                break;
        }
    }
}
