#include "RoomAllocator.h"
#include <iostream>
#include <vector>

// ============================================================================
// DỰ ÁN CTDL&GT: ĐỀ TÀI SỐ 8 - QUẢN LÝ DANH SÁCH THÍ SINH
// PHỤ TRÁCH: PHẠM KHÁNH HƯNG
// NHIỆM VỤ: Phân chia danh sách thí sinh vào n phòng thi
// ĐẶC ĐIỂM: Xác suất tên trùng chữ cái đầu trong cùng 1 phòng là nhỏ nhất
// ============================================================================

void RoomAllocator::allocateRooms(const LinkedList &list, const HashTable &table, int numRooms) {
    // ------------------------------------------------------------------------
    // KHAI BÁO CÁC BIẾN VÀ CẤU TRÚC PHÒNG THI (ĐÃ THIẾT KẾ SẴN CHO HƯNG)
    // ------------------------------------------------------------------------
    int totalCandidates = list.getCount();
    Node* p = nullptr;
    int currentRoom = 0; // Biến xoay vòng phòng thi (Round-Robin)

    // ------------------------------------------------------------------------
    // HƯỚNG DẪN THỰC HIỆN TỪNG BƯỚC CHO PHẠM KHÁNH HƯNG:
    // ------------------------------------------------------------------------
    // YÊU CẦU ĐỀ BÀI: Phân thí sinh vào n phòng thi sao cho xác suất trùng chữ cái đầu là ít nhất.
    // Ý TƯỞNG THUẬT TOÁN TỐI ƯU DỰA TRÊN BẢNG BĂM:
    // Vì bảng băm (table) đã gom nhóm tất cả các thí sinh có cùng chữ cái đầu vào từng bucket (từ 'A' đến 'Z').
    // Do đó, ta duyệt qua từng bucket của HashTable:
    // - Với mỗi nhóm chữ cái (ví dụ nhóm 'A': An, Anh...), ta rải đều lần lượt
    //   từng thí sinh vào các phòng khác nhau theo kỹ thuật Round-Robin (phòng 0, 1, 2, ..., n-1 rồi quay lại 0).
    // - Nhờ vậy, KHÔNG CÓ phòng nào bị dồn nhiều thí sinh có cùng chữ cái đầu!
    //
    // BƯỚC 1: Kiểm tra điều kiện đầu vào:
    //         if (numRooms <= 0) {
    //             std::cout << "[!] So phong thi phai lon hon 0!\n";
    //             return;
    //         }
    //         if (list.isEmpty()) {
    //             std::cout << "[!] Danh sach thi sinh rong!\n";
    //             return;
    //         }
    //
    // BƯỚC 2: Khởi tạo mảng n phòng thi (mỗi phòng là một LinkedList):
    //         std::vector<LinkedList> rooms(numRooms);
    //
    // BƯỚC 3: Duyệt qua 26 bucket của bảng băm (từ index = 0 đến 25):
    //         for (int i = 0; i < HashTable::TABLE_SIZE; ++i) {
    //             const LinkedList& bucket = table.getBucket(i);
    //             p = bucket.getHead();
    //             while (p != nullptr) {
    //                 // Đưa thí sinh vào phòng hiện tại:
    //                 rooms[currentRoom].insertTail(p->data);
    //                 
    //                 // Chuyển sang phòng tiếp theo (xoay vòng):
    //                 currentRoom = (currentRoom + 1) % numRooms;
    //                 
    //                 p = p->next;
    //             }
    //         }
    //
    // BƯỚC 4: In kết quả phân phòng ra màn hình:
    //         for (int r = 0; r < numRooms; ++r) {
    //             std::cout << "\n================= PHONG THI SO " << (r + 1) << " ================\n";
    //             rooms[r].display();
    //         }
    // ------------------------------------------------------------------------

    // THÔNG BÁO TẠM THỜI KHI THÀNH VIÊN ĐANG VIẾT CODE:
    std::cout << "\n[!] Thong bao tu he thong: Chuc nang 'Phan vao n phong thi toi uu xac suat'\n";
    std::cout << "    dang duoc thanh vien [Pham Khanh Hung] hoan thien theo huong dan trong RoomAllocator.cpp.\n";
    std::cout << "    (Thuat toan Round-Robin qua 26 bucket da duoc huong dan chi tiet).\n";
}
