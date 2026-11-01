#include "Sorter.h"
#include <iostream>

// ============================================================================
// DỰ ÁN CTDL&GT: ĐỀ TÀI SỐ 8 - QUẢN LÝ DANH SÁCH THÍ SINH
// GIẢNG VIÊN HƯỚNG DẪN: ThS. BÙI VĂN THƯỢNG - LỚP: 012012400212 - NHÓM 4
// PHỤ TRÁCH THỰC HIỆN: NGUYỄN HỮU CƯỜNG
// NHIỆM VỤ: Cài đặt giải thuật sắp xếp danh sách liên kết theo Tên tăng dần A-Z
// KIẾN TRÚC ÁP DỤNG: Chương 3 (Thuật toán Sắp xếp) & Chương 4 (Con trỏ DSLK)
// ============================================================================

void Sorter::sortByNameAZ(LinkedList &list) {
    // ------------------------------------------------------------------------
    // KHAI BÁO CÁC BIẾN VÀ CON TRỎ CẦN THIẾT (ĐÃ THIẾT KẾ SẴN CHO CƯỜNG):
    // ------------------------------------------------------------------------
    Node* head = list.getHead();
    Node* i = nullptr;
    Node* j = nullptr;
    int count = list.getCount();

    // ------------------------------------------------------------------------
    // HƯỚNG DẪN THỰC HIỆN TỪNG BƯỚC CHO NGUYỄN HỮU CƯỜNG:
    // ------------------------------------------------------------------------
    // YÊU CẦU ĐỀ TÀI: Hiển thị danh sách thí sinh theo thứ tự tên tăng dần (A-Z).
    // YÊU CẦU MÔN HỌC: Thao tác trực tiếp trên Danh sách liên kết đơn bằng con trỏ!
    //
    // BƯỚC 1: Kiểm tra danh sách rỗng hoặc chỉ có 1 phần tử (đã có thứ tự):
    //         if (head == nullptr || head->next == nullptr) {
    //             std::cout << "[!] Danh sach khong can sap xep (rong hoac co 1 thi sinh).\n";
    //             return;
    //         }
    //
    // BƯỚC 2: Sử dụng 2 vòng lặp lồng nhau duyệt con trỏ (Interchange Sort trên DSLK):
    //         for (i = head; i != nullptr; i = i->next) {
    //             for (j = i->next; j != nullptr; j = j->next) {
    //                 
    //                 // BƯỚC 3: So sánh Tên gọi (First Name) của 2 thí sinh:
    //                 // (Hàm getFirstName() đã được Linh viết sẵn trong Candidate.h)
    //                 // 
    //                 // Trường hợp 1: Tên của nút i lớn hơn Tên của nút j -> Hoán đổi:
    //                 if (i->data.getFirstName() > j->data.getFirstName()) {
    //                     Candidate temp = i->data;
    //                     i->data = j->data;
    //                     j->data = temp;
    //                 }
    //                 // Trường hợp 2: Trùng Tên (ví dụ cùng tên "Anh") -> So sánh cả Họ Tên:
    //                 else if (i->data.getFirstName() == j->data.getFirstName()) {
    //                     if (i->data.getHoTen() > j->data.getHoTen()) {
    //                         Candidate temp = i->data;
    //                         i->data = j->data;
    //                         j->data = temp;
    //                     }
    //                 }
    //             }
    //         }
    //
    // BƯỚC 4: In thông báo và gọi list.display() để xem danh sách sau khi đã sắp xếp:
    //         std::cout << "\n[+] Da sap xep danh sach thi sinh theo Thu tu Ten tang dan (A-Z) thanh cong!\n";
    //         list.display();
    // ------------------------------------------------------------------------
    // GỢI Ý TRẢ LỜI VẤN ĐÁP CHO CƯỜNG (BƯỚC 8):
    // - Câu hỏi: "Tại sao em hoán đổi data thay vì hoán đổi con trỏ next?"
    // - Trả lời: "Dạ thưa Thầy, do kiểu dữ liệu Candidate có kích thước vừa phải, việc hoán đổi
    //   data giúp mã nguồn an toàn, tránh nguy cơ đứt gãy liên kết con trỏ next trên DSLK đơn.
    //   Độ phức tạp thuật toán là O(N^2) số lần so sánh, phù hợp với quy mô danh sách phòng thi."
    // ------------------------------------------------------------------------

    // THÔNG BÁO TẠM THỜI KHI THÀNH VIÊN ĐANG VIẾT CODE:
    std::cout << "\n[!] Thong bao tu he thong: Chuc nang 'Sap xep thi sinh theo ten A-Z'\n";
    std::cout << "    dang duoc thanh vien [Nguyen Huu Cuong] hoan thien theo huong dan trong Sorter.cpp.\n";
    std::cout << "    (Cac con tro i, j va khung thuat toan da duoc khai bao san).\n";
}
