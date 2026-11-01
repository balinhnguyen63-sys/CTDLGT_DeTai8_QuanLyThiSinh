# 🎓 BỘ CÂU HỎI & ĐÁP ÁN GỢI Ý ÔN TẬP VẤN ĐÁP CÁ NHÂN (UTH)
### Giảng viên: ThS. Bùi Văn Thượng | Đề tài 8: Quản lý thí sinh (Hash table, Linked list)

---

### 1. DÀNH CHO BẠN: NGUYỄN BÁ LINH (Trưởng nhóm - Kiến trúc & Bảng băm)
- **Câu hỏi 1**: *Tại sao nhóm lại chọn Bảng băm dạng bảng tra 26 bucket kết hợp Danh sách liên kết?*
  - **Gợi ý trả lời**: Vì yêu cầu bài toán gom nhóm thí sinh theo chữ cái đầu của Tên. Tập ký tự chữ cái đầu là hữu hạn và cố định (26 chữ cái A-Z). Việc dùng mảng trực tiếp kích thước 26 với hàm băm $h(c) = c - 'A'$ cho thời gian tính băm là $O(1)$. Danh sách liên kết đơn (Separate Chaining) ở mỗi bucket giúp giải quyết va chạm một cách linh hoạt, thêm xóa thí sinh mà không cần cấp phát lại toàn bộ mảng.
- **Câu hỏi 2**: *Độ phức tạp tra cứu trong bảng băm là bao nhiêu?*
  - **Gợi ý trả lời**: Trường hợp trung bình là $O(1 + N/26)$ (với $N/26$ là độ dài trung bình mỗi danh sách liên kết). So với tìm kiếm tuần tự trên mảng $O(N)$, phương pháp này nhanh hơn gấp 26 lần!

---

### 2. DÀNH CHO BẠN: HOÀNG THẾ ANH (Module Thêm & Cập nhật)
- **Câu hỏi 1**: *Hàm thêm thí sinh xử lý những điều kiện biên và dữ liệu không hợp lệ nào?*
  - **Gợi ý trả lời**: Em kiểm tra tính duy nhất của Mã dự thi (không cho phép thêm nếu trùng mã), kiểm tra định dạng Ngày sinh (DD/MM/YYYY), và tách đúng từ cuối cùng trong chuỗi Họ tên để lấy Tên, sau đó chuẩn hóa chữ cái đầu thành chữ hoa để đưa vào đúng bucket.
- **Câu hỏi 2**: *Nếu người dùng đổi tên thí sinh trong chức năng cập nhật thì code xử lý thế nào?*
  - **Gợi ý trả lời**: Nếu tên mới có chữ cái đầu khác với tên cũ (ví dụ đổi từ "Linh" sang "Thắng"), thí sinh sẽ thuộc về bucket khác. Do đó em phải xóa thí sinh ở bucket cũ và chèn lại vào bucket mới để đảm bảo tính toàn vẹn của bảng băm.

---

### 3. DÀNH CHO BẠN: TRẦN NHẬT ANH (Module Tra cứu & Xóa)
- **Câu hỏi 1**: *Chức năng tra cứu theo Tên hoạt động như thế nào để đạt hiệu năng tối ưu?*
  - **Gợi ý trả lời**: Khi người dùng nhập tên cần tìm (ví dụ "Anh"), em lấy ngay ký tự đầu 'A', tính hàm băm ra bucket số 0 và chỉ duyệt danh sách liên kết trong bucket 0. Nhờ vậy không cần phải quét qua toàn bộ thí sinh trong cơ sở dữ liệu.
- **Câu hỏi 2**: *Thao tác xóa một node trong danh sách liên kết đơn cần lưu ý điều gì?*
  - **Gợi ý trả lời**: Cần xử lý trường hợp node cần xóa nằm ở đầu danh sách (cập nhật `head = head->next`) hoặc nằm ở giữa/cuối (dùng con trỏ `prev` để nối `prev->next = curr->next`). Cuối cùng bắt buộc phải gọi `delete` để tránh rò rỉ bộ nhớ (memory leak).

---

### 4. DÀNH CHO BẠN: NGUYỄN HỮU CƯỜNG (Module Sắp xếp & Hiển thị)
- **Câu hỏi 1**: *Tại sao bạn chọn Merge Sort để sắp xếp danh sách thí sinh mà không dùng Quick Sort hay Bubble Sort?*
  - **Gợi ý trả lời**: Merge Sort có độ phức tạp thời gian luôn ổn định là $O(N \log N)$ trong mọi trường hợp (tốt nhất, trung bình và xấu nhất). Đặc biệt, Merge Sort là thuật toán sắp xếp ổn định (Stable Sort), giúp bảo toàn thứ tự ban đầu của các thí sinh nếu họ trùng tên và trùng họ đệm.
- **Câu hỏi 2**: *Quy tắc so sánh thứ tự giữa 2 thí sinh được cài đặt ra sao?*
  - **Gợi ý trả lời**: Em ưu tiên so sánh Tên trước (từ A đến Z). Nếu Tên trùng nhau thì so sánh tiếp Họ và Tên đệm. Nếu tiếp tục trùng thì mới so sánh Mã dự thi để đảm bảo thứ tự duy nhất và chính xác.

---

### 5. DÀNH CHO BẠN: PHẠM KHÁNH HƯNG (Module Phân phòng thi tối ưu)
- **Câu hỏi 1**: *Thuật toán phân vào n phòng thi giải quyết bài toán giảm thiểu xác suất trùng chữ cái đầu như thế nào?*
  - **Gợi ý trả lời**: Em sử dụng thuật toán Tham lam cân bằng (Greedy Balanced Allocation). Bước đầu em gom thí sinh theo từng nhóm chữ cái và sắp xếp nhóm có số lượng đông nhất làm trước. Với mỗi thí sinh trong nhóm, em luôn ưu tiên chọn phòng thi hiện đang có ít người cùng chữ cái đầu nhất; nếu bằng nhau, chọn phòng có sĩ số ít nhất để đảm bảo các phòng có sĩ số cân bằng.
- **Câu hỏi 2**: *Công thức tính xác suất trùng chữ cái đầu trong phòng thi là gì?*
  - **Gợi ý trả lời**: Trong phòng có $m$ thí sinh, tổng số cặp 2 thí sinh bất kỳ là $\binom{m}{2} = \frac{m(m-1)}{2}$. Nếu nhóm chữ cái $c$ có $k_c$ thí sinh, số cặp trùng chữ cái $c$ là $\binom{k_c}{2} = \frac{k_c(k_c-1)}{2}$. Xác suất chọn 2 thí sinh trùng chữ cái đầu là:
    $$P = \frac{\sum_c \frac{k_c(k_c-1)}{2}}{\frac{m(m-1)}{2}} \times 100\%$$

---

### 6. DÀNH CHO BẠN: ĐÀO QUANG THẮNG (Module File & Kiểm thử)
- **Câu hỏi 1**: *Cấu trúc file TXT lưu trữ dữ liệu được thiết kế như thế nào?*
  - **Gợi ý trả lời**: Dữ liệu lưu dưới dạng text phân tách bằng ký tự gạch đứng `|` (`maDuThi|hoTen|gioiTinh|ngaySinh|queQuan`). Định dạng này giúp dễ dàng đọc từng dòng bằng `std::getline` và tách token mà không bị lỗi khi họ tên có khoảng trắng.
- **Câu hỏi 2**: *Bạn đã thực hiện kiểm thử những trường hợp biên nào cho hệ thống?*
  - **Gợi ý trả lời**: Em kiểm thử: (1) Nhập file trống; (2) Phân phòng khi số phòng $n > N$ (tránh chia cho 0); (3) Tên tiếng Việt có dấu đặc biệt (Đ, Â, Ă, Ê, Ô); (4) Nhập mã dự thi trùng lặp; (5) Kiểm thử tải với hơn 1.000 thí sinh để đo thời gian phản hồi.
