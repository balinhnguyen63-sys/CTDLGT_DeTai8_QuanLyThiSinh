#include "HashTable.h"
#include <iostream>
#include <cctype>
#include <stdexcept>
#include <sstream>

namespace {
std::string trim(const std::string &s) {
    const char *ws = " \t\r\n";
    std::size_t start = s.find_first_not_of(ws);
    if (start == std::string::npos) return "";
    std::size_t end = s.find_last_not_of(ws);
    return s.substr(start, end - start + 1);
}

std::string toLowerAscii(const std::string &s) {
    std::string result = s;
    for (char &c : result) {
        c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    }
    return result;
}

std::string normalizeSpaces(const std::string &s) {
    std::istringstream iss(s);
    std::string word, result;
    while (iss >> word) {
        if (!result.empty()) result += ' ';
        result += word;
    }
    return result;
}

bool containsWord(const std::string &text, const std::string &word) {
    std::istringstream iss(text);
    std::string token;
    while (iss >> token) {
        if (toLowerAscii(token) == word) return true;
    }
    return false;
}
} // namespace

// ============================================================================
// DỰ ÁN CTDL&GT: ĐỀ TÀI SỐ 8 - QUẢN LÝ DANH SÁCH THÍ SINH
// PHỤ TRÁCH: NGUYỄN BÁ LINH (TRƯỞNG NHÓM - MSSV: 044207007737)
// NỘI DUNG: Cài đặt các phương thức của Bảng băm HashTable
// ============================================================================

HashTable::HashTable() {}

HashTable::~HashTable() {
    clear();
}

// Hàm băm dạng bảng tra: ánh xạ ký tự chữ cái A-Z sang chỉ số mảng 0-25
int HashTable::hashFunction(char firstLetter) const {
    char c = std::toupper(static_cast<unsigned char>(firstLetter));
    if (c >= 'A' && c <= 'Z') {
        return c - 'A';
    }
    return 0; // Bucket mặc định cho các ký tự đặc biệt
}

// Thêm thí sinh vào bucket tương ứng
void HashTable::insert(const Candidate &c) {
    if (c.getSBD().empty()) return;
    // Chặn trùng SBD: quét toàn bảng để không chèn bản trùng
    for (int i = 0; i < TABLE_SIZE; ++i) {
        if (buckets[i].find(c.getSBD()) != nullptr) return;
    }
    char firstLetter = c.getFirstLetterOfName();
    int index = hashFunction(firstLetter);
    buckets[index].insertTail(c);
}

// Tìm kiếm theo SBD trên toàn bộ bảng băm
Node* HashTable::searchBySBD(const std::string &sbd) const {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        Node* found = buckets[i].find(sbd);
        if (found != nullptr) {
            return found;
        }
    }
    return nullptr;
}

// Tìm kiếm theo tên thí sinh: tận dụng tính chất bảng tra
// Chỉ cần băm chữ cái đầu của Tên -> truy cập trực tiếp bucket chứa tên đó!
// Hỗ trợ: không phân biệt hoa/thường, nhập họ tên đầy đủ, nhập 1 từ (Tên hoặc từ trong Họ).
void HashTable::searchByName(const std::string &name) const {
    std::string query = normalizeSpaces(trim(name));
    if (query.empty()) {
        std::cout << "[!] Ten can tim khong hop le!\n";
        return;
    }

    // Nếu là họ tên đầy đủ, băm theo chữ cái đầu của "Tên" (từ cuối cùng)
    std::string probeName = query;
    std::size_t lastSpace = query.find_last_of(" \t");
    if (lastSpace != std::string::npos) {
        probeName = query.substr(lastSpace + 1);
    }
    Candidate probe("", probeName, "", "", "");
    int index = hashFunction(probe.getFirstLetterOfName());

    std::string lowerQuery = toLowerAscii(query);
    bool isFullName = (lastSpace != std::string::npos);

    std::cout << "\n=== KET QUA TRA CUU THEO TEN: \"" << query
              << "\" (Tra cuu tai Nhom '" << static_cast<char>('A' + index) << "') ===\n";

    Node* p = buckets[index].getHead();
    int count = 0;
    while (p != nullptr) {
        std::string firstName = toLowerAscii(trim(p->data.getFirstName()));
        std::string fullName = toLowerAscii(normalizeSpaces(p->data.getHoTen()));

        bool match = false;
        if (isFullName) {
            match = fullName.find(lowerQuery) != std::string::npos;
        } else {
            match = (firstName == lowerQuery) || containsWord(fullName, lowerQuery);
        }

        if (match) {
            if (count == 0) {
                std::cout << "+---------+-----------------------+---------+-------------+----------------------+\n";
                std::cout << "| SBD     | Ho va Ten             | Phai    | Ngay Sinh   | Que Quan             |\n";
                std::cout << "+---------+-----------------------+---------+-------------+----------------------+\n";
            }
            p->data.displayRow();
            count++;
        }
        p = p->next;
    }

    if (count == 0) {
        std::cout << "--> Khong tim thay thi sinh nao co ten \"" << query << "\".\n";
    } else {
        std::cout << "+---------+-----------------------+---------+-------------+----------------------+\n";
        std::cout << "Tim thay " << count << " thi sinh phu hop.\n";
    }
}

// Xóa thí sinh khỏi bảng băm
bool HashTable::remove(const std::string &sbd, char firstLetter) {
    int index = hashFunction(firstLetter);
    return buckets[index].remove(sbd);
}

// Hiển thị toàn bộ bảng băm theo từng nhóm chữ cái A-Z
void HashTable::displayAll() const {
    std::cout << "\n=======================================================================\n";
    std::cout << "          BANG BAM THI SINH DANG BANG TRA (26 NHOM A - Z)              \n";
    std::cout << "=======================================================================\n";

    bool hasAny = false;
    for (int i = 0; i < TABLE_SIZE; ++i) {
        if (!buckets[i].isEmpty()) {
            hasAny = true;
            char letter = 'A' + i;
            std::cout << "\n>>> [NHOM " << letter << "] (So luong: " << buckets[i].getCount() << " thi sinh):\n";
            buckets[i].display();
        }
    }

    if (!hasAny) {
        std::cout << "  (Bang bam hien tai dang rong!)\n";
    }
}

// Hiển thị 1 bucket cụ thể
void HashTable::displayBucket(int index) const {
    if (index >= 0 && index < TABLE_SIZE) {
        char letter = 'A' + index;
        std::cout << "\n>>> Thong tin Nhom [" << letter << "]:\n";
        buckets[index].display();
    }
}

const LinkedList& HashTable::getBucket(int index) const {
    if (index < 0 || index >= TABLE_SIZE) {
        throw std::out_of_range("HashTable::getBucket: chi so bucket khong hop le");
    }
    return buckets[index];
}

void HashTable::clear() {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        buckets[i].clear();
    }
}
