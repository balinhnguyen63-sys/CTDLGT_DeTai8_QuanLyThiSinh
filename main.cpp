#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <vector>
#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

// =========================================================================
// PHẦN 1: NGUYỄN BÁ LINH (Trưởng nhóm)
// Thiết kế: Cấu trúc Thí sinh, Node, Danh sách liên kết đơn & Bảng băm
// =========================================================================

// 1. Cấu trúc thông tin của một Thí sinh
struct ThiSinh {
    string maDuThi;  // Mã dự thi (ví dụ: SBD001)
    string hoTen;    // Họ và tên (ví dụ: Nguyen Ba Linh)
    string gioiTinh; // Giới tính: Nam hoặc Nu
    string ngaySinh; // Ngày sinh: DD/MM/YYYY
    string queQuan;  // Quê quán: TP. Ho Chi Minh
};

// 2. Cấu trúc 1 Node trong danh sách liên kết
struct Node {
    ThiSinh data;
    Node* next;
};

// 3. Cấu trúc Danh sách liên kết đơn (List)
struct List {
    Node* head;
    Node* tail;
};

// Hàm khởi tạo danh sách liên kết rỗng
void khoiTaoList(List &ds) {
    ds.head = NULL;
    ds.tail = NULL;
}

// 4. BẢNG BĂM (Hash Table)
// Bảng băm dạng bảng tra thực chất là một mảng gồm 26 danh sách liên kết đơn,
// tương ứng với 26 chữ cái trong bảng chữ cái tiếng Anh từ 'A' đến 'Z' (A=0, B=1, ..., Z=25).
List bangBam[26];

// Khởi tạo bảng băm rỗng
void khoiTaoBangBam() {
    for (int i = 0; i < 26; i++) {
        khoiTaoList(bangBam[i]);
    }
}

// Hàm lấy tên (từ cuối cùng trong chuỗi Họ và tên)
// Ví dụ: "Nguyen Ba Linh" -> lấy được "Linh"
string layTen(string hoTen) {
    if (hoTen.empty()) return "";
    int pos = hoTen.find_last_of(" ");
    if (pos == -1) return hoTen;
    return hoTen.substr(pos + 1);
}

// Hàm lấy chữ cái đầu của Tên và chuyển thành chữ in hoa
// Ví dụ: Tên "Linh" -> lấy được chữ cái 'L'
char layChuCaiDau(string hoTen) {
    string ten = layTen(hoTen);
    if (ten.empty()) return 'A';
    char c = ten[0];
    if (c >= 'a' && c <= 'z') c = c - 32; // Đổi chữ thường sang chữ hoa
    if (c >= 'A' && c <= 'Z') return c;
    return 'A';
}

// Hàm băm (Hash Function) dạng bảng tra
// Ánh xạ chữ cái đầu ('A'..'Z') thành chỉ số mảng [0..25]
// Ví dụ: 'A' -> 0, 'B' -> 1, ..., 'L' -> 11, 'Z' -> 25
int hamBam(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c - 'A';
    }
    return 0;
}


// =========================================================================
// PHẦN 2: HOÀNG THẾ ANH
// Chức năng: Thêm thí sinh mới vào Bảng băm & Cập nhật thông tin
// =========================================================================

// Tạo một node mới chứa thông tin thí sinh
Node* taoNode(ThiSinh ts) {
    Node* p = new Node;
    p->data = ts;
    p->next = NULL;
    return p;
}

// Thêm node vào cuối danh sách liên kết
void themVaoCuoi(List &ds, Node* p) {
    if (ds.head == NULL) {
        ds.head = ds.tail = p;
    } else {
        ds.tail->next = p;
        ds.tail = p;
    }
}

// Kiểm tra mã dự thi đã tồn tại trong bảng băm chưa
bool kiemTraTrungMa(string ma) {
    for (int i = 0; i < 26; i++) {
        Node* p = bangBam[i].head;
        while (p != NULL) {
            if (p->data.maDuThi == ma) return true;
            p = p->next;
        }
    }
    return false;
}

// Thêm một thí sinh vào đúng nhóm chữ cái trong bảng băm
bool themThiSinh(ThiSinh ts) {
    if (kiemTraTrungMa(ts.maDuThi)) {
        cout << "[Loi] Ma du thi " << ts.maDuThi << " da ton tai!\n";
        return false;
    }
    // Lấy chữ cái đầu của Tên và băm ra vị trí bucket
    char chuCai = layChuCaiDau(ts.hoTen);
    int viTri = hamBam(chuCai);

    Node* p = taoNode(ts);
    themVaoCuoi(bangBam[viTri], p);
    return true;
}

// Nhập thông tin thí sinh từ bàn phím
void nhapThemThiSinh() {
    ThiSinh ts;
    cout << "\n--- THEM THI SINH MOI ---\n";
    cout << "Nhap ma du thi (vd: SBD031): ";
    getline(cin, ts.maDuThi);
    if (ts.maDuThi.empty()) {
        cout << "[Loi] Ma du thi khong duoc de trong!\n";
        return;
    }
    if (kiemTraTrungMa(ts.maDuThi)) {
        cout << "[Loi] Ma du thi nay da co trong he thong!\n";
        return;
    }

    cout << "Nhap ho va ten: ";
    getline(cin, ts.hoTen);
    cout << "Nhap gioi tinh (Nam/Nu): ";
    getline(cin, ts.gioiTinh);
    cout << "Nhap ngay sinh (DD/MM/YYYY): ";
    getline(cin, ts.ngaySinh);
    cout << "Nhap que quan: ";
    getline(cin, ts.queQuan);

    if (themThiSinh(ts)) {
        cout << "[Thanh cong] Da them thi sinh " << ts.hoTen 
             << " vao nhom chu cai '" << layChuCaiDau(ts.hoTen) << "'!\n";
    }
}


// =========================================================================
// PHẦN 3: TRẦN NHẬT ANH
// Chức năng: Tra cứu thông tin thí sinh & Xóa thí sinh
// =========================================================================

// In thông tin 1 thí sinh theo dạng dòng
void inMotThiSinh(ThiSinh ts, int stt) {
    cout << "|" << left << setw(4)  << stt
         << "|" << left << setw(10) << ts.maDuThi
         << "|" << left << setw(25) << ts.hoTen
         << "|" << left << setw(10) << ts.gioiTinh
         << "|" << left << setw(14) << ts.ngaySinh
         << "|" << left << setw(18) << ts.queQuan << "|\n";
}

// Tra cứu theo Mã dự thi
Node* timTheoMa(string ma) {
    for (int i = 0; i < 26; i++) {
        Node* p = bangBam[i].head;
        while (p != NULL) {
            if (p->data.maDuThi == ma) return p;
            p = p->next;
        }
    }
    return NULL;
}

// Tra cứu theo Tên (Ứng dụng ưu điểm của bảng băm: chỉ tìm trong đúng bucket chữ cái)
void traCuuTheoTen(string tenCanTim) {
    char chuCai = layChuCaiDau(tenCanTim);
    int viTri = hamBam(chuCai);

    cout << "\n>>> Tim kiem trong nhom chu cai '" << chuCai << "' (bucket " << viTri << "):\n";
    cout << "=================================================================================\n";
    cout << "|" << left << setw(4)  << "STT"
         << "|" << left << setw(10) << "SBD"
         << "|" << left << setw(25) << "Ho va ten"
         << "|" << left << setw(10) << "Gioi tinh"
         << "|" << left << setw(14) << "Ngay sinh"
         << "|" << left << setw(18) << "Que quan" << "|\n";
    cout << "=================================================================================\n";

    Node* p = bangBam[viTri].head;
    int stt = 1;
    bool timThay = false;

    while (p != NULL) {
        string tenTS = layTen(p->data.hoTen);
        // So sánh tên hoặc tìm từ khóa trong họ tên
        if (p->data.hoTen.find(tenCanTim) != string::npos || tenTS == tenCanTim) {
            inMotThiSinh(p->data, stt++);
            timThay = true;
        }
        p = p->next;
    }

    if (!timThay) {
        cout << "| Khong tim thay thi sinh nao phu hop trong nhom nay!                          |\n";
    }
    cout << "=================================================================================\n";
}

// Xóa thí sinh theo mã dự thi khỏi danh sách liên kết
bool xoaThiSinhTheoMa(string ma) {
    for (int i = 0; i < 26; i++) {
        Node* curr = bangBam[i].head;
        Node* prev = NULL;

        while (curr != NULL) {
            if (curr->data.maDuThi == ma) {
                // Nếu node cần xóa nằm ở đầu danh sách
                if (prev == NULL) {
                    bangBam[i].head = curr->next;
                    if (bangBam[i].head == NULL) bangBam[i].tail = NULL;
                } else {
                    prev->next = curr->next;
                    if (curr == bangBam[i].tail) bangBam[i].tail = prev;
                }
                delete curr; // Giải phóng bộ nhớ
                return true;
            }
            prev = curr;
            curr = curr->next;
        }
    }
    return false;
}


// =========================================================================
// PHẦN 4: NGUYỄN HỮU CƯỜNG
// Chức năng: Sắp xếp danh sách thí sinh tăng dần theo tên & Hiển thị
// =========================================================================

// Lấy toàn bộ thí sinh từ 26 bucket vào 1 vector để sắp xếp
vector<ThiSinh> layTatCaThiSinh() {
    vector<ThiSinh> danhSach;
    for (int i = 0; i < 26; i++) {
        Node* p = bangBam[i].head;
        while (p != NULL) {
            danhSach.push_back(p->data);
            p = p->next;
        }
    }
    return danhSach;
}

// Hàm so sánh tên 2 thí sinh (ưu tiên so sánh Tên -> rồi so sánh Họ tên)
bool soSanhTen(ThiSinh a, ThiSinh b) {
    string tenA = layTen(a.hoTen);
    string tenB = layTen(b.hoTen);
    if (tenA != tenB) return tenA < tenB;
    return a.hoTen < b.hoTen;
}

// Thuật toán sắp xếp danh sách theo Tên tăng dần (Selection Sort / Trộn)
void sapXepTheoTen(vector<ThiSinh> &ds) {
    int n = ds.size();
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (soSanhTen(ds[j], ds[minIdx])) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            ThiSinh temp = ds[i];
            ds[i] = ds[minIdx];
            ds[minIdx] = temp;
        }
    }
}

// In danh sách thí sinh ra màn hình dạng bảng
void inBangDanhSach(vector<ThiSinh> ds, string tieuDe) {
    cout << "\n=================================================================================\n";
    cout << "                    " << tieuDe << "\n";
    cout << "=================================================================================\n";
    cout << "|" << left << setw(4)  << "STT"
         << "|" << left << setw(10) << "SBD"
         << "|" << left << setw(25) << "Ho va ten"
         << "|" << left << setw(10) << "Gioi tinh"
         << "|" << left << setw(14) << "Ngay sinh"
         << "|" << left << setw(18) << "Que quan" << "|\n";
    cout << "=================================================================================\n";

    if (ds.empty()) {
        cout << "| Danh sach rong!                                                               |\n";
    } else {
        for (size_t i = 0; i < ds.size(); i++) {
            inMotThiSinh(ds[i], i + 1);
        }
    }
    cout << "=================================================================================\n";
    cout << "Tong so thi sinh: " << ds.size() << "\n";
}


// =========================================================================
// PHẦN 5: PHẠM KHÁNH HƯNG
// Chức năng: Phân danh sách vào n phòng thi sao cho xác suất trùng chữ cái đầu ít nhất
// =========================================================================

struct PhongThi {
    int soPhong;
    vector<ThiSinh> danhSach;
    int demChuCai[26] = {0}; // Đếm số thí sinh của mỗi chữ cái A-Z trong phòng này
};

// Thuật toán phân phòng: Lần lượt rải đều các thí sinh trong từng bucket vào n phòng thi
void phanChiaPhongThi(int nPhong) {
    if (nPhong <= 0) nPhong = 1;
    vector<PhongThi> dsPhong(nPhong);
    for (int i = 0; i < nPhong; i++) {
        dsPhong[i].soPhong = i + 1;
    }

    // Duyệt qua từng bucket chữ cái A-Z trong bảng băm
    for (int i = 0; i < 26; i++) {
        Node* p = bangBam[i].head;
        while (p != NULL) {
            // Tìm phòng thi đang có ít thí sinh mang chữ cái này nhất để xếp vào
            int phongTotNhat = 0;
            int minCungChuCai = dsPhong[0].demChuCai[i];
            int minSiSo = dsPhong[0].danhSach.size();

            for (int r = 1; r < nPhong; r++) {
                if (dsPhong[r].demChuCai[i] < minCungChuCai) {
                    minCungChuCai = dsPhong[r].demChuCai[i];
                    minSiSo = dsPhong[r].danhSach.size();
                    phongTotNhat = r;
                } else if (dsPhong[r].demChuCai[i] == minCungChuCai) {
                    if ((int)dsPhong[r].danhSach.size() < minSiSo) {
                        minSiSo = dsPhong[r].danhSach.size();
                        phongTotNhat = r;
                    }
                }
            }

            // Xếp thí sinh vào phòng tốt nhất
            dsPhong[phongTotNhat].danhSach.push_back(p->data);
            dsPhong[phongTotNhat].demChuCai[i]++;

            p = p->next;
        }
    }

    // In kết quả phân phòng và tính xác suất trùng chữ cái đầu
    cout << "\n=================================================================================\n";
    cout << "                  KET QUA PHAN CHIA VAO " << nPhong << " PHONG THI\n";
    cout << "=================================================================================\n";

    double tongXacSuat = 0;

    for (int i = 0; i < nPhong; i++) {
        int m = dsPhong[i].danhSach.size();
        long long soCapTrung = 0;
        for (int c = 0; c < 26; c++) {
            int k = dsPhong[i].demChuCai[c];
            if (k >= 2) soCapTrung += (k * (k - 1)) / 2;
        }

        double xacSuat = 0.0;
        if (m >= 2) {
            long long tongCap = (1LL * m * (m - 1)) / 2;
            xacSuat = (100.0 * soCapTrung) / tongCap;
        }
        tongXacSuat += xacSuat;

        cout << "\n>>> [PHONG THI SO " << dsPhong[i].soPhong << "] - Si so: " << m 
             << " thi sinh | So cap trung chu cai dau: " << soCapTrung 
             << " | Xac suat trung: " << fixed << setprecision(2) << xacSuat << "%\n";
        cout << "---------------------------------------------------------------------------------\n";
        for (size_t j = 0; j < dsPhong[i].danhSach.size(); j++) {
            ThiSinh ts = dsPhong[i].danhSach[j];
            cout << "   " << setw(3) << (j + 1) << ". " 
                 << setw(8) << ts.maDuThi << " - " 
                 << setw(22) << ts.hoTen 
                 << " (Ten: " << layTen(ts.hoTen) << ", Chu: '" << layChuCaiDau(ts.hoTen) << "')\n";
        }
    }

    cout << "\n=================================================================================\n";
    cout << "XAC SUAT TRUNG CHU CAI DAU TRUNG BINH CAC PHONG: " 
         << fixed << setprecision(2) << (tongXacSuat / nPhong) << "%\n";
    cout << "=================================================================================\n";
}


// =========================================================================
// PHẦN 6: ĐÀO QUANG THẮNG
// Chức năng: Lưu trữ và Đọc dữ liệu từ file TXT (candidates.txt)
// =========================================================================

// Lưu toàn bộ bảng băm ra file TXT
void luuFile(string tenFile) {
    ofstream file(tenFile);
    if (!file.is_open()) {
        cout << "[Loi] Khong the mo file de ghi!\n";
        return;
    }

    for (int i = 0; i < 26; i++) {
        Node* p = bangBam[i].head;
        while (p != NULL) {
            file << p->data.maDuThi << "|"
                 << p->data.hoTen   << "|"
                 << p->data.gioiTinh<< "|"
                 << p->data.ngaySinh<< "|"
                 << p->data.queQuan << "\n";
            p = p->next;
        }
    }
    file.close();
    cout << "[Thanh cong] Da luu du lieu vao file: " << tenFile << "\n";
}

// Đọc dữ liệu từ file TXT vào bảng băm
int docFile(string tenFile) {
    ifstream file(tenFile);
    if (!file.is_open()) return 0;

    khoiTaoBangBam(); // Làm rỗng bảng băm trước khi nạp
    string line;
    int dem = 0;

    while (getline(file, line)) {
        if (line.empty()) continue;
        size_t p1 = line.find("|");
        size_t p2 = line.find("|", p1 + 1);
        size_t p3 = line.find("|", p2 + 1);
        size_t p4 = line.find("|", p3 + 1);

        if (p1 != string::npos && p2 != string::npos && p3 != string::npos && p4 != string::npos) {
            ThiSinh ts;
            ts.maDuThi  = line.substr(0, p1);
            ts.hoTen    = line.substr(p1 + 1, p2 - p1 - 1);
            ts.gioiTinh = line.substr(p2 + 1, p3 - p2 - 1);
            ts.ngaySinh = line.substr(p3 + 1, p4 - p3 - 1);
            ts.queQuan  = line.substr(p4 + 1);

            char chuCai = layChuCaiDau(ts.hoTen);
            int viTri = hamBam(chuCai);
            themVaoCuoi(bangBam[viTri], taoNode(ts));
            dem++;
        }
    }
    file.close();
    return dem;
}


// =========================================================================
// HÀM MAIN & MENU ĐIỀU KHIỂN CHÍNH
// =========================================================================

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
#endif

    khoiTaoBangBam();

    // Tự động nạp dữ liệu từ file nếu có
    int soLuong = docFile("candidates.txt");
    if (soLuong > 0) {
        cout << "[Thong bao] Da tu dong nap " << soLuong << " thi sinh tu candidates.txt\n";
    }

    string inputChon;
    do {
        cout << "\n=============================================================\n";
        cout << "   HE THONG QUAN LY THI SINH - HASH TABLE & LINKED LIST      \n";
        cout << "       DE TAI 8 - CTDL & GT - THS. BUI VAN THUONG            \n";
        cout << "                  NHOM 4 - UTH                               \n";
        cout << "=============================================================\n";
        cout << "  1. Them thi sinh moi\n";
        cout << "  2. Tra cuu thi sinh theo Ma du thi\n";
        cout << "  3. Tra cuu thi sinh theo Ten (Tra cuu tren Bang Bam)\n";
        cout << "  4. Hien thi danh sach thi sinh theo thu tu Ten tang dan\n";
        cout << "  5. Phan danh sach vao n phong thi (Giam trung chu cai dau)\n";
        cout << "  6. Xoa thi sinh theo Ma du thi\n";
        cout << "  7. Luu du lieu ra file TXT (candidates.txt)\n";
        cout << "  0. Thoat chuong trinh\n";
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
                nhapThemThiSinh();
                break;
            case 2: {
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
                cout << "Nhap ten can tra cuu (vd: Linh, Anh, Thang): ";
                string ten;
                getline(cin, ten);
                traCuuTheoTen(ten);
                break;
            }
            case 4: {
                vector<ThiSinh> all = layTatCaThiSinh();
                sapXepTheoTen(all);
                inBangDanhSach(all, "DANH SACH THI SINH TANG DAN THEO TEN");
                break;
            }
            case 5: {
                cout << "Nhap so luong phong thi n (vd: 3, 4, 5): ";
                string strN;
                getline(cin, strN);
                int n = 3;
                try { n = stoi(strN); } catch (...) { n = 3; }
                phanChiaPhongThi(n);
                break;
            }
            case 6: {
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
                luuFile("candidates.txt");
                break;
            case 0:
                cout << "\n[Tam biet] Da luu du lieu va thoat chuong trinh!\n";
                luuFile("candidates.txt");
                return 0;
            default:
                cout << "[Loi] Lua chon khong hop le!\n";
        }
    } while (true);

    return 0;
}
