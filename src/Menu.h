#ifndef MENU_H
#define MENU_H

#include "HashTable.h"
#include "Sorting.h"
#include "RoomAllocation.h"
#include "FileManager.h"
#include <iostream>
#include <string>
#include <limits>

class Menu {
private:
    HashTable hashTable;
    std::string dataFile;

    void clearInputBuffer() {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::string trim(const std::string& str) {
        size_t first = str.find_first_not_of(" \t\r\n");
        if (first == std::string::npos) return "";
        size_t last = str.find_last_not_of(" \t\r\n");
        return str.substr(first, (last - first + 1));
    }

public:
    Menu(const std::string& file = "candidates.txt") : dataFile(file) {
        // Tự động tải dữ liệu nếu có file
        int loaded = FileManager::loadFromFile(hashTable, dataFile);
        if (loaded > 0) {
            std::cout << "[Khoi dong] Da tu dong doc " << loaded << " thi sinh tu file " << dataFile << "\n";
        } else {
            // Nạp dữ liệu mẫu ban đầu để sẵn sàng chạy thử nghiệm
            FileManager::generateMockData(hashTable);
            FileManager::saveToFile(hashTable, dataFile);
            std::cout << "[Khoi dong] Da tao san 30 thi sinh mau va luu vao " << dataFile << "\n";
        }
    }

    void run() {
        int choice = -1;
        do {
            std::cout << "\n==================================================================\n";
            std::cout << "     HE THONG QUAN LY THI SINH - HASH TABLE & LINKED LIST         \n";
            std::cout << "         DE TAI 8 - CTDL & GT - THS. BUI VAN THUONG               \n";
            std::cout << "               NHOM 4 (TRUONG NHOM: NGUYEN BA LINH)               \n";
            std::cout << "==================================================================\n";
            std::cout << "  1. Them thi sinh moi\n";
            std::cout << "  2. Tra cuu thi sinh (theo Ma du thi hoac theo Ten)\n";
            std::cout << "  3. Hien thi danh sach thi sinh theo thu tu Ten tang dan (Merge Sort)\n";
            std::cout << "  4. Phan danh sach vao n phong thi (Giam toi da trung chu cai dau)\n";
            std::cout << "  5. Cap nhat / Sua thong tin thi sinh\n";
            std::cout << "  6. Xoa thi sinh theo Ma du thi\n";
            std::cout << "  7. Thong ke phan bo chu cai dau (Bang tra Hash Table)\n";
            std::cout << "  8. Luu du lieu ra file TXT (" << dataFile << ")\n";
            std::cout << "  9. Doc lai du lieu tu file TXT\n";
            std::cout << " 10. Khoi phuc 30 thi sinh mau UTH\n";
            std::cout << "  0. Thoat chuong trinh\n";
            std::cout << "==================================================================\n";
            std::cout << "Nhap lua chon cua ban [0-10]: ";

            if (!(std::cin >> choice)) {
                clearInputBuffer();
                std::cout << "[Loi] Vui long nhap mot so hop le tu 0 den 10!\n";
                continue;
            }
            clearInputBuffer();

            switch (choice) {
                case 1: xuLyThemThiSinh(); break;
                case 2: xuLyTraCuu(); break;
                case 3: xuLyHienThiSapXep(); break;
                case 4: xuLyPhanPhongThi(); break;
                case 5: xuLyCapNhat(); break;
                case 6: xuLyXoa(); break;
                case 7: xuLyThongKe(); break;
                case 8: xuLyLuuFile(); break;
                case 9: xuLyDocFile(); break;
                case 10: xuLyNapMau(); break;
                case 0:
                    std::cout << "\n[Tam biet] Cam on ban da su dung chuong trinh! Du lieu da duoc luu.\n";
                    FileManager::saveToFile(hashTable, dataFile);
                    break;
                default:
                    std::cout << "[Loi] Lua chon khong hop le. Vui long chon lai!\n";
            }
        } while (choice != 0);
    }

private:
    void xuLyThemThiSinh() {
        std::cout << "\n--- THEM THI SINH MOI ---\n";
        std::string ma, ten, gt, ns, qq;

        std::cout << "Nhap ma du thi (vd: SBD031): ";
        std::getline(std::cin, ma);
        ma = trim(ma);
        if (ma.empty()) {
            std::cout << "[Loi] Ma du thi khong duoc de trong!\n";
            return;
        }

        if (hashTable.existsMa(ma)) {
            std::cout << "[Loi] Ma du thi '" << ma << "' da ton tai trong he thong!\n";
            return;
        }

        std::cout << "Nhap ho va ten (vd: Nguyen Van An): ";
        std::getline(std::cin, ten);
        ten = trim(ten);
        if (ten.empty()) {
            std::cout << "[Loi] Ho ten khong duoc de trong!\n";
            return;
        }

        std::cout << "Nhap gioi tinh (Nam/Nu): ";
        std::getline(std::cin, gt);
        gt = trim(gt);
        if (gt.empty()) gt = "Nam";

        std::cout << "Nhap ngay sinh (DD/MM/YYYY): ";
        std::getline(std::cin, ns);
        ns = trim(ns);

        std::cout << "Nhap que quan (vd: TP. Ho Chi Minh): ";
        std::getline(std::cin, qq);
        qq = trim(qq);

        ThiSinh ts(ma, ten, gt, ns, qq);
        if (hashTable.insert(ts)) {
            std::cout << "[Thanh cong] Da them thi sinh " << ten 
                      << " (Ten: " << ts.getTen() << ", Chu cai dau: " << ts.getInitialLetter() 
                      << ") vao he thong!\n";
            FileManager::saveToFile(hashTable, dataFile);
        } else {
            std::cout << "[Loi] Khong the them thi sinh!\n";
        }
    }

    void xuLyTraCuu() {
        std::cout << "\n--- TRA CUU THI SINH ---\n";
        std::cout << "1. Tra cuu theo Ma du thi\n";
        std::cout << "2. Tra cuu theo Ten hoac Ho ten\n";
        std::cout << "Chon hinh thuc tra cuu [1-2]: ";
        int subChoice;
        if (!(std::cin >> subChoice)) {
            clearInputBuffer();
            return;
        }
        clearInputBuffer();

        if (subChoice == 1) {
            std::cout << "Nhap ma du thi can tra cuu: ";
            std::string ma;
            std::getline(std::cin, ma);
            ma = trim(ma);

            ThiSinh* ts = hashTable.searchByMa(ma);
            if (ts != nullptr) {
                std::cout << "\n>>> TIM THAY THI SINH:\n";
                std::vector<ThiSinh> singleList = { *ts };
                Sorting::printTable(singleList, "KET QUA TRA CUU THEO MA");
            } else {
                std::cout << "[Thong bao] Khong tim thay thi sinh co ma: " << ma << "\n";
            }
        } else if (subChoice == 2) {
            std::cout << "Nhap ten hoac mot phan ho ten can tra cuu: ";
            std::string name;
            std::getline(std::cin, name);
            name = trim(name);

            std::vector<ThiSinh> results = hashTable.searchByName(name);
            if (!results.empty()) {
                std::cout << "\n>>> TIM THAY " << results.size() << " THI SINH PHU HOP:\n";
                Sorting::printTable(results, "KET QUA TRA CUU THEO TEN");
            } else {
                std::cout << "[Thong bao] Khong tim thay thi sinh nao phu hop voi: " << name << "\n";
            }
        }
    }

    void xuLyHienThiSapXep() {
        std::vector<ThiSinh> all = hashTable.getAll();
        if (all.empty()) {
            std::cout << "[Thong bao] Danh sach hien tai dang rong!\n";
            return;
        }

        // Sắp xếp theo tên tăng dần bằng Merge Sort O(N log N)
        Sorting::sortCandidatesByName(all);
        Sorting::printTable(all, "DANH SACH THI SINH SAP XEP THEO THU TU TEN TANG DAN");
    }

    void xuLyPhanPhongThi() {
        int total = hashTable.getTotal();
        if (total == 0) {
            std::cout << "[Thong bao] Danh sach rong! Vui long them thi sinh hoac nap du lieu mau truoc.\n";
            return;
        }

        std::cout << "\n--- PHAN DANH SACH VAO N PHONG THI ---\n";
        std::cout << "Tong so thi sinh hien co: " << total << "\n";
        std::cout << "Nhap so luong phong thi n muon phan (vd: 3, 4, 5): ";
        int n;
        if (!(std::cin >> n) || n <= 0) {
            clearInputBuffer();
            std::cout << "[Loi] So luong phong phai la mot so nguyen duong >= 1!\n";
            return;
        }
        clearInputBuffer();

        // 1. Phân phòng theo thuật toán Tối Ưu (Balanced Collision Minimization)
        std::vector<PhongThi> dsPhongToiUu = RoomAllocator::phanPhongToiUu(hashTable, n);
        RoomAllocator::inKetQuaPhanPhong(dsPhongToiUu, "PHUONG AN 1: THUAT TOAN TOI UU (GIAM XAC SUAT TRUNG CHU CAI)");

        // 2. Đối chiếu với thuật toán phân phòng tuần tự thông thường
        std::vector<ThiSinh> all = hashTable.getAll();
        std::vector<PhongThi> dsPhongTuanTu = RoomAllocator::phanPhongTuanTu(all, n);

        double pToiUu = 0, pTuanTu = 0;
        long long cToiUu = 0, cTuanTu = 0;
        for (const auto& p : dsPhongToiUu) {
            pToiUu += p.getXacSuatTrungChuCai();
            cToiUu += p.getSoCapTrungChuCai();
        }
        pToiUu /= dsPhongToiUu.size();

        for (const auto& p : dsPhongTuanTu) {
            pTuanTu += p.getXacSuatTrungChuCai();
            cTuanTu += p.getSoCapTrungChuCai();
        }
        pTuanTu /= dsPhongTuanTu.size();

        std::cout << "\n========================= SO SANH HIEU QUA GIUA 2 PHUONG AN =========================\n";
        std::cout << "  - Phuong an Thuan Tu (Chia theo thu tu nhap): " << cTuanTu << " cap trung | Xac suat: " 
                  << std::fixed << std::setprecision(2) << pTuanTu << "%\n";
        std::cout << "  - Phuong an Toi Uu   (Greedy Balanced)     : " << cToiUu << " cap trung | Xac suat: " 
                  << std::fixed << std::setprecision(2) << pToiUu << "%\n";
        if (pTuanTu > pToiUu) {
            double giam = pTuanTu - pToiUu;
            std::cout << "  >>> THUAT TOAN TOI UU DA GIAM XAC SUAT TRUNG " << giam << "% (Hieu qua cao gap nhieu lan!)\n";
        } else {
            std::cout << "  >>> Hai phuong an dat do toi uu tuong duong nhau tren tap du lieu nay.\n";
        }
        std::cout << "=====================================================================================\n";
    }

    void xuLyCapNhat() {
        std::cout << "\n--- CAP NHAT THONG TIN THI SINH ---\n";
        std::cout << "Nhap ma du thi can sua: ";
        std::string ma;
        std::getline(std::cin, ma);
        ma = trim(ma);

        ThiSinh* old = hashTable.searchByMa(ma);
        if (old == nullptr) {
            std::cout << "[Loi] Khong tim thay thi sinh co ma '" << ma << "'!\n";
            return;
        }

        std::cout << "Thong tin hien tai: " << old->hoTen << " | " << old->gioiTinh 
                  << " | " << old->ngaySinh << " | " << old->queQuan << "\n";
        std::cout << "Nhap thong tin moi (de trong neu giu nguyen):\n";

        std::string ten, gt, ns, qq;
        std::cout << "Ho va ten moi: ";
        std::getline(std::cin, ten);
        ten = trim(ten);
        if (ten.empty()) ten = old->hoTen;

        std::cout << "Gioi tinh moi (Nam/Nu): ";
        std::getline(std::cin, gt);
        gt = trim(gt);
        if (gt.empty()) gt = old->gioiTinh;

        std::cout << "Ngay sinh moi (DD/MM/YYYY): ";
        std::getline(std::cin, ns);
        ns = trim(ns);
        if (ns.empty()) ns = old->ngaySinh;

        std::cout << "Que quan moi: ";
        std::getline(std::cin, qq);
        qq = trim(qq);
        if (qq.empty()) qq = old->queQuan;

        ThiSinh updated(ma, ten, gt, ns, qq);
        if (hashTable.update(updated)) {
            std::cout << "[Thanh cong] Da cap nhat thong tin thi sinh " << ma << "!\n";
            FileManager::saveToFile(hashTable, dataFile);
        } else {
            std::cout << "[Loi] Khong the cap nhat!\n";
        }
    }

    void xuLyXoa() {
        std::cout << "\n--- XOA THI SINH ---\n";
        std::cout << "Nhap ma du thi can xoa: ";
        std::string ma;
        std::getline(std::cin, ma);
        ma = trim(ma);

        if (hashTable.removeByMa(ma)) {
            std::cout << "[Thanh cong] Da xoa thi sinh co ma '" << ma << "' khoi he thong!\n";
            FileManager::saveToFile(hashTable, dataFile);
        } else {
            std::cout << "[Loi] Khong tim thay thi sinh co ma '" << ma << "' de xoa!\n";
        }
    }

    void xuLyThongKe() {
        hashTable.printStatistics();
    }

    void xuLyLuuFile() {
        if (FileManager::saveToFile(hashTable, dataFile)) {
            std::cout << "[Thanh cong] Da luu toan bo " << hashTable.getTotal() 
                      << " thi sinh vao file " << dataFile << "!\n";
        }
    }

    void xuLyDocFile() {
        hashTable.clear();
        int count = FileManager::loadFromFile(hashTable, dataFile);
        if (count >= 0) {
            std::cout << "[Thanh cong] Da nap " << count << " thi sinh tu file " << dataFile << "!\n";
        }
    }

    void xuLyNapMau() {
        hashTable.clear();
        FileManager::generateMockData(hashTable);
        FileManager::saveToFile(hashTable, dataFile);
        std::cout << "[Thanh cong] Da nap lai 30 thi sinh mau UTH vao he thong va file " << dataFile << "!\n";
    }
};

#endif // MENU_H
