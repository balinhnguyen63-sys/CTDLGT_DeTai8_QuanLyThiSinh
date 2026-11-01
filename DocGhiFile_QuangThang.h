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
// YÊU CẦU CỦA MÔN HỌC & GIẢNG VIÊN:
// 1. Lưu trữ dữ liệu: Dùng con trỏ duyệt qua toàn bộ các danh sách liên kết
//    trong bảng băm để ghi dữ liệu từng thí sinh ra file văn bản candidates.txt.
// 2. Đọc dữ liệu: Mở file candidates.txt, đọc từng dòng, tách các trường
//    thông tin (ma, ten, gt, ns, que) và tự tạo node chèn lại vào bảng băm.
// =========================================================================

// -------------------------------------------------------------------------
// TODO 1: Quang Thắng tự viết hàm duyệt con trỏ qua 26 List và ghi dữ liệu ra file
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
    cout << "\n=============================================================\n";
    cout << " [CHƯA CÀI ĐẶT] PHẦN 6: ĐÀO QUANG THẮNG TỰ VIẾT CODE TẠI ĐÂY \n";
    cout << " File can sua: DocGhiFile_QuangThang.h                      \n";
    cout << "=============================================================\n";

    // === ĐÀO QUANG THẮNG TỰ VIẾT CODE GHI FILE Ở ĐÂY ===
}

// -------------------------------------------------------------------------
// TODO 2: Quang Thắng tự viết hàm đọc dữ liệu từ file TXT nạp vào bảng băm
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
    // === ĐÀO QUANG THẮNG TỰ VIẾT CODE ĐỌC FILE Ở ĐÂY ===

    return 0; // Tạm thời trả về 0 cho Thắng tự viết
}
