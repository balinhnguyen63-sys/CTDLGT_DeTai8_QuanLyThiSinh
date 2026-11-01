#pragma once
#include "Candidate.h"

// ============================================================================
// DỰ ÁN CTDL&GT: ĐỀ TÀI SỐ 8 - QUẢN LÝ DANH SÁCH THÍ SINH
// PHỤ TRÁCH: NGUYỄN BÁ LINH (TRƯỞNG NHÓM - MSSV: 044207007737)
// NỘI DUNG: Cấu trúc Danh sách liên kết đơn (Node & LinkedList)
// ============================================================================

// Nút trong danh sách liên kết đơn
struct Node {
    Candidate data;
    Node* next;

    Node(const Candidate &c);
};

// Lớp Danh sách liên kết đơn quản lý các thí sinh
class LinkedList {
private:
    Node* head;
    Node* tail;
    int count;

public:
    LinkedList();
    ~LinkedList();

    // Copy Constructor & Assignment Operator để sao chép sâu an toàn
    LinkedList(const LinkedList &other);
    LinkedList& operator=(const LinkedList &other);

    // Con trỏ đầu và cuối
    Node* getHead() const;
    Node* getTail() const;
    void setHead(Node* newHead);
    int getCount() const;
    bool isEmpty() const;

    // Các thao tác danh sách liên kết
    void insertTail(const Candidate &c);
    void insertHead(const Candidate &c);
    bool remove(const std::string &sbd);
    Node* find(const std::string &sbd) const;
    void clear();
    void display() const;
};
