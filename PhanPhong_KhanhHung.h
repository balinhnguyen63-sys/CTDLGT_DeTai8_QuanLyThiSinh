#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "CauTrucChung.h"

using namespace std;

// =========================================================================
// PHẦN 5: PHẠM KHÁNH HƯNG PHỤ TRÁCH
// ĐỀ TÀI: CHỨC NĂNG PHÂN DANH SÁCH VÀO N PHÒNG THI (GIẢM TRÙNG CHỮ CÁI ĐẦU)
//
// YÊU CẦU CỦA MÔN HỌC:
// 1. Khai báo cấu trúc PhongThi để lưu trữ thông tin phòng thi và số lượng thí sinh.
// 2. Cài đặt thuật toán phân bổ thí sinh vào n phòng thi:
//    - Dùng con trỏ duyệt qua từng danh sách liên kết trong 26 bucket.
//    - Rải đều các thí sinh trong cùng một bucket sang các phòng thi khác nhau
//      (ưu tiên phòng đang có ít thí sinh mang chữ cái đó nhất).
// 3. Tính toán xác suất chọn ngẫu nhiên 2 thí sinh trùng chữ cái đầu trong phòng thi.
// =========================================================================

// Cấu trúc đại diện cho 1 phòng thi
struct PhongThi {
    int soPhong;             // Số thứ tự phòng thi (1, 2, ..., n)
    vector<ThiSinh> danhSach;// Danh sách các thí sinh được phân vào phòng
    int demChuCai[26] = {0}; // Mảng đếm số thí sinh của từng chữ cái 'A'..'Z' trong phòng
};

// -------------------------------------------------------------------------
// TODO (Khánh Hưng tự code): Thuật toán phân chia n phòng thi và tính xác suất
// Hướng dẫn giải thuật:
// - Khởi tạo vector n phòng thi: vector<PhongThi> dsPhong(nPhong);
// - Duyệt vòng for i từ 0 đến 25 (qua 26 bucket):
//     + Khai báo con trỏ: Node* p = bangBam[i].head;
//     + Trong vòng while (p != NULL):
//         * Duyệt qua n phòng để tìm phòng có dsPhong[r].demChuCai[i] nhỏ nhất.
//         * Xếp thí sinh p->data vào phòng đó:
//           dsPhong[phongChon].danhSach.push_back(p->data);
//           dsPhong[phongChon].demChuCai[i]++;
//         * Di chuyển con trỏ: p = p->next;
// - Tính xác suất trùng chữ cái đầu trong phòng:
//     Số cặp trùng chữ cái = sum(k * (k - 1) / 2) với k là số người cùng chữ cái.
//     Tổng số cặp trong phòng = m * (m - 1) / 2 với m là tổng sĩ số phòng.
//     Xác suất (%) = (Số cặp trùng / Tổng số cặp) * 100%.
// -------------------------------------------------------------------------
inline void phanChiaPhongThi(int nPhong) {
    if (nPhong <= 0) nPhong = 1;
    vector<PhongThi> dsPhong(nPhong);
    for (int i = 0; i < nPhong; i++) {
        dsPhong[i].soPhong = i + 1;
    }

    // --- HƯNG DÙNG CON TRỎ DUYỆT 26 BUCKET VÀ PHÂN BỔ VÀO CÁC PHÒNG Ở ĐÂY ---
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

            // Gán thí sinh vào phòng tốt nhất
            dsPhong[phongTotNhat].danhSach.push_back(p->data);
            dsPhong[phongTotNhat].demChuCai[i]++;

            p = p->next;
        }
    }

    // In kết quả và phân tích xác suất
    cout << "\n=================================================================================\n";
    cout << "      KET QUA PHAN CHIA VAO " << nPhong << " PHONG THI (Pham Khanh Hung phu trach)\n";
    cout << "=================================================================================\n";

    double tongXacSuat = 0;

    for (int i = 0; i < nPhong; i++) {
        int m = dsPhong[i].danhSach.size();
        long long soCapTrung = 0;

        for (int c = 0; c < 26; c++) {
            int k = dsPhong[i].demChuCai[c];
            if (k >= 2) soCapTrung += (k * (k - 1)) / 2;
        }

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
