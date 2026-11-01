# Đề tài 8: Quản lý danh sách thí sinh (Hash Table, Linked List)
### Học phần: Cấu trúc dữ liệu và Giải thuật - Trường ĐH Giao thông Vận tải TP.HCM (UTH)
- **Giảng viên hướng dẫn:** ThS. Bùi Văn Thượng
- **Lớp học phần:** 012012400212 | **Nhóm:** 4
- **Trưởng nhóm:** Nguyễn Bá Linh

---

## 👥 PHÂN CHIA FILE CODE CHO TỪNG THÀNH VIÊN

Dự án được tách riêng thành từng file ứng với từng người phụ trách để mỗi bạn vào tự code và nắm chắc phần của mình:

| File mã nguồn | Thành viên phụ trách | Nhiệm vụ chính |
|:---|:---|:---|
| `CauTrucChung.h` | **Nguyễn Bá Linh** (Trưởng nhóm) | Cấu trúc dữ liệu dùng chung (`ThiSinh`, `Node`, `List`, `bangBam[26]`, hàm băm) |
| `ThemThiSinh_TheAnh.h` | **Hoàng Thế Anh** | Hàm thêm thí sinh vào bảng băm và nhập liệu từ bàn phím |
| `TraCuuXoa_NhatAnh.h` | **Trần Nhật Anh** | Hàm tra cứu theo mã, tra cứu theo tên và xóa thí sinh |
| `SapXep_HuuCuong.h` | **Nguyễn Hữu Cường** | Hàm sắp xếp danh sách theo tên tăng dần và in bảng |
| `PhanPhong_KhanhHung.h` | **Phạm Khánh Hưng** | Hàm phân danh sách vào $n$ phòng thi giảm thiểu trùng chữ cái đầu |
| `DocGhiFile_QuangThang.h` | **Đào Quang Thắng** | Hàm lưu và đọc dữ liệu từ file văn bản `candidates.txt` |
| `main.cpp` | **Nguyễn Bá Linh** | File chạy chính: `#include` các file trên và tạo menu điều khiển |

---

## 🛠️ HƯỚNG DẪN BIÊN DỊCH VÀ CHẠY

### Cách 1: Dùng lệnh g++ (C++20)
```powershell
g++ -std=c++20 -O2 main.cpp -o quanly_thisinh.exe
.\quanly_thisinh.exe
```

### Cách 2: Chạy trong VS Code
1. Mở thư mục `DeTai8_QuanLyThiSinh` trong VS Code.
2. Mở file `main.cpp`.
3. Bấm nút **▶ Run Code** ở góc trên bên phải (hoặc phím tắt `Ctrl + Alt + F5`).
