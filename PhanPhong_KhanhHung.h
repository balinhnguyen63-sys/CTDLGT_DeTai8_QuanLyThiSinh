#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "CauTrucChung.h"

using namespace std;

// =========================================================================
// PHẦN 5: PHẠM KHÁNH HƯNG PHỤ TRÁCH
// ĐỀ TÀI: CHỨC NĂNG PHÂN DANH SÁCH VÀO N PHÒNG THI (GIẢM TRÙNG CHỮ CÁI ĐẦU)
//
// YÊU CẦU CỦA MÔN HỌC & GIẢNG VIÊN:
// 1. Khai báo cấu trúc PhongThi để lưu trữ thông tin phòng thi và số lượng thí sinh.
// 2. Cài đặt thuật toán phân bổ thí sinh vào n phòng thi:
//    - Dùng con trỏ duyệt qua từng danh sách liên kết trong 26 bucket.
//    - Rải đều các thí sinh trong cùng một bucket sang các phòng thi khác nhau
//      (ưu tiên phòng đang có ít thí sinh mang chữ cái đó nhất).
// 3. Tính toán xác suất chọn ngẫu nhiên 2 thí sinh trùng chữ cái đầu trong phòng thi.
// =========================================================================

// Cấu trúc đại diện cho 1 phòng thi
struct PhongThi {
    int soPhong;             // Số thứ tự phòng thi (1, 2, ..., n)
    vector<ThiSinh> danhSach;// Danh sách các thí sinh được phân vào phòng
    int demChuCai[26] = {0}; // Mảng đếm số thí sinh của từng chữ cái 'A'..'Z' trong phòng
};

// -------------------------------------------------------------------------
// TODO (Khánh Hưng tự code): Thuật toán phân chia n phòng thi và tính xác suất
// Hướng dẫn giải thuật:
// - Khởi tạo vector n phòng thi: vector<PhongThi> dsPhong(nPhong);
// - Duyệt vòng for i từ 0 đến 25 (qua 26 bucket):
//     + Khai báo con trỏ: Node* p = bangBam[i].head;
//     + Trong vòng while (p != NULL):
//         * Duyệt qua n phòng để tìm phòng có dsPhong[r].demChuCai[i] nhỏ nhất.
//         * Xếp thí sinh p->data vào phòng đó:
//           dsPhong[phongChon].danhSach.push_back(p->data);
//           dsPhong[phongChon].demChuCai[i]++;
//         * Di chuyển con trỏ: p = p->next;
// - Tính xác suất trùng chữ cái đầu trong phòng:
//     Số cặp trùng chữ cái = sum(k * (k - 1) / 2) với k là số người cùng chữ cái.
//     Tổng số cặp trong phòng = m * (m - 1) / 2 với m là tổng sĩ số phòng.
//     Xác suất (%) = (Số cặp trùng / Tổng số cặp) * 100%.
// -------------------------------------------------------------------------
inline void phanChiaPhongThi(int nPhong) {
    cout << "\n=============================================================\n";
    cout << " [CHƯA CÀI ĐẶT] PHẦN 5: PHẠM KHÁNH HƯNG TỰ VIẾT CODE TẠI ĐÂY \n";
    cout << " File can sua: PhanPhong_KhanhHung.h                         \n";
    cout << "=============================================================\n";

    // === PHẠM KHÁNH HƯNG TỰ VIẾT CODE Ở ĐÂY ===
}
