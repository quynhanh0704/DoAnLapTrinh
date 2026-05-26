// ================================================================
//  De tai 04: Quan ly muon tra sach thu vien
//  Yeu cau: Su dung vector<> de quan ly sach
//  Gom 4 class: Sach, SachMuonVe, SachMuonDoc, ThuVien
//  Bien dich: g++ -std=c++11 QuanLyThuVien_Vector_4Class.cpp -o ThuVien
// ================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include <cstdlib>
using namespace std;
//TRANG
// ================================================================
//  CLASS CO SO: Sach
// ================================================================
class Sach {
protected:
    string maSach;
    string tenSach;
    string chuDe;
    string tacGia;
    string nhaXuatBan;
    int    namXuatBan;
    int    soTrang;
    int    soBanLuu;

public:
    // Constructor mac dinh
    Sach() : namXuatBan(0), soTrang(0), soBanLuu(0) {}

    // Constructor co tham so
    Sach(const string& ma, const string& ten, const string& chu,
         const string& tac, const string& nxb,
         int nam, int trang, int banLuu)
        : maSach(ma), tenSach(ten), chuDe(chu), tacGia(tac),
          nhaXuatBan(nxb), namXuatBan(nam), soTrang(trang), soBanLuu(banLuu) {}

    // Destructor ao (bat buoc khi co ke thua)
    virtual ~Sach() {}

    // ---------- Getter ----------
    string getMaSach()     const { return maSach; }
    string getTenSach()    const { return tenSach; }
    string getChuDe()      const { return chuDe; }
    string getTacGia()     const { return tacGia; }
    string getNhaXuatBan() const { return nhaXuatBan; }
    int    getNamXuatBan() const { return namXuatBan; }
    int    getSoTrang()    const { return soTrang; }
    int    getSoBanLuu()   const { return soBanLuu; }

    // ---------- Setter ----------
    void setTenSach(const string& s)    { tenSach = s; }
    void setChuDe(const string& s)      { chuDe = s; }
    void setTacGia(const string& s)     { tacGia = s; }
    void setNhaXuatBan(const string& s) { nhaXuatBan = s; }
    void setNamXuatBan(int n)           { namXuatBan = n; }
    void setSoTrang(int n)              { soTrang = n; }
    void setSoBanLuu(int n)             { soBanLuu = n; }

    // ---------- Ham thuan ao (pure virtual) ----------
    // Tra ve ky hieu loai sach: 'V' hoac 'D'
    virtual char getLoai() const = 0;

    // Xuat 1 dong trong bang ra man hinh
    virtual void xuatThongTin() const = 0;

    // Ghi 1 dong ra file van ban
    virtual string ghiRaFile() const = 0;

    // Doc 1 dong tu file van ban
    virtual void docTuFile(const string& dong) = 0;

    // ---------- Ham nhap thong tin chung (co the override) ----------
    virtual void nhapThongTin() {
        cout << "  Ma sach    : "; getline(cin, maSach);
        cout << "  Ten sach   : "; getline(cin, tenSach);
        cout << "  Chu de     : "; getline(cin, chuDe);
        cout << "  Tac gia    : "; getline(cin, tacGia);
        cout << "  Nha XB     : "; getline(cin, nhaXuatBan);
        cout << "  Nam XB     : "; cin >> namXuatBan;
        cout << "  So trang   : "; cin >> soTrang;
        cout << "  So ban luu : "; cin >> soBanLuu;
        cin.ignore();
    }

    // Kiem tra trung ma sach
    bool trungMa(const string& ma) const { return maSach == ma; }
};

// ===============================================================================================================================
// TRANG
//  CLASS DAN XUAT: SachMuonVe
// ================================================================
class SachMuonVe : public Sach {
private:
    string ngayMuon;       // Dinh dang: dd/mm/yyyy
    string ngayHenTra;     // Dinh dang: dd/mm/yyyy
    string tenNguoiMuon;

    // Ham noi bo: chuyen "dd/mm/yyyy" -> so nguyen de so sanh ngay
    long ngayToSo(const string& ngay) const {
        if (ngay.size() < 10) return 0;
        int d = stoi(ngay.substr(0, 2));
        int m = stoi(ngay.substr(3, 2));
        int y = stoi(ngay.substr(6, 4));
        return (long)y * 10000 + m * 100 + d;
    }

public:
    // Constructor mac dinh
    SachMuonVe() {}

    // Constructor co tham so
    SachMuonVe(const string& ma, const string& ten, const string& chu,
                    const string& tac, const string& nxb,
                    int nam, int trang, int banLuu,
                    const string& ngMuon, const string& ngHenTra,
                    const string& nguoi)
        : Sach(ma, ten, chu, tac, nxb, nam, trang, banLuu),
          ngayMuon(ngMuon), ngayHenTra(ngHenTra), tenNguoiMuon(nguoi) {}

    // ---------- Getter rieng ----------
    char   getLoai()         const override { return 'V'; }
    string getNgayMuon()     const { return ngayMuon; }
    string getNgayHenTra()   const { return ngayHenTra; }
    string getTenNguoiMuon() const { return tenNguoiMuon; }

    // ---------- Kiem tra qua han ----------
    // Tra ve true neu ngayHomNay > ngayHenTra
    bool isQuaHan(const string& ngayHomNay) const {
        return ngayToSo(ngayHomNay) > ngayToSo(ngayHenTra);
    }

    // ---------- Nhap thong tin ----------
    void nhapThongTin() override {
        Sach::nhapThongTin();   // nhap 8 truong chung truoc
        cout << "  Ten nguoi muon           : "; getline(cin, tenNguoiMuon);
        cout << "  Ngay muon  (dd/mm/yyyy)  : "; getline(cin, ngayMuon);
        cout << "  Ngay hen tra (dd/mm/yyyy): "; getline(cin, ngayHenTra);
    }

    // ---------- Xuat 1 dong bang (goi tu ThuVien) ----------
    void xuatThongTin() const override { xuatDong(0); }

    void xuatDong(int stt) const {
        // Do rong tung cot
        int w[] = {3, 6, 22, 12, 16, 18, 4, 5, 7, 16, 10, 10};

        // Ham cat chuoi neu qua dai
        auto cut = [](const string& s, int maxW) -> string {
            return (s.size() > (size_t)maxW) ? s.substr(0, maxW - 2) + ".." : s;
        };
        auto o = [&](const string& s, int w) {
            cout << "| " << left << setw(w) << cut(s, w) << " ";
        };

// ===============================================================================================================================
// QUANH
// ================================================================
//  CLASS DAN XUAT: SachMuonDoc
// ================================================================
class SachMuonDoc : public Sach {
private:
    string gioMuon;
    string gioTra;

public:
    SachMuonDoc(string ma = "", string ten = "", string cd = "", string tg = "",
                string nxb = "", string ngayXB = "", int trang = 0, int ban = 0,
                string gioM = "", string gioT = "")
        : Sach(ma, ten, cd, tg, nxb, ngayXB, trang, ban) {
        gioMuon = gioM;
        gioTra = gioT;
    }

    string getLoaiSach() { return "Muon doc"; }
    void nhap();
    void xuat();
    bool quaHan();

    // 2 ham doc/ghi file co trong class SachMuonDoc
    void docFile(string dong);
    string ghiFile();

    string chuyenChuoi() {
        return ghiFile();
    }
};

void SachMuonDoc::nhap() {
    Sach::nhap();
    cout << "Nhap gio muon doc (hh:mm): "; cin >> ws;
    getline(cin, gioMuon);
    cout << "Nhap gio tra (hh:mm): ";
    getline(cin, gioTra);
}

void SachMuonDoc::xuat() {
    Sach::xuat();
    cout << left;
    cout << "| " << setw(10) << "D";
    cout << "| " << setw(12) << "";
    cout << "| " << setw(12) << "";
    cout << "| " << setw(10) << gioMuon;
    cout << "| " << setw(10) << gioTra;
    cout << "| " << endl;
}

// Doc day du thong tin cua SachMuonDoc tu file
void SachMuonDoc::docFile(string dong) {
    Sach::docFile(dong);

    stringstream ss(dong);
    string boQua, trangStr, banStr;

    getline(ss, boQua, '|');      // loai
    getline(ss, boQua, '|');      // ma
    getline(ss, boQua, '|');      // ten
    getline(ss, boQua, '|');      // chu de
    getline(ss, boQua, '|');      // tac gia
    getline(ss, boQua, '|');      // nha xuat ban
    getline(ss, boQua, '|');      // ngay xuat ban
    getline(ss, trangStr, '|');   // so trang
    getline(ss, banStr, '|');     // so ban luu
    getline(ss, gioMuon, '|');
    getline(ss, gioTra, '|');
}

// Ghi day du thong tin cua SachMuonDoc ra file
string SachMuonDoc::ghiFile() {
    stringstream ss;
    ss << "D|" << Sach::ghiFile() << "|" << gioMuon << "|" << gioTra;
    return ss.str();
}

bool SachMuonDoc::quaHan() {
    if (gioMuon.length() < 5 || gioTra.length() < 5) return false;

    int phutMuon = atoi(gioMuon.substr(0, 2).c_str()) * 60
                 + atoi(gioMuon.substr(3, 2).c_str());
    int phutTra = atoi(gioTra.substr(0, 2).c_str()) * 60
                + atoi(gioTra.substr(3, 2).c_str());

    // Gia su muon doc qua 240 phut la qua gio
    return (phutTra - phutMuon) > 240;
}

// ===============================================================================================================================
// THU + HIEN
//  CLASS QUAN LY: ThuVien
// ================================================================
class ThuVien {
private:
    vector<Sach*> dsSach;

public:
    void thongKe() {} // HIEN
    void themSach() {} // HIEN
    void xoaSach() {} // HIEN
    void timKiemMa() {} // THU
    void timKiemTen() {} // THU
    void timKiemNXB() {} // THU
    void Menu() {} // THU
    void dieuHuong() {} // THU
};
// ===================================================================================================================================
//  HIEN
//  CLASS GIAO DIEN (Ve bang)  //
// ================================================================

class GiaoDien {
public:
    static void duongKeVe(ostream& os) { os << "  +----------+-------------------------+---------------+-----+------------------+------------+------------+-------------+\n"; }
    static void duongKeDoc(ostream& os) { os << "  +----------+-------------------------+---------------+-----+----------+----------+----------------------+\n"; 
    }
    
    static void tieuDeVe(ostream& os) {
        os << "\n  +-----------------------------------------------------------------------------------------------------------------------+\n"
           << "  |                                        DANH SACH MUON VE                                                              |\n";
        duongKeVe(os);
        os << left << "  | " << setw(9) << "Ma sach" << "| " << setw(24) << "Ten sach" << "| " << setw(14) << "Nha xuat ban" 
           << "| " << setw(4) << "SL" << "| " << setw(17) << "Nguoi muon" << "| " << setw(11) << "Ngay muon" 
           << "| " << setw(11) << "Ngay tra" << "| " << setw(12) << "Trang thai" << "|\n";
        duongKeVe(os);
    }

    static void tieuDeDoc(ostream& os) {
        os << "\n  +-------------------------------------------------------------------------------------------------------+\n"
           << "  |                                        DANH SACH MUON DOC                                             |\n";
        duongKeDoc(os);
        os << left << "  | " << setw(9) << "Ma sach" << "| " << setw(24) << "Ten sach" << "| " << setw(14) << "Nha xuat ban" 
           << "| " << setw(4) << "SL" << "| " << setw(9) << "Gio muon" << "| " << setw(9) << "Gio tra" 
           << "| " << setw(21) << "Trang thai/Thoi gian" << "|\n";
        duongKeDoc(os);
    }

    static void xuatBang(ostream& os, const vector<Sach*>& ds) {
        tieuDeVe(os); bool coVe = false;
        for (const Sach* s : ds) if (s->getLoai() == 'V') { s->xuatDong(os); duongKeVe(os); coVe = true; }
        if (!coVe) { os << "  | " << left << setw(116) << "Khong co sach muon ve" << "|\n"; duongKeVe(os); }

        tieuDeDoc(os); bool coDoc = false;
        for (const Sach* s : ds) if (s->getLoai() == 'D') { s->xuatDong(os); duongKeDoc(os); coDoc = true; }
        if (!coDoc) { os << "  | " << left << setw(102) << "Khong co sach muon doc" << "|\n"; duongKeDoc(os); }
    }
};


    
// ================================================================
//  HAM MAIN
// ================================================================
int main() {
    
}
