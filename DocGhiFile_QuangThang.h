#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "CauTrucChung.h"

using namespace std;

// =========================================================================
// PHẦN 6: ĐÀO QUANG THẮNG
// Chức năng: Lưu trữ và Đọc dữ liệu từ file TXT (candidates.txt)
// =========================================================================

// Lưu toàn bộ bảng băm ra file TXT
inline void luuFile(string tenFile) {
    ofstream file(tenFile);
    if (!file.is_open()) {
        cout << "[Loi] Khong the mo file de ghi!\n";
        return;
    }

    for (int i = 0; i < 26; i++) {
        Node* p = bangBam[i].head;
        while (p != NULL) {
            file << p->data.maDuThi << "|"
                 << p->data.hoTen   << "|"
                 << p->data.gioiTinh<< "|"
                 << p->data.ngaySinh<< "|"
                 << p->data.queQuan << "\n";
            p = p->next;
        }
    }
    file.close();
    cout << "[Thanh cong] Da luu du lieu vao file: " << tenFile << "\n";
}

// Đọc dữ liệu từ file TXT nạp vào bảng băm
inline int docFile(string tenFile) {
    ifstream file(tenFile);
    if (!file.is_open()) return 0;

    khoiTaoBangBam(); // Làm rỗng bảng băm trước khi nạp
    string line;
    int dem = 0;

    while (getline(file, line)) {
        if (line.empty()) continue;
        size_t p1 = line.find("|");
        size_t p2 = line.find("|", p1 + 1);
        size_t p3 = line.find("|", p2 + 1);
        size_t p4 = line.find("|", p3 + 1);

        if (p1 != string::npos && p2 != string::npos && p3 != string::npos && p4 != string::npos) {
            ThiSinh ts;
            ts.maDuThi  = line.substr(0, p1);
            ts.hoTen    = line.substr(p1 + 1, p2 - p1 - 1);
            ts.gioiTinh = line.substr(p2 + 1, p3 - p2 - 1);
            ts.ngaySinh = line.substr(p3 + 1, p4 - p3 - 1);
            ts.queQuan  = line.substr(p4 + 1);

            char chuCai = layChuCaiDau(ts.hoTen);
            int viTri = hamBam(chuCai);
            themVaoCuoi(bangBam[viTri], taoNode(ts));
            dem++;
        }
    }
    file.close();
    return dem;
}
