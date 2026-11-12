#include "LinkedList.h"
#include <iostream>

using namespace std;

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

// Chen thi sinh vao cuoi danh sach lien ket - O(1)
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

// Chen thi sinh vao dau danh sach lien ket - O(1)
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

// Xoa thi sinh theo SBD - O(n)
bool LinkedList::remove(const string &sbd) {
    if (head == nullptr) return false;

    // Nut can xoa o dau danh sach
    if (head->data.getSBD() == sbd) {
        Node* temp = head;
        head = head->next;
        if (head == nullptr) tail = nullptr;
        delete temp;
        count--;
        return true;
    }

    // Nut o giua hoac cuoi
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

// Tim kiem thi sinh theo SBD trong danh sach lien ket - O(n)
Node* LinkedList::find(const string &sbd) const {
    Node* p = head;
    while (p != nullptr) {
        if (p->data.getSBD() == sbd) {
            return p;
        }
        p = p->next;
    }
    return nullptr;
}

// Xoa toan bo danh sach, giai phong bo nho
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

// Hien thi toan bo thi sinh trong danh sach dang bang
void LinkedList::display() const {
    if (isEmpty()) {
        cout << "  (Danh sach rong)\n";
        return;
    }

    cout << "+---------+-----------------------+---------+-------------+----------------------+\n";
    cout << "| SBD     | Ho va Ten             | Phai    | Ngay Sinh   | Que Quan             |\n";
    cout << "+---------+-----------------------+---------+-------------+----------------------+\n";

    Node* p = head;
    while (p != nullptr) {
        p->data.displayRow();
        p = p->next;
    }
    cout << "+---------+-----------------------+---------+-------------+----------------------+\n";
    cout << "Tong cong: " << count << " thi sinh.\n";
}
