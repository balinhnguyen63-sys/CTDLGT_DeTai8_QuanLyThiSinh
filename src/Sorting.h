#ifndef SORTING_H
#define SORTING_H

#include "ThiSinh.h"
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>

namespace Sorting {

    // Hàm so sánh 2 thí sinh: ưu tiên so sánh Tên -> Họ đệm -> Mã dự thi
    inline bool compareThiSinh(const ThiSinh& a, const ThiSinh& b) {
        std::string tenA = a.getTen();
        std::string tenB = b.getTen();

        if (tenA != tenB) {
            return tenA < tenB;
        }

        std::string hoDemA = a.getHoDem();
        std::string hoDemB = b.getHoDem();
        if (hoDemA != hoDemB) {
            return hoDemA < hoDemB;
        }

        return a.maDuThi < b.maDuThi;
    }

    // Merge Sort - hàm trộn 2 mảng con đã sắp xếp
    inline void merge(std::vector<ThiSinh>& arr, int left, int mid, int right) {
        int n1 = mid - left + 1;
        int n2 = right - mid;

        std::vector<ThiSinh> L(n1);
        std::vector<ThiSinh> R(n2);

        for (int i = 0; i < n1; ++i) L[i] = arr[left + i];
        for (int j = 0; j < n2; ++j) R[j] = arr[mid + 1 + j];

        int i = 0, j = 0, k = left;
        while (i < n1 && j < n2) {
            if (compareThiSinh(L[i], R[j])) {
                arr[k] = L[i];
                i++;
            } else {
                arr[k] = R[j];
                j++;
            }
            k++;
        }

        while (i < n1) {
            arr[k] = L[i];
            i++;
            k++;
        }

        while (j < n2) {
            arr[k] = R[j];
            j++;
            k++;
        }
    }

    // Merge Sort đệ quy - Độ phức tạp O(N log N)
    inline void mergeSort(std::vector<ThiSinh>& arr, int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            mergeSort(arr, left, mid);
            mergeSort(arr, mid + 1, right);
            merge(arr, left, mid, right);
        }
    }

    // Hàm sắp xếp chính
    inline void sortCandidatesByName(std::vector<ThiSinh>& candidates) {
        if (candidates.size() <= 1) return;
        mergeSort(candidates, 0, static_cast<int>(candidates.size()) - 1);
    }

    // In bảng danh sách thí sinh ra màn hình console đẹp mắt
    inline void printTable(const std::vector<ThiSinh>& list, const std::string& title = "DANH SACH THI SINH") {
        std::cout << "\n========================================================================================\n";
        std::cout << "                             " << title << "\n";
        std::cout << "========================================================================================\n";
        std::cout << std::left 
                  << std::setw(6)  << "STT"
                  << std::setw(12) << "Ma du thi"
                  << std::setw(28) << "Ho va ten"
                  << std::setw(12) << "Gioi tinh"
                  << std::setw(14) << "Ngay sinh"
                  << std::setw(18) << "Que quan"
                  << "\n";
        std::cout << "----------------------------------------------------------------------------------------\n";

        if (list.empty()) {
            std::cout << "  (Danh sach rong)\n";
        } else {
            for (size_t i = 0; i < list.size(); ++i) {
                std::cout << std::left 
                          << std::setw(6)  << (i + 1)
                          << std::setw(12) << list[i].maDuThi
                          << std::setw(28) << list[i].hoTen
                          << std::setw(12) << list[i].gioiTinh
                          << std::setw(14) << list[i].ngaySinh
                          << std::setw(18) << list[i].queQuan
                          << "\n";
            }
        }
        std::cout << "----------------------------------------------------------------------------------------\n";
        std::cout << "Tong cong: " << list.size() << " thi sinh\n";
        std::cout << "========================================================================================\n";
    }

} // namespace Sorting

#endif // SORTING_H
