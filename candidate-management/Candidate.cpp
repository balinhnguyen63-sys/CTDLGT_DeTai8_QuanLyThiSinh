#include "Candidate.h"
#include <cctype>

namespace {
// Cắt khoảng trắng hai đầu chuỗi
std::string trim(const std::string &s) {
    const char *ws = " \t\r\n";
    std::size_t start = s.find_first_not_of(ws);
    if (start == std::string::npos) return "";
    std::size_t end = s.find_last_not_of(ws);
    return s.substr(start, end - start + 1);
}

// Giải mã codepoint UTF-8 đầu tiên của chuỗi
bool decodeFirstCodepoint(const std::string &s, unsigned int &cp) {
    if (s.empty()) return false;
    unsigned char c0 = static_cast<unsigned char>(s[0]);
    if (c0 < 0x80) { cp = c0; return true; }
    if ((c0 & 0xE0) == 0xC0 && s.size() >= 2) {
        cp = ((c0 & 0x1F) << 6) | (static_cast<unsigned char>(s[1]) & 0x3F);
        return true;
    }
    if ((c0 & 0xF0) == 0xE0 && s.size() >= 3) {
        cp = ((c0 & 0x0F) << 12) | ((static_cast<unsigned char>(s[1]) & 0x3F) << 6)
             | (static_cast<unsigned char>(s[2]) & 0x3F);
        return true;
    }
    if ((c0 & 0xF8) == 0xF0 && s.size() >= 4) {
        cp = ((c0 & 0x07) << 18) | ((static_cast<unsigned char>(s[1]) & 0x3F) << 12)
             | ((static_cast<unsigned char>(s[2]) & 0x3F) << 6)
             | (static_cast<unsigned char>(s[3]) & 0x3F);
        return true;
    }
    return false;
}

// Quy đổi codepoint tiếng Việt (UTF-8) về chữ cái Latin cơ sở A-Z
char mapCodepointToLetter(unsigned int cp) {
    if (cp >= 'a' && cp <= 'z') return static_cast<char>(cp - 'a' + 'A');
    if (cp >= 'A' && cp <= 'Z') return static_cast<char>(cp);
    if ((cp >= 0x00C0 && cp <= 0x00C5) || (cp >= 0x00E0 && cp <= 0x00E5) ||
        cp == 0x0102 || cp == 0x0103 || cp == 0x00C2 || cp == 0x00E2 ||
        (cp >= 0x1EA0 && cp <= 0x1EB7)) return 'A';          // ÀÁÂÃĂÂẠ...
    if (cp == 0x0110 || cp == 0x0111) return 'D';             // Đ / đ
    if ((cp >= 0x00C8 && cp <= 0x00CB) || (cp >= 0x00E8 && cp <= 0x00EB) ||
        (cp >= 0x1EB8 && cp <= 0x1EC7)) return 'E';           // ÈÉÊÊ...
    if ((cp >= 0x00CC && cp <= 0x00CF) || (cp >= 0x00EC && cp <= 0x00EF) ||
        (cp >= 0x1EC8 && cp <= 0x1ECB)) return 'I';           // ÌÍÎÏ...
    if ((cp >= 0x00D2 && cp <= 0x00D6) || (cp >= 0x00F2 && cp <= 0x00F6) ||
        cp == 0x00D4 || cp == 0x00F4 || cp == 0x01A0 || cp == 0x01A1 ||
        (cp >= 0x1ECC && cp <= 0x1EE3)) return 'O';           // ÒÓÔÕƠỌ...
    if ((cp >= 0x00D9 && cp <= 0x00DA) || (cp >= 0x00F9 && cp <= 0x00FA) ||
        cp == 0x01AF || cp == 0x01B0 || (cp >= 0x1EE4 && cp <= 0x1EF1)) return 'U'; // ÙÚÛƯỤ...
    if (cp == 0x00DD || cp == 0x00FD || (cp >= 0x1EF2 && cp <= 0x1EF9)) return 'Y'; // Ý...
    return 0;
}
} // namespace

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
    std::string name = trim(hoTen);
    if (name.empty()) return "";

    std::size_t lastSpace = name.find_last_of(" \t");
    if (lastSpace == std::string::npos) {
        return name;
    }
    return trim(name.substr(lastSpace + 1));
}

// Lấy ký tự đầu tiên của Tên và chuyển thành in hoa (A-Z) để làm khóa băm bảng tra.
// Hỗ trợ tên tiếng Việt có dấu (UTF-8): Đức, Ánh, Ơn, ấn ... đều về chữ cái gốc.
char Candidate::getFirstLetterOfName() const {
    std::string fn = getFirstName();
    if (fn.empty()) return 'A';

    unsigned int cp = 0;
    if (!decodeFirstCodepoint(fn, cp)) return 'A';

    char letter = mapCodepointToLetter(cp);
    return (letter != 0) ? letter : 'A';
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
