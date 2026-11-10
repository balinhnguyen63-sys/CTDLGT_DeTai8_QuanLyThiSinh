#include "RoomAllocator.h"
#include <iostream>
#include <vector>
#include <cctype>

void RoomAllocator::allocateRooms(const LinkedList &list,
                                  const HashTable &,
                                  int numRooms) {

    // BƯỚC 1: KIỂM TRA DỮ LIỆU ĐẦU VÀO
    int totalCandidates = list.getCount();

    if (numRooms <= 0) {
        std::cout << "So phong thi phai lon hon 0!\n";
        return;
    }

    if (list.isEmpty()) {
        std::cout << "Danh sach thi sinh rong!\n";
        return;
    }

    if (numRooms > totalCandidates) {
        std::cout << "So phong khong duoc lon hon so thi sinh!\n";
        return;
    }

    // BƯỚC 2: KHỞI TẠO CÁC PHÒNG THI
    std::vector<LinkedList> rooms(numRooms);
    std::vector<int> roomSize(numRooms, 0);

    // Lưu số lượng thí sinh có cùng chữ cái đầu trong mỗi phòng
    std::vector<std::vector<int>> letterCount(
        numRooms, std::vector<int>(26, 0)
    );

    int currentRoom = 0;
    Node* p = list.getHead();

    // BƯỚC 3: DUYỆT LINKEDLIST VÀ PHÂN PHÒNG
    while (p != nullptr) {

        // Lấy chữ cái đầu của tên thí sinh
        char firstLetter = p->data.getFirstLetterOfName();

        firstLetter = static_cast<char>(
            std::toupper(static_cast<unsigned char>(firstLetter))
        );

        // Nếu ký tự không thuộc A-Z thì ưu tiên phòng ít thí sinh nhất
        if (firstLetter < 'A' || firstLetter > 'Z') {
            int bestRoom = currentRoom;

            for (int i = 1; i < numRooms; i++) {
                int r = (currentRoom + i) % numRooms;

                if (roomSize[r] < roomSize[bestRoom]) {
                    bestRoom = r;
                }
            }

            rooms[bestRoom].insertTail(p->data);
            roomSize[bestRoom]++;

            currentRoom = (bestRoom + 1) % numRooms;
            p = p->next;
            continue;
        }

        int index = firstLetter - 'A';

        int bestRoom = currentRoom;
        int minSameLetter = letterCount[currentRoom][index];
        int minSize = roomSize[currentRoom];

        // Tìm phòng có số thí sinh trùng chữ cái đầu ít nhất
        for (int i = 1; i < numRooms; i++) {
            int r = (currentRoom + i) % numRooms;

            if (letterCount[r][index] < minSameLetter ||
                (letterCount[r][index] == minSameLetter &&
                 roomSize[r] < minSize)) {

                bestRoom = r;
                minSameLetter = letterCount[r][index];
                minSize = roomSize[r];
            }
        }

        // Đưa thí sinh vào phòng được chọn
        rooms[bestRoom].insertTail(p->data);
        roomSize[bestRoom]++;
        letterCount[bestRoom][index]++;

        // Chuyển vị trí bắt đầu sang phòng tiếp theo
        currentRoom = (bestRoom + 1) % numRooms;

        p = p->next;
    }

    // BƯỚC 4: HIỂN THỊ KẾT QUẢ PHÂN PHÒNG
    for (int i = 0; i < numRooms; i++) {
        std::cout << "\n========== PHONG THI "
                  << i + 1 << " ==========\n";

        std::cout << "So thi sinh: " << roomSize[i] << "\n";
        rooms[i].display();
    }
    std::cout << "\n[+] Phan phong thi thanh cong!\n";
}
