#include "Utils.h"
#include <iostream>
#include <fstream>
#include <sstream>

// ============================================================================
// DỰ ÁN CTDL&GT: ĐỀ TÀI SỐ 8 - QUẢN LÝ DANH SÁCH THÍ SINH
// GIẢNG VIÊN HƯỚNG DẪN: ThS. BÙI VĂN THƯỢNG - LỚP: 012012400212 - NHÓM 4
// PHỤ TRÁCH THỰC HIỆN: ĐÀO QUANG THẮNG
// NHIỆM VỤ: Đọc dữ liệu từ file input.txt và ghi danh sách thí sinh ra file TXT
// KIẾN TRÚC ÁP DỤNG: Xử lý tệp tin (File I/O) & Đồng bộ cấu trúc List + HashTable
// ============================================================================

bool Utils::loadFromFile(const std::string &filename, LinkedList &list, HashTable &table) {
    // ------------------------------------------------------------------------
    // KHAI BÁO CÁC BIẾN VÀ LUỒNG TỆP CẦN THIẾT (ĐÃ THIẾT KẾ SẴN CHO THẮNG):
    // ------------------------------------------------------------------------
    std::ifstream inFile(filename);
    std::string line;
    std::string sbd, hoTen, gioiTinh, ngaySinh, queQuan;
    int loadedCount = 0;

    // ------------------------------------------------------------------------
    // HƯỚNG DẪN THỰC HIỆN ĐỌC FILE TỪNG BƯỚC CHO ĐÀO QUANG THẮNG:
    // ------------------------------------------------------------------------
    // BƯỚC 1: Kiểm tra xem file có mở thành công không:
    //         if (!inFile.is_open()) {
    //             std::cout << "[!] Khong the mo file du lieu: " << filename << "\n";
    //             return false;
    //         }
    //
    // BƯỚC 2: Bỏ qua dòng tiêu đề CSV:
    //         std::getline(inFile, line); // Bỏ qua dòng "SBD,HoTen,GioiTinh,NgaySinh,QueQuan"
    //
    // BƯỚC 3: Dùng vòng lặp đọc từng dòng dữ liệu:
    //         while (std::getline(inFile, line)) {
    //             if (line.empty()) continue; // Bỏ qua dòng trống
    //             std::stringstream ss(line);
    //             
    //             // Tách 5 trường cách nhau bởi dấu phẩy ',':
    //             std::getline(ss, sbd, ',');
    //             std::getline(ss, hoTen, ',');
    //             std::getline(ss, gioiTinh, ',');
    //             std::getline(ss, ngaySinh, ',');
    //             std::getline(ss, queQuan, ',');
    //             
    //             // Tạo đối tượng thí sinh:
    //             Candidate c(sbd, hoTen, gioiTinh, ngaySinh, queQuan);
    //             
    //             // Thêm đồng thời vào Danh sách liên kết và Bảng băm:
    //             list.insertTail(c);
    //             table.insert(c);
    //             loadedCount++;
    //         }
    //
    // BƯỚC 4: Đóng luồng file và thông báo kết quả:
    //         inFile.close();
    //         std::cout << "[+] Da doc thanh cong " << loadedCount << " thi sinh tu file " << filename << "\n";
    //         return true;
    // ------------------------------------------------------------------------
    // GỢI Ý TRẢ LỜI VẤN ĐÁP CHO THẮNG (BƯỚC 8):
    // - Câu hỏi: "Tại sao khi nạp dữ liệu từ file, em phải thêm vào cả 2 cấu trúc?"
    // - Trả lời: "Dạ thưa Thầy, em thêm vào LinkedList để phục vụ việc duyệt toàn bộ danh sách
    //   và sắp xếp; đồng thời thêm vào HashTable để phân nhóm theo 26 chữ cái phục vụ việc
    //   tra cứu O(1) theo tên và phân bổ phòng thi tối ưu xác suất."
    // ------------------------------------------------------------------------

    // THÔNG BÁO TẠM THỜI KHI THÀNH VIÊN ĐANG VIẾT CODE:
    std::cout << "\n[!] Thong bao tu he thong: Chuc nang 'Doc file du lieu input.txt'\n";
    std::cout << "    dang duoc thanh vien [Dao Quang Thang] hoan thien theo huong dan trong Utils.cpp.\n";
    std::cout << "    (Cac luong tep ifstream, stringstream va thu vien da duoc khai bao san).\n";

    return false;
}

bool Utils::saveToFile(const std::string &filename, const LinkedList &list) {
    // ------------------------------------------------------------------------
    // KHAI BÁO CÁC BIẾN VÀ CON TRỎ CẦN THIẾT (ĐÃ THIẾT KẾ SẴN CHO THẮNG):
    // ------------------------------------------------------------------------
    std::ofstream outFile(filename);
    Node* p = list.getHead();

    // ------------------------------------------------------------------------
    // HƯỚNG DẪN THỰC HIỆN GHI FILE TỪNG BƯỚC CHO ĐÀO QUANG THẮNG:
    // ------------------------------------------------------------------------
    // BƯỚC 1: Kiểm tra xem file có mở thành công để ghi không:
    //         if (!outFile.is_open()) {
    //             std::cout << "[!] Khong the tao hoac mo file de ghi: " << filename << "\n";
    //             return false;
    //         }
    //
    // BƯỚC 2: Ghi dòng tiêu đề CSV chuẩn:
    //         outFile << "SBD,HoTen,GioiTinh,NgaySinh,QueQuan\n";
    //
    // BƯỚC 3: Dùng con trỏ p duyệt qua từng nút trong Danh sách liên kết:
    //         while (p != nullptr) {
    //             outFile << p->data.getSBD() << ","
    //                     << p->data.getHoTen() << ","
    //                     << p->data.getGioiTinh() << ","
    //                     << p->data.getNgaySinh() << ","
    //                     << p->data.getQueQuan() << "\n";
    //             p = p->next; // Chuyển sang nút kế tiếp
    //         }
    //
    // BƯỚC 4: Đóng luồng file và in thông báo:
    //         outFile.close();
    //         std::cout << "[+] Da luu toan bo " << list.getCount() << " thi sinh ra file " << filename << " thanh cong!\n";
    //         return true;
    // ------------------------------------------------------------------------

    // THÔNG BÁO TẠM THỜI KHI THÀNH VIÊN ĐANG VIẾT CODE:
    std::cout << "\n[!] Thong bao tu he thong: Chuc nang 'Luu danh sach thi sinh ra file TXT'\n";
    std::cout << "    dang duoc thanh vien [Dao Quang Thang] hoan thien theo huong dan trong Utils.cpp.\n";

    return false;
}
