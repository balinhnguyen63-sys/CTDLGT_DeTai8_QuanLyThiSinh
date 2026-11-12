#pragma once
#include "LinkedList.h"
#include <string>

using namespace std;

// Nguyen Ba Linh: Bang bam 26 nhom chu cai (A-Z) dung danh sach lien ket (chaining)

class HashTable {
public:
    static const int TABLE_SIZE = 26; // 26 chu cai tieng Anh tu 'A' den 'Z'

private:
    LinkedList buckets[TABLE_SIZE];   // Mang 26 danh sach lien ket

public:
    HashTable();
    ~HashTable();

    // Ham bam: chuyen chu cai dau tien cua Ten thanh chi so bucket (0 -> 25)
    int hashFunction(char firstLetter) const;

    // Chen thi sinh vao dung bucket tuong ung voi chu cai dau cua ten
    void insert(const Candidate &c);

    // Tra cuu thi sinh theo So Bao Danh (tim tren cac bucket)
    Node* searchBySBD(const string &sbd) const;

    // Tra cuu thi sinh theo Ten tren bang bam
    void searchByName(const string &name) const;

    // Xoa thi sinh khoi bang bam
    bool remove(const string &sbd, char firstLetter);

    // Hien thi toan bo bang bam theo tung nhom chu cai A-Z
    void displayAll() const;

    // Hien thi mot bucket cu the
    void displayBucket(int index) const;

    // Lay tham chieu den mot bucket
    const LinkedList& getBucket(int index) const;

    // Lay tham chieu co the thay doi den mot bucket
    LinkedList& getBucket(int index);

    // Xoa toan bo du lieu bang bam
    void clear();
};
