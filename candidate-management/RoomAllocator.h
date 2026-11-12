#pragma once
#include "LinkedList.h"
#include "HashTable.h"

using namespace std;

// Pham Khanh Hung: Phan phong thi giam thieu trung chu cai dau (Greedy)

class RoomAllocator {
public:
    static void allocateRooms(const LinkedList &list, const HashTable &table, int numRooms);
};
