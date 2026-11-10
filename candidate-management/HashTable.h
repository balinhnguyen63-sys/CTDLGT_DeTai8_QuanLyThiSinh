#pragma once
#include "LinkedList.h"
#include <string>

// ============================================================================
// DỰ ÁN CTDL&GT: ĐỀ TÀI SỐ 8 - QUẢN LÝ DANH SÁCH THÍ SINH
// PHỤ TRÁCH: NGUYỄN BÁ LINH (TRƯỞNG NHÓM - MSSV: 044207007737)
// NỘI DUNG: Cấu trúc Bảng băm dạng bảng tra 26 nhóm chữ cái (A-Z)
// ============================================================================

class HashTable {
public:
    static const int TABLE_SIZE = 26; // 26 chữ cái tiếng Anh từ 'A' đến 'Z'

private:
    LinkedList buckets[TABLE_SIZE];   // Mảng 26 danh sách liên kết (chaining / bảng tra)

public:
    HashTable();
    ~HashTable();

    // Hàm băm: chuyển chữ cái đầu tiên của Tên thành chỉ số bucket (0 -> 25)
    int hashFunction(char firstLetter) const;

    // Chèn thí sinh vào đúng bucket tương ứng với chữ cái đầu của tên
    void insert(const Candidate &c);

    // Tra cứu thí sinh theo Số Báo Danh (tìm trên các bucket)
    Node* searchBySBD(const std::string &sbd) const;

    // Tra cứu thí sinh theo Tên (tận dụng bảng tra O(1) để đến ngay bucket)
    void searchByName(const std::string &name) const;

    // Xóa thí sinh khỏi bảng băm
    bool remove(const std::string &sbd, char firstLetter);

    // Hiển thị toàn bộ bảng băm theo từng nhóm chữ cái A-Z
    void displayAll() const;

    // Hiển thị một bucket cụ thể
    void displayBucket(int index) const;

    // Lấy tham chiếu đến một bucket (phục vụ phân phòng thi)
    const LinkedList& getBucket(int index) const;

    // Lấy tham chiếu có thể thay đổi đến một bucket (phục vụ sắp xếp bucket)
    LinkedList& getBucket(int index);

    // Xóa toàn bộ dữ liệu bảng băm
    void clear();
};
