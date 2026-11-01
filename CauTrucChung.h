#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// =========================================================================
// PHẦN 1: NGUYỄN BÁ LINH (Trưởng nhóm)
// Cấu trúc dữ liệu dùng chung cho toàn bộ dự án
// =========================================================================

// 1. Cấu trúc thông tin Thí sinh
struct ThiSinh {
    string maDuThi;  // Ví dụ: SBD001
    string hoTen;    // Ví dụ: Nguyen Ba Linh
    string gioiTinh; // Nam hoặc Nu
    string ngaySinh; // 15/08/2004
    string queQuan;  // TP. Ho Chi Minh
};

// 2. Cấu trúc 1 Node trong danh sách liên kết
struct Node {
    ThiSinh data;
    Node* next;
};

// 3. Cấu trúc Danh sách liên kết đơn (List)
struct List {
    Node* head;
    Node* tail;
};

// Khởi tạo danh sách liên kết rỗng
inline void khoiTaoList(List &ds) {
    ds.head = NULL;
    ds.tail = NULL;
}

// Tạo một node mới
inline Node* taoNode(ThiSinh ts) {
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

// 4. BẢNG BĂM (Hash Table)
// Gồm 26 danh sách liên kết đơn, tương ứng 26 chữ cái 'A' đến 'Z' (A=0, ..., Z=25)
inline List bangBam[26];

// Khởi tạo 26 danh sách rỗng
inline void khoiTaoBangBam() {
    for (int i = 0; i < 26; i++) {
        khoiTaoList(bangBam[i]);
    }
}

// Hàm lấy tên (từ cuối cùng trong họ và tên)
// Ví dụ: "Nguyen Ba Linh" -> lấy ra "Linh"
inline string layTen(string hoTen) {
    if (hoTen.empty()) return "";
    int pos = hoTen.find_last_of(" ");
    if (pos == -1) return hoTen;
    return hoTen.substr(pos + 1);
}

// Hàm lấy chữ cái đầu của tên và đổi thành chữ hoa
// Ví dụ: "Linh" -> 'L'
inline char layChuCaiDau(string hoTen) {
    string ten = layTen(hoTen);
    if (ten.empty()) return 'A';
    char c = ten[0];
    if (c >= 'a' && c <= 'z') c = c - 32;
    if (c >= 'A' && c <= 'Z') return c;
    return 'A';
}

// Hàm băm (Hash Function) dạng bảng tra
// Ánh xạ chữ cái 'A'..'Z' thành số 0..25
inline int hamBam(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c - 'A';
    }
    return 0;
}
