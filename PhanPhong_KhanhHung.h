#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "CauTrucChung.h"

using namespace std;

// =========================================================================
// PHẦN 5: PHẠM KHÁNH HƯNG
// Chức năng: Phân danh sách vào n phòng thi sao cho xác suất trùng chữ cái đầu là ít nhất
// =========================================================================

struct PhongThi {
    int soPhong;
    vector<ThiSinh> danhSach;
    int demChuCai[26] = {0}; // Đếm số thí sinh của từng chữ cái 'A'..'Z' trong phòng
};

// Thuật toán: Rải đều các thí sinh trong từng bucket vào n phòng thi
inline void phanChiaPhongThi(int nPhong) {
    if (nPhong <= 0) nPhong = 1;
    vector<PhongThi> dsPhong(nPhong);
    for (int i = 0; i < nPhong; i++) {
        dsPhong[i].soPhong = i + 1;
    }

    // Duyệt qua từng bucket chữ cái A-Z trong bảng băm
    for (int i = 0; i < 26; i++) {
        Node* p = bangBam[i].head;
        while (p != NULL) {
            // Tìm phòng thi đang có ít thí sinh mang chữ cái này nhất để xếp vào
            int phongTotNhat = 0;
            int minCungChuCai = dsPhong[0].demChuCai[i];
            int minSiSo = dsPhong[0].danhSach.size();

            for (int r = 1; r < nPhong; r++) {
                if (dsPhong[r].demChuCai[i] < minCungChuCai) {
                    minCungChuCai = dsPhong[r].demChuCai[i];
                    minSiSo = dsPhong[r].danhSach.size();
                    phongTotNhat = r;
                } else if (dsPhong[r].demChuCai[i] == minCungChuCai) {
                    if ((int)dsPhong[r].danhSach.size() < minSiSo) {
                        minSiSo = dsPhong[r].danhSach.size();
                        phongTotNhat = r;
                    }
                }
            }

            // Xếp thí sinh vào phòng tốt nhất
            dsPhong[phongTotNhat].danhSach.push_back(p->data);
            dsPhong[phongTotNhat].demChuCai[i]++;

            p = p->next;
        }
    }

    // In kết quả phân chia phòng thi và tính toán xác suất
    cout << "\n=================================================================================\n";
    cout << "      KET QUA PHAN CHIA VAO " << nPhong << " PHONG THI (Pham Khanh Hung phu trach)\n";
    cout << "=================================================================================\n";

    double tongXacSuat = 0;

    for (int i = 0; i < nPhong; i++) {
        int m = dsPhong[i].danhSach.size();
        long long soCapTrung = 0;

        // Tính số cặp thí sinh trùng chữ cái đầu: k * (k - 1) / 2
        for (int c = 0; c < 26; c++) {
            int k = dsPhong[i].demChuCai[c];
            if (k >= 2) soCapTrung += (k * (k - 1)) / 2;
        }

        // Xác suất chọn ngẫu nhiên 2 người trùng chữ cái đầu
        double xacSuat = 0.0;
        if (m >= 2) {
            long long tongCap = (1LL * m * (m - 1)) / 2;
            xacSuat = (100.0 * soCapTrung) / tongCap;
        }
        tongXacSuat += xacSuat;

        cout << "\n>>> [PHONG THI SO " << dsPhong[i].soPhong << "] - Si so: " << m 
             << " thi sinh | So cap trung chu cai dau: " << soCapTrung 
             << " | Xac suat trung: " << fixed << setprecision(2) << xacSuat << "%\n";
        cout << "---------------------------------------------------------------------------------\n";
        for (size_t j = 0; j < dsPhong[i].danhSach.size(); j++) {
            ThiSinh ts = dsPhong[i].danhSach[j];
            cout << "   " << setw(3) << (j + 1) << ". " 
                 << setw(8) << ts.maDuThi << " - " 
                 << setw(22) << ts.hoTen 
                 << " (Ten: " << layTen(ts.hoTen) << ", Chu: '" << layChuCaiDau(ts.hoTen) << "')\n";
        }
    }

    cout << "\n=================================================================================\n";
    cout << "XAC SUAT TRUNG CHU CAI DAU TRUNG BINH CAC PHONG: " 
         << fixed << setprecision(2) << (tongXacSuat / nPhong) << "%\n";
    cout << "=================================================================================\n";
}
