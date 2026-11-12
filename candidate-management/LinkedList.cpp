#include "LinkedList.h"
#include <iostream>

// Nguyen Ba Linh: Cai dat cac phuong thuc cua Node & LinkedList

Node::Node(const Candidate &c) : data(c), next(nullptr) {}

LinkedList::LinkedList() : head(nullptr), tail(nullptr), count(0) {}

LinkedList::~LinkedList() {
    clear();
}

LinkedList::LinkedList(const LinkedList &other) : head(nullptr), tail(nullptr), count(0) {
    Node* p = other.head;
    while (p != nullptr) {
        insertTail(p->data);
        p = p->next;
    }
}

LinkedList& LinkedList::operator=(const LinkedList &other) {
    if (this != &other) {
        clear();
        Node* p = other.head;
        while (p != nullptr) {
            insertTail(p->data);
            p = p->next;
        }
    }
    return *this;
}

Node* LinkedList::getHead() const { return head; }
Node* LinkedList::getTail() const { return tail; }

void LinkedList::setHead(Node* newHead) {
    head = newHead;
    // Cập nhật lại tail và count
    tail = head;
    count = 0;
    if (tail != nullptr) {
        count = 1;
        while (tail->next != nullptr) {
            tail = tail->next;
            count++;
        }
    }
}

int LinkedList::getCount() const { return count; }
bool LinkedList::isEmpty() const { return head == nullptr; }

// Chèn thí sinh vào cuối danh sách liên kết - O(1)
void LinkedList::insertTail(const Candidate &c) {
    Node* newNode = new Node(c);
    if (head == nullptr) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
    count++;
}

// Chèn thí sinh vào đầu danh sách liên kết - O(1)
void LinkedList::insertHead(const Candidate &c) {
    Node* newNode = new Node(c);
    if (head == nullptr) {
        head = tail = newNode;
    } else {
        newNode->next = head;
        head = newNode;
    }
    count++;
}

// Xóa thí sinh theo SBD - O(n)
bool LinkedList::remove(const std::string &sbd) {
    if (head == nullptr) return false;

    // Trường hợp nút cần xóa ở đầu danh sách
    if (head->data.getSBD() == sbd) {
        Node* temp = head;
        head = head->next;
        if (head == nullptr) tail = nullptr;
        delete temp;
        count--;
        return true;
    }

    // Trường hợp nút ở vị trí giữa hoặc cuối
    Node* prev = head;
    Node* curr = head->next;
    while (curr != nullptr) {
        if (curr->data.getSBD() == sbd) {
            prev->next = curr->next;
            if (curr == tail) {
                tail = prev;
            }
            delete curr;
            count--;
            return true;
        }
        prev = curr;
        curr = curr->next;
    }
    return false;
}

// Tìm kiếm thí sinh theo SBD trong danh sách liên kết - O(n)
Node* LinkedList::find(const std::string &sbd) const {
    Node* p = head;
    while (p != nullptr) {
        if (p->data.getSBD() == sbd) {
            return p;
        }
        p = p->next;
    }
    return nullptr;
}

// Xóa toàn bộ danh sách, giải phóng bộ nhớ động
void LinkedList::clear() {
    Node* current = head;
    while (current != nullptr) {
        Node* nextNode = current->next;
        delete current;
        current = nextNode;
    }
    head = tail = nullptr;
    count = 0;
}

// Hiển thị toàn bộ thí sinh trong danh sách dạng bảng
void LinkedList::display() const {
    if (isEmpty()) {
        std::cout << "  (Danh sach rong)\n";
        return;
    }

    std::cout << "+---------+-----------------------+---------+-------------+----------------------+\n";
    std::cout << "| SBD     | Ho va Ten             | Phai    | Ngay Sinh   | Que Quan             |\n";
    std::cout << "+---------+-----------------------+---------+-------------+----------------------+\n";

    Node* p = head;
    while (p != nullptr) {
        p->data.displayRow();
        p = p->next;
    }
    std::cout << "+---------+-----------------------+---------+-------------+----------------------+\n";
    std::cout << "Tong cong: " << count << " thi sinh.\n";
}
