#include <iostream>
#include <list>
#include <string>
#include <iomanip>
#include <vector>
#include <stack>
#include <queue>
#include <fstream>
#include <set>
#include <random> 

using namespace std;

// =====================
// Kelas User untuk autentikasi
// =====================
class User {
public:
    string username;
    string password;

    User(string uname, string pwd) : username(uname), password(pwd) {}

    // Mengecek login user
    bool login(string uname, string pwd) {
        return username == uname && password == pwd;
    }
};

// =====================
// Kelas Movie untuk data film
// =====================
class Movie {
private:
    string title;
    string schedule;
    string day;
    int price;

public:
    Movie(string t, string s, string d, int p) : title(t), schedule(s), day(d), price(p) {}

    string getTitle() const { return title; }
    void setTitle(const string& t) { title = t; }

    string getSchedule() const { return schedule; }
    void setSchedule(const string& s) { schedule = s; }

    string getDay() const { return day; }
    void setDay(const string& d) { day = d; }

    int getPrice() const { return price; }
    void setPrice(int p) { price = p; }
};

// =====================
// Baca/simpan user, barcode
// =====================
void saveUser(const string& username, const string& password) {
    ofstream fout("users.txt", ios::app);
    fout << username << "," << password << endl;
    fout.close();
}

void loadUsers(list<User*>& users) {
    ifstream fin("users.txt");
    string line;
    while (getline(fin, line)) {
        size_t pos = line.find(',');
        if (pos != string::npos) {
            string uname = line.substr(0, pos);
            string pwd = line.substr(pos + 1);
            users.push_back(new User(uname, pwd));
        }
    }
    fin.close();
}

// Membuat nomor barcode random dengan jumlah digit tetap
string generateBarcode(int length = 16) {
    string barcode;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 9);
    for (int i = 0; i < length; ++i) {
        barcode += to_string(dis(gen));
    }
    return barcode;
}
