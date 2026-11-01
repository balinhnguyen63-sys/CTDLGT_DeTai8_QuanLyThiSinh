#ifndef THISINH_H
#define THISINH_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cctype>

struct ThiSinh {
    std::string maDuThi;  // Ví dụ: SBD001, UTH101
    std::string hoTen;    // Họ và tên đầy đủ, ví dụ: Nguyễn Bá Linh
    std::string gioiTinh; // Nam hoặc Nữ
    std::string ngaySinh; // DD/MM/YYYY
    std::string queQuan;  // Ví dụ: TP. Hồ Chí Minh, Hà Nội

    // Constructor mặc định
    ThiSinh() : maDuThi(""), hoTen(""), gioiTinh("Nam"), ngaySinh(""), queQuan("") {}

    // Constructor có tham số
    ThiSinh(std::string ma, std::string ten, std::string gt, std::string ns, std::string qq)
        : maDuThi(ma), hoTen(ten), gioiTinh(gt), ngaySinh(ns), queQuan(qq) {}

    // Lấy tên (từ cuối cùng trong họ tên)
    std::string getTen() const {
        if (hoTen.empty()) return "";
        std::stringstream ss(hoTen);
        std::string word, lastWord;
        while (ss >> word) {
            lastWord = word;
        }
        return lastWord;
    }

    // Lấy họ và tên đệm (phần trước từ cuối cùng)
    std::string getHoDem() const {
        if (hoTen.empty()) return "";
        std::stringstream ss(hoTen);
        std::vector<std::string> words;
        std::string word;
        while (ss >> word) {
            words.push_back(word);
        }
        if (words.size() <= 1) return "";
        std::string hodem = "";
        for (size_t i = 0; i < words.size() - 1; ++i) {
            hodem += words[i] + (i + 2 < words.size() ? " " : "");
        }
        return hodem;
    }

    // Chuẩn hóa ký tự đầu của Tên thành ký tự Latin hoa A-Z (xử lý cả tiếng Việt có dấu)
    char getInitialLetter() const {
        std::string ten = getTen();
        if (ten.empty()) return 'Z';

        unsigned char c0 = static_cast<unsigned char>(ten[0]);
        if (c0 >= 'a' && c0 <= 'z') return static_cast<char>(toupper(c0));
        if (c0 >= 'A' && c0 <= 'Z') return static_cast<char>(c0);

        // Xử lý các ký tự UTF-8 tiếng Việt phổ biến (2 byte: 0xC3, 0xC4, 0xC5, 0xE1...)
        if (ten.size() >= 2) {
            unsigned char c1 = static_cast<unsigned char>(ten[1]);
            // Đ, đ (UTF-8: C4 90, C4 91)
            if (c0 == 0xC4 && (c1 == 0x90 || c1 == 0x91)) return 'D';
            // Â, Ă, Á, À, Ả, Ã, Ạ (C3 80..85, C4 82, C4 83...)
            if (c0 == 0xC3 && (c1 >= 0x80 && c1 <= 0x85)) return 'A';
            if (c0 == 0xC3 && (c1 >= 0xA0 && c1 <= 0xA5)) return 'A';
            // Ê, É, È, Ẻ, Ẽ, Ẹ (C3 88..8B, C3 A8..AB...)
            if (c0 == 0xC3 && (c1 >= 0x88 && c1 <= 0x8B)) return 'E';
            if (c0 == 0xC3 && (c1 >= 0xA8 && c1 <= 0xAB)) return 'E';
            // Í, Ì, Ỉ, Ĩ, Ị (C3 8C..8F, C3 AC..AF...)
            if (c0 == 0xC3 && (c1 >= 0x8C && c1 <= 0x8F)) return 'I';
            if (c0 == 0xC3 && (c1 >= 0xAC && c1 <= 0xAF)) return 'I';
            // Ô, Ơ, Ó, Ò, Ỏ, Õ, Ọ (C3 92..96, C3 B2..B6...)
            if (c0 == 0xC3 && (c1 >= 0x92 && c1 <= 0x96)) return 'O';
            if (c0 == 0xC3 && (c1 >= 0xB2 && c1 <= 0xB6)) return 'O';
            // Ư, Ú, Ù, Ủ, Ũ, U (C3 99..9C, C3 B9..BC...)
            if (c0 == 0xC3 && (c1 >= 0x99 && c1 <= 0x9C)) return 'U';
            if (c0 == 0xC3 && (c1 >= 0xB9 && c1 <= 0xBC)) return 'U';
            // Ý, Ỳ, Ỷ, Ỹ, Ỵ
            if (c0 == 0xC3 && (c1 == 0x9D || c1 == 0xBD)) return 'Y';
        }

        return 'A'; // fallback
    }

    // Chuyển đối tượng sang dòng văn bản để lưu file TXT
    std::string toFileLine() const {
        return maDuThi + "|" + hoTen + "|" + gioiTinh + "|" + ngaySinh + "|" + queQuan;
    }

    // Khởi tạo từ dòng văn bản đọc từ file TXT
    static bool fromFileLine(const std::string& line, ThiSinh& ts) {
        if (line.empty()) return false;
        std::stringstream ss(line);
        std::string ma, ten, gt, ns, qq;
        if (std::getline(ss, ma, '|') &&
            std::getline(ss, ten, '|') &&
            std::getline(ss, gt, '|') &&
            std::getline(ss, ns, '|') &&
            std::getline(ss, qq)) {
            ts = ThiSinh(ma, ten, gt, ns, qq);
            return true;
        }
        return false;
    }
};

#endif // THISINH_H
