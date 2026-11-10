#include "Sorter.h"
#include <iostream>

// ============================================================================
// DỰ ÁN CTDL&GT: ĐỀ TÀI SỐ 8 - QUẢN LÝ DANH SÁCH THÍ SINH
// GIẢNG VIÊN HƯỚNG DẪN: ThS. BÙI VĂN THƯỢNG - LỚP: 012012400212 - NHÓM 4
// PHỤ TRÁCH THỰC HIỆN: NGUYỄN HỮU CƯỜNG
// NHIỆM VỤ: Sắp xếp DSLK theo Tên tăng dần A-Z bằng Merge Sort (stable)
// ============================================================================

// Trả về true nếu thí sinh x phải đứng TRƯỚC thí sinh y MỘT CÁCH CHẶT CHẼ
static bool dungTruoc(const Candidate &x, const Candidate &y) {
    if (x.getFirstName() != y.getFirstName())
        return x.getFirstName() < y.getFirstName();
    return x.getHoTen() < y.getHoTen();
}

// Trộn 2 danh sách đã sắp xếp thành 1 danh sách
// Khi bằng nhau thì lấy nút của danh sách TRÁI (a) trước -> giữ tính stable
static Node* tron(Node* a, Node* b) {
    if (a == nullptr) return b;
    if (b == nullptr) return a;

    if (dungTruoc(b->data, a->data)) {   // chỉ lấy b khi b nhỏ hơn a hẳn
        b->next = tron(a, b->next);
        return b;
    } else {
        a->next = tron(a->next, b);
        return a;
    }
}

// Merge Sort: chia đôi danh sách, sắp xếp từng nửa, rồi trộn lại
static Node* mergeSort(Node* head) {
    if (head == nullptr || head->next == nullptr) return head;

    // Tìm giữa danh sách bằng 2 con trỏ chậm/nhanh
    Node* slow = head;
    Node* fast = head->next;
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }

    Node* nuaPhai = slow->next;
    slow->next = nullptr;                // cắt danh sách làm 2 nửa

    return tron(mergeSort(head), mergeSort(nuaPhai));
}

void Sorter::sortByNameAZ(LinkedList &list) {
    Node* head = list.getHead();

    if (head == nullptr || head->next == nullptr) {
        std::cout << "[!] Danh sach khong can sap xep (rong hoac co 1 thi sinh).\n";
        return;
    }

    list.setHead(mergeSort(head));       // gắn lại đầu danh sách sau khi sắp xếp

    std::cout << "\n[+] Da sap xep danh sach thi sinh theo Thu tu Ten tang dan (A-Z) thanh cong!\n";
    list.display();
}
