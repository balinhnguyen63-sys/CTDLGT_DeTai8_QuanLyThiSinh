#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "ThiSinh.h"
#include <vector>
#include <functional>

struct Node {
    ThiSinh data;
    Node* next;

    Node(const ThiSinh& ts) : data(ts), next(nullptr) {}
};

class LinkedList {
private:
    Node* head;
    Node* tail;
    int count;

public:
    LinkedList() : head(nullptr), tail(nullptr), count(0) {}

    ~LinkedList() {
        clear();
    }

    // Copy constructor (deep copy)
    LinkedList(const LinkedList& other) : head(nullptr), tail(nullptr), count(0) {
        Node* curr = other.head;
        while (curr != nullptr) {
            pushBack(curr->data);
            curr = curr->next;
        }
    }

    // Copy assignment
    LinkedList& operator=(const LinkedList& other) {
        if (this != &other) {
            clear();
            Node* curr = other.head;
            while (curr != nullptr) {
                pushBack(curr->data);
                curr = curr->next;
            }
        }
        return *this;
    }

    bool empty() const {
        return head == nullptr;
    }

    int size() const {
        return count;
    }

    Node* getHead() const {
        return head;
    }

    void clear() {
        Node* curr = head;
        while (curr != nullptr) {
            Node* temp = curr;
            curr = curr->next;
            delete temp;
        }
        head = nullptr;
        tail = nullptr;
        count = 0;
    }

    // Thêm vào cuối danh sách liên kết
    void pushBack(const ThiSinh& ts) {
        Node* newNode = new Node(ts);
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        count++;
    }

    // Thêm vào đầu danh sách liên kết
    void pushFront(const ThiSinh& ts) {
        Node* newNode = new Node(ts);
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head = newNode;
        }
        count++;
    }

    // Tìm kiếm theo Mã dự thi
    ThiSinh* findByMa(const std::string& ma) {
        Node* curr = head;
        while (curr != nullptr) {
            if (curr->data.maDuThi == ma) {
                return &(curr->data);
            }
            curr = curr->next;
        }
        return nullptr;
    }

    // Tìm kiếm theo Tên hoặc Họ tên
    void findByName(const std::string& namePart, std::vector<ThiSinh>& results) const {
        Node* curr = head;
        std::string searchLower = namePart;
        std::transform(searchLower.begin(), searchLower.end(), searchLower.begin(), ::tolower);

        while (curr != nullptr) {
            std::string fullNameLower = curr->data.hoTen;
            std::transform(fullNameLower.begin(), fullNameLower.end(), fullNameLower.begin(), ::tolower);
            if (fullNameLower.find(searchLower) != std::string::npos) {
                results.push_back(curr->data);
            }
            curr = curr->next;
        }
    }

    // Xóa theo Mã dự thi
    bool removeByMa(const std::string& ma) {
        if (head == nullptr) return false;

        // Nếu phần tử cần xóa nằm ở đầu
        if (head->data.maDuThi == ma) {
            Node* temp = head;
            head = head->next;
            if (head == nullptr) tail = nullptr;
            delete temp;
            count--;
            return true;
        }

        Node* prev = head;
        Node* curr = head->next;
        while (curr != nullptr) {
            if (curr->data.maDuThi == ma) {
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

    // Lấy toàn bộ danh sách thí sinh ra vector
    void getAll(std::vector<ThiSinh>& list) const {
        Node* curr = head;
        while (curr != nullptr) {
            list.push_back(curr->data);
            curr = curr->next;
        }
    }

    // Duyệt qua từng node với lambda / function
    void forEach(std::function<void(const ThiSinh&)> func) const {
        Node* curr = head;
        while (curr != nullptr) {
            func(curr->data);
            curr = curr->next;
        }
    }
};

#endif // LINKEDLIST_H
