#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include "CauTrucChung.h"

using namespace std;

// =========================================================================
// PHẦN 3: TRẦN NHẬT ANH
// Chức năng: Tra cứu thí sinh (theo mã, theo tên) & Xóa thí sinh
// =========================================================================

// In thông tin 1 thí sinh theo định dạng dòng
inline void inMotThiSinh(ThiSinh ts, int stt) {
    cout << "|" << left << setw(4)  << stt
         << "|" << left << setw(10) << ts.maDuThi
         << "|" << left << setw(25) << ts.hoTen
         << "|" << left << setw(10) << ts.gioiTinh
         << "|" << left << setw(14) << ts.ngaySinh
         << "|" << left << setw(18) << ts.queQuan << "|\n";
}

// 1. Tra cứu thí sinh theo Mã dự thi (duyệt qua các danh sách liên kết)
inline Node* timTheoMa(string ma) {
    for (int i = 0; i < 26; i++) {
        Node* p = bangBam[i].head;
        while (p != NULL) {
            if (p->data.maDuThi == ma) return p;
            p = p->next;
        }
    }
    return NULL;
}

// 2. Tra cứu thí sinh theo Tên (Ứng dụng ưu điểm của bảng băm: chỉ tìm trong đúng bucket chữ cái)
inline void traCuuTheoTen(string tenCanTim) {
    char chuCai = layChuCaiDau(tenCanTim);
    int viTri = hamBam(chuCai);

    cout << "\n>>> Tim kiem trong nhom chu cai '" << chuCai << "' (bucket " << viTri << "):\n";
    cout << "=================================================================================\n";
    cout << "|" << left << setw(4)  << "STT"
         << "|" << left << setw(10) << "SBD"
         << "|" << left << setw(25) << "Ho va ten"
         << "|" << left << setw(10) << "Gioi tinh"
         << "|" << left << setw(14) << "Ngay sinh"
         << "|" << left << setw(18) << "Que quan" << "|\n";
    cout << "=================================================================================\n";

    Node* p = bangBam[viTri].head;
    int stt = 1;
    bool timThay = false;

    while (p != NULL) {
        string tenTS = layTen(p->data.hoTen);
        if (p->data.hoTen.find(tenCanTim) != string::npos || tenTS == tenCanTim) {
            inMotThiSinh(p->data, stt++);
            timThay = true;
        }
        p = p->next;
    }

    if (!timThay) {
        cout << "| Khong tim thay thi sinh nao phu hop trong nhom nay!                          |\n";
    }
    cout << "=================================================================================\n";
}

// 3. Xóa thí sinh theo mã dự thi khỏi danh sách liên kết
inline bool xoaThiSinhTheoMa(string ma) {
    for (int i = 0; i < 26; i++) {
        Node* curr = bangBam[i].head;
        Node* prev = NULL;

        while (curr != NULL) {
            if (curr->data.maDuThi == ma) {
                // Nếu node cần xóa nằm ở ngay đầu danh sách
                if (prev == NULL) {
                    bangBam[i].head = curr->next;
                    if (bangBam[i].head == NULL) bangBam[i].tail = NULL;
                } else {
                    // Nếu node cần xóa nằm ở giữa hoặc cuối
                    prev->next = curr->next;
                    if (curr == bangBam[i].tail) bangBam[i].tail = prev;
                }
                delete curr; // Giải phóng bộ nhớ
                return true;
            }
            prev = curr;
            curr = curr->next;
        }
    }
    return false;
}
