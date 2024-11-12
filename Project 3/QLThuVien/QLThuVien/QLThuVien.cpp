#define _CRT_SECURE_NO_WARNINGS
#define NOMINMAX
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>  // Cho hàm exit
#include <conio.h>  // Cho hàm _getch() để đặt mật khẩu
#include <ctime>
#include <vector>
#include <limits> // Thư viện cần thiết để sử dụng std::numeric_limits
#include <windows.h>
using namespace std;

// hàm tô màu
void setColor(int color) {
    // Lấy handle của console
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // Đặt màu cho console
    SetConsoleTextAttribute(hConsole, color);
}
// Tạo các Class quản lý thư viện
class Admin {
private:
    string username;
    string password;

public:
    Admin(string user = "", string pass = "") : username(user), password(pass) {}

    bool verifyLogin(string inputUser, string inputPass) {
        return (inputUser == username && inputPass == password);
    }

    bool login() {
        ifstream adminFile("Admin.txt");
        if (!adminFile.is_open()) {
            setColor(4);
            cout << "Khong the mo file Admin.txt\n";
            return false;
        }

        string userInput, passInput;
        int attempts = 0;

        while (attempts < 3) {
            // Hiển thị giao diện đăng nhập
            setColor(6);
            cout << "* * * * * * * * * * * * * * * * * * * *\n";
            setColor(6);
            cout << "*";
            setColor(10);
            cout << "          DANG NHAP HE THONG         ";
            setColor(6);
            cout << "*\n";
            setColor(6);
            cout << "* * * * * * * * * * * * * * * * * * * *\n";
            setColor(9);
            cout << "User: ";
            setColor(15);
            cin >> userInput;
            setColor(9);
            cout << "Password: ";
            setColor(15);

            char ch;
            passInput = "";

            while (true) {
                ch = _getch();

                if (ch == 13) { // Enter key
                    break;
                }
                else if (ch == 8) { // Backspace key
                    if (!passInput.empty()) {
                        cout << "\b \b"; // Xóa ký tự trên màn hình
                        passInput.pop_back(); // Xóa ký tự cuối cùng trong chuỗi mật khẩu
                    }
                }
                else if (ch == 224 || ch == -32) { // Phím điều khiển (arrow keys)
                    int nextCh = _getch(); // Lấy ký tự tiếp theo
                }
                else if (ch >= 0 && ch <= 255 && isprint(ch)) {
                    bool isShiftHeld = (GetKeyState(VK_SHIFT) & 0x8000) != 0;

                    if (isShiftHeld && isalpha(ch)) {
                        ch = toupper(ch);
                    }
                    else if (isShiftHeld && isdigit(ch)) {
                        switch (ch) {
                        case '1': ch = '!'; break;
                        case '2': ch = '@'; break;
                        case '3': ch = '#'; break;
                        case '4': ch = '$'; break;
                        case '5': ch = '%'; break;
                        case '6': ch = '^'; break;
                        case '7': ch = '&'; break;
                        case '8': ch = '*'; break;
                        case '9': ch = '('; break;
                        case '0': ch = ')'; break;
                        }
                    }

                    passInput.push_back(ch);
                    cout << "*";
                }
            }

            cout << endl;

            string line;
            bool isLoginSuccessful = false;

            while (getline(adminFile, line)) {
                stringstream ss(line);
                string storedUser, storedPass;

                getline(ss, storedUser, '|');
                getline(ss, storedPass, '|');

                Admin admin(storedUser, storedPass);
                if (admin.verifyLogin(userInput, passInput)) {
                    setColor(2);
                    cout << "Dang nhap thanh cong!\n";
                    isLoginSuccessful = true;
                    break;
                }
            }

            adminFile.clear();
            adminFile.seekg(0, ios::beg);

            if (isLoginSuccessful) {
                return true;
            }
            else {
                attempts++; // Tăng số lần thử

                setColor(4);
                cout << "Sai user hoac password. Vui long thu lai.\n";
                cout << "Ban da nhap sai " << attempts << " lan. Qua 3 lan se thoat chuong trinh.\n";

                // Kiểm tra nếu đã đủ 3 lần sai thì không cần gọi system("cls") nữa
                if (attempts < 3) {
                    // Đợi một khoảng thời gian ngắn để người dùng có thể đọc thông báo trước khi xóa màn hình
                    Sleep(1000);
                    system("cls");
                }
            }
        }

        setColor(4);
        cout << "Ban da nhap sai qua nhieu, thoat khoi he thong!\n";
        return false;
    }
};
class Sach {
public:
    string maSach, tenSach, tacGia, nhaXuatBan, ngayNhapKho;
    int giaBan, namPhatHanh, soTrang, tinhTrang;

    Sach() : giaBan(0), namPhatHanh(0), soTrang(0), tinhTrang(0) {}

    void hienThiThongTin() {
        // Đặt màu sắc cho các tiêu đề
        setColor(10); // Màu xanh lá cây cho tiêu đề
        cout << "Ma Sach: ";
        setColor(15); // Màu trắng cho giá trị
        cout << maSach << endl;

        setColor(10);
        cout << "Ten Sach: ";
        setColor(11);
        cout << tenSach << endl;

        setColor(10);
        cout << "Tac Gia: ";
        setColor(13);
        cout << tacGia << endl;

        setColor(10);
        cout << "Nha Xuat Ban: ";
        setColor(15);
        cout << nhaXuatBan << endl;

        setColor(10);
        cout << "Gia Ban: ";
        setColor(15);
        cout << giaBan; setColor(14); cout << " dong" << endl;

        setColor(10);
        cout << "Nam Phat Hanh: ";
        setColor(15);
        cout << namPhatHanh << endl;

        setColor(10);
        cout << "So Trang: ";
        setColor(15);
        cout << soTrang; setColor(14); cout <<" trang" << endl;

        setColor(10);
        cout << "Ngay Nhap Kho: ";
        setColor(15);
        cout << ngayNhapKho << endl;

        setColor(10);
        cout << "Tinh Trang: ";
        setColor(15);
        cout << (tinhTrang == 0 ? "Chua muon" : "Dang duoc muon") << endl;

        // Đặt lại màu sắc cho ngắt dòng
        setColor(6); // Màu vàng cho ngắt dòng
        cout << "----------------------------\n";
        setColor(7); // Đặt lại màu sắc về mặc định nếu cần
    }

    void hienThiTatCaSach() {
        ifstream file("Sach.txt");
        if (!file.is_open()) {
            cout << "Khong the mo file Sach.txt\n";
            return;
        }

        string line;
        while (getline(file, line)) {
            Sach sach;
            stringstream ss(line);

            // Đảm bảo rằng các trường được phân tách đúng
            getline(ss, sach.maSach, '|');
            getline(ss, sach.tenSach, '|');
            getline(ss, sach.tacGia, '|');
            getline(ss, sach.nhaXuatBan, '|');
            ss >> sach.giaBan;
            ss.ignore(); // Bỏ qua ký tự '|'
            ss >> sach.namPhatHanh;
            ss.ignore(); // Bỏ qua ký tự '|'
            ss >> sach.soTrang;
            ss.ignore(); // Bỏ qua ký tự '|'
            getline(ss, sach.ngayNhapKho, '|');
            ss >> sach.tinhTrang;

            sach.hienThiThongTin();
        }

        file.close(); // Đóng file
    }

    void themSach() {
        ofstream file("Sach.txt", ios::app);
        if (!file.is_open()) {
            setColor(14);
            cout << "Khong the mo file Sach.txt\n";
            return;
        }

        Sach sach;
        setColor(11);
        cout << "Nhap Ma Sach: ";
        setColor(15);
        cin >> sach.maSach;

        // Kiểm tra mã sách đã tồn tại trong file
        ifstream checkFile("Sach.txt");
        string line;
        while (getline(checkFile, line)) {
            if (line.find(sach.maSach) != string::npos) {
                setColor(14);
                cout << "Ma sach da ton tai. Khong the them.\n";
                checkFile.close();
                file.close(); // Đóng file ghi
                return;
            }
        }
        checkFile.close();

        // Nhập thông tin sách
        setColor(11);
        cout << "Nhap Ten Sach: ";
        setColor(15);
        cin.ignore(); // Xóa bộ đệm để nhập chuỗi
        getline(cin, sach.tenSach);
        setColor(11);
        cout << "Nhap Tac Gia: ";
        setColor(15);
        getline(cin, sach.tacGia);
        setColor(11);
        cout << "Nhap Nha Xuat Ban: ";
        setColor(15);
        getline(cin, sach.nhaXuatBan);
        setColor(11);
        cout << "Nhap Gia Ban: ";
        setColor(15);
        cin >> sach.giaBan;
        setColor(11);
        cout << "Nhap Nam Phat Hanh: ";
        setColor(15);
        cin >> sach.namPhatHanh;
        setColor(11);
        cout << "Nhap So Trang: ";
        setColor(15);
        cin >> sach.soTrang;
        setColor(11);
        cout << "Nhap Ngay Nhap Kho (yyyy-mm-dd): ";
        setColor(15);
        cin >> sach.ngayNhapKho;
        sach.tinhTrang = 0; // Mặc định tình trạng là chưa được mượn

        // Ghi thông tin sách vào file
        file << sach.maSach << "|" << sach.tenSach << "|" << sach.tacGia << "|"
            << sach.nhaXuatBan << "|" << sach.giaBan << "|" << sach.namPhatHanh
            << "|" << sach.soTrang << "|" << sach.ngayNhapKho << "|" << sach.tinhTrang << endl;
        setColor(10);
        cout << "Them sach thanh cong!\n";
        file.close(); // Đóng file ghi
    }

    void xoaSach() {
        string maSachXoa;
        setColor(11);
        cout << "Nhap Ma Sach can xoa: ";
        setColor(15);
        cin >> maSachXoa;

        ifstream file("Sach.txt");
        ofstream tempFile("temp.txt");
        bool sachTonTai = false;

        if (!file.is_open() || !tempFile.is_open()) {
            setColor(12);
            cout << "Khong the mo file\n";
            return;
        }

        string line;
        while (getline(file, line)) {
            if (line.find(maSachXoa) == 0) {
                stringstream ss(line);
                string maSach;
                for (int i = 0; i < 8; i++) getline(ss, maSach, '|');
                int tinhTrang;
                ss >> tinhTrang;

                if (tinhTrang == 0) {
                    sachTonTai = true;
                }
                else {
                    setColor(12);
                    cout << "Khong the xoa vi sach dang duoc muon\n";
                    tempFile << line << endl;
                    continue;
                }
            }
            else {
                tempFile << line << endl;
            }
        }

        file.close();
        tempFile.close();

        if (sachTonTai) {
            remove("Sach.txt");
            if (rename("temp.txt", "Sach.txt") != 0) {
                setColor(12);
                cout << "Loi khi doi ten file\n";
            }
            else {
                setColor(10);
                cout << "Xoa sach thanh cong!\n";
            }
        }
        else {
            setColor(12);
            cout << "Khong tim thay ma sach hoac sach dang duoc muon\n";
            remove("temp.txt");
        }
    }
};
class PhieuMuon {
public:
    int soPhieuMuon;
    string maBanDoc, maSach, ngayMuon, ngayPhaiTra;
    int tinhTrang;

    PhieuMuon() : soPhieuMuon(0), tinhTrang(0) {}

    void hienThiThongTin() {
        setColor(10);
        cout << "So Phieu Muon: "; setColor(14); cout << soPhieuMuon << endl;
        setColor(10);
        cout << "Ma Ban Doc: "; setColor(13); cout << maBanDoc << endl;
        setColor(10);
        cout << "Ma Sach: "; setColor(11); cout << maSach << endl;
        setColor(10);
        cout << "Ngay Muon: "; setColor(9);cout << ngayMuon << endl;
        setColor(10);
        cout << "Ngay Phai Tra: "; setColor(9);cout << ngayPhaiTra << endl;
        setColor(10);
        cout << "Tinh Trang: "; setColor(15); cout << (tinhTrang == 1 ? "Dang muon" : "Da tra") << endl;
        setColor(14);
        cout << "----------------------------\n";
        setColor(8);
    }

    void muonSach() {
        ofstream file("PhieuMuon.txt", ios::app);
        if (!file.is_open()) {
            setColor(12);
            cout << "Khong the mo file PhieuMuon.txt\n";
            return;
        }

        PhieuMuon phieu;

        // Đọc số phiếu mượn cuối cùng từ file
        ifstream phieuFile("PhieuMuon.txt");
        int maxSoPhieuMuon = 0;
        string line;

        while (getline(phieuFile, line)) {
            stringstream ss(line);
            ss >> phieu.soPhieuMuon; // Lấy số phiếu mượn
            if (phieu.soPhieuMuon > maxSoPhieuMuon) {
                maxSoPhieuMuon = phieu.soPhieuMuon; // Cập nhật số phiếu mượn lớn nhất
            }
        }
        phieu.soPhieuMuon = maxSoPhieuMuon + 1; // Tăng số phiếu mượn lên 1
        setColor(11);
        cout << "So Phieu Muon: "; setColor(15); cout << phieu.soPhieuMuon << endl; // Hiển thị số phiếu mượn mới
        setColor(11);
        cout << "Nhap Ma Ban Doc: ";
        setColor(15);
        cin >> phieu.maBanDoc;
        setColor(11);
        cout << "Nhap Ma Sach: ";
        setColor(15);
        cin >> phieu.maSach;

        ifstream sachFile("Sach.txt");
        bool sachTonTai = false;
        bool sachDaDuocMuon = false;

        while (getline(sachFile, line)) {
            if (line.find(phieu.maSach) == 0) {
                sachTonTai = true;
                stringstream ss(line);
                int tinhTrang;
                ss.seekg(0, ios::end);
                ss.seekg(-1, ios::cur);
                ss >> tinhTrang;

                if (tinhTrang == 0) { // Sách chưa được mượn
                    phieu.tinhTrang = 1;
                    time_t now = time(0);
                    tm* ltm = localtime(&now);
                    stringstream date;
                    date << 1900 + ltm->tm_year << "-" << 1 + ltm->tm_mon << "-" << ltm->tm_mday;
                    phieu.ngayMuon = date.str();

                    // Nhập ngày phải trả hoặc mặc định là 7 ngày sau
                    setColor(11);
                    cout << "Nhap Ngay Phai Tra (yyyy-mm-dd) hoac nhan Enter de mac dinh tra sau 7 ngay: ";
                    string ngayTraInput;
                    setColor(15);
                    cin.ignore(); // Bỏ qua ký tự newline
                    getline(cin, ngayTraInput);

                    if (ngayTraInput.empty()) { // Nếu không nhập gì
                        // Tính ngày trả là 7 ngày sau ngày mượn
                        ltm->tm_mday += 7; // Cộng 7 ngày
                        mktime(ltm); // Cập nhật lại cấu trúc thời gian
                        stringstream dateTra;
                        dateTra << 1900 + ltm->tm_year << "-" << 1 + ltm->tm_mon << "-" << ltm->tm_mday;
                        phieu.ngayPhaiTra = dateTra.str();
                    }
                    else {
                        phieu.ngayPhaiTra = ngayTraInput; // Gán ngày phải trả nhập vào
                    }

                    // Ghi thông tin vào file phiếu mượn
                    file << phieu.soPhieuMuon << "|" << phieu.maBanDoc << "|" << phieu.maSach << "|"
                        << phieu.ngayMuon << "|" << phieu.ngayPhaiTra << "|" << phieu.tinhTrang << endl;
                    setColor(10);
                    cout << "Muon sach thanh cong!\n";

                    // Cập nhật trạng thái sách trong file
                    sachFile.close();

                    // Cập nhật trạng thái sách trong file Sach.txt
                    ofstream tempSachFile("tempSach.txt");
                    ifstream sachFileForUpdate("Sach.txt");

                    while (getline(sachFileForUpdate, line)) {
                        if (line.find(phieu.maSach) == 0) {
                            tempSachFile << line.substr(0, line.size() - 1) << "1" << endl; // Cập nhật trạng thái sách
                        }
                        else {
                            tempSachFile << line << endl;
                        }
                    }

                    sachFileForUpdate.close();
                    tempSachFile.close();

                    remove("Sach.txt");
                    if (rename("tempSach.txt", "Sach.txt") != 0) {
                        setColor(12);
                        cout << "Khong the doi ten file Sach.txt\n";
                    }

                    file.close(); // Đóng file sau khi ghi
                    return; // Ngưng vòng lặp khi đã tìm thấy sách
                }
                else {
                    setColor(14);
                    cout << "Sach da co ai do muon roi. Vui long cho nhe!\n";
                    sachDaDuocMuon = true; // Sách đã được mượn
                    break; // Ngưng vòng lặp khi đã tìm thấy sách
                }
            }
        }

        sachFile.close();

        if (sachTonTai && !sachDaDuocMuon) {
            setColor(14);
            cout << "Sach da duoc muon!\n";
        }
        else if (!sachTonTai) {
            setColor(12);
            cout << "Khong tim thay sach!\n";
        }

        file.close();
    }

    void hienThiTatCaPhieuMuon() {
        ifstream file("PhieuMuon.txt");
        if (!file.is_open()) {
            setColor(12);
            cout << "Khong the mo file PhieuMuon.txt\n";
            return;
        }

        string line;
        while (getline(file, line)) {
            PhieuMuon phieu;
            stringstream ss(line);
            string maSach;

            ss >> phieu.soPhieuMuon;
            ss.ignore(); // Bỏ qua ký tự '|' sau soPhieuMuon
            getline(ss, phieu.maBanDoc, '|');
            getline(ss, phieu.maSach, '|');
            getline(ss, phieu.ngayMuon, '|');
            getline(ss, phieu.ngayPhaiTra, '|');
            ss >> phieu.tinhTrang;

            phieu.hienThiThongTin();
        }

        file.close();
    }

    void traSach() {
        int soPhieuTra;
        setColor(11);
        cout << "Nhap So Phieu Muon can tra: ";
        setColor(15);
        cin >> soPhieuTra;

        ifstream file("PhieuMuon.txt");
        ofstream tempFile("temp.txt");
        bool timThayPhieu = false;

        if (!file.is_open() || !tempFile.is_open()) {
            setColor(12);
            cout << "Khong the mo file\n";
            return;
        }

        string line;

        while (getline(file, line)) {
            stringstream ss(line);
            int soPhieuMuon;
            ss >> soPhieuMuon;

            if (soPhieuMuon == soPhieuTra) {
                timThayPhieu = true;
                string maSach;
                getline(ss, maSach, '|');

                ifstream sachFile("Sach.txt");
                ofstream tempSachFile("tempSach.txt");

                string lineSach;
                while (getline(sachFile, lineSach)) {
                    if (lineSach.find(maSach) == 0) {
                        tempSachFile << lineSach.substr(0, lineSach.size() - 1) << "0" << endl; // Cập nhật trạng thái sách
                    }
                    else {
                        tempSachFile << lineSach << endl;
                    }
                }

                sachFile.close();
                tempSachFile.close();

                remove("Sach.txt");
                if (rename("tempSach.txt", "Sach.txt") != 0) {
                    setColor(12);
                    cout << "Khong the doi ten file Sach.txt\n";
                }
                setColor(10);
                cout << "Tra sach thanh cong!\n";
            }
            else {
                tempFile << line << endl;
            }
        }

        file.close();
        tempFile.close();

        if (timThayPhieu) {
            remove("PhieuMuon.txt");
            if (rename("temp.txt", "PhieuMuon.txt") != 0) {
                setColor(12);
                cout << "Khong the doi ten file PhieuMuon.txt\n";
            }
        }
        else {
            setColor(14);
            cout << "Khong tim thay so phieu muon\n";
            remove("temp.txt");
        }
    }
};
class BanDoc {
public:
    string maBanDoc, tenBanDoc, khoa;
    int ngaySinh, thangSinh, namSinh;
    string ngayDangKy; // Thêm trường cho ngày đăng ký

    BanDoc() : ngaySinh(1), thangSinh(1), namSinh(1970) {
        // Lấy ngày hiện tại
        time_t now = time(0);
        tm* ltm = localtime(&now);
        // Định dạng ngày đăng ký
        ngayDangKy = to_string(ltm->tm_mday) + "/" + to_string(1 + ltm->tm_mon) + "/" + to_string(1900 + ltm->tm_year);
    }

    void hienThiTatCaBanDoc() {
        ifstream file("BanDoc.txt");
        if (!file.is_open()) {
            cout << "Khong the mo file BanDoc.txt\n";
            return;
        }

        string line;
        while (getline(file, line)) {
            BanDoc banDoc;
            stringstream ss(line);

            getline(ss, banDoc.maBanDoc, '|');
            getline(ss, banDoc.tenBanDoc, '|');
            getline(ss, banDoc.khoa, '|');

            // Đọc ngày, tháng, năm sinh
            ss >> banDoc.ngaySinh;
            ss.ignore(); // Bỏ qua ký tự phân cách
            ss >> banDoc.thangSinh;
            ss.ignore(); // Bỏ qua ký tự phân cách
            ss >> banDoc.namSinh;
            ss.ignore(); // Bỏ qua ký tự phân cách
            getline(ss, banDoc.ngayDangKy, '|'); // Đọc ngày đăng ký

            // Hiển thị thông tin
            banDoc.hienThiThongTin();
        }

        file.close();
    }

    void themBanDoc() {
        ofstream file("BanDoc.txt", ios::app);
        if (!file.is_open()) {
            setColor(12);
            cout << "Khong the mo file BanDoc.txt\n";
            return;
        }

        BanDoc banDoc;
        setColor(11);
        cout << "Nhap Ma Ban Doc: ";
        setColor(15);
        cin >> banDoc.maBanDoc;

        ifstream checkFile("BanDoc.txt");
        string line;
        while (getline(checkFile, line)) {
            if (line.find(banDoc.maBanDoc) != string::npos) {
                setColor(14);
                cout << "Ma ban doc da ton tai. Khong the them.\n";
                checkFile.close();
                file.close(); // Đóng file ghi
                return;
            }
        }
        checkFile.close();
        setColor(11);
        cout << "Nhap Ten Ban Doc: ";
        setColor(15);
        cin.ignore();
        getline(cin, banDoc.tenBanDoc);
        setColor(11);
        cout << "Nhap Khoa: ";
        setColor(15);
        getline(cin, banDoc.khoa);
        setColor(11);
        cout << "Nhap Ngay Sinh (dd mm yyyy): ";
        setColor(15);
        cin >> banDoc.ngaySinh >> banDoc.thangSinh >> banDoc.namSinh;

        // Ghi thông tin vào file theo định dạng yêu cầu
        file << banDoc.maBanDoc << "|" << banDoc.tenBanDoc << "|" << banDoc.khoa << "|"
            << banDoc.ngaySinh << "|" << banDoc.thangSinh << "|" << banDoc.namSinh << "|"
            << banDoc.ngayDangKy << endl; // Ghi thêm ngày đăng ký
        setColor(10);
        cout << "Them ban doc thanh cong!\n";
        file.close();
    }

    void hienThiThongTin() {
        setColor(10);
        cout << "Ma Ban Doc: "; setColor(11); cout << maBanDoc << endl;
        setColor(10);
        cout << "Ten Ban Doc: "; setColor(13); cout << tenBanDoc << endl;
        setColor(10);
        cout << "Khoa: "; setColor(15); cout << khoa << endl;
        setColor(10);
        cout << "Ngay Sinh: "; setColor(15); cout << ngaySinh << "/" << thangSinh << "/" << namSinh << endl;
        setColor(10);
        cout << "Ngay Dang Ky: "; setColor(9); cout << ngayDangKy << endl; // Hiển thị ngày đăng ký
        setColor(14);
        cout << "----------------------------\n";
        setColor(8);
    }

    void xoaBanDoc() {
        string maBanDocXoa;
        setColor(11);
        cout << "Nhap Ma Ban Doc can xoa: ";
        setColor(15);
        cin >> maBanDocXoa;

        ifstream file("BanDoc.txt");
        ofstream tempFile("temp.txt");
        bool banDocTonTai = false;
        bool coPhieuMuon = false;

        if (!file.is_open()) {
            cout << "Khong the mo file BanDoc.txt\n";
            return;
        }

        string line;
        while (getline(file, line)) {
            if (line.find(maBanDocXoa) == 0) {
                banDocTonTai = true;
                // Kiểm tra nếu bạn đọc có phiếu mượn nào không
                coPhieuMuon = checkPhieuMuon(maBanDocXoa);
                if (coPhieuMuon) {
                    setColor(12);
                    cout << "Khong the xoa ban doc, vi ban doc dang co phieu muon\n";
                }
                // Nếu có phiếu mượn, không ghi vào tệp tạm
            }
            else {
                tempFile << line << endl; // Ghi lại thông tin của bạn đọc không bị xóa
            }
        }

        file.close();
        tempFile.close();

        if (banDocTonTai && !coPhieuMuon) {
            // Nếu bạn đọc tồn tại và không có phiếu mượn, thực hiện xóa
            remove("BanDoc.txt");
            if (rename("temp.txt", "BanDoc.txt") != 0) {
                setColor(12);
                cout << "Loi khi doi ten file\n";
            }
            else {
                setColor(10);
                cout << "Xoa ban doc thanh cong!\n";
            }
        }
        else if (!banDocTonTai) {
            setColor(14);
            cout << "Khong tim thay ma ban doc\n";
            remove("temp.txt"); // Xóa file tạm nếu không tìm thấy
        }
    }

    // Hàm kiểm tra xem bạn đọc có phiếu mượn nào không
    bool checkPhieuMuon(const string& maBanDoc) {
        ifstream file("PhieuMuon.txt");
        if (!file.is_open()) {
            setColor(12);
            cout << "Khong the mo file PhieuMuon.txt\n";
            return false;
        }

        string line;
        while (getline(file, line)) {
            string maBanDocPhieu;
            stringstream ss(line);

            // Đọc soPhieuMuon (bỏ qua nếu không cần thiết)
            getline(ss, maBanDocPhieu, '|'); // Đọc soPhieuMuon (bỏ qua)
            getline(ss, maBanDocPhieu, '|'); // Đọc maBanDoc

            if (maBanDocPhieu == maBanDoc) {
                file.close();
                return true; // Có phiếu mượn
            }
        }

        file.close();
        return false; // Không có phiếu mượn
    }
};

// Tạo giao diện để người dùng nhìn thấy và tương tác
void mainMenu() {
    system("cls");
    setColor(6);
    cout << "* * * * * * * * * * * * * * * * * * * *\n";
    setColor(9); cout << "*             "; setColor(10); cout << "MENU CHINH"; setColor(9); cout << "              *\n";
    setColor(9);cout << "* "; setColor(15);cout << "1. Quan ly sach";  setColor(9);cout << "                     *\n";
    setColor(9);cout << "* ";setColor(15);cout << "2. Quan ly ban doc";setColor(9);cout << "                  *\n"; // Chỉnh sửa cho khớp với 1
    setColor(9);cout << "* ";setColor(15);cout << "3. Quan ly phieu muon";setColor(9);cout << "               *\n"; // Chỉnh sửa cho khớp với 1
    setColor(9);cout << "* ";setColor(12);cout << "0. Thoat";setColor(9);cout << "                            *\n"; // Chỉnh sửa cho khớp với 1
    setColor(6);
    cout << "* * * * * * * * * * * * * * * * * * * *\n";
}
void quanLySachMenu() {
    system("cls");
    setColor(6);
    cout << "* * * * * * * * * * * * * * * * * * * *\n";
    setColor(9);
    cout << "*           ";
    setColor(10);
    cout << "QUAN LY SACH";
    setColor(9);
    cout << "              *\n";

    setColor(9);
    cout << "* ";
    setColor(15);
    cout << "1. Hien thi tat ca sach";
    setColor(9);
    cout << "             *\n";

    setColor(9);
    cout << "* ";
    setColor(15);
    cout << "2. Them sach";
    setColor(9);
    cout << "                        *\n";

    setColor(9);
    cout << "* ";
    setColor(15);
    cout << "3. Xoa sach";
    setColor(9);
    cout << "                         *\n";

    setColor(9);
    cout << "* ";
    setColor(12);
    cout << "0. Tro ve";
    setColor(9);
    cout << "                           *\n";

    setColor(6);
    cout << "* * * * * * * * * * * * * * * * * * * *\n";
}
void quanLyBanDocMenu() {
    system("cls");
    setColor(6);
    cout << "* * * * * * * * * * * * * * * * * * * *\n";
    setColor(9);
    cout << "*          ";
    setColor(10);
    cout << "QUAN LY BAN DOC";
    setColor(9);
    cout << "            *\n";

    setColor(9);
    cout << "* ";
    setColor(15);
    cout << "1. Hien thi tat ca ban doc";
    setColor(9);
    cout << "          *\n";

    setColor(9);
    cout << "* ";
    setColor(15);
    cout << "2. Them ban doc";
    setColor(9);
    cout << "                     *\n";

    setColor(9);
    cout << "* ";
    setColor(15);
    cout << "3. Xoa ban doc";
    setColor(9);
    cout << "                      *\n";

    setColor(9);
    cout << "* ";
    setColor(12);
    cout << "0. Tro ve";
    setColor(9);
    cout << "                           *\n";

    setColor(6);
    cout << "* * * * * * * * * * * * * * * * * * * *\n";
}
void quanLyPhieuMuonMenu() {
    system("cls");
    setColor(6);
    cout << "* * * * * * * * * * * * * * * * * * * *\n";
    setColor(9);
    cout << "*          ";
    setColor(10);
    cout << "QUAN LY PHIEU MUON";
    setColor(9);
    cout << "         *\n";

    setColor(9);
    cout << "* ";
    setColor(15);
    cout << "1. Hien thi tat ca phieu muon";
    setColor(9);
    cout << "       *\n";

    setColor(9);
    cout << "* ";
    setColor(15);
    cout << "2. Muon sach";
    setColor(9);
    cout << "                        *\n";

    setColor(9);
    cout << "* ";
    setColor(15);
    cout << "3. Tra sach";
    setColor(9);
    cout << "                         *\n";

    setColor(9);
    cout << "* ";
    setColor(12);
    cout << "0. Tro ve";
    setColor(9);
    cout << "                           *\n";

    setColor(6);
    cout << "* * * * * * * * * * * * * * * * * * * *\n";
}
void EndChuongTrinh() {
    system("cls");
    setColor(14);
    cout << "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
    cout << "*                                                                                   *\n";
    setColor(14);
    cout << "*    "; setColor(10); cout << "CAM ON VI DA SU DUNG DICH VU QUAN LY THU VIEN CUA TEAM NHAU NHUC NHU NHIEU"; setColor(14); cout << "     * \n";
    setColor(14);
    cout << "*                                                                                   *\n";
    cout << "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
}
// Chạy chương trình
int main() {
    Admin admin;
    if (!admin.login()) {
        return 0;
    }

    Sach sach;
    BanDoc banDoc;
    PhieuMuon phieuMuon;

    int luaChon;
    do {
        mainMenu();
        setColor(11);
        cout << "Nhap lua chon: ";
        setColor(15);
        cin >> luaChon;

        // Kiểm tra nhập liệu
        while (cin.fail() || luaChon < 0 || luaChon > 3) {
            setColor(12);
            cout << "Lua chon khong hop le. Vui long nhap lai!! ";
            cin.clear(); // Xóa lỗi
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Xóa bộ đệm
            setColor(11);
            cout << "Nhap lua chon: ";
            setColor(15);
            cin >> luaChon;
        }

        switch (luaChon) {
        case 1: {
            int luaChonSach;
            do {
                quanLySachMenu();
                setColor(11);
                cout << "Nhap lua chon: ";
                setColor(15);
                cin >> luaChonSach;

                // Kiểm tra nhập liệu cho sách
                while (cin.fail() || luaChonSach < 0 || luaChonSach > 3) {
                    setColor(12);
                    cout << "Lua chon khong hop le. Vui long nhap lai!! ";
                    cin.clear(); // Xóa lỗi
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Xóa bộ đệm
                    setColor(11);
                    cout << "Nhap lua chon: ";
                    setColor(15);
                    cin >> luaChonSach;
                }

                switch (luaChonSach) {
                case 1:
                    sach.hienThiTatCaSach();
                    break;
                case 2:
                    sach.themSach();
                    break;
                case 3:
                    sach.xoaSach();
                    break;
                }
                if (luaChonSach != 0) {
                    // Ask user to press 1 to return to main menu
                    setColor(14);
                    cout << "Nhan 1 de quay lai menu chinh: ";
                    cin >> luaChonSach;
                }
            } while (luaChonSach != 0); // Nhấn 0 để trở về menu chính
            break;
        }
        case 2: {
            int luaChonBanDoc;
            do {
                quanLyBanDocMenu();
                setColor(11);
                cout << "Nhap lua chon: ";
                setColor(15);
                cin >> luaChonBanDoc;

                // Kiểm tra nhập liệu cho bạn đọc
                while (cin.fail() || luaChonBanDoc < 0 || luaChonBanDoc > 3) {
                    setColor(12);
                    cout << "Lua chon khong hop le. Vui long nhap lai!! ";
                    cin.clear(); // Xóa lỗi
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Xóa bộ đệm
                    setColor(11);
                    cout << "Nhap lua chon: ";
                    setColor(15);
                    cin >> luaChonBanDoc;
                }

                switch (luaChonBanDoc) {
                case 1:
                    banDoc.hienThiTatCaBanDoc();
                    break;
                case 2:
                    banDoc.themBanDoc();
                    break;
                case 3:
                    banDoc.xoaBanDoc();
                    break;
                }
                if (luaChonBanDoc != 0) {
                    // Ask user to press 1 to return to main menu
                    setColor(14);
                    cout << "Nhan 1 de quay lai menu chinh: ";
                    cin >> luaChonBanDoc;
                }
            } while (luaChonBanDoc != 0); // Nhấn 0 để trở về menu chính
            break;
        }
        case 3: {
            int luaChonPhieuMuon;
            do {
                quanLyPhieuMuonMenu();
                setColor(11);
                cout << "Nhap lua chon: ";
                setColor(15);
                cin >> luaChonPhieuMuon;

                // Kiểm tra nhập liệu cho phiếu mượn
                while (cin.fail() || luaChonPhieuMuon < 0 || luaChonPhieuMuon > 3) {
                    setColor(12);
                    cout << "Lua chon khong hop le. Vui long nhap lai!! ";
                    cin.clear(); // Xóa lỗi
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Xóa bộ đệm
                    setColor(11);
                    cout << "Nhap lua chon: ";
                    setColor(15);
                    cin >> luaChonPhieuMuon;
                }

                switch (luaChonPhieuMuon) {
                case 1:
                    phieuMuon.hienThiTatCaPhieuMuon();
                    break;
                case 2:
                    phieuMuon.muonSach();
                    break;
                case 3:
                    phieuMuon.traSach();
                    break;
                }
                if (luaChonPhieuMuon != 0) {
                    // Ask user to press 1 to return to main menu
                    setColor(14);
                    cout << "Nhan 1 de quay lai menu chinh: ";
                    cin >> luaChonPhieuMuon;
                }
            } while (luaChonPhieuMuon != 0); // Nhấn 0 để trở về menu chính
            break;
        }
        }
    } while (luaChon != 0); // Khi nhập 0 từ menu chính, chương trình sẽ thoát
    system("cls");
    EndChuongTrinh();
    return 0;
}