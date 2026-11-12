#pragma once
#include "LinkedList.h"
#include "HashTable.h"

// Nguyen Huu Cuong: Sap xep thi sinh theo Ten tang dan A-Z (Merge Sort)

class Sorter {
public:
    static void sortByNameAZ(LinkedList &list);
    static void sortBuckets(HashTable &table);
};
