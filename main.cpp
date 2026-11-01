#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

// =========================================================================
// GỌI CÁC FILE CHỨC NĂNG CỦA 6 THÀNH VIÊN TRONG NHÓM
// =========================================================================
#include "CauTrucChung.h"         // PHẦN 1: Nguyễn Bá Linh (Trưởng nhóm - Cấu trúc chung)
#include "ThemThiSinh_TheAnh.h"     // PHẦN 2: Hoàng Thế Anh (Chức năng Thêm thí sinh)
#include "TraCuuXoa_NhatAnh.h"      // PHẦN 3: Trần Nhật Anh (Chức năng Tra cứu & Xóa)
#include "SapXep_HuuCuong.h"        // PHẦN 4: Nguyễn Hữu Cường (Chức năng Sắp xếp & Hiển thị)
#include "PhanPhong_KhanhHung.h"    // PHẦN 5: Phạm Khánh Hưng (Chức năng Phân phòng thi)
#include "DocGhiFile_QuangThang.h"  // PHẦN 6: Đào Quang Thắng (Chức năng Đọc & Ghi file)

// =========================================================================
// HÀM MAIN: NGUYỄN BÁ LINH (Trưởng nhóm phụ trách điều phối & Menu chính)
// =========================================================================

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
#endif

    // Khởi tạo bảng băm
    khoiTaoBangBam();

    // Tự động nạp dữ liệu mẫu từ candidates.txt
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
        cout << "  5. Phan danh sach vao n phong thi  (Pham Khanh Hung code)  \n";
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
                cout << "\n[Tam biet] Da luu du lieu va thoat chuong trinh!\n";
                luuFile("candidates.txt");
                return 0;

            default:
                cout << "[Loi] Lua chon khong hop le!\n";
        }
    } while (true);

    return 0;
}
