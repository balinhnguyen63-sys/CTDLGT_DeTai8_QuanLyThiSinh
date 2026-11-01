#include "RoomAllocator.h"
#include <iostream>
#include <vector>

// ============================================================================
// DỰ ÁN CTDL&GT: ĐỀ TÀI SỐ 8 - QUẢN LÝ DANH SÁCH THÍ SINH
// GIẢNG VIÊN HƯỚNG DẪN: ThS. BÙI VĂN THƯỢNG - LỚP: 012012400212 - NHÓM 4
// PHỤ TRÁCH THỰC HIỆN: PHẠM KHÁNH HƯNG
// NHIỆM VỤ: Phân chia danh sách thí sinh vào n phòng thi
// ĐẶC ĐIỂM: Xác suất tên trùng chữ cái đầu trong cùng 1 phòng là nhỏ nhất
// KIẾN TRÚC ÁP DỤNG: Chương 4 (Kỹ thuật Round-Robin) & Chương 6 (Bảng băm A-Z)
// ============================================================================

void RoomAllocator::allocateRooms(const LinkedList &list, const HashTable &table, int numRooms) {
    // ------------------------------------------------------------------------
    // KHAI BÁO CÁC BIẾN VÀ CẤU TRÚC PHÒNG THI (ĐÃ THIẾT KẾ SẴN CHO HƯNG):
    // ------------------------------------------------------------------------
    int totalCandidates = list.getCount();
    Node* p = nullptr;
    int currentRoom = 0; // Chỉ số phòng xoay vòng (Round-Robin: 0 -> numRooms - 1)

    // ------------------------------------------------------------------------
    // HƯỚNG DẪN THỰC HIỆN TỪNG BƯỚC CHO PHẠM KHÁNH HƯNG:
    // ------------------------------------------------------------------------
    // YÊU CẦU ĐỀ BÀI: Phân thí sinh vào n phòng thi sao cho xác suất trùng chữ cái đầu là ít nhất.
    // Ý TƯỞNG THUẬT TOÁN ĐỘT PHÁ TẬN DỤNG BẢNG BĂM:
    // - Bảng băm (HashTable) đã gom nhóm tất cả thí sinh có cùng chữ cái đầu vào từng bucket (A-Z).
    // - Do đó, với mỗi bucket (chữ cái), ta rải đều lần lượt từng thí sinh vào các phòng khác nhau
    //   theo cơ chế xoay vòng Round-Robin: phòng 0, phòng 1, ..., phòng n-1 rồi quay lại 0.
    // - Nhờ vậy, KHÔNG CÓ phòng nào bị dồn cục nhiều thí sinh có cùng chữ cái đầu -> Xác suất trùng là NHỎ NHẤT!
    //
    // BƯỚC 1: Kiểm tra tính hợp lệ của tham số đầu vào:
    //         if (numRooms <= 0) {
    //             std::cout << "[!] So luong phong thi phai lon hon 0!\n";
    //             return;
    //         }
    //         if (list.isEmpty()) {
    //             std::cout << "[!] Danh sach thi sinh hien dang rong, khong the phan phong!\n";
    //             return;
    //         }
    //
    // BƯỚC 2: Khởi tạo mảng n phòng thi (mỗi phòng thi là 1 LinkedList):
    //         std::vector<LinkedList> rooms(numRooms);
    //
    // BƯỚC 3: Duyệt qua 26 bucket của bảng băm (từ index = 0 đến 25):
    //         for (int i = 0; i < HashTable::TABLE_SIZE; ++i) {
    //             const LinkedList& bucket = table.getBucket(i);
    //             p = bucket.getHead();
    //             while (p != nullptr) {
    //                 // Thêm thí sinh vào phòng hiện tại:
    //                 rooms[currentRoom].insertTail(p->data);
    //                 
    //                 // Xoay vòng sang phòng kế tiếp:
    //                 currentRoom = (currentRoom + 1) % numRooms;
    //                 
    //                 p = p->next;
    //             }
    //         }
    //
    // BƯỚC 4: Hiển thị danh sách thí sinh từng phòng ra màn hình:
    //         std::cout << "\n=======================================================================\n";
    //         std::cout << "        KET QUA PHAN CHIA THI SINH VAO " << numRooms << " PHONG THI (TOI UU XAC SUAT)        \n";
    //         std::cout << "=======================================================================\n";
    //         for (int r = 0; r < numRooms; ++r) {
    //             std::cout << "\n>>> [PHONG THI SO " << (r + 1) << "] (Tong: " << rooms[r].getCount() << " thi sinh):\n";
    //             rooms[r].display();
    //         }
    // ------------------------------------------------------------------------
    // GỢI Ý TRẢ LỜI VẤN ĐÁP CHO HƯNG (BƯỚC 8):
    // - Câu hỏi: "Giải thuật của em tại sao lại tối ưu được xác suất trùng chữ cái đầu?"
    // - Trả lời: "Dạ thưa Thầy, em kết hợp giữa Bảng băm (Chương 6) và cơ chế Hàng đợi xoay vòng
    //   Round-Robin (Chương 4). Vì các thí sinh cùng chữ cái đầu được nhóm trong 1 bucket, khi rải
    //   đều lần lượt vào các phòng khác nhau theo chu kỳ mod n, số lượng thí sinh trùng chữ cái đầu
    //   giữa các phòng chỉ chênh lệch tối đa 1 người, đảm bảo tính công bằng và phân tán tối đa."
    // ------------------------------------------------------------------------

    // THÔNG BÁO TẠM THỜI KHI THÀNH VIÊN ĐANG VIẾT CODE:
    std::cout << "\n[!] Thong bao tu he thong: Chuc nang 'Phan vao n phong thi toi uu xac suat'\n";
    std::cout << "    dang duoc thanh vien [Pham Khanh Hung] hoan thien theo huong dan trong RoomAllocator.cpp.\n";
    std::cout << "    (Thuat toan Round-Robin qua 26 bucket da duoc huong dan chi tiet).\n";
}
