#pragma once
#include <iostream>
#include <string>
#include <iomanip>

// ============================================================================
// DỰ ÁN CTDL&GT: ĐỀ TÀI SỐ 8 - QUẢN LÝ DANH SÁCH THÍ SINH (HASH TABLE, LINKED LIST)
// PHỤ TRÁCH: NGUYỄN BÁ LINH (TRƯỞNG NHÓM - MSSV: 044207007737)
// NỘI DUNG: Mô hình dữ liệu Thí sinh (Candidate)
// ============================================================================

class Candidate {
private:
    std::string sbd;       // Mã dự thi / Số báo danh (duy nhất)
    std::string hoTen;     // Họ và tên thí sinh
    std::string gioiTinh;  // Giới tính (Nam / Nữ)
    std::string ngaySinh;  // Ngày sinh (dd/mm/yyyy)
    std::string queQuan;   // Quê quán / Nơi sinh

public:
    // Constructors
    Candidate();
    Candidate(const std::string &sbd, const std::string &hoTen,
              const std::string &gioiTinh, const std::string &ngaySinh,
              const std::string &queQuan);

    // Getters
    std::string getSBD() const;
    std::string getHoTen() const;
    std::string getGioiTinh() const;
    std::string getNgaySinh() const;
    std::string getQueQuan() const;

    // Setters
    void setSBD(const std::string &sbd);
    void setHoTen(const std::string &hoTen);
    void setGioiTinh(const std::string &gioiTinh);
    void setNgaySinh(const std::string &ngaySinh);
    void setQueQuan(const std::string &queQuan);

    // Phương thức nghiệp vụ phục vụ Bảng băm & Sắp xếp
    std::string getFirstName() const;         // Trích xuất Tên (từ cuối cùng trong họ tên, ví dụ: "Linh")
    char getFirstLetterOfName() const;       // Lấy chữ cái đầu tiên của tên (A-Z) để băm bảng tra

    // Hiển thị thông tin thí sinh
    void displayRow() const;                 // In dạng dòng trong bảng
};
