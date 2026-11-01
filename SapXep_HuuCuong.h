#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "CauTrucChung.h"
#include "TraCuuXoa_NhatAnh.h"

using namespace std;

// =========================================================================
// PHẦN 4: NGUYỄN HỮU CƯỜNG
// Chức năng: Sắp xếp danh sách thí sinh tăng dần theo Tên & Hiển thị bảng
// =========================================================================

// Lấy toàn bộ thí sinh từ 26 bucket vào 1 vector để chuẩn bị sắp xếp
inline vector<ThiSinh> layTatCaThiSinh() {
    vector<ThiSinh> danhSach;
    for (int i = 0; i < 26; i++) {
        Node* p = bangBam[i].head;
        while (p != NULL) {
            danhSach.push_back(p->data);
            p = p->next;
        }
    }
    return danhSach;
}

// Hàm so sánh 2 thí sinh: ưu tiên so sánh Tên (A-Z), nếu trùng tên thì so sánh Họ tên
inline bool soSanhTen(ThiSinh a, ThiSinh b) {
    string tenA = layTen(a.hoTen);
    string tenB = layTen(b.hoTen);
    if (tenA != tenB) return tenA < tenB;
    return a.hoTen < b.hoTen;
}

// Thuật toán sắp xếp danh sách theo Tên tăng dần
inline void sapXepTheoTen(vector<ThiSinh> &ds) {
    int n = ds.size();
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (soSanhTen(ds[j], ds[minIdx])) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            ThiSinh temp = ds[i];
            ds[i] = ds[minIdx];
            ds[minIdx] = temp;
        }
    }
}

// In danh sách thí sinh ra màn hình dạng bảng căn lề đẹp mắt
inline void inBangDanhSach(vector<ThiSinh> ds, string tieuDe) {
    cout << "\n=================================================================================\n";
    cout << "                    " << tieuDe << "\n";
    cout << "=================================================================================\n";
    cout << "|" << left << setw(4)  << "STT"
         << "|" << left << setw(10) << "SBD"
         << "|" << left << setw(25) << "Ho va ten"
         << "|" << left << setw(10) << "Gioi tinh"
         << "|" << left << setw(14) << "Ngay sinh"
         << "|" << left << setw(18) << "Que quan" << "|\n";
    cout << "=================================================================================\n";

    if (ds.empty()) {
        cout << "| Danh sach rong!                                                               |\n";
    } else {
        for (size_t i = 0; i < ds.size(); i++) {
            inMotThiSinh(ds[i], i + 1);
        }
    }
    cout << "=================================================================================\n";
    cout << "Tong so thi sinh: " << ds.size() << "\n";
}
