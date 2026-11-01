# 📋 HƯỚNG DẪN PHÂN CÔNG VÀ LÀM BÀI DỰ ÁN CTDL & GT (NHÓM 4 - UTH)

> **Học phần**: Cấu trúc dữ liệu và Giải thuật  
> **Giảng viên**: ThS. Bùi Văn Thượng  
> **Lớp học phần**: 012012400212  
> **Đề tài số 8**: Quản lý danh sách thí sinh (Hash table, Linked list)  
> **Trưởng nhóm**: Nguyễn Bá Linh  

---

## 👥 1. DANH SÁCH NHÓM & PHÂN CÔNG NHIỆM VỤ

| STT | Họ và Tên | Vai trò | Module Code phụ trách | Phần Báo cáo Word phụ trách |
|:---:|:---|:---:|:---|:---|
| 1 | **Nguyễn Bá Linh** | Trưởng nhóm | `ThiSinh.h`, `LinkedList.h`, `HashTable.h`, `Menu.h`, `main.cpp` | Phần I (Bối cảnh, mục tiêu), Phần II (Mô hình & cấu trúc dữ liệu), Phần VI, VII |
| 2 | **Hoàng Thế Anh** | Thành viên | `Module Thêm & Cập nhật thí sinh` (Validate mã, ngày sinh, tách tên) | Mục I.2 (Đối tượng quản lý), I.3 (Đầu vào/ra), III.3 (Cài đặt thêm/sửa) |
| 3 | **Trần Nhật Anh** | Thành viên | `Module Tra cứu & Xóa thí sinh` (Tra cứu mã, băm tra cứu tên, xóa node) | Mục I.4 (Chức năng), II.3 (Thao tác trên CTDL), III.3 (Tra cứu/xóa) |
| 4 | **Nguyễn Hữu Cường** | Thành viên | `Module Sắp xếp & Hiển thị` (`Sorting.h` - Merge Sort theo Tên A-Z) | Mục II.4 (Giải thuật sắp xếp), II.5 (Độ phức tạp), III.2 (Hiện thực Merge Sort) |
| 5 | **Phạm Khánh Hưng** | Thành viên | `Module Phân phòng thi` (`RoomAllocation.h` - Greedy Balanced) | Mục II.4 (Giải thuật phân phòng), III.3 (Công thức xác suất trùng) |
| 6 | **Đào Quang Thắng** | Thành viên | `Module File & Kiểm thử` (`FileManager.h`, `candidates.txt`, Test cases) | Mục I.5 (Trường hợp biên), Phần IV (Kiểm thử, hiệu năng), Phần V (Sử dụng AI) |

---

## 🛠️ 2. QUY TRÌNH LÀM VIỆC VỚI GITHUB VÀ MÃ NGUỒN

### Bước 1: Clone dự án về máy
```bash
git clone https://github.com/balinhnguyen63-sys/CTDLGT_DeTai8_QuanLyThiSinh.git
cd CTDLGT_DeTai8_QuanLyThiSinh
```

### Bước 2: Tạo nhánh riêng của mình (không commit thẳng vào main)
- Hoàng Thế Anh: `git checkout -b feature/themanh-them-thisinh`
- Trần Nhật Anh: `git checkout -b feature/nhatanh-tracuu-xoa`
- Nguyễn Hữu Cường: `git checkout -b feature/cuong-sapxep-mergesort`
- Phạm Khánh Hưng: `git checkout -b feature/hung-phanphongthi`
- Đào Quang Thắng: `git checkout -b feature/thang-file-testcase`

### Bước 3: Biên dịch và chạy thử code
Dùng compiler g++ (chuẩn C++20):
```bash
g++ -std=c++20 -O2 main.cpp -o quanly_thisinh.exe
./quanly_thisinh.exe
```
Hoặc mở thư mục bằng **VS Code** và bấm **▶ Run Code** (Ctrl + Alt + F5).

### Bước 4: Commit và đẩy lên GitHub
```bash
git add .
git commit -m "Hoan thanh phan viec cua [Ten ban]"
git push origin feature/[ten-nhanh-cua-ban]
```

---

## 📄 3. HƯỚNG DẪN VIẾT BÁO CÁO WORD (`BaoCao_DeTai8_Nhom4_PhanCong.docx`)

1. Mở file `BaoCao_DeTai8_Nhom4_PhanCong.docx` trong thư mục dự án.
2. Tìm đến đúng các mục có gắn tag `[PHỤ TRÁCH: <TÊN BẠN>]`.
3. Đọc phần gợi ý dàn ý đã được soạn sẵn bên dưới tiêu đề và điền nội dung chi tiết theo kết quả code thực tế của bạn.
4. Chụp ảnh màn hình chức năng bạn phụ trách lúc chạy console đưa vào mục tương ứng để báo cáo thêm sinh động.
5. Kiểm tra lại Bảng 1 ở trang 4 để đảm bảo đúng nhiệm vụ thực tế của mình.
