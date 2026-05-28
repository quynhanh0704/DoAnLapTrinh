// ================================================================ 
//  De tai 04: Quan ly muon tra sach thu vien
//  Ngon ngu  : C++ (C++11)
// ================================================================
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include <ctime>
#include <cctype>
using namespace std;

// ================================================================
//  LOP CO SO TRUU TUONG: Sach
// ================================================================
class Sach {
protected:
    string maSach, tenSach, tacGia;
    int    soBanLuu;

public:
    Sach() : soBanLuu(0) {}
    virtual ~Sach() {}

    string getMaSach() const { return maSach; }
    string getTenSach() const { return tenSach; }
    string getTacGia() const { return tacGia; }
    
    // Cac setter de phuc vu chuc nang Sua sach
    void setMaSach(string ma) { maSach = ma; }
    void setTenSach(string ten) { tenSach = ten; }
    void setTacGia(string tg) { tacGia = tg; }
    void setSoBanLuu(int sl) { soBanLuu = sl; }
    
    virtual char   getLoai() const = 0;
    virtual bool   isQuaHan() const = 0; 
    virtual void   xuatDong(ostream& os) const = 0; 
    virtual string ghiRaFile() const = 0;
    virtual void   docTuFile(const string& dong) = 0;

    virtual void nhapThongTin() {
        cout << "  Ma sach    : "; getline(cin, maSach);
        cout << "  Ten sach   : "; getline(cin, tenSach);
        cout << "  Tac gia    : "; getline(cin, tacGia);
        cout << "  Tong SL    : "; cin >> soBanLuu;
        cin.ignore();
    }
};

// ================================================================
//  LOP DAN XUAT: SachMuonVe
// ================================================================
class SachMuonVe : public Sach {
private:
    string ngayMuon, ngayHenTra, tenNguoiMuon;

    int dateToInt(const string& dateStr) const {
        if (dateStr.length() < 10) return 99999999;
        return stoi(dateStr.substr(6, 4)) * 10000 + stoi(dateStr.substr(3, 2)) * 100 + stoi(dateStr.substr(0, 2));
    }

public:
    SachMuonVe() {}
    char getLoai() const override { return 'V'; }

    bool isQuaHan() const override {
        if (ngayHenTra.empty()) return false;
        time_t t = time(0); tm* now = localtime(&t);
        int currentYMD = (now->tm_year + 1900) * 10000 + (now->tm_mon + 1) * 100 + now->tm_mday;
        return currentYMD > dateToInt(ngayHenTra);
    }

    void nhapThongTin() override {
        Sach::nhapThongTin();
        cout << "  Ten nguoi muon           : "; getline(cin, tenNguoiMuon);
        cout << "  Ngay muon  (dd/mm/yyyy)  : "; getline(cin, ngayMuon);
        cout << "  Ngay hen tra (dd/mm/yyyy): "; getline(cin, ngayHenTra);
    }

    void xuatDong(ostream& os) const override {
        string trangThai = isQuaHan() ? "[QUA HAN]" : "";
        os << left << "  |"
           << " " << setw(9)  << maSach       << "|"
           << " " << setw(24) << tenSach      << "|"
           << " " << setw(14) << tacGia       << "|"
           << " " << setw(4)  << soBanLuu     << "|"
           << " " << setw(17) << tenNguoiMuon << "|"
           << " " << setw(11) << ngayMuon     << "|"
           << " " << setw(11) << ngayHenTra   << "|"
           << " " << setw(12) << trangThai    << "|\n";
    }

    string ghiRaFile() const override {
        ostringstream o;
        o << "V|" << maSach << "|" << tenSach << "|" << tacGia << "|" << soBanLuu << "|"
          << ngayMuon << "|" << ngayHenTra << "|" << tenNguoiMuon;
        return o.str();
    }

    void docTuFile(const string& dong) override {
        istringstream ss(dong); string tok;
        getline(ss, tok, '|'); getline(ss, maSach, '|'); getline(ss, tenSach, '|');
        getline(ss, tacGia, '|'); getline(ss, tok, '|'); soBanLuu = stoi(tok);
        getline(ss, ngayMuon, '|'); getline(ss, ngayHenTra, '|'); getline(ss, tenNguoiMuon);
    }
};

// ================================================================
//  LOP DAN XUAT: SachMuonDoc
// ================================================================
class SachMuonDoc : public Sach {
private:
    string gioMuon, gioTra;

    int gioToPhut(const string& g) const {
        if (g.size() < 5) return 0;
        return stoi(g.substr(0, 2)) * 60 + stoi(g.substr(3, 2));
    }

    int tinhThoiGianDoc() const {
        if (gioMuon.empty()) return -1;
        int phutMuon = gioToPhut(gioMuon), phutTra;
        if (gioTra.empty() || gioTra == "--:--") {
            time_t t = time(0); tm* now = localtime(&t);
            phutTra = now->tm_hour * 60 + now->tm_min;
        } else phutTra = gioToPhut(gioTra);
        
        int diff = phutTra - phutMuon;
        return (diff < 0) ? diff + 1440 : diff;
    }

public:
    SachMuonDoc() {}
    char getLoai() const override { return 'D'; }

    bool isQuaHan() const override { return (tinhThoiGianDoc() > 240); }

    void nhapThongTin() override {
        Sach::nhapThongTin();
        cout << "  Gio muon (HH:MM)                             : "; getline(cin, gioMuon);
        cout << "  Gio tra  (HH:MM, nhap '--:--' neu chua tra)  : "; getline(cin, gioTra);
    }

    void xuatDong(ostream& os) const override {
        string gt = gioTra.empty() ? "--:--" : gioTra;
        int t = tinhThoiGianDoc();
        string thoiGian = to_string(t/60) + "h" + to_string(t%60) + "m " + (isQuaHan() ? "[QUA HAN]" : "");
        
        os << left << "  |"
           << " " << setw(9)  << maSach     << "|"
           << " " << setw(24) << tenSach    << "|"
           << " " << setw(14) << tacGia     << "|"
           << " " << setw(4)  << soBanLuu   << "|"
           << " " << setw(9)  << gioMuon    << "|"
           << " " << setw(9)  << gt         << "|"
           << " " << setw(21) << thoiGian   << "|\n";
    }

    string ghiRaFile() const override {
        ostringstream o;
        o << "D|" << maSach << "|" << tenSach << "|" << tacGia << "|" << soBanLuu << "|"
          << gioMuon << "|" << (gioTra.empty() ? "--:--" : gioTra);
        return o.str();
    }

    void docTuFile(const string& dong) override {
        istringstream ss(dong); string tok;
        getline(ss, tok, '|'); getline(ss, maSach, '|'); getline(ss, tenSach, '|');
        getline(ss, tacGia, '|'); getline(ss, tok, '|'); soBanLuu = stoi(tok);
        getline(ss, gioMuon, '|'); getline(ss, gioTra);
    }
};

// ================================================================
//  CLASS GIAO DIEN (Ve bang)
// ================================================================
class GiaoDien {
public:
    static void duongKeVe(ostream& os) { os << "  +----------+-------------------------+---------------+-----+------------------+------------+------------+-------------+\n"; }
    static void duongKeDoc(ostream& os) { os << "  +----------+-------------------------+---------------+-----+----------+----------+----------------------+\n"; }
    
    static void tieuDeVe(ostream& os) {
        os << "\n  +-----------------------------------------------------------------------------------------------------------------------+\n"
           << "  |                                        DANH SACH MUON VE                                                              |\n";
        duongKeVe(os);
        os << left << "  | " << setw(9) << "Ma sach" << "| " << setw(24) << "Ten sach" << "| " << setw(14) << "Tac gia" 
           << "| " << setw(4) << "SL" << "| " << setw(17) << "Nguoi muon" << "| " << setw(11) << "Ngay muon" 
           << "| " << setw(11) << "Ngay tra" << "| " << setw(12) << "Trang thai" << "|\n";
        duongKeVe(os);
    }

    static void tieuDeDoc(ostream& os) {
        os << "\n  +-------------------------------------------------------------------------------------------------------+\n"
           << "  |                                        DANH SACH MUON DOC                                             |\n";
        duongKeDoc(os);
        os << left << "  | " << setw(9) << "Ma sach" << "| " << setw(24) << "Ten sach" << "| " << setw(14) << "Tac gia" 
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
//  LOP QUAN LY: ThuVien
// ================================================================
class ThuVien {
private:
    vector<Sach*> dsSach;
    string tenFile;

    int timViTri(const string& ma) const {
        for (int i = 0; i < (int)dsSach.size(); i++)
            if (dsSach[i]->getMaSach() == ma) return i;
        return -1;
    }

public:
    ThuVien(const string& file = "input.txt") : tenFile(file) {}
    ~ThuVien() { for (Sach* s : dsSach) delete s; }

    void docTuFile() {
        ifstream f(tenFile);
        if (!f.is_open()) { cout << "  [!] Khong mo duoc file: " << tenFile << "\n"; return; }
        for (Sach* s : dsSach) delete s; dsSach.clear();
        
        string dong;
        while (getline(f, dong)) {
            if (dong.empty()) continue;
            Sach* s = nullptr;
            if (dong[0] == 'V') s = new SachMuonVe();
            else if (dong[0] == 'D') s = new SachMuonDoc();
            if (s) { s->docTuFile(dong); dsSach.push_back(s); }
        }
        cout << "  Da doc " << dsSach.size() << " cuon sach tu file.\n";
    }

    void ghiRaFile() const {
        ofstream f(tenFile);
        if (!f.is_open()) return;
        for (const Sach* s : dsSach) f << s->ghiRaFile() << "\n";
    }

    void xuatDanhSach() const {
        if (dsSach.empty()) { cout << "  Danh sach trong!\n"; return; }
        GiaoDien::xuatBang(cout, dsSach);
    }

    void xuatDanhSachRaFile(const string& fileXuat) const {
        ofstream f(fileXuat);
        if (!f.is_open()) { cout << "  [!] Khong mo duoc file xuat!\n"; return; }
        GiaoDien::xuatBang(f, dsSach);
        cout << "  Da xuat ra file: " << fileXuat << "\n";
    }

    void timKiem() const {
        string tu; cout << "  Nhap tu khoa (Ma/Ten/TacGia): "; getline(cin, tu);
        for (char& c : tu) c = tolower(c);
        
        vector<Sach*> dsKetQua;
        for (Sach* s : dsSach) {
            string ma = s->getMaSach(), ten = s->getTenSach(), tg = s->getTacGia();
            for (char& c : ma) c = tolower(c); 
            for (char& c : ten) c = tolower(c); 
            for (char& c : tg) c = tolower(c);
            if (ma.find(tu) != string::npos || ten.find(tu) != string::npos || tg.find(tu) != string::npos)
                dsKetQua.push_back(s);
        }
        
        if (dsKetQua.empty()) cout << "  => Khong tim thay ket qua phu hop!\n";
        else { cout << "  => Phat hien " << dsKetQua.size() << " ket qua:\n"; GiaoDien::xuatBang(cout, dsKetQua); }
    }

    void themSach() {
        cout << "  Chon loai sach (1. Muon ve | 2. Muon doc): ";
        int ch; cin >> ch; cin.ignore();
        Sach* s = nullptr;
        if (ch == 1) s = new SachMuonVe();
        else if (ch == 2) s = new SachMuonDoc();
        else { cout << "  Lua chon khong hop le!\n"; return; }
        
        s->nhapThongTin();
        if (timViTri(s->getMaSach()) >= 0) { cout << "  [!] Ma sach da ton tai! Huy them.\n"; delete s; return; }
        dsSach.push_back(s); ghiRaFile();
        cout << "  Da them sach va cap nhat file.\n";
    }

    void xoaSach() {
        string ma; cout << "  Ma sach can xoa: "; getline(cin, ma);
        int i = timViTri(ma);
        if (i < 0) { cout << "  Khong tim thay ma sach!\n"; return; }
        delete dsSach[i]; dsSach.erase(dsSach.begin() + i); ghiRaFile();
        cout << "  Da xoa sach va cap nhat file.\n";
    }

    // Tinh nang Sua Sach
    void suaSach() {
        string ma; cout << "  Nhap ma sach can sua: "; getline(cin, ma);
        int i = timViTri(ma);
        if (i < 0) { cout << "  [!] Khong tim thay sach co ma " << ma << "!\n"; return; }
        
        cout << "\n  +--------------------------------+\n";
        cout << "  |     CHON THONG TIN CAN SUA     |\n";
        cout << "  +--------------------------------+\n";
        cout << "  | 1. Ma sach                     |\n";
        cout << "  | 2. Ten sach                    |\n";
        cout << "  | 3. Tac gia                     |\n";
        cout << "  | 4. So luong                    |\n";
        cout << "  +--------------------------------+\n";
        cout << "  Nhap cac lua chon (VD: 124 de sua Ma, Ten, So luong): ";
        
        string choices;
        getline(cin, choices);
        Sach* s = dsSach[i];
        
        // Vong lap thong minh xu ly cac ki tu nguoi dung go
        for(char c : choices) {
            if (c == '1') {
                string newMa; cout << "  - Nhap ma sach moi: "; getline(cin, newMa);
                if (newMa != s->getMaSach() && timViTri(newMa) >= 0) {
                    cout << "    [!] Ma sach " << newMa << " da ton tai. Bo qua!\n";
                } else {
                    s->setMaSach(newMa);
                }
            }
            else if (c == '2') {
                string newTen; cout << "  - Nhap ten sach moi: "; getline(cin, newTen);
                s->setTenSach(newTen);
            }
            else if (c == '3') {
                string newTG; cout << "  - Nhap tac gia moi: "; getline(cin, newTG);
                s->setTacGia(newTG);
            }
            else if (c == '4') {
                int newSL; cout << "  - Nhap so luong moi: "; cin >> newSL; cin.ignore();
                s->setSoBanLuu(newSL);
            }
        }
        ghiRaFile();
        cout << "  => Da cap nhat thong tin sach va luu vao file.\n";
    }

    void thongKe() const {
        int ve = 0, doc = 0, veQua = 0, docQua = 0;
        for (const Sach* s : dsSach) {
            if (s->getLoai() == 'V') { ve++; if (s->isQuaHan()) veQua++; }
            else if (s->getLoai() == 'D') { doc++; if (s->isQuaHan()) docQua++; }
        }
        cout << "\n  +------------------------------------------------------+\n";
        cout << "  |                THONG KE THU VIEN                     |\n";
        cout << "  +------------------------------------------------------+\n";
        cout << "  | Tong so sach co trong he thong: " << setw(20) << left << dsSach.size() << " |\n";
        cout << "  | So luong sach dang muon ve    : " << setw(20) << left << ve << " |\n";
        cout << "  | So luong sach dang muon doc   : " << setw(20) << left << doc << " |\n";
        cout << "  | So luong muon ve qua ngay     : " << setw(20) << left << veQua << " |\n";
        cout << "  | So luong muon doc qua gio     : " << setw(20) << left << docQua << " |\n";
        cout << "  +------------------------------------------------------+\n";
    }

    void chayMenu() {
        int c; bool isLoaded = false; 
        do {
            cout<<"\n  +======================================================+\n"
                << "  |      HE THONG QUAN LY MUON TRA SACH THU VIEN         |\n"
                << "  |======================================================|\n"
                << "  |  1. Nhap thong tin tu file 'input.txt'               |\n"
                << "  |  2. Xuat ra man hinh                                 |\n"
                << "  |  3. Xuat ra file 'ketqua.txt'                        |\n"
                << "  |  4. Tim kiem sach                                    |\n"
                << "  |  5. Them sach                                        |\n"
                << "  |  6. Xoa sach                                         |\n"
                << "  |  7. Sua thong tin sach                               |\n"
                << "  |  8. Thong ke thu vien                                |\n"
                << "  |  0. Thoat chuong trinh                               |\n"
                << "  +======================================================+\n"
                << "  Lua chon: ";
            cin >> c; cin.ignore();

            if (c >= 2 && c <= 8 && !isLoaded) {
                cout << "  [!] Vui long nhap thong tin tu file (Phim 1) truoc!\n";
                continue;
            }

            switch (c) {
                case 1: docTuFile(); isLoaded = true; break;
                case 2: xuatDanhSach(); break;
                case 3: xuatDanhSachRaFile("ketqua.txt"); break;
                case 4: timKiem(); break;
                case 5: themSach(); break;
                case 6: xoaSach(); break;
                case 7: suaSach(); break;
                case 8: thongKe(); break;
                case 0: cout << "  Tam biet!\n"; break;
                default: cout << "  Lua chon khong hop le!\n";
            }
        } while (c != 0);
    }
};

int main() {
    ThuVien tv("input.txt");
    tv.chayMenu();
    return 0;
}
