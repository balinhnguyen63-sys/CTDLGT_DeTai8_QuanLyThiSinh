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
// YÊU CẦU CỦA MÔN HỌC & GIẢNG VIÊN:
// 1. Tra cứu theo Mã dự thi: Dùng con trỏ duyệt qua các danh sách liên kết.
// 2. Tra cứu theo Tên: Vận dụng bảng băm, băm chữ cái đầu của tên cần tìm
//    để nhảy thẳng vào đúng bucket, sau đó dùng con trỏ duyệt danh sách đó.
// 3. Xóa thí sinh: Tự thao tác 2 con trỏ (curr và prev), xử lý xóa đầu danh sách
//    hoặc xóa giữa/cuối danh sách và giải phóng bộ nhớ (delete curr).
// =========================================================================

// Hàm in thông tin 1 thí sinh theo định dạng dòng (để phục vụ hiển thị kết quả)
inline void inMotThiSinh(ThiSinh ts, int stt) {
    cout << "|" << left << setw(4)  << stt
         << "|" << left << setw(10) << ts.maDuThi
         << "|" << left << setw(25) << ts.hoTen
         << "|" << left << setw(10) << ts.gioiTinh
         << "|" << left << setw(14) << ts.ngaySinh
         << "|" << left << setw(18) << ts.queQuan << "|\n";
}

// -------------------------------------------------------------------------
// TODO 1: Nhật Anh tự khai báo con trỏ và viết hàm tìm kiếm theo Mã dự thi
// Hướng dẫn:
// - Duyệt vòng for i từ 0 đến 25 (qua 26 bucket).
// - Khai báo con trỏ: Node* p = bangBam[i].head;
// - Trong vòng lặp while (p != NULL):
//     + Nếu p->data.maDuThi == ma thì return p; (trả về node tìm thấy).
//     + Di chuyển con trỏ: p = p->next;
// - Nếu duyệt hết không thấy thì return NULL;
// -------------------------------------------------------------------------
inline Node* timTheoMa(string ma) {
    // === TRẦN NHẬT ANH TỰ VIẾT CODE Ở ĐÂY ===

    return NULL; // Tạm thời để trống cho Nhật Anh tự viết
}

// -------------------------------------------------------------------------
// TODO 2: Nhật Anh tự viết hàm tra cứu theo Tên trên Bảng băm
// Hướng dẫn:
// - Bước 1: Lấy chữ cái đầu của tên: char c = layChuCaiDau(tenCanTim);
// - Bước 2: Băm ra vị trí bucket: int viTri = hamBam(c);
// - Bước 3: Dùng con trỏ Node* p = bangBam[viTri].head để duyệt duy nhất bucket này!
//     + Trong while (p != NULL): kiểm tra tên và in thông tin: inMotThiSinh(p->data, stt++);
//     + Di chuyển con trỏ: p = p->next;
// -------------------------------------------------------------------------
inline void traCuuTheoTen(string tenCanTim) {
    cout << "\n=============================================================\n";
    cout << " [CHƯA CÀI ĐẶT] PHẦN 3: TRẦN NHẬT ANH TỰ VIẾT CODE TẠI ĐÂY   \n";
    cout << " File can sua: TraCuuXoa_NhatAnh.h                           \n";
    cout << "=============================================================\n";

    // === TRẦN NHẬT ANH TỰ VIẾT CODE Ở ĐÂY ===
}

// -------------------------------------------------------------------------
// TODO 3: Nhật Anh tự viết thao tác con trỏ xóa Node theo Mã dự thi
// Hướng dẫn thao tác 2 con trỏ (curr và prev):
// - Khai báo: Node* curr = bangBam[i].head; Node* prev = NULL;
// - Trong vòng lặp while (curr != NULL):
//     + Nếu curr->data.maDuThi == ma:
//         * Xóa ở đầu (prev == NULL): bangBam[i].head = curr->next;
//         * Xóa ở giữa/cuối: prev->next = curr->next;
//         * Cập nhật tail nếu xóa node cuối: if (curr == bangBam[i].tail) bangBam[i].tail = prev;
//         * delete curr; (Giải phóng bộ nhớ).
//         * return true;
//     + Di chuyển 2 con trỏ: prev = curr; curr = curr->next;
// -------------------------------------------------------------------------
inline bool xoaThiSinhTheoMa(string ma) {
    // === TRẦN NHẬT ANH TỰ VIẾT CODE Ở ĐÂY ===

    return false; // Tạm thời để trống cho Nhật Anh tự viết
}
