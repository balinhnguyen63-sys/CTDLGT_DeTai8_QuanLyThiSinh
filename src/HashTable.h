#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "ThiSinh.h"
#include "LinkedList.h"
#include <iostream>
#include <vector>
#include <iomanip>

class HashTable {
public:
    static const int TABLE_SIZE = 26; // 26 chữ cái A-Z

private:
    LinkedList buckets[TABLE_SIZE];
    int totalElements;

    // Hàm băm dạng bảng tra: ánh xạ ký tự đầu tiên của tên ('A'..'Z') thành chỉ số [0..25]
    int hashFunction(char initialChar) const {
        char upper = static_cast<char>(toupper(static_cast<unsigned char>(initialChar)));
        if (upper >= 'A' && upper <= 'Z') {
            return upper - 'A';
        }
        return 25; // fallback về 'Z'
    }

public:
    HashTable() : totalElements(0) {}

    // Lấy ký tự chữ cái tương ứng với bucket index
    static char getCharFromIndex(int index) {
        if (index >= 0 && index < TABLE_SIZE) {
            return static_cast<char>('A' + index);
        }
        return '?';
    }

    int getTotal() const {
        return totalElements;
    }

    // Kiểm tra mã dự thi đã tồn tại chưa
    bool existsMa(const std::string& ma) const {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            Node* curr = buckets[i].getHead();
            while (curr != nullptr) {
                if (curr->data.maDuThi == ma) {
                    return true;
                }
                curr = curr->next;
            }
        }
        return false;
    }

    // Thêm thí sinh vào bảng băm theo chữ cái đầu của Tên
    bool insert(const ThiSinh& ts) {
        if (existsMa(ts.maDuThi)) {
            return false; // Mã dự thi đã tồn tại
        }
        char initial = ts.getInitialLetter();
        int index = hashFunction(initial);
        buckets[index].pushBack(ts);
        totalElements++;
        return true;
    }

    // Tra cứu thí sinh theo Mã dự thi (duyệt các bucket)
    ThiSinh* searchByMa(const std::string& ma) {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            ThiSinh* found = buckets[i].findByMa(ma);
            if (found != nullptr) {
                return found;
            }
        }
        return nullptr;
    }

    // Tra cứu thí sinh theo Tên (tối ưu hóa: băm ngay chữ cái đầu để tra đúng bucket)
    std::vector<ThiSinh> searchByName(const std::string& name) const {
        std::vector<ThiSinh> results;
        if (name.empty()) return results;

        // Xác định chữ cái đầu để tra cứu nhanh vào bucket tương ứng
        char initial = 'A';
        unsigned char c0 = static_cast<unsigned char>(name[0]);
        if (c0 >= 'a' && c0 <= 'z') initial = static_cast<char>(toupper(c0));
        else if (c0 >= 'A' && c0 <= 'Z') initial = static_cast<char>(c0);
        else {
            // Trường hợp tiếng Việt có dấu
            ThiSinh temp("", name, "", "", "");
            initial = temp.getInitialLetter();
        }

        int targetBucket = hashFunction(initial);
        buckets[targetBucket].findByName(name, results);

        // Nếu không thấy trong bucket băm, tìm kiếm dự phòng toàn bộ bảng tra
        if (results.empty()) {
            for (int i = 0; i < TABLE_SIZE; ++i) {
                if (i != targetBucket) {
                    buckets[i].findByName(name, results);
                }
            }
        }

        return results;
    }

    // Xóa thí sinh theo Mã dự thi
    bool removeByMa(const std::string& ma) {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            if (buckets[i].removeByMa(ma)) {
                totalElements--;
                return true;
            }
        }
        return false;
    }

    // Cập nhật thông tin thí sinh (giữ nguyên mã dự thi)
    bool update(const ThiSinh& newInfo) {
        // Tìm xem thí sinh cũ ở đâu
        ThiSinh* old = searchByMa(newInfo.maDuThi);
        if (old == nullptr) return false;

        // Nếu tên thay đổi làm đổi bucket, cần xóa ở bucket cũ và chèn vào bucket mới
        char oldInitial = old->getInitialLetter();
        char newInitial = newInfo.getInitialLetter();

        if (hashFunction(oldInitial) == hashFunction(newInitial)) {
            *old = newInfo;
        } else {
            removeByMa(newInfo.maDuThi);
            insert(newInfo);
        }
        return true;
    }

    // Lấy toàn bộ thí sinh trong bảng băm
    std::vector<ThiSinh> getAll() const {
        std::vector<ThiSinh> all;
        all.reserve(totalElements);
        for (int i = 0; i < TABLE_SIZE; ++i) {
            buckets[i].getAll(all);
        }
        return all;
    }

    // Lấy danh sách thí sinh trong một bucket cụ thể
    std::vector<ThiSinh> getCandidatesInBucket(int bucketIndex) const {
        std::vector<ThiSinh> list;
        if (bucketIndex >= 0 && bucketIndex < TABLE_SIZE) {
            buckets[bucketIndex].getAll(list);
        }
        return list;
    }

    // Lấy số lượng thí sinh trong bucket
    int getBucketSize(int bucketIndex) const {
        if (bucketIndex >= 0 && bucketIndex < TABLE_SIZE) {
            return buckets[bucketIndex].size();
        }
        return 0;
    }

    // Xóa sạch toàn bộ bảng băm
    void clear() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            buckets[i].clear();
        }
        totalElements = 0;
    }

    // Thống kê phân bố các bucket bảng tra
    void printStatistics() const {
        std::cout << "\n================ THONG KE PHAN BO THEO CHU CAI DAU ================\n";
        std::cout << std::left << std::setw(8) << "Nhom" 
                  << std::setw(12) << "So luong" 
                  << "Bieu do truc quan\n";
        std::cout << "-------------------------------------------------------------------\n";
        for (int i = 0; i < TABLE_SIZE; ++i) {
            int sz = buckets[i].size();
            if (sz > 0) {
                std::cout << "  " << getCharFromIndex(i) << "     : "
                          << std::setw(8) << sz << "  ";
                for (int s = 0; s < sz; ++s) std::cout << "#";
                std::cout << "\n";
            }
        }
        std::cout << "-------------------------------------------------------------------\n";
        std::cout << "Tong so thi sinh: " << totalElements << "\n";
    }
};

#endif // HASHTABLE_H
