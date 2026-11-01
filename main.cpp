#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

// =========================================================================
// HỌC PHẦN: CẤU TRÚC DỮ LIỆU VÀ GIẢI THUẬT - TRƯỜNG ĐH GIAO THÔNG VẬN TẢI TP.HCM (UTH)
// GIẢNG VIÊN HƯỚNG DẪN: ThS. BÙI VĂN THƯỢNG
// ĐỀ TÀI SỐ 8: QUẢN LÝ DANH SÁCH THÍ SINH (Hash Table & Linked List)
// NHÓM 4 (GỒM 6 THÀNH VIÊN)
// =========================================================================


// =========================================================================
// PHẦN 1: NGUYỄN BÁ LINH (Trưởng nhóm phụ trách) - [ĐÃ HOÀN THÀNH]
// CẤU TRÚC DỮ LIỆU DÙNG CHUNG: Thí sinh, Node, List, Bảng băm & Hàm băm
// =========================================================================

// 1. Cấu trúc thông tin của một Thí sinh (chuẩn 5 trường theo đề bài)
struct ThiSinh {
    string maDuThi;  // Mã dự thi (ví dụ: SBD001, khóa chính không trùng)
    string hoTen;    // Họ và tên đầy đủ (ví dụ: Nguyen Ba Linh)
    string gioiTinh; // Giới tính: Nam hoặc Nu
    string ngaySinh; // Ngày sinh: DD/MM/YYYY
    string queQuan;  // Quê quán: TP. Ho Chi Minh
};

// 2. Cấu trúc 1 Node trong danh sách liên kết đơn (giống hệt bài học trên lớp)
struct Node {
    ThiSinh data;    // Dữ liệu thí sinh
    Node* next;      // Con trỏ trỏ tới node tiếp theo
};

// 3. Cấu trúc Danh sách liên kết đơn (List)
struct List {
    Node* head;      // Con trỏ đầu danh sách
    Node* tail;      // Con trỏ cuối danh sách
};

// Khởi tạo 1 danh sách liên kết rỗng
void khoiTaoList(List &ds) {
    ds.head = NULL;
    ds.tail = NULL;
}

// Cấp phát động tạo một Node mới chứa dữ liệu thí sinh
Node* taoNode(ThiSinh ts) {
    Node* p = new Node;
    p->data = ts;
    p->next = NULL;
    return p;
}

// Thao tác con trỏ: Gắn node vào cuối danh sách liên kết
void themVaoCuoi(List &ds, Node* p) {
    if (ds.head == NULL) {
        ds.head = ds.tail = p;
    } else {
        ds.tail->next = p;
        ds.tail = p;
    }
}

// 4. BẢNG BĂM (Hash Table) DẠNG BẢNG TRA:
// Đề bài yêu cầu: Bảng băm dạng bảng tra, các thí sinh được nhóm theo chữ cái bắt đầu của Tên.
// Bảng băm thực chất là một mảng gồm 26 List (tương ứng với 26 chữ cái 'A' đến 'Z'):
List bangBam[26];

// Khởi tạo 26 danh sách rỗng trong bảng băm
void khoiTaoBangBam() {
    for (int i = 0; i < 26; i++) {
        khoiTaoList(bangBam[i]);
    }
}

// Hàm lấy tên (từ cuối cùng trong chuỗi Họ và tên)
// Ví dụ: "Nguyen Ba Linh" -> lấy ra "Linh"
string layTen(string hoTen) {
    if (hoTen.empty()) return "";
    int pos = hoTen.find_last_of(" ");
    if (pos == -1) return hoTen;
    return hoTen.substr(pos + 1);
}

// Hàm lấy chữ cái đầu của tên và đổi thành chữ hoa
// Ví dụ: Tên "Linh" -> lấy ra ký tự 'L'
char layChuCaiDau(string hoTen) {
    string ten = layTen(hoTen);
    if (ten.empty()) return 'A';
    char c = ten[0];
    if (c >= 'a' && c <= 'z') c = c - 32; // Đổi chữ thường sang chữ hoa
    if (c >= 'A' && c <= 'Z') return c;
    return 'A';
}

// Hàm băm (Hash Function) dạng bảng tra
// Ánh xạ chữ cái 'A'..'Z' thành số nguyên [0..25]
// Ví dụ: 'A' -> 0, 'B' -> 1, ..., 'L' -> 11, 'Z' -> 25
int hamBam(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c - 'A';
    }
    return 0;
}


// =========================================================================
// PHẦN 2: HOÀNG THẾ ANH PHỤ TRÁCH - [CHƯA LÀM - THẾ ANH TỰ CODE]
// CHỨC NĂNG: THÊM THÍ SINH VÀO BẢNG BĂM
//
// YÊU CẦU CỦA MÔN HỌC & GIẢNG VIÊN:
// 1. Kiểm tra tính hợp lệ: Mã dự thi không được trùng lặp.
// 2. Thao tác con trỏ: Tự tạo Node mới (taoNode) và tự trỏ các con trỏ
//    (head, tail, next) để gắn vào cuối danh sách liên kết của bucket tương ứng.
// 3. Khai báo biến nhập liệu đầy đủ: maDuThi, hoTen, gioiTinh, ngaySinh, queQuan.
// =========================================================================

// TODO 1: Thế Anh tự khai báo biến và viết hàm kiểm tra mã dự thi đã có trong bảng băm chưa
// Hướng dẫn:
// - Duyệt vòng for i từ 0 đến 25 (qua 26 bucket trong bangBam).
// - Khai báo con trỏ: Node* p = bangBam[i].head;
// - Trong vòng lặp while (p != NULL):
//     + Nếu p->data.maDuThi == ma thì return true; (bị trùng).
//     + Di chuyển con trỏ: p = p->next;
// - Nếu duyệt hết không thấy thì return false;
bool kiemTraTrungMa(string ma) {
    // === HOÀNG THẾ ANH TỰ VIẾT CODE Ở ĐÂY ===

    return false; // Tạm thời để trống cho Thế Anh tự code
}

// TODO 2: Thế Anh tự viết hàm băm và tự thao tác con trỏ chèn vào cuối List
// Hướng dẫn thao tác con trỏ:
// - Bước 1: Kiểm tra mã: if (kiemTraTrungMa(ts.maDuThi)) return false;
// - Bước 2: Lấy chữ cái đầu của tên: char c = layChuCaiDau(ts.hoTen);
// - Bước 3: Tính chỉ số bucket: int viTri = hamBam(c);
// - Bước 4: Tạo node mới: Node* p = taoNode(ts);
// - Bước 5: TỰ TRỎ CON TRỎ GẮN VÀO CUỐI DANH SÁCH LIÊN KẾT:
//     if (bangBam[viTri].head == NULL) {
//         bangBam[viTri].head = bangBam[viTri].tail = p;
//     } else {
//         bangBam[viTri].tail->next = p;
//         bangBam[viTri].tail = p;
//     }
bool themThiSinh(ThiSinh ts) {
    // === HOÀNG THẾ ANH TỰ VIẾT CODE Ở ĐÂY ===

    return false; // Tạm thời để trống cho Thế Anh tự code
}

// TODO 3: Thế Anh tự khai báo biến và viết hàm nhập thông tin từ bàn phím
// Hướng dẫn: Khai báo ThiSinh ts; dùng getline(cin, ts.maDuThi),... và gọi themThiSinh(ts);
void nhapThemThiSinh() {
    cout << "\n=============================================================\n";
    cout << " [CHƯA CÀI ĐẶT] PHẦN 2: HOÀNG THẾ ANH TỰ VIẾT CODE TẠI ĐÂY   \n";
    cout << "=============================================================\n";

    // === HOÀNG THẾ ANH TỰ VIẾT CODE NHẬP LIỆU Ở ĐÂY ===
}


// =========================================================================
// PHẦN 3: TRẦN NHẬT ANH PHỤ TRÁCH - [CHƯA LÀM - NHẬT ANH TỰ CODE]
// CHỨC NĂNG: TRA CỨU THÔNG TIN & XÓA THÍ SINH
//
// YÊU CẦU CỦA MÔN HỌC & GIẢNG VIÊN:
// 1. Tra cứu theo Mã dự thi: Dùng con trỏ duyệt qua các danh sách trong Bảng băm.
// 2. Tra cứu theo Tên: Vận dụng bảng băm, băm chữ cái đầu của tên cần tìm
//    để nhảy thẳng vào đúng bucket, sau đó dùng con trỏ duyệt danh sách đó.
// 3. Xóa thí sinh: Tự thao tác 2 con trỏ (curr và prev), xử lý xóa đầu danh sách
//    hoặc xóa giữa/cuối danh sách và giải phóng bộ nhớ (delete curr).
// =========================================================================

// Hàm in 1 dòng thông tin thí sinh ra bảng
void inMotThiSinh(ThiSinh ts, int stt) {
    cout << "|" << left << setw(4)  << stt
         << "|" << left << setw(10) << ts.maDuThi
         << "|" << left << setw(25) << ts.hoTen
         << "|" << left << setw(10) << ts.gioiTinh
         << "|" << left << setw(14) << ts.ngaySinh
         << "|" << left << setw(18) << ts.queQuan << "|\n";
}

// TODO 1: Nhật Anh tự khai báo con trỏ và viết hàm tìm kiếm theo Mã dự thi
// Hướng dẫn:
// - Duyệt vòng for i từ 0 đến 25 (qua 26 bucket).
// - Khai báo con trỏ: Node* p = bangBam[i].head;
// - Trong vòng lặp while (p != NULL):
//     + Nếu p->data.maDuThi == ma thì return p; (trả về node tìm thấy).
//     + Di chuyển con trỏ: p = p->next;
// - Nếu duyệt hết không thấy thì return NULL;
Node* timTheoMa(string ma) {
    // === TRẦN NHẬT ANH TỰ VIẾT CODE Ở ĐÂY ===

    return NULL; // Tạm thời để trống cho Nhật Anh tự code
}

// TODO 2: Nhật Anh tự viết hàm tra cứu theo Tên trên Bảng băm
// Hướng dẫn tận dụng hàm băm:
// - Bước 1: Lấy chữ cái đầu: char c = layChuCaiDau(tenCanTim);
// - Bước 2: Băm ra vị trí bucket: int viTri = hamBam(c);
// - Bước 3: Dùng con trỏ Node* p = bangBam[viTri].head để duyệt duy nhất bucket này!
//     + Trong while (p != NULL): kiểm tra tên và in thông tin: inMotThiSinh(p->data, stt++);
//     + Di chuyển con trỏ: p = p->next;
void traCuuTheoTen(string tenCanTim) {
    cout << "\n=============================================================\n";
    cout << " [CHƯA CÀI ĐẶT] PHẦN 3: TRẦN NHẬT ANH TỰ VIẾT CODE TẠI ĐÂY   \n";
    cout << "=============================================================\n";

    // === TRẦN NHẬT ANH TỰ VIẾT CODE Ở ĐÂY ===
}

// TODO 3: Nhật Anh tự viết thao tác con trỏ xóa Node theo Mã dự thi
// Hướng dẫn thao tác 2 con trỏ (curr và prev):
// - Khai báo: Node* curr = bangBam[i].head; Node* prev = NULL;
// - Trong vòng lặp while (curr != NULL):
//     + Nếu curr->data.maDuThi == ma:
//         * Xóa ở đầu (prev == NULL): bangBam[i].head = curr->next;
//         * Xóa ở giữa/cuối: prev->next = curr->next;
//         * Cập nhật tail nếu xóa node cuối: if (curr == bangBam[i].tail) bangBam[i].tail = prev;
//         * delete curr; (Giải phóng bộ nhớ).
//         * return true;
//     + Di chuyển 2 con trỏ: prev = curr; curr = curr->next;
bool xoaThiSinhTheoMa(string ma) {
    // === TRẦN NHẬT ANH TỰ VIẾT CODE Ở ĐÂY ===

    return false; // Tạm thời để trống cho Nhật Anh tự code
}


// =========================================================================
// PHẦN 4: NGUYỄN HỮU CƯỜNG PHỤ TRÁCH - [CHƯA LÀM - CƯỜNG TỰ CODE]
// CHỨC NĂNG: SẮP XẾP DANH SÁCH THÍ SINH THEO TÊN TĂNG DẦN
//
// YÊU CẦU CỦA MÔN HỌC & GIẢNG VIÊN:
// 1. Dùng con trỏ duyệt qua 26 danh sách liên kết trong bảng băm để lấy toàn bộ dữ liệu.
// 2. Viết hàm so sánh thứ tự 2 thí sinh theo Tên (A-Z), nếu trùng Tên thì so sánh Họ và tên.
// 3. Tự cài đặt thuật toán sắp xếp (Selection Sort hoặc Interchange Sort) đổi chỗ 2 phần tử.
// 4. In bảng danh sách thí sinh đã sắp xếp ra màn hình console.
// =========================================================================

// TODO 1: Cường dùng con trỏ gom toàn bộ thí sinh từ 26 List vào 1 vector
// Hướng dẫn:
// - Khai báo: vector<ThiSinh> danhSach;
// - Duyệt vòng for i từ 0 đến 25:
//     + Khai báo con trỏ: Node* p = bangBam[i].head;
//     + Vòng while (p != NULL): danhSach.push_back(p->data); p = p->next;
// - return danhSach;
vector<ThiSinh> layTatCaThiSinh() {
    vector<ThiSinh> danhSach;

    // === NGUYỄN HỮU CƯỜNG TỰ VIẾT CODE Ở ĐÂY ===

    return danhSach; // Tạm thời để trống cho Hữu Cường tự code
}

// TODO 2: Cường viết hàm so sánh thứ tự 2 thí sinh a và b theo Tên
// Hướng dẫn:
// - Lấy tên: string tenA = layTen(a.hoTen); string tenB = layTen(b.hoTen);
// - Nếu (tenA != tenB) thì return tenA < tenB;
// - Nếu trùng tên: so sánh tiếp a.hoTen < b.hoTen;
bool soSanhTen(ThiSinh a, ThiSinh b) {
    // === NGUYỄN HỮU CƯỜNG TỰ VIẾT CODE Ở ĐÂY ===

    return false; // Tạm thời để trống cho Hữu Cường tự code
}

// TODO 3: Cường tự cài đặt thuật toán sắp xếp danh sách theo Tên tăng dần
// Hướng dẫn (Thuật toán Chọn trực tiếp / Selection Sort):
// - for (int i = 0; i < n - 1; i++)
// -     for (int j = i + 1; j < n; j++)
// -         nếu soSanhTen(ds[j], ds[minIdx]) thì cập nhật minIdx = j;
// -     hoán vị đổi chỗ ds[i] và ds[minIdx].
void sapXepTheoTen(vector<ThiSinh> &ds) {
    // === NGUYỄN HỮU CƯỜNG TỰ VIẾT THUẬT TOÁN SẮP XẾP Ở ĐÂY ===
}

// TODO 4: Cường viết hàm in bảng danh sách thí sinh ra màn hình console
void inBangDanhSach(vector<ThiSinh> ds, string tieuDe) {
    cout << "\n=============================================================\n";
    cout << " [CHƯA CÀI ĐẶT] PHẦN 4: NGUYỄN HỮU CƯỜNG TỰ VIẾT CODE TẠI ĐÂY\n";
    cout << "=============================================================\n";

    // === NGUYỄN HỮU CƯỜNG TỰ VIẾT CODE IN BẢNG Ở ĐÂY ===
}


// =========================================================================
// PHẦN 5: PHẠM KHÁNH HƯNG PHỤ TRÁCH - [CHƯA LÀM - HƯNG TỰ CODE]
// CHỨC NĂNG: PHÂN DANH SÁCH VÀO N PHÒNG THI (GIẢM TRÙNG CHỮ CÁI ĐẦU)
//
// YÊU CẦU CỦA MÔN HỌC & GIẢNG VIÊN:
// 1. Khai báo cấu trúc PhongThi để lưu trữ thông tin phòng thi và số lượng thí sinh.
// 2. Cài đặt thuật toán phân bổ thí sinh vào n phòng thi:
//    - Dùng con trỏ duyệt qua từng danh sách liên kết trong 26 bucket.
//    - Rải đều các thí sinh trong cùng một bucket sang các phòng thi khác nhau
//      (ưu tiên phòng đang có ít thí sinh mang chữ cái đó nhất).
// 3. Tính toán xác suất chọn ngẫu nhiên 2 thí sinh trùng chữ cái đầu trong phòng thi.
// =========================================================================

// Cấu trúc đại diện cho 1 phòng thi
struct PhongThi {
    int soPhong;             // Số thứ tự phòng thi (1, 2, ..., n)
    vector<ThiSinh> danhSach;// Danh sách các thí sinh được phân vào phòng
    int demChuCai[26] = {0}; // Mảng đếm số thí sinh của từng chữ cái 'A'..'Z' trong phòng
};

// TODO: Khánh Hưng tự viết hàm phân chia n phòng thi và tính xác suất
// Hướng dẫn giải thuật:
// - Khởi tạo vector n phòng thi: vector<PhongThi> dsPhong(nPhong);
// - Duyệt vòng for i từ 0 đến 25 (qua 26 bucket):
//     + Khai báo con trỏ: Node* p = bangBam[i].head;
//     + Trong vòng while (p != NULL):
//         * Duyệt qua n phòng để tìm phòng có dsPhong[r].demChuCai[i] nhỏ nhất.
//         * Xếp thí sinh p->data vào phòng đó:
//           dsPhong[phongChon].danhSach.push_back(p->data);
//           dsPhong[phongChon].demChuCai[i]++;
//         * Di chuyển con trỏ: p = p->next;
// - Tính xác suất trùng chữ cái đầu trong phòng:
//     Số cặp trùng chữ cái = sum(k * (k - 1) / 2) với k là số người cùng chữ cái.
//     Tổng số cặp trong phòng = m * (m - 1) / 2 với m là tổng sĩ số phòng.
//     Xác suất (%) = (Số cặp trùng / Tổng số cặp) * 100%.
void phanChiaPhongThi(int nPhong) {
    cout << "\n=============================================================\n";
    cout << " [CHƯA CÀI ĐẶT] PHẦN 5: PHẠM KHÁNH HƯNG TỰ VIẾT CODE TẠI ĐÂY \n";
    cout << "=============================================================\n";

    // === PHẠM KHÁNH HƯNG TỰ VIẾT CODE Ở ĐÂY ===
}


// =========================================================================
// PHẦN 6: ĐÀO QUANG THẮNG PHỤ TRÁCH - [CHƯA LÀM - THẮNG TỰ CODE]
// CHỨC NĂNG: LƯU TRỮ VÀ ĐỌC DỮ LIỆU TỪ FILE TXT
//
// YÊU CẦU CỦA MÔN HỌC & GIẢNG VIÊN:
// 1. Lưu trữ dữ liệu: Dùng con trỏ duyệt qua toàn bộ các danh sách liên kết
//    trong bảng băm để ghi dữ liệu từng thí sinh ra file văn bản candidates.txt.
// 2. Đọc dữ liệu: Mở file candidates.txt, đọc từng dòng, tách các trường
//    thông tin (ma, ten, gt, ns, que) và tự tạo node chèn lại vào bảng băm.
// =========================================================================

// TODO 1: Quang Thắng tự viết hàm duyệt con trỏ qua 26 List và ghi dữ liệu ra file
// Hướng dẫn:
// - Khai báo: ofstream file(tenFile);
// - Duyệt vòng for i từ 0 đến 25:
//     + Khai báo con trỏ: Node* p = bangBam[i].head;
//     + Vòng while (p != NULL):
//         * Ghi: file << p->data.maDuThi << "|" << p->data.hoTen << "|" ... << "\n";
//         * Di chuyển con trỏ: p = p->next;
// - Đóng file: file.close();
void luuFile(string tenFile) {
    cout << "\n=============================================================\n";
    cout << " [CHƯA CÀI ĐẶT] PHẦN 6: ĐÀO QUANG THẮNG TỰ VIẾT CODE TẠI ĐÂY \n";
    cout << "=============================================================\n";

    // === ĐÀO QUANG THẮNG TỰ VIẾT CODE GHI FILE Ở ĐÂY ===
}

// TODO 2: Quang Thắng tự viết hàm đọc dữ liệu từ file TXT nạp vào bảng băm
// Hướng dẫn:
// - Khai báo: ifstream file(tenFile);
// - Làm rỗng bảng băm: khoiTaoBangBam();
// - Đọc từng dòng: while (getline(file, line)):
//     + Tách chuỗi theo dấu "|" để lấy maDuThi, hoTen, gioiTinh, ngaySinh, queQuan.
//     + Băm ký tự đầu để tìm vị trí bucket: viTri = hamBam(layChuCaiDau(ts.hoTen));
//     + Tạo Node và gắn vào cuối: themVaoCuoi(bangBam[viTri], taoNode(ts));
// - Đóng file và trả về số lượng thí sinh đã nạp.
int docFile(string tenFile) {
    // === ĐÀO QUANG THẮNG TỰ VIẾT CODE ĐỌC FILE Ở ĐÂY ===

    return 0; // Tạm thời trả về 0 cho Thắng tự code
}


// =========================================================================
// HÀM MAIN: NGUYỄN BÁ LINH (Trưởng nhóm phụ trách) - [ĐÃ HOÀN THÀNH]
// Giao diện menu điều khiển gọi đến các hàm của 5 bạn
// =========================================================================

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
#endif

    // Khởi tạo bảng băm gồm 26 danh sách liên kết rỗng
    khoiTaoBangBam();

    // Tự động nạp dữ liệu từ file nếu có
    int soLuong = docFile("candidates.txt");
    if (soLuong > 0) {
        cout << "[Thong bao] Da nap " << soLuong << " thi sinh tu candidates.txt\n";
    }

    string inputChon;
    do {
        cout << "\n=============================================================\n";
        cout << "   HE THONG QUAN LY THI SINH - HASH TABLE & LINKED LIST      \n";
        cout << "       DE TAI 8 - CTDL & GT - THS. BUI VAN THUONG            \n";
        cout << "               NHOM 4 - UTH (6 THANH VIEN)                   \n";
        cout << "=============================================================\n";
        cout << "  1. Them thi sinh moi               (Hoang The Anh code)    \n";
        cout << "  2. Tra cuu theo Ma du thi          (Tran Nhat Anh code)    \n";
        cout << "  3. Tra cuu theo Ten tren Bang Bam  (Tran Nhat Anh code)    \n";
        cout << "  4. Hien thi danh sach theo Ten A-Z (Nguyen Huu Cuong code) \n";
        cout << "  5. Phan danh sach vao n phòng thi  (Pham Khanh Hung code)  \n";
        cout << "  6. Xoa thi sinh theo Ma du thi     (Tran Nhat Anh code)    \n";
        cout << "  7. Luu du lieu ra file TXT         (Dao Quang Thang code)  \n";
        cout << "  0. Thoat chuong trinh                                      \n";
        cout << "=============================================================\n";
        cout << "Nhap lua chon cua ban [0-7]: ";

        if (!getline(cin, inputChon)) break;
        if (inputChon.empty()) continue;

        int chon = -1;
        try {
            chon = stoi(inputChon);
        } catch (...) {
            cout << "[Loi] Vui long nhap so tu 0 den 7!\n";
            continue;
        }

        switch (chon) {
            case 1:
                // Gọi chức năng của Hoàng Thế Anh
                nhapThemThiSinh();
                break;

            case 2: {
                // Gọi chức năng của Trần Nhật Anh
                cout << "Nhap ma du thi can tim: ";
                string ma;
                getline(cin, ma);
                Node* p = timTheoMa(ma);
                if (p != NULL) {
                    cout << "\n>>> TIM THAY THI SINH:\n";
                    vector<ThiSinh> ds = { p->data };
                    inBangDanhSach(ds, "KET QUA TRA CUU THEO MA");
                } else {
                    cout << "[Thong bao] Khong tim thay thi sinh co ma: " << ma << "\n";
                }
                break;
            }

            case 3: {
                // Gọi chức năng của Trần Nhật Anh
                cout << "Nhap ten can tra cuu (vd: Linh, Anh, Thang): ";
                string ten;
                getline(cin, ten);
                traCuuTheoTen(ten);
                break;
            }

            case 4: {
                // Gọi chức năng của Nguyễn Hữu Cường
                vector<ThiSinh> all = layTatCaThiSinh();
                sapXepTheoTen(all);
                inBangDanhSach(all, "DANH SACH THI SINH TANG DAN THEO TEN");
                break;
            }

            case 5: {
                // Gọi chức năng của Phạm Khánh Hưng
                cout << "Nhap so luong phong thi n (vd: 3, 4, 5): ";
                string strN;
                getline(cin, strN);
                int n = 3;
                try { n = stoi(strN); } catch (...) { n = 3; }
                phanChiaPhongThi(n);
                break;
            }

            case 6: {
                // Gọi chức năng của Trần Nhật Anh
                cout << "Nhap ma du thi can xoa: ";
                string ma;
                getline(cin, ma);
                if (xoaThiSinhTheoMa(ma)) {
                    cout << "[Thanh cong] Da xoa thi sinh " << ma << " khoi he thong!\n";
                } else {
                    cout << "[Loi] Khong tim thay thi sinh co ma " << ma << "!\n";
                }
                break;
            }

            case 7:
                // Gọi chức năng của Đào Quang Thắng
                luuFile("candidates.txt");
                break;

            case 0:
                cout << "\n[Tam biet] Da thoat chuong trinh!\n";
                return 0;

            default:
                cout << "[Loi] Lua chon khong hop le!\n";
        }
    } while (true);

    return 0;
}
