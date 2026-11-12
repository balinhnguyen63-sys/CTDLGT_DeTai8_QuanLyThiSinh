#include "Sorter.h"
#include <iostream>

using namespace std;

// Nguyen Huu Cuong: Cai dat Merge Sort cho danh sach lien ket va cac bucket

// Tra ve true neu thi sinh x phai dung truoc thi sinh y
static bool dungTruoc(const Candidate &x, const Candidate &y) {
    if (x.getFirstName() != y.getFirstName())
        return x.getFirstName() < y.getFirstName();
    return x.getHoTen() < y.getHoTen();
}

// Tron 2 danh sach da sap xep thanh 1 danh sach
static Node* tron(Node* a, Node* b) {
    if (a == nullptr) return b;
    if (b == nullptr) return a;

    if (dungTruoc(b->data, a->data)) {
        b->next = tron(a, b->next);
        return b;
    } else {
        a->next = tron(a->next, b);
        return a;
    }
}

// Merge Sort: chia doi danh sach, sap xep tung nua, roi tron lai
static Node* mergeSort(Node* head) {
    if (head == nullptr || head->next == nullptr) return head;

    // Tim giua danh sach bang 2 con tro cham va nhanh
    Node* slow = head;
    Node* fast = head->next;
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }

    Node* nuaPhai = slow->next;
    slow->next = nullptr; // Cat danh sach lam 2 nua

    return tron(mergeSort(head), mergeSort(nuaPhai));
}

void Sorter::sortByNameAZ(LinkedList &list) {
    Node* head = list.getHead();

    if (head == nullptr || head->next == nullptr) {
        cout << "[!] Danh sach khong can sap xep (rong hoac co 1 thi sinh).\n";
        return;
    }

    list.setHead(mergeSort(head));

    cout << "\n[+] Da sap xep danh sach thi sinh theo Thu tu Ten tang dan (A-Z) thanh cong!\n";
    list.display();
}

// Sap xep tung bucket cua bang bam
void Sorter::sortBuckets(HashTable &table) {
    for (int i = 0; i < HashTable::TABLE_SIZE; ++i) {
        LinkedList &bucket = table.getBucket(i);
        if (bucket.getHead() != nullptr && bucket.getHead()->next != nullptr) {
            bucket.setHead(mergeSort(bucket.getHead()));
        }
    }
    cout << "[+] Da sap xep cac bucket cua Bang bam theo Ten tang dan (A-Z) thanh cong!\n";
}