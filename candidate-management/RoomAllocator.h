#pragma once
#include "LinkedList.h"
#include "HashTable.h"

// ============================================================================
// DỰ ÁN CTDL&GT: ĐỀ TÀI SỐ 8 - QUẢN LÝ DANH SÁCH THÍ SINH
// PHỤ TRÁCH: PHẠM KHÁNH HƯNG (MSSV THÀNH VIÊN NHÓM 4)
// NỘI DUNG: Phân danh sách thí sinh vào n phòng thi sao cho xác suất trùng chữ cái đầu là ít nhất
// ============================================================================

class RoomAllocator {
public:
    // Hàm phân chia thí sinh vào n phòng thi
    static void allocateRooms(const LinkedList &list, const HashTable &table, int numRooms);
};
