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

    char c = (char)toupper((unsigned char)fn[0]);
    if (c >= 'A' && c <= 'Z') return c;
    return 'A';
}

// In mot dong trong bang danh sach thi sinh
void Candidate::displayRow() const {
    cout << "| " << left << setw(13) << sbd
         << "| " << left << setw(22) << hoTen
         << "| " << left << setw(8) << gioiTinh
         << "| " << left << setw(12) << ngaySinh
         << "| " << left << setw(20) << queQuan
         << " |\n";
}
