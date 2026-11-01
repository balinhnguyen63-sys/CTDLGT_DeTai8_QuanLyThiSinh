#pragma once
#include <iostream>
#include <string>
#include "CauTrucChung.h"

using namespace std;

// =========================================================================
// PHẦN 2: HOÀNG THẾ ANH PHỤ TRÁCH
// ĐỀ TÀI: CHỨC NĂNG THÊM THÍ SINH VÀO BẢNG BĂM
//
// YÊU CẦU CỦA MÔN HỌC & GIẢNG VIÊN:
// 1. Kiểm tra tính hợp lệ: Mã dự thi không được trùng lặp với thí sinh đã có.
// 2. Thao tác con trỏ: Tự tạo Node mới (new Node) và tự trỏ các con trỏ
//    (head, tail, next) để gắn node mới vào cuối danh sách liên kết của bucket.
// 3. Khai báo biến nhập liệu đầy đủ: maDuThi, hoTen, gioiTinh, ngaySinh, queQuan.
// =========================================================================

// -------------------------------------------------------------------------
// TODO 1: Thế Anh tự khai báo biến và viết hàm kiểm tra mã dự thi đã có chưa
// Hướng dẫn thao tác con trỏ:
// - Duyệt vòng for i từ 0 đến 25 (qua 26 bucket trong bangBam).
// - Khai báo con trỏ: Node* p = bangBam[i].head;
// - Trong vòng lặp while (p != NULL):
//     + Nếu p->data.maDuThi == ma thì return true; (bị trùng mã).
//     + Di chuyển con trỏ: p = p->next;
// - Nếu duyệt hết không thấy thì return false;
// -------------------------------------------------------------------------
inline bool kiemTraTrungMa(string ma) {
    // === HOÀNG THẾ ANH TỰ VIẾT CODE Ở ĐÂY ===

    return false; // Tạm thời để trống cho Thế Anh tự viết
}

// -------------------------------------------------------------------------
// TODO 2: Thế Anh tự viết hàm băm và tự thao tác con trỏ chèn vào cuối List
// Hướng dẫn thao tác con trỏ:
// - Bước 1: Kiểm tra mã: if (kiemTraTrungMa(ts.maDuThi)) return false;
// - Bước 2: Lấy chữ cái đầu của tên: char c = layChuCaiDau(ts.hoTen);
// - Bước 3: Tính chỉ số bucket: int viTri = hamBam(c);
// - Bước 4: Tạo node mới: Node* p = taoNode(ts);
// - Bước 5: TỰ TRỎ CON TRỎ GẮN VÀO CUỐI DANH SÁCH LIÊN KẾT:
//     if (bangBam[viTri].head == NULL) {
//         bangBam[viTri].head = bangBam[viTri].tail = p;
//     } else {
//         bangBam[viTri].tail->next = p;
//         bangBam[viTri].tail = p;
//     }
// -------------------------------------------------------------------------
inline bool themThiSinh(ThiSinh ts) {
    // === HOÀNG THẾ ANH TỰ VIẾT CODE Ở ĐÂY ===

    return false; // Tạm thời để trống cho Thế Anh tự viết
}

// -------------------------------------------------------------------------
// TODO 3: Thế Anh tự khai báo biến và viết hàm nhập thông tin từ bàn phím
// Hướng dẫn:
// - Khai báo: ThiSinh ts;
// - Dùng getline(cin, ts.maDuThi), getline(cin, ts.hoTen), ...
// - Gọi hàm: themThiSinh(ts);
// -------------------------------------------------------------------------
inline void nhapThemThiSinh() {
    cout << "\n=============================================================\n";
    cout << " [CHƯA CÀI ĐẶT] PHẦN 2: HOÀNG THẾ ANH TỰ VIẾT CODE TẠI ĐÂY   \n";
    cout << " File can sua: ThemThiSinh_TheAnh.h                          \n";
    cout << "=============================================================\n";

    // === HOÀNG THẾ ANH TỰ VIẾT CODE NHẬP LIỆU Ở ĐÂY ===
}
