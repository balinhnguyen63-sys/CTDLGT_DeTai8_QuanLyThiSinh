#pragma once
#include "LinkedList.h"
#include "HashTable.h"
#include <string>

// Nhom 4 - De tai 8: Quan ly danh sach thi sinh
// Nguyen Ba Linh, Hoang The Anh, Tran Nhat Anh

class CandidateManager {
private:
    LinkedList candidateList; // Danh sach lien ket luu thi sinh
    HashTable hashTable;      // Bang bam 26 bucket (A-Z) tra cuu theo ten

    // Menu va du lieu mau (Nguyen Ba Linh)
    void showMenu() const;
    void initSampleData();

public:
    CandidateManager();
    ~CandidateManager();

    // Hoang The Anh: Them va sua thong tin thi sinh
    bool addCandidate();
    bool updateCandidate();

    // Tran Nhat Anh: Tra cuu va xoa thi sinh
    void searchBySBD();
    void searchByName();
    bool deleteCandidate();

    // Cac chuc nang goi module khac
    void displayAll() const;          // Xem danh sach (Nguyen Ba Linh)
    void displayHashTable() const;    // Xem bang bam (Nguyen Ba Linh)
    void sortCandidates();            // Sap xep (Nguyen Huu Cuong)
    void allocateExamRooms();         // Phan phong thi (Pham Khanh Hung)
    void loadData();                  // Doc file (Dao Quang Thang)
    void saveData();                  // Ghi file (Dao Quang Thang)

    // Vong lap chay chuong trinh
    void run();
};
