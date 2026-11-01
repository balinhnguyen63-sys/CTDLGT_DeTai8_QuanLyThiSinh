#pragma once
#include "LinkedList.h"
#include "HashTable.h"
#include <string>

// ============================================================================
// DỰ ÁN CTDL&GT: ĐỀ TÀI SỐ 8 - QUẢN LÝ DANH SÁCH THÍ SINH
// PHỤ TRÁCH: ĐÀO QUANG THẮNG (MSSV THÀNH VIÊN NHÓM 4)
// NỘI DUNG: Đọc dữ liệu từ file input.txt và ghi dữ liệu ra file TXT
// ============================================================================

class Utils {
public:
    // Đọc danh sách thí sinh từ file TXT vào LinkedList và HashTable
    static bool loadFromFile(const std::string &filename, LinkedList &list, HashTable &table);

    // Ghi toàn bộ danh sách thí sinh từ LinkedList ra file TXT
    static bool saveToFile(const std::string &filename, const LinkedList &list);
};
