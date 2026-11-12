#include "Candidate.h"
#include <cctype>

using namespace std;

namespace {
// Cat khoang trang hai dau chuoi
string trim(const string &s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    if (start == string::npos) return "";
    size_t end = s.find_last_not_of(" \t\r\n");
    return s.substr(start, end - start + 1);
}

// Giai ma codepoint UTF-8 dau tien cua chuoi
bool decodeFirstCodepoint(const string &s, unsigned int &cp) {
    if (s.empty()) return false;
    unsigned char c0 = (unsigned char)s[0];
    if (c0 < 0x80) {
        cp = c0;
        return true;
    }
    if ((c0 & 0xE0) == 0xC0 && s.size() >= 2) {
        cp = ((c0 & 0x1F) << 6) | ((unsigned char)s[1] & 0x3F);
        return true;
    }
    if ((c0 & 0xF0) == 0xE0 && s.size() >= 3) {
        cp = ((c0 & 0x0F) << 12) | (((unsigned char)s[1] & 0x3F) << 6)
             | ((unsigned char)s[2] & 0x3F);
        return true;
    }
    if ((c0 & 0xF8) == 0xF0 && s.size() >= 4) {
        cp = ((c0 & 0x07) << 18) | (((unsigned char)s[1] & 0x3F) << 12)
             | (((unsigned char)s[2] & 0x3F) << 6) | ((unsigned char)s[3] & 0x3F);
        return true;
    }
    return false;
}

// Quy doi codepoint tieng Viet (UTF-8) ve chu cai Latin co ban A-Z
char mapCodepointToLetter(unsigned int cp) {
    if (cp >= 'a' && cp <= 'z') return (char)(cp - 'a' + 'A');
    if (cp >= 'A' && cp <= 'Z') return (char)cp;
    if ((cp >= 0x00C0 && cp <= 0x00C5) || (cp >= 0x00E0 && cp <= 0x00E5) ||
        cp == 0x0102 || cp == 0x0103 || cp == 0x00C2 || cp == 0x00E2 ||
        (cp >= 0x1EA0 && cp <= 0x1EB7)) return 'A';              // À Á Â Ã Ă Ạ...
    if (cp == 0x0110 || cp == 0x0111) return 'D';                 // Đ / đ
    if ((cp >= 0x00C8 && cp <= 0x00CB) || (cp >= 0x00E8 && cp <= 0x00EB) ||
        (cp >= 0x1EB8 && cp <= 0x1EC7)) return 'E';              // È É Ê Ẹ...
    if ((cp >= 0x00CC && cp <= 0x00CF) || (cp >= 0x00EC && cp <= 0x00EF) ||
        (cp >= 0x1EC8 && cp <= 0x1ECB)) return 'I';              // Ì Í Î Ị...
    if ((cp >= 0x00D2 && cp <= 0x00D6) || (cp >= 0x00F2 && cp <= 0x00F6) ||
        cp == 0x01A0 || cp == 0x01A1 ||
        (cp >= 0x1ECC && cp <= 0x1EE3)) return 'O';              // Ò Ó Ô Ơ Ọ...
    if ((cp >= 0x00D9 && cp <= 0x00DA) || (cp >= 0x00F9 && cp <= 0x00FA) ||
        cp == 0x01AF || cp == 0x01B0 ||
        (cp >= 0x1EE4 && cp <= 0x1EF1)) return 'U';              // Ù Ú Ư Ụ...
    if (cp == 0x00DD || cp == 0x00FD || (cp >= 0x1EF2 && cp <= 0x1EF9)) return 'Y'; // Ý...
    return 0;
}
} // namespace

// Nguyen Ba Linh: Cai dat cac phuong thuc cua lop Candidate

Candidate::Candidate() : sbd(""), hoTen(""), gioiTinh(""), ngaySinh(""), queQuan("") {}

Candidate::Candidate(const string &sbd, const string &hoTen,
                     const string &gioiTinh, const string &ngaySinh,
                     const string &queQuan)
    : sbd(sbd), hoTen(hoTen), gioiTinh(gioiTinh), ngaySinh(ngaySinh), queQuan(queQuan) {}

string Candidate::getSBD() const { return sbd; }
string Candidate::getHoTen() const { return hoTen; }
string Candidate::getGioiTinh() const { return gioiTinh; }
string Candidate::getNgaySinh() const { return ngaySinh; }
string Candidate::getQueQuan() const { return queQuan; }

void Candidate::setSBD(const string &sbd) { this->sbd = sbd; }
void Candidate::setHoTen(const string &hoTen) { this->hoTen = hoTen; }
void Candidate::setGioiTinh(const string &gioiTinh) { this->gioiTinh = gioiTinh; }
void Candidate::setNgaySinh(const string &ngaySinh) { this->ngaySinh = ngaySinh; }
void Candidate::setQueQuan(const string &queQuan) { this->queQuan = queQuan; }

// Trich xuat tu cuoi cung trong ho ten lam Ten
string Candidate::getFirstName() const {
    string name = trim(hoTen);
    if (name.empty()) return "";

    size_t lastSpace = name.find_last_of(" \t");
    if (lastSpace == string::npos) {
        return name;
    }
    return trim(name.substr(lastSpace + 1));
}

// Lay chu cai dau tien cua Ten (A-Z) de bam vao bang tra
char Candidate::getFirstLetterOfName() const {
    string fn = getFirstName();
    if (fn.empty()) return 'A';

    unsigned int cp = 0;
    if (!decodeFirstCodepoint(fn, cp)) return 'A';

    char letter = mapCodepointToLetter(cp);
    return (letter != 0) ? letter : 'A';
}

// In mot dong trong bang danh sach thi sinh
void Candidate::displayRow() const {
    cout << "| " << left << setw(8) << sbd
         << "| " << left << setw(22) << hoTen
         << "| " << left << setw(8) << gioiTinh
         << "| " << left << setw(12) << ngaySinh
         << "| " << left << setw(20) << queQuan
         << " |\n";
}
