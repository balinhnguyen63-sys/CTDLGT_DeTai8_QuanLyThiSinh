#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include "CauTrucChung.h"

using namespace std;

// =========================================================================
// PHẦN 3: TRẦN NHẬT ANH PHỤ TRÁCH
// ĐỀ TÀI: CHỨC NĂNG TRA CỨU THÔNG TIN & XÓA THÍ SINH
//
// YÊU CẦU CỦA MÔN HỌC:
// 1. Tra cứu theo Mã dự thi: Dùng con trỏ duyệt qua các danh sách trong Bảng băm.
// 2. Tra cứu theo Tên: Vận dụng ưu điểm của Bảng băm, băm chữ cái đầu của tên
//    cần tìm để nhảy thẳng vào đúng bucket, sau đó dùng con trỏ duyệt danh sách đó.
// 3. Xóa thí sinh: Tự thao tác 2 con trỏ (curr và prev), xử lý xóa đầu danh sách
//    hoặc xóa giữa/cuối danh sách và giải phóng bộ nhớ (delete).
// =========================================================================

// Hàm in 1 dòng thông tin thí sinh ra bảng
inline void inMotThiSinh(ThiSinh ts, int stt) {
    cout << "|" << left << setw(4)  << stt
         << "|" << left << setw(10) << ts.maDuThi
         << "|" << left << setw(25) << ts.hoTen
         << "|" << left << setw(10) << ts.gioiTinh
         << "|" << left << setw(14) << ts.ngaySinh
         << "|" << left << setw(18) << ts.queQuan << "|\n";
}

// -------------------------------------------------------------------------
// TODO 1 (Nhật Anh tự code): Hàm tra cứu thí sinh theo Mã dự thi
// Hướng dẫn:
// - Duyệt vòng for i từ 0 đến 25 (qua 26 bucket).
// - Khai báo con trỏ: Node* p = bangBam[i].head;
// - Trong vòng lặp while (p != NULL):
//     + Nếu p->data.maDuThi == ma thì return p; (trả về con trỏ node tìm thấy).
//     + Di chuyển con trỏ: p = p->next;
// - Nếu không tìm thấy thì return NULL;
// -------------------------------------------------------------------------
inline Node* timTheoMa(string ma) {
    // --- NHẬT ANH TỰ VIẾT CON TRỎ TÌM KIẾM Ở ĐÂY ---
    for (int i = 0; i < 26; i++) {
        Node* p = bangBam[i].head;
        while (p != NULL) {
            if (p->data.maDuThi == ma) return p;
            p = p->next;
        }
    }
    return NULL;
}

// -------------------------------------------------------------------------
// TODO 2 (Nhật Anh tự code): Hàm tra cứu theo Tên trên Bảng băm
// Hướng dẫn tận dụng hàm băm:
// - Bước 1: Lấy chữ cái đầu của tên cần tìm: char chuCai = layChuCaiDau(tenCanTim);
// - Bước 2: Tính chỉ số bucket: int viTri = hamBam(chuCai);
// - Bước 3: Dùng con trỏ Node* p = bangBam[viTri].head để duyệt duy nhất bucket này!
//           Trong khi duyệt: nếu tìm thấy p->data.hoTen khớp tên thì in ra.
// -------------------------------------------------------------------------
inline void traCuuTheoTen(string tenCanTim) {
    // --- NHẬT ANH TỰ VIẾT CODE TRA CỨU BẰNG BĂM Ở ĐÂY ---
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

// -------------------------------------------------------------------------
// TODO 3 (Nhật Anh tự code): Thao tác con trỏ xóa một thí sinh theo Mã dự thi
// Hướng dẫn tự trỏ con trỏ để xóa:
// - Khai báo 2 con trỏ: Node* curr = bangBam[i].head; Node* prev = NULL;
// - Trong vòng lặp while (curr != NULL):
//     + Nếu curr->data.maDuThi == ma:
//         * Trường hợp 1 (Xóa ở đầu): if (prev == NULL) bangBam[i].head = curr->next;
//         * Trường hợp 2 (Xóa ở giữa/cuối): prev->next = curr->next;
//         * Cập nhật tail nếu xóa phần tử cuối.
//         * delete curr; (Giải phóng bộ nhớ).
//         * return true;
//     + Di chuyển 2 con trỏ: prev = curr; curr = curr->next;
// -------------------------------------------------------------------------
inline bool xoaThiSinhTheoMa(string ma) {
    // --- NHẬT ANH TỰ VIẾT THAO TÁC CON TRỎ XÓA NODE Ở ĐÂY ---
    for (int i = 0; i < 26; i++) {
        Node* curr = bangBam[i].head;
        Node* prev = NULL;

        while (curr != NULL) {
            if (curr->data.maDuThi == ma) {
                if (prev == NULL) {
                    bangBam[i].head = curr->next;
                    if (bangBam[i].head == NULL) bangBam[i].tail = NULL;
                } else {
                    prev->next = curr->next;
                    if (curr == bangBam[i].tail) bangBam[i].tail = prev;
                }
                delete curr;
                return true;
            }
            prev = curr;
            curr = curr->next;
        }
    }
    return false;
}
