# Đề tài 8: Quản lý danh sách thí sinh (Hash Table, Linked List)
### Học phần: Cấu trúc dữ liệu và Giải thuật - Trường ĐH Giao thông Vận tải TP.HCM (UTH)
- **Giảng viên hướng dẫn:** ThS. Bùi Văn Thượng
- **Lớp học phần:** 012012400212 | **Nhóm:** 4
- **Trưởng nhóm:** Nguyễn Bá Linh (MSSV: 044207007737)

---

## 📂 Cấu trúc thư mục mã nguồn

```
DeTai8_QuanLyThiSinh/
├── src/
│   ├── ThiSinh.h            # Cấu trúc Thí sinh, tách tên, ký tự đầu
│   ├── LinkedList.h         # Danh sách liên kết đơn (Node & LinkedList)
│   ├── HashTable.h          # Bảng băm dạng bảng tra 26 bucket (A-Z)
│   ├── Sorting.h            # Thuật toán Merge Sort O(N log N) theo tên
│   ├── RoomAllocation.h     # Thuật toán Greedy phân phòng thi tối ưu xác suất
│   ├── FileManager.h        # Đọc/ghi dữ liệu file TXT
│   └── Menu.h               # Giao diện menu console điều hướng
├── candidates.txt           # File dữ liệu mẫu 30 thí sinh
├── main.cpp                 # Điểm khởi chạy chương trình (hỗ trợ console UTF-8)
└── README.md
```

---

## 🛠️ Hướng dẫn biên dịch và chạy

### Cách 1: Biên dịch bằng g++ (chuẩn C++20)
```powershell
g++ -std=c++20 -O2 main.cpp -o quanly_thisinh.exe
.\quanly_thisinh.exe
```

### Cách 2: Chạy trực tiếp trong VS Code
1. Mở thư mục `DeTai8_QuanLyThiSinh` trong VS Code.
2. Mở file `main.cpp`.
3. Bấm nút **▶ Run Code** ở góc trên bên phải (hoặc phím tắt `Ctrl + Alt + F5`).

---

## 📌 Các chức năng chính
1. **Thêm thí sinh:** Kiểm tra trùng mã dự thi, chuẩn hóa ngày sinh.
2. **Tra cứu thí sinh:** Tra cứu theo mã dự thi và tra cứu theo tên qua bảng tra $O(L)$.
3. **Hiển thị danh sách:** Sắp xếp tăng dần theo tên bằng Merge Sort $O(N \log N)$.
4. **Phân danh sách vào $n$ phòng thi:** Thuật toán Greedy cân bằng rải đều các thí sinh cùng chữ cái đầu vào các phòng khác nhau để giảm thiểu xác suất trùng tên.
5. **Cập nhật & Xóa:** Quản lý sửa đổi thông tin hoặc xóa thí sinh khỏi danh sách liên kết.
6. **Lưu/Đọc file:** Lưu và khôi phục dữ liệu từ file `candidates.txt`.
