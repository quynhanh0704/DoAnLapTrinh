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
    MyTime gioMuon, gioHenTra; 

    int tinhThoiGianDoc() const {
        if (gioMuon.isChuaTra()) return 0;
        int phutMuon = gioMuon.getGio() * 60 + gioMuon.getPhut();
        
        MyTime gioHienTai(14, 0, 0); // Gio bao cao do an
        int phutHienTai = gioHienTai.getGio() * 60 + gioHienTai.getPhut();
        
        int diff = phutHienTai - phutMuon;
        return (diff < 0) ? diff + 1440 : diff;
    }

public:
    SachMuonDoc() {}
    char getLoai() const override { return 'D'; }

    bool isQuaHan() const override { 
        MyTime gioHienTai(14, 0, 0); 
        if (gioHenTra.isChuaTra()) return false; 
        return gioHienTai > gioHenTra; 
    }

    void nhapThongTin() override {
        Sach::nhapThongTin();
        cout << "  Gio muon    (HH:MM)                        : "; gioMuon.nhap();
        cout << "  Gio hen tra (HH:MM, go '--:--' neu khong)  : "; gioHenTra.nhap();
    }

    void xuatDong(ostream& os) const override {
        string thoiGian;
        if (isQuaHan()) {
            thoiGian = "Qua Han";
        } else {
            thoiGian = "Dang Muon";
        }
        
        os << left << "  |"
           << " " << setw(5)  << getLoai()    << "|"
           << " " << setw(9)  << maSach       << "|"
           << " " << setw(21) << tenSach      << "|"
           << " " << setw(14) << chuDe        << "|"
           << " " << setw(17) << tacGia       << "|"
           << " " << setw(20) << nhaXuatBan   << "|"
           << " " << setw(13) << TGXuatBan.toString()   << "|"
           << " " << setw(9)  << soTrang      << "|"
           << " " << setw(8)  << soBanLuu     << "|"
           << " " << setw(11) << gioMuon.toString()   << "|"
           << " " << setw(13) << gioHenTra.toString() << "|"
           << " " << setw(11) << thoiGian    << "|\n";
    }

    string ghiRaFile() const override {
        ostringstream o;
        o << "D|" << maSach << "|" << tenSach << "|" << chuDe << "|" << tacGia << "|" 
          << nhaXuatBan << "|" << TGXuatBan.toString() << "|" << soTrang << "|" << soBanLuu << "|"
          << gioMuon.toString() << "|" << gioHenTra.toString();
        return o.str();
    }

    void docTuFile(const string& dong) override {
        istringstream ss(dong); string tok;
        getline(ss, tok, '|'); getline(ss, maSach, '|'); getline(ss, tenSach, '|');
        getline(ss, chuDe, '|'); getline(ss, tacGia, '|'); getline(ss, nhaXuatBan, '|');
        getline(ss, tok, '|'); TGXuatBan.ganTuChuoi(tok);
        getline(ss, tok, '|'); soTrang = stoi(tok);
        getline(ss, tok, '|'); soBanLuu = stoi(tok);
        
        string gM, gT;
        getline(ss, gM, '|'); gioMuon.ganTuChuoi(gM);
        getline(ss, gT);      gioHenTra.ganTuChuoi(gT);
    }
};

// ===============================================================================================================================
// THU + HIEN
//  CLASS QUAN LY: ThuVien
// ================================================================
class ThuVien {
private:
    vector<Sach*> dsSach;
    string tenFile;       
    string toLower(string str) const {
     	transform(str.begin(), str.end(), str.begin(), ::tolower);
    	return str;
    }
     int timViTri(string ma) const // THU
    {
        ma = toLower(ma);
        for (size_t i = 0; i < dsSach.size(); ++i)
        {          
       	    if (toLower(dsSach[i]->getMaSoSach()) == ma) return i; 
        }
         return -1;
    }
   
public:
     ThuVien(string file) : tenFile(file) {
        docTuFile(); 
    }
    void timKiemMa() // THU
    {
         
         bool thay = false; 
         ma = toLower(ma);
         cout << "\n--- KET QUA TIM KIEM THEO MA SACH ---\n"; 
         for (const auto& s : dsSach) { 
            if (toLower(s->getMaSoSach()) == ma) { 
             cout << "[+] Tim thay sach: " << s->getTenSach() << " | Tac gia: " << s->getTacGia() << " [Con " << s->getSoBanLuu() << " ban luu]\n";
             thay = true;
             }
         }
         if (!thay) cout << "[-] Khong ton tai ma so sach nay trong he thong.\n";
 }


    void timKiemTen() // THU
    {
        bool thay = false;
        ten = toLower(ten); 
        cout << "\n--- KET QUA TIM KIEM THEO TEN SACH ---\n";
         for (const auto& s : dsSach) {
             if (toLower(s->getTenSach()).find(ten) != string::npos) 
             {
                 cout << "[+] Ma: " << s->getMaSoSach() << " | " << s->getTenSach() << " (" << s->getChuDe() << ")\n";
                 thay = true;
             } 
        } 
    }
    void timKiemTheoNXB(string nxb) const // THU
    { 
        bool thay = false;
        nxb = toLower(nxb); 
        cout << "\n--- KET QUA TIM KIEM THEO NHA XUAT BAN ---\n"; 
        for (const auto& s : dsSach) { 
            if (toLower(s->getNhaXuatBan()) == nxb) 
            { 
                cout << "[+] Ma: " << s->getMaSoSach() << " | " << s->getTenSach() << " (" << s->getSoTrang() << " trang)\n"; 
                thay = true;
            } 
        } 
        if (!thay) cout << "[-] Thu vien chua nhap sach cua NXB nay.\n"; 
        if (!thay) cout << "[-] Khong tim thay sach nao khop voi tu khoa: " << ten << endl; 

    } 
    void docTuFile() // THU
    {
        ifstream fileIn(tenFile);
        if (!fileIn.is_open()) 
        {  
            cout << "[!] Khong the mo file " << tenFile << ". Thu vien hien tai dang trong.\n";
            return;
        }
         for (auto sachPtr : dsSach) delete sachPtr;
        dsSach.clear();
        string dong;
        while (getline(fileIn, dong)) {
            if (dong.empty()) continue; 
            stringstream ss(dong);      
            string ma, ten, cd, tg, nxb, ngay, t_trang, t_luu;
            getline(ss, ma, ','); getline(ss, ten, ','); 
            getline(ss, cd, ',');
            getline(ss, tg, ','); getline(ss, nxb, ','); getline(ss, ngay, ',');
  		    getline(ss, t_trang, ',');
            getline(ss, t_luu, ',');
            
            int soTrang = stoi(t_trang); 
            int soBanLuu = stoi(t_luu);   
            dsSach.push_back(new Sach(ma, ten, cd, tg, nxb, ngay, soTrang, soBanLuu));
        }
        fileIn.close(); // Đóng file sau khi đọc xong

    }


    ~ThuVien() // THU
    {
        for (auto sachPtr : dsSach) {
            delete sachPtr; 
        }
        dsSach.clear(); 
    }

    void Menu() {} // THU
    {    
        void chayMenu() {
        int choice;
        do {
            cout << "\033[2J\033[H"; // Lệnh ANSI xóa sạch màn hình cũ console mỗi lần lặp lại menu
            cout << "\n\t+-----------------------------------------+";
            cout << "\n\t|     HE THONG QUAN LY THU VIEN UML       |";
            cout << "\n\t+-----------------------------------------+";
            cout << "\n\t|  1. Xem toan bo danh sach sach          |";
            cout << "\n\t|  2. Them sach moi                       |";
            cout << "\n\t|  3. Xoa sach khoi he thong              |";
            cout << "\n\t|  4. Tim kiem sach (Thong minh)          |";
            cout << "\n\t|  5. Xuat file bao cao (.txt)            |";
            cout << "\n\t|  0. Sao luu du lieu & Thoat             |";
            cout << "\n\t+-----------------------------------------+\n";

            while (true) {
                try {
                    cout << "\t=> Chon chuc nang (0-5): "; cin >> choice;
                    if (cin.fail() || choice < 0 || choice > 5) {
                        throw runtime_error("\t[Loi] Vui long nhap dung so tu 0 den 5!");
                    }
                    break;                } 
                catch (const runtime_error &e) {
                    cin.clear(); cin.ignore(1000, '\n');
                    cout << e.what() << endl;                 }
            }
            cin.ignore(); 
            switch (choice) {
                case 0:
                    ghiRaFile(); 
                    cout << "[*] Tat chuong trinh thanh cong. Hen gap lai ban!" << endl;
                    break;
                case 1: xuatDanhSach(); system("pause"); break;
                case 2: themSach(); system("pause"); break;
                case 3: xoaSach(); system("pause"); break;
                case 4: timKiem(); system("pause"); break;
                case 5: {
                    string nameF; cout << "Nhap ten file muon xuat (vd: baocao.txt): ";
                    getline(cin, nameF);
                    xuatDanhSachRaFile(nameF);
                    system("pause");
                    break;
                }
            }
        } while (choice != 0); 
    }
}

    }

    void dieuHuong() {} // THU
    void thongKe() {} // HIEN
    void themSach() {} // HIEN
    void xoaSach() {} // HIEN
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
