#include "RoomAllocator.h"
#include <iostream>
#include <vector>
#include <cctype>

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
    std::vector<int> roomSize(numRooms, 0);

    // Đếm số thí sinh theo từng chữ cái trong mỗi phòng
    std::vector<std::vector<int>> letterCount(
        numRooms, std::vector<int>(26, 0)
    );

    int currentRoom = 0;

    // BƯỚC 3: Lấy dữ liệu trực tiếp từ LinkedList
    const Node* p = list.getHead();

    while (p != nullptr) {

        // Lấy chữ cái đầu của Tên
        char firstLetter = p->data.getFirstLetterOfName();
        firstLetter = std::toupper(
            static_cast<unsigned char>(firstLetter)
        );

        if (firstLetter < 'A' || firstLetter > 'Z') {
            p = p->next;
            continue;
        }

        int index = firstLetter - 'A';

        int bestRoom = -1;
        int minSameLetter = totalCandidates + 1;
        int minSize = totalCandidates + 1;

        // BƯỚC 4: Tìm phòng phù hợp nhất
        for (int j = 0; j < numRooms; j++) {

            int r = (currentRoom + j) % numRooms;

            int sameLetter = letterCount[r][index];

            if (sameLetter < minSameLetter ||
                (sameLetter == minSameLetter &&
                 roomSize[r] < minSize)) {

                minSameLetter = sameLetter;
                minSize = roomSize[r];
                bestRoom = r;
            }
        }

        // BƯỚC 5: Đưa thí sinh vào phòng
        rooms[bestRoom].insertTail(p->data);

        roomSize[bestRoom]++;
        letterCount[bestRoom][index]++;

        currentRoom = (bestRoom + 1) % numRooms;

        p = p->next;
    }

    // BƯỚC 6: Xuất kết quả
    std::cout << "\n========== KET QUA PHAN PHONG THI ==========\n";
    std::cout << "Tong so thi sinh: " << totalCandidates << "\n";
    std::cout << "Tong so phong thi: " << numRooms << "\n";

    for (int r = 0; r < numRooms; r++) {

        std::cout << "\n========== PHONG THI SO "
                  << r + 1 << " ==========\n";

        std::cout << "So thi sinh: " << roomSize[r] << "\n";

        rooms[r].display();
    }

    std::cout << "\n[+] Phan phong thi thanh cong!\n";
}
