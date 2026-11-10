#pragma once
#include "LinkedList.h"
#include "HashTable.h"

// ============================================================================
// DỰ ÁN CTDL&GT: ĐỀ TÀI SỐ 8 - QUẢN LÝ DANH SÁCH THÍ SINH
// PHỤ TRÁCH: NGUYỄN HỮU CƯỜNG (THÀNH VIÊN NHÓM 4)
// NỘI DUNG: Sắp xếp danh sách thí sinh theo Tên tăng dần (A-Z)
// ============================================================================

class Sorter {
public:
    // Sắp xếp danh sách liên kết theo Tên tăng dần A-Z (Merge Sort, stable)
    static void sortByNameAZ(LinkedList &list);

    // Sắp xếp từng bucket của bảng băm theo Tên tăng dần A-Z
    static void sortBuckets(HashTable &table);
};
