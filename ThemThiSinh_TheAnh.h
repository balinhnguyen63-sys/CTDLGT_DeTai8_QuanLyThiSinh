#pragma once
#include <iostream>
#include <string>
#include "CauTrucChung.h"

using namespace std;

// =========================================================================
// PHẦN 2: HOÀNG THẾ ANH PHỤ TRÁCH
// ĐỀ TÀI: CHỨC NĂNG THÊM THÍ SINH VÀO BẢNG BĂM
// 
// YÊU CẦU CỦA MÔN HỌC:
// 1. Kiểm tra tính hợp lệ: Mã dự thi không được trùng lặp với thí sinh đã có.
// 2. Tự thao tác con trỏ: Khi thêm thí sinh, tự tạo Node mới và tự trỏ
//    con trỏ (head, tail, next) để gắn vào cuối danh sách liên kết của bucket.
// 3. Khai báo biến nhập liệu đầy đủ: họ tên, mã dự thi, giới tính, ngày sinh, quê quán.
// =========================================================================

// -------------------------------------------------------------------------
// TODO 1 (Thế Anh tự code): Hàm kiểm tra mã dự thi có bị trùng lặp không
// Hướng dẫn:
// - Duyệt vòng for i từ 0 đến 25 (qua 26 bucket trong bangBam).
// - Khai báo con trỏ: Node* p = bangBam[i].head;
// - Dùng vòng lặp while (p != NULL):
//     + Nếu p->data.maDuThi == ma thì trả về true (bị trùng mã).
//     + Di chuyển con trỏ: p = p->next;
// - Nếu duyệt hết không thấy thì trả về false.
// -------------------------------------------------------------------------
inline bool kiemTraTrungMa(string ma) {
    // --- THẾ ANH TỰ KHAI BÁO BIẾN VÀ VIẾT CODE TỰ TRỎ CON TRỎ Ở ĐÂY ---
    for (int i = 0; i < 26; i++) {
        Node* p = bangBam[i].head;
        while (p != NULL) {
            if (p->data.maDuThi == ma) return true;
            p = p->next;
        }
    }
    return false;
}

// -------------------------------------------------------------------------
// TODO 2 (Thế Anh tự code): Hàm thêm thí sinh vào đúng bucket trong Bảng băm
// Hướng dẫn thao tác con trỏ:
// - Bước 1: Kiểm tra trùng mã: nếu kiemTraTrungMa(ts.maDuThi) == true thì báo lỗi và return false.
// - Bước 2: Lấy chữ cái đầu của Tên: char c = layChuCaiDau(ts.hoTen);
// - Bước 3: Tính vị trí bucket bằng hàm băm: int viTri = hamBam(c);
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
    // --- THẾ ANH TỰ VIẾT THAO TÁC CON TRỎ Ở ĐÂY ---
    if (kiemTraTrungMa(ts.maDuThi)) {
        cout << "[Loi] Ma du thi " << ts.maDuThi << " da ton tai!\n";
        return false;
    }

    char chuCai = layChuCaiDau(ts.hoTen);
    int viTri = hamBam(chuCai);

    Node* p = taoNode(ts);
    // Tự trỏ con trỏ vào cuối danh sách liên kết:
    if (bangBam[viTri].head == NULL) {
        bangBam[viTri].head = bangBam[viTri].tail = p;
    } else {
        bangBam[viTri].tail->next = p;
        bangBam[viTri].tail = p;
    }
    return true;
}

// -------------------------------------------------------------------------
// TODO 3 (Thế Anh tự code): Hàm nhập thông tin thí sinh từ bàn phím
// Hướng dẫn:
// - Khai báo biến: ThiSinh ts;
// - Dùng getline(cin, ts.maDuThi), getline(cin, ts.hoTen), ...
// - Sau khi nhập xong thì gọi: themThiSinh(ts);
// -------------------------------------------------------------------------
inline void nhapThemThiSinh() {
    cout << "\n--- THEM THI SINH MOI (Hoang The Anh phu trach) ---\n";
    ThiSinh ts;

    cout << "Nhap ma du thi (vd: SBD031): ";
    getline(cin, ts.maDuThi);
    if (ts.maDuThi.empty()) {
        cout << "[Loi] Ma du thi khong duoc de trong!\n";
        return;
    }

    cout << "Nhap ho va ten: ";
    getline(cin, ts.hoTen);
    cout << "Nhap gioi tinh (Nam/Nu): ";
    getline(cin, ts.gioiTinh);
    cout << "Nhap ngay sinh (DD/MM/YYYY): ";
    getline(cin, ts.ngaySinh);
    cout << "Nhap que quan: ";
    getline(cin, ts.queQuan);

    if (themThiSinh(ts)) {
        cout << "[Thanh cong] Da them thi sinh " << ts.hoTen 
             << " vao nhom chu cai '" << layChuCaiDau(ts.hoTen) << "'!\n";
    }
}
