#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "CauTrucChung.h"
#include "TraCuuXoa_NhatAnh.h"

using namespace std;

// =========================================================================
// PHẦN 4: NGUYỄN HỮU CƯỜNG PHỤ TRÁCH
// ĐỀ TÀI: CHỨC NĂNG SẮP XẾP DANH SÁCH THÍ SINH THEO TÊN TĂNG DẦN
//
// YÊU CẦU CỦA MÔN HỌC & GIẢNG VIÊN:
// 1. Dùng con trỏ duyệt qua 26 danh sách liên kết trong bảng băm để lấy toàn bộ dữ liệu.
// 2. Viết hàm so sánh thứ tự 2 thí sinh theo Tên (A-Z), nếu trùng Tên thì so sánh Họ và tên.
// 3. Tự cài đặt thuật toán sắp xếp (Selection Sort hoặc Interchange Sort) đổi chỗ 2 phần tử.
// 4. In bảng danh sách thí sinh đã sắp xếp ra màn hình console.
// =========================================================================

// -------------------------------------------------------------------------
// TODO 1: Cường dùng con trỏ gom toàn bộ thí sinh từ 26 List vào 1 vector
// Hướng dẫn:
// - Khai báo: vector<ThiSinh> danhSach;
// - Duyệt vòng for i từ 0 đến 25:
//     + Khai báo con trỏ: Node* p = bangBam[i].head;
//     + Vòng while (p != NULL):
//         * danhSach.push_back(p->data);
//         * p = p->next;
// - return danhSach;
// -------------------------------------------------------------------------
inline vector<ThiSinh> layTatCaThiSinh() {
    vector<ThiSinh> danhSach;

    // === NGUYỄN HỮU CƯỜNG TỰ VIẾT CODE Ở ĐÂY ===

    return danhSach; // Tạm thời để trống cho Hữu Cường tự viết
}

// -------------------------------------------------------------------------
// TODO 2: Cường viết hàm so sánh thứ tự 2 thí sinh a và b theo Tên
// Hướng dẫn:
// - Lấy tên: string tenA = layTen(a.hoTen); string tenB = layTen(b.hoTen);
// - Nếu (tenA != tenB) thì return tenA < tenB;
// - Nếu trùng tên: so sánh tiếp a.hoTen < b.hoTen;
// -------------------------------------------------------------------------
inline bool soSanhTen(ThiSinh a, ThiSinh b) {
    // === NGUYỄN HỮU CƯỜNG TỰ VIẾT CODE Ở ĐÂY ===

    return false; // Tạm thời để trống cho Hữu Cường tự viết
}

// -------------------------------------------------------------------------
// TODO 3: Cường tự cài đặt thuật toán sắp xếp danh sách theo Tên tăng dần
// Hướng dẫn (Thuật toán Chọn trực tiếp / Selection Sort):
// - for (int i = 0; i < n - 1; i++)
// -     for (int j = i + 1; j < n; j++)
// -         nếu soSanhTen(ds[j], ds[minIdx]) thì cập nhật minIdx = j;
// -     hoán vị đổi chỗ ds[i] và ds[minIdx].
// -------------------------------------------------------------------------
inline void sapXepTheoTen(vector<ThiSinh> &ds) {
    // === NGUYỄN HỮU CƯỜNG TỰ VIẾT THUẬT TOÁN SẮP XẾP Ở ĐÂY ===
}

// -------------------------------------------------------------------------
// TODO 4: Cường viết hàm in bảng danh sách thí sinh ra màn hình console
// -------------------------------------------------------------------------
inline void inBangDanhSach(vector<ThiSinh> ds, string tieuDe) {
    cout << "\n=============================================================\n";
    cout << " [CHƯA CÀI ĐẶT] PHẦN 4: NGUYỄN HỮU CƯỜNG TỰ VIẾT CODE TẠI ĐÂY\n";
    cout << " File can sua: SapXep_HuuCuong.h                             \n";
    cout << "=============================================================\n";

    // === NGUYỄN HỮU CƯỜNG TỰ VIẾT CODE IN BẢNG Ở ĐÂY ===
}
