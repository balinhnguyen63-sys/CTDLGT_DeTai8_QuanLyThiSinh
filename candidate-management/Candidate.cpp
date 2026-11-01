#include "Candidate.h"
#include <cctype>

// ============================================================================
// DỰ ÁN CTDL&GT: ĐỀ TÀI SỐ 8 - QUẢN LÝ DANH SÁCH THÍ SINH
// PHỤ TRÁCH: NGUYỄN BÁ LINH (TRƯỞNG NHÓM - MSSV: 044207007737)
// NỘI DUNG: Cài đặt các phương thức của lớp Candidate
// ============================================================================

Candidate::Candidate() : sbd(""), hoTen(""), gioiTinh(""), ngaySinh(""), queQuan("") {}

Candidate::Candidate(const std::string &sbd, const std::string &hoTen,
                     const std::string &gioiTinh, const std::string &ngaySinh,
                     const std::string &queQuan)
    : sbd(sbd), hoTen(hoTen), gioiTinh(gioiTinh), ngaySinh(ngaySinh), queQuan(queQuan) {}

std::string Candidate::getSBD() const { return sbd; }
std::string Candidate::getHoTen() const { return hoTen; }
std::string Candidate::getGioiTinh() const { return gioiTinh; }
std::string Candidate::getNgaySinh() const { return ngaySinh; }
std::string Candidate::getQueQuan() const { return queQuan; }

void Candidate::setSBD(const std::string &sbd) { this->sbd = sbd; }
void Candidate::setHoTen(const std::string &hoTen) { this->hoTen = hoTen; }
void Candidate::setGioiTinh(const std::string &gioiTinh) { this->gioiTinh = gioiTinh; }
void Candidate::setNgaySinh(const std::string &ngaySinh) { this->ngaySinh = ngaySinh; }
void Candidate::setQueQuan(const std::string &queQuan) { this->queQuan = queQuan; }

// Trích xuất từ cuối cùng trong họ tên làm "Tên" (phù hợp văn hóa đặt tên Việt Nam)
std::string Candidate::getFirstName() const {
    if (hoTen.empty()) return "";
    size_t lastSpace = hoTen.find_last_of(" \t");
    if (lastSpace == std::string::npos) {
        return hoTen;
    }
    return hoTen.substr(lastSpace + 1);
}

// Lấy ký tự đầu tiên của Tên và chuyển thành in hoa (A-Z) để làm khóa băm bảng tra
char Candidate::getFirstLetterOfName() const {
    std::string fn = getFirstName();
    if (fn.empty()) return 'A';
    char firstChar = std::toupper(static_cast<unsigned char>(fn[0]));
    if (firstChar >= 'A' && firstChar <= 'Z') {
        return firstChar;
    }
    return 'A'; // Ký tự mặc định nếu có dấu đặc biệt
}

// In một dòng trong bảng danh sách thí sinh
void Candidate::displayRow() const {
    std::cout << "| " << std::left << std::setw(8) << sbd
              << "| " << std::left << std::setw(22) << hoTen
              << "| " << std::left << std::setw(8) << gioiTinh
              << "| " << std::left << std::setw(12) << ngaySinh
              << "| " << std::left << std::setw(20) << queQuan
              << " |\n";
}
