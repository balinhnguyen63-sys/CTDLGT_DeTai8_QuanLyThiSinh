# BÀI TẬP DỰ ÁN CẤU TRÚC DỮ LIỆU VÀ GIẢI THUẬT

## ĐỀ TÀI SỐ 8: QUẢN LÝ DANH SÁCH THÍ SINH (HASH TABLE, LINKED LIST)
- **Giảng viên hướng dẫn:** ThS. Bùi Văn Thượng
- **Nhóm thực hiện:** Nhóm 4
- **Lớp học phần:** 012012400212 - Trường Đại học Giao thông Vận tải TP.HCM (UTH)
- **Trưởng nhóm:** Nguyễn Bá Linh (MSSV: 044207007737)

---

## 1. Cấu trúc thư mục dự án

Dự án được cấu trúc theo mô hình phân tách module chuẩn hóa giống dự án mẫu (`OrderingApplication_Group05`):

```text
DeTai8_QuanLyThiSinh/
├── Phân công nhiệm vụ.docx      # File Word bảng phân công nhiệm vụ và % đóng góp 6 thành viên
├── README.md                    # Tài liệu giới thiệu tổng quan dự án
└── candidate-management/        # Thư mục mã nguồn C++ của dự án
    ├── CMakeLists.txt           # Cấu hình biên dịch tự động bằng CMake (C++17)
    ├── HUONGDAN.txt             # Hướng dẫn chi tiết cách build, chạy và phân nhiệm vụ
    ├── input.txt                # Bộ dữ liệu mẫu 30 thí sinh (CSV)
    ├── main.cpp                 # Điểm khởi chạy chương trình (gọi CandidateManager)
    │
    ├── Candidate.h / .cpp       # Mô hình dữ liệu Thí sinh (Linh)
    ├── LinkedList.h / .cpp      # Cấu trúc Node & Danh sách liên kết đơn (Linh)
    ├── HashTable.h / .cpp       # Cấu trúc Bảng băm dạng bảng tra 26 bucket A-Z (Linh)
    │
    ├── CandidateManager.h / .cpp# Quản lý hệ thống: Thêm, Sửa (Thế Anh) | Tra cứu, Xóa (Nhật Anh)
    ├── Sorter.h / .cpp          # Sắp xếp danh sách theo Tên tăng dần A-Z (Hữu Cường)
    ├── RoomAllocator.h / .cpp   # Phân chia n phòng thi giảm thiểu trùng chữ cái đầu (Khánh Hưng)
    └── Utils.h / .cpp           # Xử lý đọc file input.txt và ghi file TXT (Quang Thắng)
```

---

## 2. Bảng phân công nhiệm vụ và mã nguồn phụ trách

| STT | Họ và Tên | Vai trò / % Đóng góp | File phụ trách | Nhiệm vụ chính |
|:---:|:---|:---:|:---|:---|
| 1 | **Nguyễn Bá Linh** | Trưởng nhóm (100%) | `Candidate.h`, `Candidate.cpp`<br>`LinkedList.h`, `LinkedList.cpp`<br>`HashTable.h`, `HashTable.cpp`<br>`main.cpp` | Kiến trúc tổng thể, mô hình thí sinh, cài đặt danh sách liên kết đơn, cài đặt bảng băm dạng bảng tra 26 nhóm A-Z, menu điều phối chính. *(Đã hoàn thiện)* |
| 2 | **Hoàng Thế Anh** | Thành viên (100%) | `CandidateManager.h`<br>`CandidateManager.cpp` | Chức năng thêm mới thí sinh (kiểm tra trùng SBD) và cập nhật thông tin thí sinh. |
| 3 | **Trần Nhật Anh** | Thành viên (100%) | `CandidateManager.h`<br>`CandidateManager.cpp` | Chức năng tra cứu thí sinh theo SBD, tra cứu theo Tên qua Bảng băm, và xóa thí sinh khỏi hệ thống. |
| 4 | **Nguyễn Hữu Cường** | Thành viên (100%) | `Sorter.h`<br>`Sorter.cpp` | Chức năng sắp xếp danh sách liên kết theo thứ tự Tên tăng dần từ A đến Z. |
| 5 | **Phạm Khánh Hưng** | Thành viên (100%) | `RoomAllocator.h`<br>`RoomAllocator.cpp` | Chức năng phân danh sách vào n phòng thi sao cho xác suất tên trùng chữ cái đầu là ít nhất (Thuật toán tham lam Greedy đếm tần suất chữ cái đầu để giảm thiểu trùng lặp). |
| 6 | **Đào Quang Thắng** | Thành viên (100%) | `Utils.h`<br>`Utils.cpp`<br>`input.txt` | Chức năng đọc dữ liệu từ file `input.txt` vào hệ thống, lưu danh sách ra file TXT, chuẩn bị bộ dữ liệu mẫu. |

---

## 3. Hướng dẫn biên dịch và chạy chương trình

### Cách 1: Sử dụng CMake (Khuyên dùng)
```bash
cd candidate-management
mkdir build
cd build
cmake ..
cmake --build .
./app       # Linux / macOS
app.exe     # Windows
```

### Cách 2: Biên dịch trực tiếp bằng g++
```bash
cd candidate-management
g++ -std=c++17 main.cpp Candidate.cpp LinkedList.cpp HashTable.cpp CandidateManager.cpp Sorter.cpp RoomAllocator.cpp Utils.cpp -o app.exe
./app.exe
```
