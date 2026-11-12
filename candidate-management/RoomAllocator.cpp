#include "RoomAllocator.h"
#include <iostream>
#include <vector>
#include <cctype>

using namespace std;

void RoomAllocator::allocateRooms(const LinkedList &list,
                                  const HashTable &,
                                  int numRooms) {

    // Kiem tra du lieu dau vao
    int totalCandidates = list.getCount();

    if (numRooms <= 0) {
        cout << "[!] So phong thi phai lon hon 0!\n";
        return;
    }

    if (list.isEmpty()) {
        cout << "[!] Danh sach thi sinh rong!\n";
        return;
    }

    if (numRooms > totalCandidates) {
        cout << "[!] So phong khong duoc lon hon so thi sinh!\n";
        return;
    }

    // Khoi tao cac phong thi va bang dem
    vector<LinkedList> rooms(numRooms);
    vector<int> roomSize(numRooms, 0);

    // Luu so luong thi sinh cung chu cai dau trong moi phong
    vector<vector<int>> letterCount(
        numRooms, vector<int>(26, 0)
    );

    int currentRoom = 0;
    Node* p = list.getHead();

    // Duyet qua tung thi sinh va xep vao phong toi uu nhat
    while (p != nullptr) {

        // Lay chu cai dau tien cua ten thi sinh
        char firstLetter = toupper(p->data.getFirstLetterOfName());

        // Neu ky tu khong thuoc A-Z thi uu tien phong it thi sinh nhat
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

        // Tim phong co so thi sinh trung chu cai dau it nhat
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

        // Dua thi sinh vao phong duoc chon
        rooms[bestRoom].insertTail(p->data);
        roomSize[bestRoom]++;
        letterCount[bestRoom][index]++;

        // Chuyen vi tri bat dau sang phong tiep theo
        currentRoom = (bestRoom + 1) % numRooms;

        p = p->next;
    }

    // Hien thi ket qua phan phong
    for (int i = 0; i < numRooms; i++) {
        cout << "\n========== PHONG THI "
             << i + 1 << " ==========\n";

        cout << "So thi sinh: " << roomSize[i] << "\n";
        rooms[i].display();
    }

    cout << "\n=======================================\n";
    cout << "Tong so thi sinh: " << totalCandidates << "\n";
    cout << "Tong so phong thi: " << numRooms << "\n";
    cout << "=======================================\n";
    cout << "\n[+] Phan phong thi thanh cong!\n";
}
