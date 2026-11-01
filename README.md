# ĐỀ TÀI 8: QUẢN LÝ DANH SÁCH THÍ SINH (HASH TABLE & LINKED LIST)
### BÀI TẬP DỰ ÁN HỌC PHẦN CẤU TRÚC DỮ LIỆU VÀ GIẢI THUẬT
**Trường Đại học Giao thông Vận tải TP. Hồ Chí Minh (UTH)**  
**Giảng viên hướng dẫn**: ThS. Bùi Văn Thượng  
**Lớp học phần**: 012012400212 | **Nhóm**: 4  

---

## 👥 THÀNH VIÊN NHÓM
1. **Nguyễn Bá Linh** (Trưởng nhóm - 044207007737)
2. **Hoàng Thế Anh**
3. **Trần Nhật Anh**
4. **Nguyễn Hữu Cường**
5. **Phạm Khánh Hưng**
6. **Đào Quang Thắng**

---

## 📂 CẤU TRÚC THƯ MỤC DỰ ÁN

```
DeTai8_QuanLyThiSinh/
├── src/
│   ├── ThiSinh.h            # Cấu trúc Thí sinh, tách tên, chữ cái đầu
│   ├── LinkedList.h         # Danh sách liên kết đơn (Node & LinkedList)
│   ├── HashTable.h          # Bảng băm dạng bảng tra 26 bucket (A-Z)
│   ├── Sorting.h            # Thuật toán Merge Sort O(N log N) theo tên
│   ├── RoomAllocation.h     # Thuật toán Greedy phân phòng thi tối ưu xác suất
│   ├── FileManager.h        # Đọc/ghi dữ liệu file TXT & sinh dữ liệu mẫu
│   └── Menu.h               # Giao diện menu console điều hướng
├── candidates.txt           # File dữ liệu mẫu 30 thí sinh UTH
├── main.cpp                 # Điểm khởi chạy chương trình (UTF-8 console)
├── BaoCao_DeTai8_Nhom4_PhanCong.docx # Báo cáo Word hoàn chỉnh đã phân công 6 bạn
├── HUONG_DAN_CHO_5_BAN.md   # Hướng dẫn chi tiết từng bạn làm phần của mình
├── OnTap_VanDap_CaNhan.md   # Bộ câu hỏi & đáp án gợi ý vấn đáp miệng
└── README.md
```

---

## 🚀 HƯỚNG DẪN BIÊN DỊCH VÀ CHẠY CHƯƠNG TRÌNH

### 1. Dùng dòng lệnh g++ (C++20)
```powershell
g++ -std=c++20 -O2 main.cpp -o quanly_thisinh.exe
.\quanly_thisinh.exe
```

### 2. Dùng VS Code
- Mở thư mục `DeTai8_QuanLyThiSinh` trong VS Code.
- Mở file `main.cpp`.
- Bấm nút **▶ Run Code** (hoặc tổ hợp phím `Ctrl + Alt + F5`).

---

## 🎯 CÁC CHỨC NĂNG CHÍNH CỦA HỆ THỐNG
1. **Thêm thí sinh mới**: Kiểm tra trùng mã dự thi, chuẩn hóa ngày sinh.
2. **Tra cứu thí sinh**: Tra cứu nhanh theo mã và tra cứu theo tên (truy cập trực tiếp bucket chữ cái đầu $O(L)$).
3. **Hiển thị danh sách thí sinh**: Sắp xếp thứ tự tên tăng dần bằng thuật toán Merge Sort $O(N \log N)$.
4. **Phân danh sách vào $n$ phòng thi**: Thuật toán Greedy cân bằng rải đều các thí sinh cùng chữ cái đầu vào các phòng khác nhau, giảm thiểu tối đa xác suất trùng tên.
5. **Cập nhật & Xóa**: Quản lý chỉnh sửa thông tin thí sinh linh hoạt.
6. **Lưu trữ & Đọc file TXT**: Tự động lưu và khôi phục dữ liệu từ `candidates.txt`.
