#include "CandidateManager.h"
#include "Sorter.h"
#include "RoomAllocator.h"
#include "Utils.h"
#include <iostream>
#include <limits>

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
    // ------------------------------------------------------------------------
    // KHAI BÁO CÁC BIẾN VÀ CON TRỎ CẦN THIẾT (ĐÃ THIẾT KẾ SẴN CHO THẾ ANH):
    // ------------------------------------------------------------------------
    std::string sbd, hoTen, gioiTinh, ngaySinh, queQuan;
    Node* pCheck = nullptr;

    // ------------------------------------------------------------------------
    // HƯỚNG DẪN THỰC HIỆN TỪNG BƯỚC CHO HOÀNG THẾ ANH:
    // ------------------------------------------------------------------------
    // BƯỚC 1: Nhập Số Báo Danh (SBD) từ bàn phím:
    //         std::cout << "\n--- THEM THI SINH MOI ---\n";
    //         std::cout << "Nhap Ma Du Thi / SBD (vi du: TS099): ";
    //         std::cin >> sbd;
    //
    // BƯỚC 2: Kiểm tra trùng mã SBD bằng con trỏ duyệt danh sách liên kết:
    //         pCheck = candidateList.find(sbd);
    //         if (pCheck != nullptr) {
    //             std::cout << "[!] Loi: Ma du thi " << sbd << " da ton tai trong he thong!\n";
    //             return false;
    //         }
    //
    // BƯỚC 3: Nhập các thông tin còn lại của thí sinh:
    //         std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    //         std::cout << "Nhap Ho va Ten: "; std::getline(std::cin, hoTen);
    //         std::cout << "Nhap Gioi Tinh (Nam/Nu): "; std::getline(std::cin, gioiTinh);
    //         std::cout << "Nhap Ngay Sinh (dd/mm/yyyy): "; std::getline(std::cin, ngaySinh);
    //         std::cout << "Nhap Que Quan: "; std::getline(std::cin, queQuan);
    //
    // BƯỚC 4: Tạo đối tượng Candidate và chèn vào Danh sách liên kết + Bảng băm:
    //         Candidate newCandidate(sbd, hoTen, gioiTinh, ngaySinh, queQuan);
    //         candidateList.insertTail(newCandidate); // O(1)
    //         hashTable.insert(newCandidate);         // O(1)
    //
    // BƯỚC 5: In thông báo thêm thành công và return true:
    //         std::cout << "[+] Da them thi sinh " << hoTen << " (SBD: " << sbd << ") thanh cong!\n";
    //         return true;
    // ------------------------------------------------------------------------

    // THÔNG BÁO TẠM THỜI:
    std::cout << "\n[!] Thong bao tu he thong: Chuc nang 'Them thi sinh moi (kiem tra trung SBD)'\n";
    std::cout << "    dang duoc thanh vien [Hoang The Anh] hoan thien theo huong dan trong CandidateManager.cpp.\n";

    return false;
}

bool CandidateManager::updateCandidate() {
    // ------------------------------------------------------------------------
    // KHAI BÁO CÁC BIẾN VÀ CON TRỎ CẦN THIẾT (ĐÃ THIẾT KẾ SẴN CHO THẾ ANH):
    // ------------------------------------------------------------------------
    std::string sbd;
    std::string newHoTen, newGioiTinh, newNgaySinh, newQueQuan;
    Node* pTarget = nullptr;

    // ------------------------------------------------------------------------
    // HƯỚNG DẪN THỰC HIỆN TỪNG BƯỚC CHO HOÀNG THẾ ANH:
    // ------------------------------------------------------------------------
    // BƯỚC 1: Nhập SBD của thí sinh cần cập nhật:
    //         std::cout << "\n--- CAP NHAT THONG TIN THI SINH ---\n";
    //         std::cout << "Nhap SBD thi sinh can cap nhat: ";
    //         std::cin >> sbd;
    //
    // BƯỚC 2: Tìm kiếm thí sinh trong danh sách liên kết bằng con trỏ:
    //         pTarget = candidateList.find(sbd);
    //         if (pTarget == nullptr) {
    //             std::cout << "[!] Khong tim thay thi sinh co SBD: " << sbd << "\n";
    //             return false;
    //         }
    //
    // BƯỚC 3: Hiển thị thông tin hiện tại của thí sinh:
    //         std::cout << "Thong tin hien tai:\n";
    //         pTarget->data.displayRow();
    //
    // BƯỚC 4: Nhập thông tin mới và cập nhật dữ liệu:
    //         std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    //         std::cout << "Nhap Ho Ten moi (de trong neu giu nguyen): ";
    //         std::getline(std::cin, newHoTen);
    //         if (!newHoTen.empty()) pTarget->data.setHoTen(newHoTen);
    //         // Tuong tu voi gioiTinh, ngaySinh, queQuan...
    //         std::cout << "[+] Cap nhat thong tin thanh cong!\n";
    //         return true;
    // ------------------------------------------------------------------------

    // THÔNG BÁO TẠM THỜI:
    std::cout << "\n[!] Thong bao tu he thong: Chuc nang 'Cap nhat thong tin thi sinh'\n";
    std::cout << "    dang duoc thanh vien [Hoang The Anh] hoan thien theo huong dan trong CandidateManager.cpp.\n";

    return false;
}

// ============================================================================
// PHẦN VIỆC CỦA THÀNH VIÊN: TRẦN NHẬT ANH
// NHIỆM VỤ: Tra cứu thí sinh (theo SBD & theo Tên qua Bảng băm) & Xóa thí sinh
// KIẾN TRÚC ÁP DỤNG: Chương 2 (Tìm kiếm), Chương 4 (Xóa nút DSLK), Chương 6 (Bảng băm)
// ============================================================================

void CandidateManager::searchBySBD() {
    // ------------------------------------------------------------------------
    // KHAI BÁO CÁC BIẾN VÀ CON TRỎ CẦN THIẾT (ĐÃ THIẾT KẾ SẴN CHO NHẬT ANH):
    // ------------------------------------------------------------------------
    std::string sbd;
    Node* result = nullptr;

    // ------------------------------------------------------------------------
    // HƯỚNG DẪN THỰC HIỆN TỪNG BƯỚC CHO TRẦN NHẬT ANH:
    // ------------------------------------------------------------------------
    // BƯỚC 1: Nhập Số Báo Danh cần tra cứu:
    //         std::cout << "\n--- TRA CUU THI SINH THEO SO BAO DANH ---\n";
    //         std::cout << "Nhap So Bao Danh: ";
    //         std::cin >> sbd;
    //
    // BƯỚC 2: Sử dụng con trỏ tìm kiếm qua Bảng băm hoặc Danh sách liên kết:
    //         result = hashTable.searchBySBD(sbd); // hoặc candidateList.find(sbd);
    //
    // BƯỚC 3: Kiểm tra nếu tìm thấy:
    //         if (result != nullptr) {
    //             std::cout << "\n[+] Tim thay thi sinh:\n";
    //             std::cout << "+---------+-----------------------+---------+-------------+----------------------+\n";
    //             std::cout << "| SBD     | Ho va Ten             | Phai    | Ngay Sinh   | Que Quan             |\n";
    //             std::cout << "+---------+-----------------------+---------+-------------+----------------------+\n";
    //             result->data.displayRow();
    //             std::cout << "+---------+-----------------------+---------+-------------+----------------------+\n";
    //         } else {
    //             std::cout << "[-] Khong tim thay thi sinh co SBD: " << sbd << "\n";
    //         }
    // ------------------------------------------------------------------------

    // THÔNG BÁO TẠM THỜI:
    std::cout << "\n[!] Thong bao tu he thong: Chuc nang 'Tra cuu theo So Bao Danh'\n";
    std::cout << "    dang duoc thanh vien [Tran Nhat Anh] hoan thien theo huong dan trong CandidateManager.cpp.\n";
}

void CandidateManager::searchByName() {
    // ------------------------------------------------------------------------
    // KHAI BÁO CÁC BIẾN CẦN THIẾT (ĐÃ THIẾT KẾ SẴN CHO NHẬT ANH):
    // ------------------------------------------------------------------------
    std::string name;

    // ------------------------------------------------------------------------
    // HƯỚNG DẪN THỰC HIỆN TỪNG BƯỚC CHO TRẦN NHẬT ANH:
    // ------------------------------------------------------------------------
    // BƯỚC 1: Nhập tên cần tra cứu:
    //         std::cout << "\n--- TRA CUU THI SINH THEO TEN (BANG BAM) ---\n";
    //         std::cout << "Nhap Ten thi sinh (vi du: Linh, Anh, Cuong...): ";
    //         std::cin >> name;
    //
    // BƯỚC 2: Tận dụng Bảng băm dạng bảng tra để tìm kiếm cực nhanh O(1):
    //         hashTable.searchByName(name);
    // ------------------------------------------------------------------------

    // THÔNG BÁO TẠM THỜI:
    std::cout << "\n[!] Thong bao tu he thong: Chuc nang 'Tra cuu theo Ten tren Bang bam'\n";
    std::cout << "    dang duoc thanh vien [Tran Nhat Anh] hoan thien theo huong dan trong CandidateManager.cpp.\n";
}

bool CandidateManager::deleteCandidate() {
    // ------------------------------------------------------------------------
    // KHAI BÁO CÁC BIẾN VÀ CON TRỎ CẦN THIẾT (ĐÃ THIẾT KẾ SẴN CHO NHẬT ANH):
    // ------------------------------------------------------------------------
    std::string sbd;
    Node* pTarget = nullptr;

    // ------------------------------------------------------------------------
    // HƯỚNG DẪN THỰC HIỆN TỪNG BƯỚC CHO TRẦN NHẬT ANH:
    // ------------------------------------------------------------------------
    // BƯỚC 1: Nhập SBD của thí sinh cần xóa:
    //         std::cout << "\n--- XOA THI SINH KHOI HE THONG ---\n";
    //         std::cout << "Nhap SBD thi sinh can xoa: ";
    //         std::cin >> sbd;
    //
    // BƯỚC 2: Tìm nút cần xóa để lấy chữ cái đầu của tên (phục vụ xóa trên Bảng băm):
    //         pTarget = candidateList.find(sbd);
    //         if (pTarget == nullptr) {
    //             std::cout << "[!] Khong tim thay thi sinh co SBD: " << sbd << "\n";
    //             return false;
    //         }
    //         char firstLetter = pTarget->data.getFirstLetterOfName();
    //
    // BƯỚC 3: Gọi hàm xóa trên cả Danh sách liên kết và Bảng băm:
    //         candidateList.remove(sbd);
    //         hashTable.remove(sbd, firstLetter);
    //         std::cout << "[+] Da xoa thanh cong thi sinh " << sbd << " khoi he thong!\n";
    //         return true;
    // ------------------------------------------------------------------------

    // THÔNG BÁO TẠM THỜI:
    std::cout << "\n[!] Thong bao tu he thong: Chuc nang 'Xoa thi sinh theo SBD'\n";
    std::cout << "    dang duoc thanh vien [Tran Nhat Anh] hoan thien theo huong dan trong CandidateManager.cpp.\n";

    return false;
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
}

void CandidateManager::allocateExamRooms() {
    int numRooms;
    std::cout << "Nhap so luong phong thi can phan chia (n > 0): ";
    std::cin >> numRooms;
    RoomAllocator::allocateRooms(candidateList, hashTable, numRooms);
}

void CandidateManager::loadData() {
    std::string filename;
    std::cout << "Nhap ten file can doc (mac dinh: input.txt): ";
    std::cin >> filename;
    if (filename.empty()) filename = "input.txt";
    Utils::loadFromFile(filename, candidateList, hashTable);
}

void CandidateManager::saveData() {
    std::string filename;
    std::cout << "Nhap ten file can luu (mac dinh: candidates_out.txt): ";
    std::cin >> filename;
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
