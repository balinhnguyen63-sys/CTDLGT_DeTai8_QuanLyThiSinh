#ifndef ROOMALLOCATION_H
#define ROOMALLOCATION_H

#include "ThiSinh.h"
#include "HashTable.h"
#include <vector>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <map>
#include <cmath>

struct PhongThi {
    int maPhong;
    std::vector<ThiSinh> danhSach;
    std::map<char, int> demChuCaiDau; // Đếm số thí sinh của mỗi chữ cái đầu trong phòng

    PhongThi(int ma = 0) : maPhong(ma) {}

    int getSiSo() const {
        return static_cast<int>(danhSach.size());
    }

    int getCountByInitial(char c) const {
        auto it = demChuCaiDau.find(c);
        if (it != demChuCaiDau.end()) return it->second;
        return 0;
    }

    void themThiSinh(const ThiSinh& ts) {
        danhSach.push_back(ts);
        char c = ts.getInitialLetter();
        demChuCaiDau[c]++;
    }

    // Tính số cặp trùng chữ cái đầu trong phòng thi này: C_j = sum (k_c * (k_c - 1) / 2)
    long long getSoCapTrungChuCai() const {
        long long capTrung = 0;
        for (const auto& pair : demChuCaiDau) {
            int k = pair.second;
            if (k >= 2) {
                capTrung += (1LL * k * (k - 1)) / 2;
            }
        }
        return capTrung;
    }

    // Tính xác suất chọn ngẫu nhiên 2 thí sinh trong phòng trùng chữ cái đầu: P_j = C_j / C(m, 2)
    double getXacSuatTrungChuCai() const {
        int m = getSiSo();
        if (m < 2) return 0.0;
        long long tongCap = (1LL * m * (m - 1)) / 2;
        long long capTrung = getSoCapTrungChuCai();
        return (100.0 * capTrung) / tongCap; // Đơn vị %
    }
};

class RoomAllocator {
public:
    // Cấu trúc nhóm chữ cái để sắp xếp
    struct NhomChuCai {
        char kyTu;
        std::vector<ThiSinh> thiSinhs;
    };

    // Thuật toán phân bổ phòng thi tối ưu: giảm thiểu xác suất trùng chữ cái đầu
    static std::vector<PhongThi> phanPhongToiUu(const HashTable& ht, int soPhong) {
        if (soPhong <= 0) soPhong = 1;

        std::vector<PhongThi> danhSachPhong(soPhong);
        for (int i = 0; i < soPhong; ++i) {
            danhSachPhong[i] = PhongThi(i + 1);
        }

        // Bước 1: Thu thập thí sinh theo từng nhóm chữ cái đầu từ các bucket của bảng băm
        std::vector<NhomChuCai> danhSachNhom;
        for (int i = 0; i < HashTable::TABLE_SIZE; ++i) {
            std::vector<ThiSinh> inBucket = ht.getCandidatesInBucket(i);
            if (!inBucket.empty()) {
                NhomChuCai nhom;
                nhom.kyTu = HashTable::getCharFromIndex(i);
                nhom.thiSinhs = inBucket;
                danhSachNhom.push_back(nhom);
            }
        }

        // Bước 2: Sắp xếp các nhóm theo số lượng thí sinh giảm dần (nhóm đông phân trước)
        std::sort(danhSachNhom.begin(), danhSachNhom.end(), [](const NhomChuCai& a, const NhomChuCai& b) {
            return a.thiSinhs.size() > b.thiSinhs.size();
        });

        // Bước 3: Thuật toán tham lam cân bằng (Greedy Balanced):
        // Với mỗi nhóm chữ cái c:
        // Phân từng thí sinh vào phòng có số thí sinh mang chữ cái c ít nhất;
        // Nếu bằng nhau, chọn phòng có sĩ số hiện tại ít nhất để đảm bảo cân bằng phòng.
        for (const auto& nhom : danhSachNhom) {
            char c = nhom.kyTu;
            for (const auto& ts : nhom.thiSinhs) {
                int bestRoomIdx = 0;
                int minSameChar = danhSachPhong[0].getCountByInitial(c);
                int minTotal = danhSachPhong[0].getSiSo();

                for (int r = 1; r < soPhong; ++r) {
                    int sameChar = danhSachPhong[r].getCountByInitial(c);
                    int total = danhSachPhong[r].getSiSo();

                    if (sameChar < minSameChar) {
                        minSameChar = sameChar;
                        minTotal = total;
                        bestRoomIdx = r;
                    } else if (sameChar == minSameChar) {
                        if (total < minTotal) {
                            minTotal = total;
                            bestRoomIdx = r;
                        }
                    }
                }

                danhSachPhong[bestRoomIdx].themThiSinh(ts);
            }
        }

        return danhSachPhong;
    }

    // Phương án phân phòng ngẫu nhiên / tuần tự (để đối chiếu hiệu quả thuật toán)
    static std::vector<PhongThi> phanPhongTuanTu(const std::vector<ThiSinh>& allList, int soPhong) {
        if (soPhong <= 0) soPhong = 1;
        std::vector<PhongThi> danhSachPhong(soPhong);
        for (int i = 0; i < soPhong; ++i) {
            danhSachPhong[i] = PhongThi(i + 1);
        }

        for (size_t i = 0; i < allList.size(); ++i) {
            danhSachPhong[i % soPhong].themThiSinh(allList[i]);
        }
        return danhSachPhong;
    }

    // Hiển thị kết quả phân phòng và phân tích xác suất
    static void inKetQuaPhanPhong(const std::vector<PhongThi>& dsPhong, const std::string& tieuDe = "KET QUA PHAN PHONG THI") {
        std::cout << "\n========================================================================================\n";
        std::cout << "                        " << tieuDe << "\n";
        std::cout << "========================================================================================\n";

        double tongXacSuat = 0.0;
        long long tongCapTrung = 0;
        int tongThiSinh = 0;

        for (const auto& phong : dsPhong) {
            tongThiSinh += phong.getSiSo();
            long long cap = phong.getSoCapTrungChuCai();
            tongCapTrung += cap;
            double p = phong.getXacSuatTrungChuCai();
            tongXacSuat += p;

            std::cout << "\n>>> [PHONG THI SO " << phong.maPhong << "] - Si so: " << phong.getSiSo() 
                      << " thi sinh | So cap trung chu cai dau: " << cap 
                      << " | Xac suat trung: " << std::fixed << std::setprecision(2) << p << "%\n";
            std::cout << "    Phan bo chu cai dau trong phong: ";
            for (const auto& item : phong.demChuCaiDau) {
                std::cout << item.first << ":" << item.second << " ";
            }
            std::cout << "\n";

            std::cout << "    " << std::left 
                      << std::setw(6)  << "STT"
                      << std::setw(12) << "Ma du thi"
                      << std::setw(28) << "Ho va ten"
                      << std::setw(12) << "Gioi tinh"
                      << std::setw(12) << "Ten (Chu)"
                      << "\n";
            std::cout << "    --------------------------------------------------------------------\n";

            for (size_t i = 0; i < phong.danhSach.size(); ++i) {
                const auto& ts = phong.danhSach[i];
                std::string tenChu = ts.getTen() + " (" + ts.getInitialLetter() + ")";
                std::cout << "    " << std::left 
                          << std::setw(6)  << (i + 1)
                          << std::setw(12) << ts.maDuThi
                          << std::setw(28) << ts.hoTen
                          << std::setw(12) << ts.gioiTinh
                          << std::setw(12) << tenChu
                          << "\n";
            }
        }

        double xacSuatTrungBinh = dsPhong.empty() ? 0.0 : (tongXacSuat / dsPhong.size());
        std::cout << "\n============================== TONG KET DANH GIA THUAT TOAN ==============================\n";
        std::cout << " - Tong so phong thi: " << dsPhong.size() << "\n";
        std::cout << " - Tong so thi sinh duoc phan: " << tongThiSinh << "\n";
        std::cout << " - Tong so cap thi sinh trung chu cai dau: " << tongCapTrung << " cap\n";
        std::cout << " - XAC SUAT TRUNG CHU CAI DAU TRUNG BINH MOI PHONG: " 
                  << std::fixed << std::setprecision(2) << xacSuatTrungBinh << "%\n";
        std::cout << "========================================================================================\n";
    }
};

#endif // ROOMALLOCATION_H
