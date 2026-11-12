#pragma once
#include "LinkedList.h"
#include "HashTable.h"
#include <string>

// Dao Quang Thang: Doc va ghi du lieu thi sinh tu file CSV / TXT

class Utils {
public:
    static bool loadFromFile(const std::string &filename, LinkedList &list, HashTable &table);
    static bool saveToFile(const std::string &filename, const LinkedList &list);
};
