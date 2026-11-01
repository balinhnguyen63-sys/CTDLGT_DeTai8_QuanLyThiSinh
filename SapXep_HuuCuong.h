#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "CauTrucChung.h"
#include "TraCuuXoa_NhatAnh.h"

using namespace std;

// =========================================================================
// PHẦN 4: NGUYỄN HỮU CƯỜNG PHỤ TRÁCH
// ĐỀ TÀI: CHỨC NĂNG SẮP XẾP DANH SÁCH THÍ SINH THEO TÊN TĂNG DẦN
//
// YÊU CẦU CỦA MÔN HỌC:
// 1. Dùng con trỏ duyệt qua 26 danh sách liên kết trong bảng băm để lấy toàn bộ dữ liệu.
// 2. Viết hàm so sánh thứ tự 2 thí sinh theo Tên (A-Z), nếu trùng Tên thì so sánh Họ và tên.
// 3. Cài đặt thuật toán sắp xếp (Selection Sort hoặc Interchange Sort) đổi chỗ 2 phần tử.
// 4. In bảng danh sách thí sinh đã sắp xếp ra màn hình console.
// =========================================================================

// -------------------------------------------------------------------------
// TODO 1 (Cường tự code): Dùng con trỏ gom toàn bộ thí sinh từ 26 List vào 1 vector
// Hướng dẫn:
// - Khai báo: vector<ThiSinh> danhSach;
// - Duyệt vòng for i từ 0 đến 25:
//     + Khai báo con trỏ: Node* p = bangBam[i].head;
//     + Vòng while (p != NULL): danhSach.push_back(p->data); p = p->next;
// - Trả về danhSach.
// -------------------------------------------------------------------------
inline vector<ThiSinh> layTatCaThiSinh() {
    vector<ThiSinh> danhSach;
    // --- CƯỜNG TỰ DÙNG CON TRỎ DUYỆT 26 LIST Ở ĐÂY ---
    for (int i = 0; i < 26; i++) {
        Node* p = bangBam[i].head;
        while (p != NULL) {
            danhSach.push_back(p->data);
            p = p->next;
        }
    }
    return danhSach;
}

// -------------------------------------------------------------------------
// TODO 2 (Cường tự code): Hàm so sánh thứ tự 2 thí sinh a và b theo Tên
// Hướng dẫn:
// - Lấy tên của a: string tenA = layTen(a.hoTen);
// - Lấy tên của b: string tenB = layTen(b.hoTen);
// - Nếu (tenA != tenB) thì return tenA < tenB;
// - Nếu trùng tên: so sánh tiếp a.hoTen < b.hoTen;
// -------------------------------------------------------------------------
inline bool soSanhTen(ThiSinh a, ThiSinh b) {
    // --- CƯỜNG TỰ VIẾT HÀM SO SÁNH Ở ĐÂY ---
    string tenA = layTen(a.hoTen);
    string tenB = layTen(b.hoTen);
    if (tenA != tenB) return tenA < tenB;
    return a.hoTen < b.hoTen;
}

// -------------------------------------------------------------------------
// TODO 3 (Cường tự code): Cài đặt thuật toán sắp xếp danh sách theo Tên tăng dần
// Hướng dẫn (Thuật toán Chọn trực tiếp / Selection Sort):
// - 2 vòng lặp lồng nhau: for (int i = 0; i < n - 1; i++) và for (int j = i + 1; j < n; j++)
// - Tìm phần tử nhỏ nhất và hoán vị (swap) ds[i] với ds[minIdx].
// -------------------------------------------------------------------------
inline void sapXepTheoTen(vector<ThiSinh> &ds) {
    // --- CƯỜNG TỰ VIẾT THUẬT TOÁN SẮP XẾP Ở ĐÂY ---
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

// -------------------------------------------------------------------------
// TODO 4 (Cường tự code): In bảng danh sách thí sinh ra màn hình console
// -------------------------------------------------------------------------
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
