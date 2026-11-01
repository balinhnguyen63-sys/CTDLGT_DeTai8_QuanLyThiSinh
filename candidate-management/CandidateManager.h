#pragma once
#include "LinkedList.h"
#include "HashTable.h"
#include <string>

// ============================================================================
// DỰ ÁN CTDL&GT: ĐỀ TÀI SỐ 8 - QUẢN LÝ DANH SÁCH THÍ SINH
// PHỤ TRÁCH CHÍNH: NGUYỄN BÁ LINH (Kiến trúc hệ thống & Menu điều khiển)
// PHỐI HỢP CÙNG: HOÀNG THẾ ANH & TRẦN NHẬT ANH
// ============================================================================

class CandidateManager {
private:
    LinkedList candidateList; // Danh sách liên kết đơn lưu toàn bộ thí sinh
    HashTable hashTable;      // Bảng băm 26 bucket (A-Z) tra cứu nhanh theo tên

    // Giao diện menu và luồng điều khiển (Nguyễn Bá Linh hoàn thiện)
    void showMenu() const;
    void initSampleData();

public:
    CandidateManager();
    ~CandidateManager();

    // ========================================================================
    // PHẦN VIỆC CỦA HOÀNG THẾ ANH:
    // Thêm mới thí sinh (kiểm tra trùng SBD) & Cập nhật thông tin thí sinh
    // ========================================================================
    bool addCandidate();
    bool updateCandidate();

    // ========================================================================
    // PHẦN VIỆC CỦA TRẦN NHẬT ANH:
    // Tra cứu thí sinh (theo SBD & theo Tên qua Bảng băm) & Xóa thí sinh
    // ========================================================================
    void searchBySBD();
    void searchByName();
    bool deleteCandidate();

    // ========================================================================
    // CÁC CHỨC NĂNG GỌI ĐẾN MODULE CỦA THÀNH VIÊN KHÁC
    // ========================================================================
    void displayAll() const;          // Xem toàn bộ danh sách (Nguyễn Bá Linh)
    void displayHashTable() const;    // Xem bảng băm 26 bucket A-Z (Nguyễn Bá Linh)
    void sortCandidates();            // Gọi Sorter của Nguyễn Hữu Cường
    void allocateExamRooms();         // Gọi RoomAllocator của Phạm Khánh Hưng
    void loadData();                  // Gọi Utils của Đào Quang Thắng
    void saveData();                  // Gọi Utils của Đào Quang Thắng

    // Vòng lặp chạy ứng dụng chính
    void run();
};
