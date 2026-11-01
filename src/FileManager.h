#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "ThiSinh.h"
#include "HashTable.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

class FileManager {
public:
    // Lưu toàn bộ dữ liệu bảng băm ra file TXT
    static bool saveToFile(const HashTable& ht, const std::string& filename) {
        std::ofstream outFile(filename);
        if (!outFile.is_open()) {
            std::cerr << "[Loi] Khong the mo file " << filename << " de ghi!\n";
            return false;
        }

        std::vector<ThiSinh> all = ht.getAll();
        for (const auto& ts : all) {
            outFile << ts.toFileLine() << "\n";
        }

        outFile.close();
        return true;
    }

    // Đọc dữ liệu từ file TXT và nạp vào bảng băm
    static int loadFromFile(HashTable& ht, const std::string& filename) {
        std::ifstream inFile(filename);
        if (!inFile.is_open()) {
            return -1; // Không mở được file
        }

        std::string line;
        int count = 0;
        while (std::getline(inFile, line)) {
            if (line.empty()) continue;
            ThiSinh ts;
            if (ThiSinh::fromFileLine(line, ts)) {
                if (ht.insert(ts)) {
                    count++;
                }
            }
        }

        inFile.close();
        return count;
    }

    // Nạp dữ liệu mẫu chất lượng cao cho thí sinh Việt Nam
    static void generateMockData(HashTable& ht) {
        std::vector<ThiSinh> sampleData = {
            ThiSinh("SBD001", "Nguyen Ba Linh", "Nam", "15/08/2004", "TP. Ho Chi Minh"),
            ThiSinh("SBD002", "Hoang The Anh", "Nam", "20/03/2004", "Ha Noi"),
            ThiSinh("SBD003", "Tran Nhat Anh", "Nam", "12/11/2004", "Da Nang"),
            ThiSinh("SBD004", "Nguyen Huu Cuong", "Nam", "05/06/2004", "Nghe An"),
            ThiSinh("SBD005", "Pham Khanh Hung", "Nam", "18/09/2004", "Binh Duong"),
            ThiSinh("SBD006", "Dao Quang Thang", "Nam", "22/01/2004", "Hai Phong"),
            ThiSinh("SBD007", "Le Thi Mai Anh", "Nu", "10/02/2004", "Hue"),
            ThiSinh("SBD008", "Vu Duc Binh", "Nam", "14/07/2004", "Quang Ninh"),
            ThiSinh("SBD009", "Doan Van Chau", "Nam", "30/08/2004", "Nam Dinh"),
            ThiSinh("SBD010", "Pham Tien Dung", "Nam", "09/04/2004", "Thanh Hoa"),
            ThiSinh("SBD011", "Bui My Duyen", "Nu", "25/12/2004", "Dong Nai"),
            ThiSinh("SBD012", "Dinh Hoang Giang", "Nam", "03/10/2004", "Thai Binh"),
            ThiSinh("SBD013", "Nguyen Ngoc Ha", "Nu", "17/05/2004", "Can Tho"),
            ThiSinh("SBD014", "Tran Quoc Huy", "Nam", "08/08/2004", "Quang Nam"),
            ThiSinh("SBD015", "Pham Thu Huong", "Nu", "19/09/2004", "Bac Ninh"),
            ThiSinh("SBD016", "Le Gia Huy", "Nam", "11/03/2004", "Vung Tau"),
            ThiSinh("SBD017", "Ngo Quang Khai", "Nam", "02/02/2004", "Ha Tinh"),
            ThiSinh("SBD018", "Dang Tuan Kiet", "Nam", "28/06/2004", "Binh Dinh"),
            ThiSinh("SBD019", "Hoang Thi Lan", "Nu", "07/07/2004", "Lam Dong"),
            ThiSinh("SBD020", "Nguyen Van Long", "Nam", "21/04/2004", "Long An"),
            ThiSinh("SBD021", "Tran Thi Tuyet Mai", "Nu", "16/01/2004", "Tien Giang"),
            ThiSinh("SBD022", "Phan Thanh Nam", "Nam", "29/10/2004", "Khanh Hoa"),
            ThiSinh("SBD023", "Bui Thi Yen Nhi", "Nu", "04/09/2004", "Ben Tre"),
            ThiSinh("SBD024", "Do Minh Quan", "Nam", "13/05/2004", "Phu Tho"),
            ThiSinh("SBD025", "Nguyen Hong Son", "Nam", "24/11/2004", "Vinh Phuc"),
            ThiSinh("SBD026", "Pham Minh Tam", "Nam", "31/03/2004", "An Giang"),
            ThiSinh("SBD027", "Vo Van Thang", "Nam", "15/07/2004", "Quang Binh"),
            ThiSinh("SBD028", "Nguyen Thi Thanh Thao", "Nu", "06/12/2004", "Gia Lai"),
            ThiSinh("SBD029", "Tran Duc Thinh", "Nam", "18/08/2004", "Tay Ninh"),
            ThiSinh("SBD030", "Le Van Vu", "Nam", "27/02/2004", "Soc Trang")
        };

        for (const auto& ts : sampleData) {
            ht.insert(ts);
        }
    }
};

#endif // FILEMANAGER_H
