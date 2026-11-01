#include "HashTable.h"
#include <iostream>
#include <cctype>

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
// Chỉ cần băm chữ cái đầu của tên -> truy cập trực tiếp bucket chứa tên đó!
void HashTable::searchByName(const std::string &name) const {
    if (name.empty()) {
        std::cout << "[!] Ten can tim khong hop le!\n";
        return;
    }

    char firstChar = name[0];
    int index = hashFunction(firstChar);

    std::cout << "\n=== KET QUA TRA CUU THEO TEN: \"" << name << "\" (Tra cuu tai Nhom '" << (char)('A' + index) << "') ===\n";

    Node* p = buckets[index].getHead();
    int count = 0;
    while (p != nullptr) {
        // So sánh tên gọi hoặc họ tên có chứa chuỗi tìm kiếm
        if (p->data.getFirstName() == name || p->data.getHoTen().find(name) != std::string::npos) {
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
        std::cout << "--> Khong tim thay thi sinh nao co ten \"" << name << "\".\n";
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
        return buckets[0];
    }
    return buckets[index];
}

void HashTable::clear() {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        buckets[i].clear();
    }
}
