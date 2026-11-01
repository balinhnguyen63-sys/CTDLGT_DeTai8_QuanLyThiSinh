#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// =========================================================================
// PHẦN 1: NGUYỄN BÁ LINH (Trưởng nhóm phụ trách)
// ĐỀ TÀI 8: QUẢN LÝ DANH SÁCH THÍ SINH (Hash Table & Linked List)
// YÊU CẦU CỦA MÔN HỌC:
// 1. Định nghĩa cấu trúc dữ liệu Thí sinh (ThiSinh).
// 2. Định nghĩa cấu trúc Node và cấu trúc Danh sách liên kết đơn (List).
// 3. Khai báo Bảng băm dạng bảng tra gồm 26 List (tương ứng 'A'..'Z').
// 4. Viết hàm tách tên và hàm băm ánh xạ chữ cái đầu vào chỉ số mảng [0..25].
// =========================================================================

// 1. Cấu trúc thông tin Thí sinh
struct ThiSinh {
    string maDuThi;  // Mã dự thi (ví dụ: SBD001, duy nhất không trùng)
    string hoTen;    // Họ và tên (ví dụ: Nguyen Ba Linh)
    string gioiTinh; // Giới tính: Nam hoặc Nu
    string ngaySinh; // Ngày sinh: DD/MM/YYYY
    string queQuan;  // Quê quán: TP. Ho Chi Minh
};

// 2. Cấu trúc 1 Node trong danh sách liên kết đơn
struct Node {
    ThiSinh data;    // Dữ liệu thí sinh
    Node* next;      // Con trỏ trỏ tới node tiếp theo
};

// 3. Cấu trúc Danh sách liên kết đơn (List)
struct List {
    Node* head;      // Con trỏ trỏ tới phần tử đầu danh sách
    Node* tail;      // Con trỏ trỏ tới phần tử cuối danh sách
};

// Hàm khởi tạo 1 danh sách liên kết rỗng
inline void khoiTaoList(List &ds) {
    ds.head = NULL;
    ds.tail = NULL;
}

// Hàm cấp phát và tạo 1 Node mới chứa dữ liệu thí sinh
inline Node* taoNode(ThiSinh ts) {
    // TODO: Linh có thể tự chỉnh sửa cách cấp phát node tại đây:
    Node* p = new Node;
    p->data = ts;
    p->next = NULL;
    return p;
}

// Thêm node vào cuối danh sách liên kết
inline void themVaoCuoi(List &ds, Node* p) {
    if (ds.head == NULL) {
        ds.head = ds.tail = p;
    } else {
        ds.tail->next = p;
        ds.tail = p;
    }
}

// 4. BẢNG BĂM (Hash Table) DẠNG BẢNG TRA
// Đề bài yêu cầu: Nhóm các thí sinh theo chữ cái bắt đầu của Tên.
// Bảng băm là mảng gồm 26 danh sách liên kết đơn (tương ứng từ 'A' đến 'Z'):
inline List bangBam[26];

// Khởi tạo 26 danh sách rỗng trong bảng băm
inline void khoiTaoBangBam() {
    for (int i = 0; i < 26; i++) {
        khoiTaoList(bangBam[i]);
    }
}

// 5. CÁC HÀM XỬ LÝ CHUỖI VÀ HÀM BĂM
// TODO: Linh kiểm tra và tự viết/tối ưu các hàm này:

// Hàm lấy tên (từ cuối cùng trong chuỗi Họ và tên)
// Ví dụ: "Nguyen Ba Linh" -> lấy ra "Linh"
inline string layTen(string hoTen) {
    if (hoTen.empty()) return "";
    int pos = hoTen.find_last_of(" ");
    if (pos == -1) return hoTen;
    return hoTen.substr(pos + 1);
}

// Hàm lấy chữ cái đầu của tên và đổi thành chữ in hoa
// Ví dụ: Tên "Linh" -> lấy ra 'L'
inline char layChuCaiDau(string hoTen) {
    string ten = layTen(hoTen);
    if (ten.empty()) return 'A';
    char c = ten[0];
    if (c >= 'a' && c <= 'z') c = c - 32; // Chuyển chữ thường sang chữ hoa
    if (c >= 'A' && c <= 'Z') return c;
    return 'A';
}

// Hàm băm (Hash Function) dạng bảng tra
// Ánh xạ chữ cái 'A'..'Z' thành số nguyên [0..25]
// Ví dụ: 'A' -> 0, 'B' -> 1, ..., 'L' -> 11, 'Z' -> 25
inline int hamBam(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c - 'A';
    }
    return 0;
}
