// ================================================================
//  De tai 04: Quan ly muon tra sach thu vien
//  Yeu cau moi:
//  - Su dung vector<> de quan ly sach
//  - Gom 4 class: Sach, SachMuonVe, SachMuonDoc, ThuVien
//  - Nam xuat ban, ngay muon, ngay hen tra, gio muon, gio tra luu bang string
//  - 4 class deu co ham docFile va ghiFile
//  - File input: V/D|Ma sach|Ten sach|Chu de|Tac gia|NXB|Nam XB|So trang|So ban luu|Thoi gian muon|Thoi gian tra
//  - File output: tach danh sach sach muon ve va sach muon doc
//  Bien dich: g++ -std=c++11 QuanLyThuVien_InputOutput_TheoYeuCau.cpp -o ThuVien
// ================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <ctime>
using namespace std;
class MyDate
{
    private:
        int ngay, thang, nam;
    public:
        MyDate(int n=0, int t=0, int na=0)
        {
            ngay=n; thang=t; nam=na;
        }
        void nhap()
        {
            char dau1, dau2;
            cout<<"Nhap ngay/thang/nam: "; 
            cin>>ngay>>dau1>>thang>>dau2>>nam;
        }
        void display() const
        {
            cout << toString();
        }
        void ganTuChuoi(const string &s)
        {
            stringstream ss(s);
            string date;
            getline(ss, date, '/'); ngay = date.empty() ? 0 : atoi(date.c_str());
            getline(ss, date, '/'); thang = date.empty() ? 0 : atoi(date.c_str());
            getline(ss, date);      nam = date.empty() ? 0 : atoi(date.c_str());
        }
        void docFile(stringstream &ss)
        {
            string s;
            getline(ss, s, '|');
            ganTuChuoi(s);
        }
        bool operator>(const MyDate &x) const
        {
           if(nam > x.nam) return true;
           if(nam == x.nam && thang > x.thang) return true;
           if(nam == x.nam && thang == x.thang && ngay > x.ngay) return true;
           return false;
           
        }
        bool operator==(const MyDate &a) const
        {
            return ngay==a.ngay && thang==a.thang && nam==a.nam;
        }
        string toString() const {
            stringstream ss;
            if (ngay < 10) ss << "0";
            ss << ngay << "/";
            if (thang < 10) ss << "0";
            ss << thang << "/" << nam;
            return ss.str();
    }
        
};
class MyTime
{
    private:
        int gio, phut, giay;
    public:
        MyTime(int g=0,int p=0,int gi=0) 
        {
            gio=g; phut=p; giay=gi;
        }
        void nhap()
        {
            char dau1, dau2;
            //cout<<"Nhap gio:phut:giay : " ; 
            cin>>gio>>dau1>>phut>>dau2>>giay;
        }
        void display() const
        {
            cout << toString();
        }
        void ganTuChuoi(const string &s)
        {
            stringstream ss(s);
            string time;
            getline(ss, time, ':'); gio = time.empty() ? 0 : atoi(time.c_str());
            getline(ss, time, ':'); phut = time.empty() ? 0 : atoi(time.c_str());
            if (getline(ss, time, ':')) giay = time.empty() ? 0 : atoi(time.c_str());
            else giay = 0;
        }
        void docFile(stringstream &ss)
        {
            string s;
            getline(ss, s, '|');
            ganTuChuoi(s);
        }
        bool operator>(const MyTime &x) const
        {
            if(gio > x.gio) return true;
            if(gio == x.gio && phut > x.phut) return true;
            if(gio == x.gio && phut == x.phut && giay > x.giay) return true;
            return false;;
        }

        bool operator<(const MyTime &x) const
        {
            if(gio < x.gio) return true;
            if(gio == x.gio && phut < x.phut) return true;
            if(gio == x.gio && phut == x.phut && giay < x.giay) return true;
            return false;
        }

        bool operator==(const MyTime &x) const
        {
            return gio == x.gio && phut == x.phut && giay == x.giay;
        }

        static MyTime now()
        {
            std::time_t t = std::time(nullptr);
            std::tm *lt = std::localtime(&t);
            return MyTime(lt->tm_hour, lt->tm_min, lt->tm_sec);
        }
        string toString() const
        {
            stringstream ss;
            if(gio < 10) ss<<"0";
            ss<<gio<<":";
            if(phut < 10) ss<<"0";
            ss<<phut<<":";
            if(giay < 10) ss<<"0";
            ss<<giay;
            return ss.str();
        }
        
};
// ================================================================
//  CLASS CO SO: Sach
// ================================================================
class Sach {
protected:
    string loaiSach;
    string maSach;
    string tenSach;
    string chuDe;
    string tacGia;
    string nhaXuatBan;
    string namXuatBan;
    int soTrang;
    int soBanLuu;

public:
    Sach(string loai = "", string ma = "", string ten = "", string cd = "", string tg = "",
         string nxb = "", string namXB ="" , int trang = 0, int ban = 0) {
        loaiSach = loai;
        maSach = ma;
        tenSach = ten;
        chuDe = cd;
        tacGia = tg;
        nhaXuatBan = nxb;
        namXuatBan = namXB;
        soTrang = trang;
        soBanLuu = ban;
    }

    virtual ~Sach() {}

    string getLoaiSach() { return loaiSach; }
    string getMaSach() { return maSach; }
    string getTenSach() { return tenSach; }
    string getNhaXuatBan() { return nhaXuatBan; }
    int getSoBanLuu() { return soBanLuu; }

    virtual void nhap();
    virtual void xuat();

    // Ham doc/ghi file co o class Sach
    virtual void docFile(stringstream &ss);
    virtual void ghiFile(ofstream &file);

    virtual string trangThai() = 0;
    virtual string chuyenChuoi() = 0;
};

void Sach::nhap() {
    cout << "Nhap ma sach: "; cin >> ws;
    getline(cin, maSach);
    cout << "Nhap ten sach: ";
    getline(cin, tenSach);
    cout << "Nhap chu de: ";
    getline(cin, chuDe);
    cout << "Nhap ten tac gia: ";
    getline(cin, tacGia);
    cout << "Nhap nha xuat ban: ";
    getline(cin, nhaXuatBan);
    cout << "Nhap nam xuat ban: ";
    getline(cin,namXuatBan);
    cout << "Nhap so trang: ";
    cin >> soTrang;
    cout << "Nhap so ban luu: ";
    cin >> soBanLuu;
}

void Sach::xuat() {
    cout << left;
    cout << "| " << setw(8) << loaiSach;
    cout << "| " << setw(10) << maSach;
    cout << "| " << setw(22) << tenSach;
    cout << "| " << setw(15) << chuDe;
    cout << "| " << setw(16) << tacGia;
    cout << "| " << setw(14) << nhaXuatBan;
    cout << "| " << setw(12) << namXuatBan;
    cout << "| " << right << setw(8) << soTrang;
    cout << "| " << setw(8) << soBanLuu;
}

void Sach::docFile(stringstream &ss) {
    string trangStr, banStr;

    getline(ss, maSach, '|');
    getline(ss, tenSach, '|');
    getline(ss, chuDe, '|');
    getline(ss, tacGia, '|');
    getline(ss, nhaXuatBan, '|');
    getline(ss, namXuatBan, '|');
    getline(ss, trangStr, '|');
    getline(ss, banStr, '|');
    stringstream doiTrang(trangStr);
    doiTrang >> soTrang;
    stringstream doiBan(banStr);
    doiBan >> soBanLuu;
}

void Sach::ghiFile(ofstream &file) {
    file << left;
    file << "| " << setw(8) << loaiSach;
    file << "| " << setw(10) << maSach;
    file << "| " << setw(22) << tenSach;
    file << "| " << setw(15) << chuDe;
    file << "| " << setw(16) << tacGia;
    file << "| " << setw(14) << nhaXuatBan;
    file << "| " << setw(12) << namXuatBan;
    file << "| " << right << setw(8) << soTrang;
    file << "| " << setw(8) << soBanLuu;
}

// ================================================================
//  CLASS DAN XUAT: SachMuonVe
// ================================================================
class SachMuonVe : public Sach {
private:
    MyDate ngayMuon, ngayHenTra;

public:
    SachMuonVe(string ma = "", string ten = "", string cd = "", string tg = "",
               string nxb = "", string namXB = "", int trang = 0, int ban = 0,
               MyDate ngayM = MyDate() , MyDate ngayT = MyDate())
        : Sach("V", ma, ten, cd, tg, nxb, namXB, trang, ban) {
        ngayMuon = ngayM;
        ngayHenTra = ngayT;
    }

    void nhap();
    void xuat();

    // Ham doc/ghi file co o class SachMuonVe
    void docFile(stringstream &ss);
    void ghiFile(ofstream &file);

    string trangThai();
    string chuyenChuoi();
};

void SachMuonVe::nhap() {
    loaiSach = "V";
    Sach::nhap();
    cout << "Nhap ngay muon: "; 
    ngayMuon.nhap();
    cout << "Nhap ngay hen tra: ";
    ngayHenTra.nhap();
}

void SachMuonVe::xuat() {
    Sach::xuat();
    cout << left;
    cout << "| " << setw(14) << ngayMuon.toString();
    cout << "| " << setw(14) << ngayHenTra.toString();
    cout << "| " << setw(12) << trangThai();
    cout << "|" << endl;
}

void SachMuonVe::docFile(stringstream &ss) {
    loaiSach = "V";
    Sach::docFile(ss);
    ngayMuon.docFile(ss);
    ngayHenTra.docFile(ss);
}

void SachMuonVe::ghiFile(ofstream &file) {
    Sach::ghiFile(file);
    file << left;
    file << "| " << setw(14) << ngayMuon.toString();
    file << "| " << setw(14) << ngayHenTra.toString();
    file << "| " << setw(12) << trangThai();
    file << "|" << endl;
}

string SachMuonVe::trangThai() {
    MyDate Hientai(29,5,2026);
    if( Hientai > ngayHenTra) return "Qua Han";
    else return "Dang Muon";

}

string SachMuonVe::chuyenChuoi() {
    stringstream ss;
    ss << "V|" << maSach << "|" << tenSach << "|" << chuDe << "|" << tacGia << "|"
       << nhaXuatBan << "|" << namXuatBan << "|" << soTrang << "|" << soBanLuu
       << "|" << ngayMuon.toString() << "|" << ngayHenTra.toString();
    return ss.str();
}

// ================================================================
//  CLASS DAN XUAT: SachMuonDoc
// ================================================================
class SachMuonDoc : public Sach {
private:
    MyTime gioMuon;
    MyTime gioTra;

public:
    SachMuonDoc(string ma = "", string ten = "", string cd = "", string tg = "",
                string nxb = "", string namXB = "", int trang = 0, int ban = 0,
                MyTime gioM = MyTime(), MyTime gioT = MyTime())
        : Sach("D", ma, ten, cd, tg, nxb, namXB, trang, ban) {
        gioMuon = gioM;
        gioTra = gioT;
    }

    void nhap();
    void xuat();

    // Ham doc/ghi file co o class SachMuonDoc
    void docFile(stringstream &ss);
    void ghiFile(ofstream &file);

    string trangThai();
    string chuyenChuoi();
};

void SachMuonDoc::nhap() {
    loaiSach = "D";
    Sach::nhap();
    cout << "Nhap gio muon: "; 
    gioMuon.nhap();
    cout << "Nhap gio tra: ";
    gioTra.nhap();
}

void SachMuonDoc::xuat() {
    Sach::xuat();
    cout << left;
    cout << "| " << setw(12) << gioMuon.toString();
    cout << "| " << setw(12) << gioTra.toString();
    cout << "| " << setw(12) << trangThai();
    cout << "|" << endl;
}

void SachMuonDoc::docFile(stringstream &ss) {
    loaiSach = "D";
    Sach::docFile(ss);
    gioMuon.docFile(ss);
    gioTra.docFile(ss);
}

void SachMuonDoc::ghiFile(ofstream &file) {
    Sach::ghiFile(file);
    file << left;
    file << "| " << setw(12) << gioMuon.toString();
    file << "| " << setw(12) << gioTra.toString();
    file << "| " << setw(12) << trangThai();
    file << "|" << endl;
}

string SachMuonDoc::trangThai() {
    MyTime Hientai = MyTime::now();
    if ( Hientai > gioTra ) return "Qua Han";
    else return "Dang Muon";
}

string SachMuonDoc::chuyenChuoi() {
    stringstream ss;
    ss << "D|" << maSach << "|" << tenSach << "|" << chuDe << "|" << tacGia << "|"
       << nhaXuatBan << "|" << namXuatBan << "|" << soTrang << "|" << soBanLuu
       << "|" << gioMuon.toString() << "|" << gioTra.toString();
    return ss.str();
}

// ================================================================
//  CLASS QUAN LY: ThuVien
// ================================================================
class ThuVien {
private:
    vector<Sach*> dsSach;

public:
    ~ThuVien();

    // Ham doc/ghi file co o class ThuVien
    void docFile(string tenFile);
    void ghiFile(string tenFile);

    void ghiFileDuLieu(string tenFile);
    void themSach();
    void hienThiDanhSach();
    void timTheoMa();
    void timTheoTen();
    void timTheoNhaXuatBan();
    void suaSach();
    void xoaSach();
    void thongKe();
    void hienThiMenu();
    void chayChuongTrinh();
};

ThuVien::~ThuVien() {
    for (size_t i = 0; i < dsSach.size(); i++) {
        delete dsSach[i];
    }
    dsSach.clear();
}

void keBangMuonVe(ostream &out) {
    out << "+---------+-----------+-----------------------+----------------+-----------------+---------------+-------------+---------+---------+---------------+---------------+-------------+" << endl;
}

void tieuDeMuonVe(ostream &out) {
    out << "\nDANH SACH CUA SACH MUON VE" << endl;
    keBangMuonVe(out);
    out << left;
    out << "| " << setw(8) << "Loai";
    out << "| " << setw(10) << "Ma sach";
    out << "| " << setw(22) << "Ten sach";
    out << "| " << setw(15) << "Chu de";
    out << "| " << setw(16) << "Ten tac gia";
    out << "| " << setw(14) << "Nha xuat ban";
    out << "| " << setw(12) << "Nam XB";
    out << "| " << setw(8) << "So trang";
    out << "| " << setw(8) << "Ban luu";
    out << "| " << setw(14) << "Ngay muon";
    out << "| " << setw(14) << "Ngay hen tra";
    out << "| " << setw(12) << "Trang thai";
    out << "|" << endl;
    keBangMuonVe(out);
}

void keBangMuonDoc(ostream &out) {
    out << "+---------+-----------+-----------------------+----------------+-----------------+---------------+-------------+---------+---------+-------------+-------------+-------------+" << endl;
}

void tieuDeMuonDoc(ostream &out) {
    out << "\nDANH SACH CUA SACH MUON DOC" << endl;
    keBangMuonDoc(out);
    out << left;
    out << "| " << setw(8) << "Loai";
    out << "| " << setw(10) << "Ma sach";
    out << "| " << setw(22) << "Ten sach";
    out << "| " << setw(15) << "Chu de";
    out << "| " << setw(16) << "Ten tac gia";
    out << "| " << setw(14) << "Nha xuat ban";
    out << "| " << setw(12) << "Nam XB";
    out << "| " << setw(8) << "So trang";
    out << "| " << setw(8) << "Ban luu";
    out << "| " << setw(12) << "Gio muon";
    out << "| " << setw(12) << "Gio tra";
    out << "| " << setw(12) << "Trang thai";
    out << "|" << endl;
    keBangMuonDoc(out);
}

void ThuVien::docFile(string tenFile) {
    ifstream file(tenFile.c_str());
    if (!file) {
        cout << "Khong mo duoc file " << tenFile << ". Khoi tao du lieu mau." << endl;
        MyDate muon(12,5,2026), tra(20,5,2026);
        MyTime gmuon(8,00,00), gtra(11,30,00);
        dsSach.push_back(new SachMuonVe("MS01", "Lap trinh C++", "CNTT", "Nguyen Van A", "Tre", "2007", 350, 10, muon, tra));
        dsSach.push_back(new SachMuonDoc("MS02", "CTDLGT", "CNTT", "Tran Van B", "Giao Duc", "2008", 420, 5, gmuon, gtra));
        return;
    }

    string line;
    while (getline(file, line)) {
        if (line == "") continue;

        stringstream ss(line);
        string loai;
        getline(ss, loai, '|');

        Sach *s = NULL;
        if (loai == "V") {
            s = new SachMuonVe();
        } else if (loai == "D") {
            s = new SachMuonDoc();
        }

        if (s != NULL) {
            s->docFile(ss);
            dsSach.push_back(s);
        }
    }

    file.close();
}

// Ghi file dau ra theo dung yeu cau: tach sach muon ve va sach muon doc
void ThuVien::ghiFile(string tenFile) {
    ofstream file(tenFile.c_str());
    if (!file) {
        cout << "Khong mo duoc file de ghi!" << endl;
        return;
    }

    tieuDeMuonVe(file);
    for (size_t i = 0; i < dsSach.size(); i++) {
        if (dsSach[i]->getLoaiSach() == "V") {
            dsSach[i]->ghiFile(file);
        }
    }
    keBangMuonVe(file);

    tieuDeMuonDoc(file);
    for (size_t i = 0; i < dsSach.size(); i++) {
        if (dsSach[i]->getLoaiSach() == "D") {
            dsSach[i]->ghiFile(file);
        }
    }
    keBangMuonDoc(file);

    file.close();
    cout << "Da ghi file dau ra: " << tenFile << endl;
}

// Ghi lai du lieu theo cau truc input de cap nhat file dau vao
void ThuVien::ghiFileDuLieu(string tenFile) {
    ofstream file(tenFile.c_str());
    if (!file) {
        cout << "Khong mo duoc file de cap nhat!" << endl;
        return;
    }

    for (size_t i = 0; i < dsSach.size(); i++) {
        file << dsSach[i]->chuyenChuoi() << endl;
    }

    file.close();
}

void ThuVien::themSach() {
    int loai;
    cout << "\nChon loai sach can them:" << endl;
    cout << "1. Sach muon ve" << endl;
    cout << "2. Sach muon doc" << endl;
    cout << "Nhap lua chon: ";
    cin >> loai;

    Sach *s = NULL;
    if (loai == 1) s = new SachMuonVe();
    else if (loai == 2) s = new SachMuonDoc();
    else {
        cout << "Loai sach khong hop le!" << endl;
        return;
    }

    s->nhap();

    if (s->getMaSach() == "") {
        cout << "Ma sach rong, khong them vao danh sach!" << endl;
        delete s;
        return;
    }

    dsSach.push_back(s);
    cout << "Them sach thanh cong!" << endl;
}

void ThuVien::hienThiDanhSach() {
    if (dsSach.empty()) {
        cout << "Danh sach sach trong!" << endl;
        return;
    }

    tieuDeMuonVe(cout);
    for (size_t i = 0; i < dsSach.size(); i++) {
        if (dsSach[i]->getLoaiSach() == "V") dsSach[i]->xuat();
    }
    keBangMuonVe(cout);

    tieuDeMuonDoc(cout);
    for (size_t i = 0; i < dsSach.size(); i++) {
        if (dsSach[i]->getLoaiSach() == "D") dsSach[i]->xuat();
    }
    keBangMuonDoc(cout);
}

void ThuVien::timTheoMa() {
    string ma;
    cout << "Nhap ma sach can tim: "; cin >> ws;
    getline(cin, ma);

    bool timThay = false;
    for (size_t i = 0; i < dsSach.size(); i++) {
        if (dsSach[i]->getMaSach() == ma) {
            if (dsSach[i]->getLoaiSach() == "V") tieuDeMuonVe(cout);
            else tieuDeMuonDoc(cout);
            dsSach[i]->xuat();
            timThay = true;
        }
    }

    if (!timThay) cout << "Khong tim thay sach co ma: " << ma << endl;
}

void ThuVien::timTheoTen() {
    string ten;
    cout << "Nhap ten sach can tim: "; cin >> ws;
    getline(cin, ten);

    bool timThay = false;
    for (size_t i = 0; i < dsSach.size(); i++) {
        if (dsSach[i]->getTenSach().find(ten) != string::npos) {
            if (dsSach[i]->getLoaiSach() == "V") tieuDeMuonVe(cout);
            else tieuDeMuonDoc(cout);
            dsSach[i]->xuat();
            timThay = true;
        }
    }

    if (!timThay) cout << "Khong tim thay sach co ten: " << ten << endl;
}

void ThuVien::timTheoNhaXuatBan() {
    string nxb;
    cout << "Nhap nha xuat ban can tim: "; cin >> ws;
    getline(cin, nxb);

    bool timThay = false;
    for (size_t i = 0; i < dsSach.size(); i++) {
        if (dsSach[i]->getNhaXuatBan().find(nxb) != string::npos) {
            if (dsSach[i]->getLoaiSach() == "V") tieuDeMuonVe(cout);
            else tieuDeMuonDoc(cout);
            dsSach[i]->xuat();
            timThay = true;
        }
    }

    if (!timThay) cout << "Khong tim thay sach cua nha xuat ban: " << nxb << endl;
}

void ThuVien::suaSach() {
    string ma;
    cout << "Nhap ma sach can sua: "; cin >> ws;
    getline(cin, ma);

    for (size_t i = 0; i < dsSach.size(); i++) {
        if (dsSach[i]->getMaSach() == ma) {
            int loai;
            cout << "Nhap lai loai sach:" << endl;
            cout << "1. Sach muon ve" << endl;
            cout << "2. Sach muon doc" << endl;
            cout << "Nhap lua chon: ";
            cin >> loai;

            Sach *s = NULL;
            if (loai == 1) s = new SachMuonVe();
            else if (loai == 2) s = new SachMuonDoc();
            else {
                cout << "Loai sach khong hop le!" << endl;
                return;
            }

            s->nhap();
            delete dsSach[i];
            dsSach[i] = s;
            cout << "Sua thong tin sach thanh cong!" << endl;
            return;
        }
    }

    cout << "Khong tim thay sach co ma: " << ma << endl;
}

void ThuVien::xoaSach() {
    string ma;
    cout << "Nhap ma sach can xoa: "; cin >> ws;
    getline(cin, ma);

    for (size_t i = 0; i < dsSach.size(); i++) {
        if (dsSach[i]->getMaSach() == ma) {
            delete dsSach[i];
            dsSach.erase(dsSach.begin() + i);
            cout << "Xoa sach thanh cong!" << endl;
            return;
        }
    }

    cout << "Khong tim thay sach co ma: " << ma << endl;
}

void ThuVien::thongKe() {
    int tongSach = dsSach.size();
    int soMuonVe = 0;
    int soMuonDoc = 0;
    int tongBanLuu = 0;
    int quaHanV = 0;
    int quaHanM = 0;

    for (size_t i = 0; i < dsSach.size(); i++) {
        if (dsSach[i]->getLoaiSach() == "V")
        {
            soMuonVe++;
            if(dsSach[i]->trangThai() == "Qua Han") quaHanV++;
        } 
        else if (dsSach[i]->getLoaiSach() == "D") 
        {
            soMuonDoc++;
            if(dsSach[i]->trangThai() == "Qua Han") quaHanM++;
        }
        tongBanLuu += dsSach[i]->getSoBanLuu();
    }

    cout << "\n========== THONG KE THU VIEN ==========" << endl;
    cout << "Tong so dau sach: " << tongSach << endl;
    cout << "Tong so ban luu trong thu vien: " << tongBanLuu << endl;
    cout << "So sach muon ve: " << soMuonVe << "\n" << "So sach muon ve qua han: " << quaHanV <<endl;
    cout << "So sach muon doc: " << soMuonDoc << "\n" << "So sach muon doc qua han: " << quaHanM <<endl;
}

void ThuVien::hienThiMenu() {
    cout << "\n+------------ HE THONG ------------+" << endl;
    cout << "| QUAN LY MUON TRA SACH THU VIEN   |" << endl;
    cout << "+----------------------------------+" << endl;
    cout << "| 1. Them sach                     |" << endl;
    cout << "| 2. Hien thi danh sach sach       |" << endl;
    cout << "| 3. Tim sach theo ma              |" << endl;
    cout << "| 4. Tim sach theo ten             |" << endl;
    cout << "| 5. Tim sach theo nha xuat ban    |" << endl;
    cout << "| 6. Sua thong tin sach            |" << endl;
    cout << "| 7. Xoa sach                      |" << endl;
    cout << "| 8. Thong ke                      |" << endl;
    cout << "| 9. Ghi file output               |" << endl;
    cout << "| 0. Thoat                         |" << endl;
    cout << "+----------------------------------+" << endl;
    cout << "Chon chuc nang: ";
}

void ThuVien::chayChuongTrinh() {
    string fileInput = "books_input.txt";
    string fileOutput = "books_output.txt";
    docFile(fileInput);

    int luaChon;
    do {
        hienThiMenu();
        cin >> luaChon;

        switch (luaChon) {
            case 1:
                themSach();
                ghiFileDuLieu(fileInput);
                break;
            case 2:
                hienThiDanhSach();
                break;
            case 3:
                timTheoMa();
                break;
            case 4:
                timTheoTen();
                break;
            case 5:
                timTheoNhaXuatBan();
                break;
            case 6:
                suaSach();
                ghiFileDuLieu(fileInput);
                break;
            case 7:
                xoaSach();
                ghiFileDuLieu(fileInput);
                break;
            case 8:
                thongKe();
                break;
            case 9:
                ghiFile(fileOutput);
                break;
            case 0:
                ghiFileDuLieu(fileInput);
                ghiFile(fileOutput);
                cout << "Thoat chuong trinh!" << endl;
                break;
            default:
                cout << "Chon sai chuc nang!" << endl;
        }
    } while (luaChon != 0);
}

// ================================================================
//  HAM MAIN
// ================================================================
int main() {
    ThuVien tv;
    tv.chayChuongTrinh();
    return 0;
}
