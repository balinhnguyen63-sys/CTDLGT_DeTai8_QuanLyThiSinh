#include "RoomAllocator.h"
#include <iostream>
#include <vector>

void RoomAllocator::allocateRooms(const LinkedList &list, const HashTable &table, int numRooms) {

    int totalCandidates = list.getCount();
    Node* p = nullptr;
    int currentRoom = 0; // Chỉ số phòng xoay vòng (Round-Robin: 0 -> numRooms - 1)
 // BƯỚC 1: Kiểm tra điều kiện đầu vào
    if (numRooms <= 0) {
        std::cout << "[!] So phong thi phai lon hon 0!\n";
        return;
    }

    if (list.isEmpty()) {
        std::cout << "[!] Danh sach thi sinh rong!\n";
        return;
    }

    // BƯỚC 2: Khởi tạo danh sách các phòng thi
    int totalCandidates = list.getCount();
    Node* p = nullptr;
    int currentRoom = 0;

    std::vector<LinkedList> rooms(numRooms);

    // BƯỚC 3: Duyệt qua từng bucket của HashTable
    for (int i = 0; i < HashTable::TABLE_SIZE; ++i) {

        const LinkedList& bucket = table.getBucket(i);

        p = bucket.getHead();

        while (p != nullptr) {

            // Đưa thí sinh vào phòng hiện tại
            rooms[currentRoom].insertTail(p->data);

            // Chuyển sang phòng tiếp theo theo Round-Robin
            currentRoom = (currentRoom + 1) % numRooms;

            p = p->next;
        }
    }

    // BƯỚC 4: In kết quả phân phòng
    std::cout << "\n========== KET QUA PHAN PHONG THI ==========\n";
    std::cout << "Tong so thi sinh: " << totalCandidates << "\n";
    std::cout << "Tong so phong thi: " << numRooms << "\n";

    for (int r = 0; r < numRooms; ++r) {

        std::cout << "\n========== PHONG THI SO "
                  << (r + 1) << " ==========\n";

        rooms[r].display();
    }

    std::cout << "\n[+] Phan phong thi thanh cong!\n";
}
