#include "Sorter.h"
#include <iostream>

void Sorter::sortByNameAZ(LinkedList &list) {
    Node* head = list.getHead();

    // Danh sách rỗng hoặc chỉ có 1 phần tử thì không cần sắp xếp
    if (head == nullptr || head->next == nullptr) {
        std::cout << "[!] Danh sach khong can sap xep (rong hoac co 1 thi sinh).\n";
        return;
    }

    // Interchange Sort trên danh sách liên kết đơn
    for (Node* i = head; i != nullptr; i = i->next) {
        for (Node* j = i->next; j != nullptr; j = j->next) {

            bool canDoiCho = false;

            if (i->data.getFirstName() > j->data.getFirstName()) {
                canDoiCho = true;                          // Tên của i lớn hơn
            } else if (i->data.getFirstName() == j->data.getFirstName()
                       && i->data.getHoTen() > j->data.getHoTen()) {
                canDoiCho = true;                          // Trùng Tên thì xét Họ tên
            }

            if (canDoiCho) {
                Candidate temp = i->data;
                i->data = j->data;
                j->data = temp;
            }
        }
    }

    std::cout << "\n[+] Da sap xep danh sach thi sinh theo Thu tu Ten tang dan (A-Z) thanh cong!\n";
    list.display();
}
