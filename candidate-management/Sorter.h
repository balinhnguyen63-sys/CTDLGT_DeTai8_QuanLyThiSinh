#pragma once
#include "LinkedList.h"

// ============================================================================
// DỰ ÁN CTDL&GT: ĐỀ TÀI SỐ 8 - QUẢN LÝ DANH SÁCH THÍ SINH
// PHỤ TRÁCH: NGUYỄN HỮU CƯỜNG (MSSV THÀNH VIÊN NHÓM 4)
// NỘI DUNG: Sắp xếp danh sách thí sinh theo thứ tự tên tăng dần (A-Z)
// ============================================================================

class Sorter {
public:
    // Thuật toán sắp xếp danh sách liên kết theo Tên tăng dần A-Z
    // (Nếu trùng Tên thì so sánh tiếp Họ và Tên đệm)
    static void sortByNameAZ(LinkedList &list);
};
