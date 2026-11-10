#include "RoomAllocator.h"
#include <iostream>
#include <vector>

void RoomAllocator::allocateRooms(const LinkedList &list,
                                  const HashTable &table,
                                  int numRooms) {

    // BƯỚC 1: Kiểm tra dữ liệu đầu vào
    int totalCandidates = list.getCount();

    if (numRooms <= 0) {
        std::cout << "[!] So phong thi phai lon hon 0!\n";
        return;
    }

    if (list.isEmpty()) {
        std::cout << "[!] Danh sach thi sinh rong!\n";
        return;
    }

    if (numRooms > totalCandidates) {
        std::cout << "[!] So phong khong duoc lon hon so thi sinh!\n";
        return;
    }

    // BƯỚC 2: Khởi tạo danh sách phòng
    std::vector<LinkedList> rooms(numRooms);

    int currentRoom = 0;

    // BƯỚC 3: Lấy dữ liệu trực tiếp từ LinkedList
    Node* p = list.getHead();

    while (p != nullptr) {

        // Thêm thí sinh vào phòng hiện tại
        rooms[currentRoom].insertTail(p->data);

        // Chuyển sang phòng tiếp theo
        currentRoom = (currentRoom + 1) % numRooms;

        p = p->next;
    }

    // BƯỚC 4: In kết quả
    std::cout << "\n========== KET QUA PHAN PHONG THI ==========\n";
    std::cout << "Tong so thi sinh: " << totalCandidates << "\n";
    std::cout << "Tong so phong thi: " << numRooms << "\n";

    for (int r = 0; r < numRooms; ++r) {

        std::cout << "\n========== PHONG THI SO "
                  << r + 1 << " ==========\n";

        rooms[r].display();
    }

    std::cout << "\n[+] Phan phong thi thanh cong!\n";
}
