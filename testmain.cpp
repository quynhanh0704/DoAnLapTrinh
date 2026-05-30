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
#include <cstdlib>
#include <cctype>
using namespace std;

// ================================================================
//  CLASS MyDate 
// ================================================================
class MyDate {
private:
    int ngay, thang, nam;
public:
    MyDate(int n = 0, int t = 0, int na = 0) {
        ngay = n; thang = t; nam = na;
    }
    
    void nhap() {
        char dau1, dau2;
        cin >> ngay >> dau1 >> thang >> dau2 >> nam;
    }
    
    void display() const { cout << toString(); }
    
    void ganTuChuoi(const string &s) {
        stringstream ss(s); string date;
        getline(ss, date, '/'); ngay = date.empty() ? 0 : atoi(date.c_str());
        getline(ss, date, '/'); thang = date.empty() ? 0 : atoi(date.c_str());
        getline(ss, date);      nam = date.empty() ? 0 : atoi(date.c_str());
    }
    
    bool operator>(const MyDate &x) const {
       if(nam > x.nam) return true;
       if(nam == x.nam && thang > x.thang) return true;
       if(nam == x.nam && thang == x.thang && ngay > x.ngay) return true;
       return false;
    }
    
    bool operator==(const MyDate &a) const {
        return ngay == a.ngay && thang == a.thang && nam == a.nam;
    }
    
    string toString() const {
        stringstream ss;
        if (ngay < 10) ss << "0"; ss << ngay << "/";
        if (thang < 10) ss << "0"; ss << thang << "/" << nam;
        return ss.str();
    }
};

// ================================================================
//  CLASS MyTime 
// ================================================================
class MyTime {
private:
    int gio, phut, giay;
public:
    MyTime(int g = 0, int p = 0, int gi = 0) {
        gio = g; phut = p; giay = gi;
    }
    
    void nhap() {
        string s; getline(cin, s); ganTuChuoi(s);
    }
    
    void display() const { cout << toString(); }
    
    void ganTuChuoi(const string &s) {
        if (s == "--:--" || s == "") { gio = -1; phut = -1; giay = -1; return; }
        stringstream ss(s); string time;
        getline(ss, time, ':'); gio = time.empty() ? 0 : atoi(time.c_str());
        getline(ss, time, ':'); phut = time.empty() ? 0 : atoi(time.c_str());
        if (getline(ss, time, ':')) giay = time.empty() ? 0 : atoi(time.c_str());
        else giay = 0;
    }
    
    bool operator>(const MyTime &x) const {
        if(gio > x.gio) return true;
        if(gio == x.gio && phut > x.phut) return true;
        if(gio == x.gio && phut == x.phut && giay > x.giay) return true;
        return false;
    }

    bool isChuaTra() const { return gio == -1; }
    int getGio() const { return gio; }
    int getPhut() const { return phut; }
    
    string toString() const {
        if (gio == -1) return "--:--";
        stringstream ss;
        if(gio < 10) ss << "0"; ss << gio << ":";
        if(phut < 10) ss << "0"; ss << phut;
        return ss.str();
    }
};

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
    MyDate ngayMuon, ngayHenTra; 
    string tenNguoiMuon;

public:
    SachMuonVe() {}
    char getLoai() const override { return 'V'; }

    bool isQuaHan() const override {
        MyDate ngayHienTai(10, 6, 2026); // Ngay bao cao
        return (ngayHienTai > ngayHenTra); 
    }

    void nhapThongTin() override {
        Sach::nhapThongTin();
        cout << "  Ten nguoi muon             : "; getline(cin, tenNguoiMuon);
        cout << "  Ngay muon (VD: 01/05/2026) : "; ngayMuon.nhap(); cin.ignore();
        cout << "  Ngay tra  (VD: 15/05/2026) : "; ngayHenTra.nhap(); cin.ignore();
    }

    void xuatDong(ostream& os) const override {
        string trangThai = isQuaHan() ? "[QUA HAN]" : "";
        os << left << "  |"
           << " " << setw(9)  << maSach       << "|"
           << " " << setw(24) << tenSach      << "|"
           << " " << setw(14) << tacGia       << "|"
           << " " << setw(4)  << soBanLuu     << "|"
           << " " << setw(17) << tenNguoiMuon << "|"
           << " " << setw(11) << ngayMuon.toString()   << "|" 
           << " " << setw(11) << ngayHenTra.toString() << "|"
           << " " << setw(12) << trangThai    << "|\n";
    }

    string ghiRaFile() const override {
        ostringstream o;
        o << "V|" << maSach << "|" << tenSach << "|" << tacGia << "|" << soBanLuu << "|"
          << ngayMuon.toString() << "|" << ngayHenTra.toString() << "|" << tenNguoiMuon;
        return o.str();
    }

    void docTuFile(const string& dong) override {
        istringstream ss(dong); string tok;
        getline(ss, tok, '|'); getline(ss, maSach, '|'); getline(ss, tenSach, '|');
        getline(ss, tacGia, '|'); getline(ss, tok, '|'); soBanLuu = stoi(tok);
        
        string ngM, ngT;
        getline(ss, ngM, '|'); ngayMuon.ganTuChuoi(ngM);
        getline(ss, ngT, '|'); ngayHenTra.ganTuChuoi(ngT);
        getline(ss, tenNguoiMuon);
    }
};

// ================================================================
//  LOP DAN XUAT: SachMuonDoc
// ================================================================
class SachMuonDoc : public Sach {
private:
    MyTime gioMuon, gioHenTra; 

    int tinhThoiGianDoc() const {
        if (gioMuon.isChuaTra()) return 0;
        int phutMuon = gioMuon.getGio() * 60 + gioMuon.getPhut();
        
        MyTime gioHienTai(14, 0, 0); // Gio bao cao
        int phutHienTai = gioHienTai.getGio() * 60 + gioHienTai.getPhut();
        
        int diff = phutHienTai - phutMuon;
        return (diff < 0) ? diff + 1440 : diff;
    }

public:
    SachMuonDoc() {}
    char getLoai() const override { return 'D'; }

    // Logic kiem tra qua han don gian nhat: gioHienTai > gioHenTra
    bool isQuaHan() const override { 
        MyTime gioHienTai(14, 0, 0); 
        if (gioHenTra.isChuaTra()) return false; // Neu khong hen tra thi khong qua han
        return gioHienTai > gioHenTra; 
    }

    void nhapThongTin() override {
        Sach::nhapThongTin();
        cout << "  Gio muon    (HH:MM)                        : "; gioMuon.nhap();
        cout << "  Gio hen tra (HH:MM, go '--:--' neu khong)  : "; gioHenTra.nhap();
    }

    void xuatDong(ostream& os) const override {
        // Neu qua han -> in [QUA HAN], neu khong -> in thoi gian da doc
        string thoiGian;
        if (isQuaHan()) {
            thoiGian = "[QUA HAN]";
        } else {
            int t = tinhThoiGianDoc();
            thoiGian = to_string(t/60) + "h" + to_string(t%60) + "m";
        }
        
        os << left << "  |"
           << " " << setw(9)  << maSach     << "|"
           << " " << setw(24) << tenSach    << "|"
           << " " << setw(14) << tacGia     << "|"
           << " " << setw(4)  << soBanLuu   << "|"
           << " " << setw(9)  << gioMuon.toString()    << "|"
           << " " << setw(9)  << gioHenTra.toString()  << "|"
           << " " << setw(21) << thoiGian   << "|\n";
    }

    string ghiRaFile() const override {
        ostringstream o;
        o << "D|" << maSach << "|" << tenSach << "|" << tacGia << "|" << soBanLuu << "|"
          << gioMuon.toString() << "|" << gioHenTra.toString();
        return o.str();
    }

    void docTuFile(const string& dong) override {
        istringstream ss(dong); string tok;
        getline(ss, tok, '|'); getline(ss, maSach, '|'); getline(ss, tenSach, '|');
        getline(ss, tacGia, '|'); getline(ss, tok, '|'); soBanLuu = stoi(tok);
        
        string gM, gT;
        getline(ss, gM, '|'); gioMuon.ganTuChuoi(gM);
        getline(ss, gT);      gioHenTra.ganTuChuoi(gT);
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
        // Da doi ten cot thanh Gio hen de phu hop voi code hien tai
        os << left << "  | " << setw(9) << "Ma sach" << "| " << setw(24) << "Ten sach" << "| " << setw(14) << "Tac gia" 
           << "| " << setw(4) << "SL" << "| " << setw(9) << "Gio muon" << "| " << setw(9) << "Gio hen" 
           << "| " << setw(21) << "Trang thai/Thoi gian" << "|\n";
        duongKeDoc(os);
    }

    static void xuatBang(ostream& os, const vector<Sach*>& ds) {
        tieuDeVe(os); bool coVe = false;
        for (const Sach* s : ds) if (s->getLoai() == 'V') { s->xuatDong(os); duongKeVe(os); coVe = true; }
        if (!coVe) { os << "  | " << left << setw(117) << "Khong co sach muon ve" << "|\n"; duongKeVe(os); }

        tieuDeDoc(os); bool coDoc = false;
        for (const Sach* s : ds) if (s->getLoai() == 'D') { s->xuatDong(os); duongKeDoc(os); coDoc = true; }
        if (!coDoc) { os << "  | " << left << setw(101) << "Khong co sach muon doc" << "|\n"; duongKeDoc(os); }
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
        
        for(char c : choices) {
            if (c == '1') {
                string newMa; cout << "  - Nhap ma sach moi: "; getline(cin, newMa);
                if (newMa != s->getMaSach() && timViTri(newMa) >= 0) {
                    cout << "    [!] Ma sach " << newMa << " da ton tai. Bo qua!\n";
                } else { s->setMaSach(newMa); }
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
