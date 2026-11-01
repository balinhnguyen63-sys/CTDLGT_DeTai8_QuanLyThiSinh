#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "CauTrucChung.h"

using namespace std;

// =========================================================================
// PHẦN 6: ĐÀO QUANG THẮNG PHỤ TRÁCH
// ĐỀ TÀI: CHỨC NĂNG LƯU TRỮ VÀ ĐỌC DỮ LIỆU TỪ FILE TXT
//
// YÊU CẦU CỦA MÔN HỌC:
// 1. Lưu trữ dữ liệu: Dùng con trỏ duyệt qua toàn bộ các danh sách liên kết
//    trong bảng băm để ghi dữ liệu từng thí sinh ra file văn bản candidates.txt.
// 2. Đọc dữ liệu: Mở file candidates.txt, đọc từng dòng, tách các trường
//    thông tin (ma, ten, gt, ns, que) và tự tạo node chèn lại vào bảng băm.
// =========================================================================

// -------------------------------------------------------------------------
// TODO 1 (Quang Thắng tự code): Hàm lưu toàn bộ bảng băm ra file TXT
// Hướng dẫn:
// - Khai báo: ofstream file(tenFile);
// - Duyệt vòng for i từ 0 đến 25:
//     + Khai báo con trỏ: Node* p = bangBam[i].head;
//     + Vòng while (p != NULL):
//         * Ghi: file << p->data.maDuThi << "|" << p->data.hoTen << "|" ... << "\n";
//         * Di chuyển con trỏ: p = p->next;
// - Đóng file: file.close();
// -------------------------------------------------------------------------
inline void luuFile(string tenFile) {
    // --- THẮNG DÙNG CON TRỎ DUYỆT BẢNG BĂM VÀ GHI FILE Ở ĐÂY ---
    ofstream file(tenFile);
    if (!file.is_open()) {
        cout << "[Loi] Khong the mo file de ghi!\n";
        return;
    }

    for (int i = 0; i < 26; i++) {
        Node* p = bangBam[i].head;
        while (p != NULL) {
            file << p->data.maDuThi << "|"
                 << p->data.hoTen   << "|"
                 << p->data.gioiTinh<< "|"
                 << p->data.ngaySinh<< "|"
                 << p->data.queQuan << "\n";
            p = p->next;
        }
    }
    file.close();
    cout << "[Thanh cong] Da luu du lieu vao file: " << tenFile << "\n";
}

// -------------------------------------------------------------------------
// TODO 2 (Quang Thắng tự code): Hàm đọc dữ liệu từ file TXT nạp vào bảng băm
// Hướng dẫn:
// - Khai báo: ifstream file(tenFile);
// - Làm rỗng bảng băm: khoiTaoBangBam();
// - Đọc từng dòng: while (getline(file, line)):
//     + Tách chuỗi theo dấu "|" để lấy maDuThi, hoTen, gioiTinh, ngaySinh, queQuan.
//     + Băm ký tự đầu để tìm vị trí bucket: viTri = hamBam(layChuCaiDau(ts.hoTen));
//     + Tạo Node và gắn vào cuối: themVaoCuoi(bangBam[viTri], taoNode(ts));
// - Đóng file và trả về số lượng thí sinh đã nạp.
// -------------------------------------------------------------------------
inline int docFile(string tenFile) {
    // --- THẮNG ĐỌC FILE VÀ NẠP VÀO BẢNG BĂM Ở ĐÂY ---
    ifstream file(tenFile);
    if (!file.is_open()) return 0;

    khoiTaoBangBam();
    string line;
    int dem = 0;

    while (getline(file, line)) {
        if (line.empty()) continue;
        size_t p1 = line.find("|");
        size_t p2 = line.find("|", p1 + 1);
        size_t p3 = line.find("|", p2 + 1);
        size_t p4 = line.find("|", p3 + 1);

        if (p1 != string::npos && p2 != string::npos && p3 != string::npos && p4 != string::npos) {
            ThiSinh ts;
            ts.maDuThi  = line.substr(0, p1);
            ts.hoTen    = line.substr(p1 + 1, p2 - p1 - 1);
            ts.gioiTinh = line.substr(p2 + 1, p3 - p2 - 1);
            ts.ngaySinh = line.substr(p3 + 1, p4 - p3 - 1);
            ts.queQuan  = line.substr(p4 + 1);

            char chuCai = layChuCaiDau(ts.hoTen);
            int viTri = hamBam(chuCai);
            themVaoCuoi(bangBam[viTri], taoNode(ts));
            dem++;
        }
    }
    file.close();
    return dem;
}
