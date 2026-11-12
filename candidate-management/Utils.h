#pragma once
#include "LinkedList.h"
#include "HashTable.h"
#include <string>

using namespace std;

// Dao Quang Thang: Doc va ghi du lieu thi sinh tu file CSV / TXT

class Utils {
public:
    static bool loadFromFile(const string &filename, LinkedList &list, HashTable &table);
    static bool saveToFile(const string &filename, const LinkedList &list);
};
