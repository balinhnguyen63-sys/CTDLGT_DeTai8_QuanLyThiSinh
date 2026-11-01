#pragma once
#include <iostream>
#include <string>
#include "CauTrucChung.h"

using namespace std;

// =========================================================================
// PHẦN 2: HOÀNG THẾ ANH
// Chức năng: Thêm thí sinh mới vào Bảng băm & Kiểm tra dữ liệu hợp lệ
// =========================================================================

// Kiểm tra xem mã dự thi đã tồn tại trong bảng băm chưa
inline bool kiemTraTrungMa(string ma) {
    for (int i = 0; i < 26; i++) {
        Node* p = bangBam[i].head;
        while (p != NULL) {
            if (p->data.maDuThi == ma) return true;
            p = p->next;
        }
    }
    return false;
}

// Thêm một thí sinh vào đúng bucket chữ cái trong bảng băm
inline bool themThiSinh(ThiSinh ts) {
    if (kiemTraTrungMa(ts.maDuThi)) {
        cout << "[Loi] Ma du thi " << ts.maDuThi << " da ton tai!\n";
        return false;
    }

    // 1. Lấy chữ cái đầu của tên (ví dụ: 'L')
    char chuCai = layChuCaiDau(ts.hoTen);

    // 2. Băm ra chỉ số bucket (ví dụ: 'L' - 'A' = 11)
    int viTri = hamBam(chuCai);

    // 3. Tạo node và thêm vào cuối danh sách liên kết của bucket đó
    Node* p = taoNode(ts);
    themVaoCuoi(bangBam[viTri], p);
    return true;
}

// Hàm nhập thông tin thí sinh từ bàn phím và gọi hàm themThiSinh
inline void nhapThemThiSinh() {
    ThiSinh ts;
    cout << "\n--- THEM THI SINH MOI (Hoang The Anh phu trach) ---\n";
    cout << "Nhap ma du thi (vd: SBD031): ";
    getline(cin, ts.maDuThi);
    if (ts.maDuThi.empty()) {
        cout << "[Loi] Ma du thi khong duoc de trong!\n";
        return;
    }
    if (kiemTraTrungMa(ts.maDuThi)) {
        cout << "[Loi] Ma du thi nay da co trong he thong!\n";
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
