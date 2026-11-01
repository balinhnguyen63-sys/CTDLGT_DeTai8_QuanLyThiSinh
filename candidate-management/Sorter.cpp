#include "Sorter.h"
#include <iostream>

// ============================================================================
// DỰ ÁN CTDL&GT: ĐỀ TÀI SỐ 8 - QUẢN LÝ DANH SÁCH THÍ SINH
// PHỤ TRÁCH: NGUYỄN HỮU CƯỜNG
// NHIỆM VỤ: Cài đặt giải thuật sắp xếp danh sách liên kết theo Tên tăng dần A-Z
// ============================================================================

void Sorter::sortByNameAZ(LinkedList &list) {
    // ------------------------------------------------------------------------
    // KHAI BÁO CÁC BIẾN VÀ CON TRỎ CẦN THIẾT (ĐÃ THIẾT KẾ SẴN CHO CƯỜNG)
    // ------------------------------------------------------------------------
    Node* head = list.getHead();
    Node* i = nullptr;
    Node* j = nullptr;
    int count = list.getCount();

    // ------------------------------------------------------------------------
    // HƯỚNG DẪN THỰC HIỆN TỪNG BƯỚC CHO NGUYỄN HỮU CƯỜNG:
    // ------------------------------------------------------------------------
    // YÊU CẦU MÔN HỌC: Sắp xếp trực tiếp trên Danh sách liên kết đơn bằng con trỏ!
    // Gợi ý: Thuật toán Interchange Sort / Selection Sort trên DSLK:
    //
    // BƯỚC 1: Kiểm tra danh sách rỗng hoặc chỉ có 1 phần tử:
    //         if (head == nullptr || head->next == nullptr) {
    //             return; // Đã có thứ tự, không cần sắp xếp
    //         }
    //
    // BƯỚC 2: Dùng 2 vòng lặp lồng nhau duyệt con trỏ:
    //         for (i = head; i != nullptr; i = i->next) {
    //             for (j = i->next; j != nullptr; j = j->next) {
    //                 
    //                 // BƯỚC 3: So sánh Tên (First Name) của 2 thí sinh:
    //                 // Lấy tên qua hàm: i->data.getFirstName() và j->data.getFirstName()
    //                 // 
    //                 // Trường hợp 1: Tên của i lớn hơn Tên của j -> Hoán đổi
    //                 // if (i->data.getFirstName() > j->data.getFirstName()) {
    //                 //     Candidate temp = i->data;
    //                 //     i->data = j->data;
    //                 //     j->data = temp;
    //                 // }
    //                 // 
    //                 // Trường hợp 2 (Mở rộng): Nếu trùng Tên -> So sánh cả Họ Tên:
    //                 // else if (i->data.getFirstName() == j->data.getFirstName()) {
    //                 //     if (i->data.getHoTen() > j->data.getHoTen()) {
    //                 //         Candidate temp = i->data;
    //                 //         i->data = j->data;
    //                 //         j->data = temp;
    //                 //     }
    //                 // }
    //             }
    //         }
    //
    // BƯỚC 4: In thông báo hoàn tất sắp xếp và gọi list.display() để xem kết quả.
    // ------------------------------------------------------------------------

    // THÔNG BÁO TẠM THỜI KHI THÀNH VIÊN ĐANG VIẾT CODE:
    std::cout << "\n[!] Thong bao tu he thong: Chuc nang 'Sap xep thi sinh theo ten A-Z'\n";
    std::cout << "    dang duoc thanh vien [Nguyen Huu Cuong] hoan thien theo huong dan trong Sorter.cpp.\n";
    std::cout << "    (Cac con tro i, j va khung thuat toan da duoc khai bao san).\n";
}
