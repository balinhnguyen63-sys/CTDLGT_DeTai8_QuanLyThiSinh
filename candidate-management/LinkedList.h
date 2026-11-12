#pragma once
#include "Candidate.h"

using namespace std;

// Nguyen Ba Linh: Danh sach lien ket don (Node & LinkedList)

// Nut trong danh sach lien ket don
struct Node {
    Candidate data;
    Node* next;

    Node(const Candidate &c);
};

// Lop Danh sach lien ket don quan ly thi sinh
class LinkedList {
private:
    Node* head;
    Node* tail;
    int count;

public:
    LinkedList();
    ~LinkedList();

    // Copy Constructor & Assignment Operator
    LinkedList(const LinkedList &other);
    LinkedList& operator=(const LinkedList &other);

    // Con tro dau va cuoi
    Node* getHead() const;
    Node* getTail() const;
    void setHead(Node* newHead);
    int getCount() const;
    bool isEmpty() const;

    // Cac thao tac danh sach lien ket
    void insertTail(const Candidate &c);
    void insertHead(const Candidate &c);
    bool remove(const string &sbd);
    Node* find(const string &sbd) const;
    void clear();
    void display() const;
};
