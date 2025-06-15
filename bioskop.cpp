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

// =====================
// Kelas Cinema untuk manajemen film & kursi
// =====================
class Cinema {
private:
    vector<vector<int>> seats;
    vector<Movie*> movies;
    const int numSeats = 50; 

    // Membuat teks rata tengah
    string center(const string &str, int width) {
        int len = str.length();
        if (len >= width) {
            return str;
        }
        int leftPadding = (width - len) / 2;
        int rightPadding = width - len - leftPadding;
        return string(leftPadding, ' ') + str + string(rightPadding, ' ');
    }

    // Membuat harga rata tengah
    string centerPrice(int price, int width) {
        string priceStr = "Rp " + to_string(price * 10000);
        int len = priceStr.length();
        if (len >= width) {
            return priceStr;
        }
        int leftPadding = (width - len) / 2;
        int rightPadding = width - len - leftPadding;
        return string(leftPadding, ' ') + priceStr + string(rightPadding, ' ');
    }

public:
    Cinema() {
        for (auto movie : movies) {
            delete movie;
        }
    }

    // Menambah film baru
    void addMovie(Movie* movie) {
        movies.push_back(movie);
        seats.push_back(vector<int>(numSeats, 0));
    }

    // Menampilkan daftar film
    void displayMovies() {
        cout << "\033[1;34m" << setw(5) << center("ID", 5) 
             << setw(30) << center("Judul Film", 30) 
             << setw(15) << center("Hari", 15) 
             << setw(20) << center("Jam Tayang", 20) 
             << setw(15) << center("Harga", 15) 
             << setw(10) << center("Studio", 10) 
             << "\033[0m" << endl;
        cout << "\033[1;34m----------------------------------------------------------------------------------------------\033[0m" << endl;
        for (size_t i = 0; i < movies.size(); ++i) {
            cout << setw(5)  << center(to_string(i + 1), 5)
                 << setw(30) << center(movies[i]->getTitle(), 30)
                 << setw(15) << center(movies[i]->getDay(), 15)
                 << setw(20) << center(movies[i]->getSchedule(), 20)
                 << setw(15) << centerPrice(movies[i]->getPrice(), 15)
                 << setw(10) << center("Studio " + string(1, 'A' + i), 10) 
                 << endl;
        }
        cout << "\033[1;34m-----------------------------------------------------------------------------------------------\033[0m" << endl;
    }

    // Memilih kursi (jika belum dibooking)
    bool selectSeat(size_t movieID, int seatNumber) {
        if (seats[movieID][seatNumber] == 0) {
            seats[movieID][seatNumber] = 1;
            return true;
        }
        return false;
    }

    // Mengambil pointer Movie berdasarkan ID
    Movie* getMovie(size_t movieID) {
        return movies[movieID];
    }

    // Mendapatkan jumlah film
    size_t getNumberOfMovies() {
        return movies.size();
    }

    // Menampilkan tiket setelah booking
    void displayTicket(User* user, Movie* movie, int seatNumber) {
        char studio = 'A' + stoi(movie->getSchedule().substr(1, 1)) - 1;
        cout << "\033[1;32m=============================================" << endl;
        cout << "   Ticket - " << movie->getTitle() << endl;
        cout << "=============================================" << endl;
        cout << "Movie: " << movie->getTitle() << endl;
        cout << "Time : " << movie->getSchedule() << endl;
        cout << "Seat : " << seatNumber << endl;
        cout << "Price: Rp " << movie->getPrice() * 10000 << endl;
        cout << "Studio: " << studio << endl;
        cout << "=============================================" << endl;
        cout << "Enjoy your movie, " << user->username << "!" << endl;
        cout << "\033[0m" << endl;
        cout << endl;
    }
};

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
// =====================
// Kelas Cinema utk manajemen film sama kursi
// =====================
class Cinema {
private:
    vector<vector<int>> seats;
    vector<Movie*> movies;
    const int numSeats = 50; 

    // Membuat teks rata tengah
    string center(const string &str, int width) {
        int len = str.length();
        if (len >= width) {
            return str;
        }
        int leftPadding = (width - len) / 2;
        int rightPadding = width - len - leftPadding;
        return string(leftPadding, ' ') + str + string(rightPadding, ' ');
    }

    // Membuat harga rata tengah
    string centerPrice(int price, int width) {
        string priceStr = "Rp " + to_string(price * 10000);
        int len = priceStr.length();
        if (len >= width) {
            return priceStr;
        }
        int leftPadding = (width - len) / 2;
        int rightPadding = width - len - leftPadding;
        return string(leftPadding, ' ') + priceStr + string(rightPadding, ' ');
    }

public:
    Cinema() {
        for (auto movie : movies) {
            delete movie;
        }
    }

    // Menambah film baru
    void addMovie(Movie* movie) {
        movies.push_back(movie);
        seats.push_back(vector<int>(numSeats, 0));
    }

    // Menampilkan daftar filmnya ada apa aja 
    void displayMovies() {
        cout << "\033[1;34m" << setw(5) << center("ID", 5) 
             << setw(30) << center("Judul Film", 30) 
             << setw(15) << center("Hari", 15) 
             << setw(20) << center("Jam Tayang", 20) 
             << setw(15) << center("Harga", 15) 
             << setw(10) << center("Studio", 10) 
             << "\033[0m" << endl;
        cout << "\033[1;34m----------------------------------------------------------------------------------------------\033[0m" << endl;
        for (size_t i = 0; i < movies.size(); ++i) {
            cout << setw(5)  << center(to_string(i + 1), 5)
                 << setw(30) << center(movies[i]->getTitle(), 30)
                 << setw(15) << center(movies[i]->getDay(), 15)
                 << setw(20) << center(movies[i]->getSchedule(), 20)
                 << setw(15) << centerPrice(movies[i]->getPrice(), 15)
                 << setw(10) << center("Studio " + string(1, 'A' + i), 10) 
                 << endl;
        }
        cout << "\033[1;34m-----------------------------------------------------------------------------------------------\033[0m" << endl;
    }

    // Memilih kursi (jika belum dibooking)
    bool selectSeat(size_t movieID, int seatNumber) {
        if (seats[movieID][seatNumber] == 0) {
            seats[movieID][seatNumber] = 1;
            return true;
        }
        return false;
    }

    // Mengambil pointer Movie berdasarkan ID
    Movie* getMovie(size_t movieID) {
        return movies[movieID];
    }

    // Mendapatkan jumlah film
    size_t getNumberOfMovies() {
        return movies.size();
    }

    // Menampilkan tiket setelah booking
    void displayTicket(User* user, Movie* movie, int seatNumber) {
        char studio = 'A' + stoi(movie->getSchedule().substr(1, 1)) - 1;
        cout << "\033[1;32m=============================================" << endl;
        cout << "   Ticket - " << movie->getTitle() << endl;
        cout << "=============================================" << endl;
        cout << "Movie: " << movie->getTitle() << endl;
        cout << "Time : " << movie->getSchedule() << endl;
        cout << "Seat : " << seatNumber << endl;
        cout << "Price: Rp " << movie->getPrice() * 10000 << endl;
        cout << "Studio: " << studio << endl;
        cout << "=============================================" << endl;
        cout << "Enjoy your movie, " << user->username << "!" << endl;
        cout << "\033[0m" << endl;
        cout << endl;
    }
};

// =====================
// Fungsi utama aplikasi
// =====================
int main() {
    list<User*> users; 
    Cinema cinema;

    stack<string> bookingActions;
    queue<User*> waitingList;

    // Membaca data user dari file users.txt sebelum menu
    loadUsers(users);

    displayHeader();
    cout << endl;
    displayMenu();

    string choice;
    cin >> choice;

    // =====================
    // Proses Register
    // =====================
    if (choice == "1") {
        string username, password;
        cout << "Enter username: ";
        cin >> username;

        if (username.length() > 20) {
            cout << "\033[1;31mInvalid username length. Maximum length is 20 characters.\033[0m" << endl;
            return 0;
        }

        cout << "Enter password: ";
        cin >> password;
        users.push_back(new User(username, password));
        saveUser(username, password);

        cout << "\033[1;32mRegistration successful!\033[0m" << endl;
        cout << endl;

        cout << "=========================" << endl;
        cout << "\033[38;5;208mPlease login to continue.\033[0m" << endl;

        cout << "Username: ";
        cin >> username;
        cout << "Password: ";
        cin >> password;
        cout << endl;

        bool loggedIn = false;
        User* currentUser = nullptr;
        for (User* user : users) {
            if (user->login(username, password)) {
                loggedIn = true;
                currentUser = user;
                break;
            }
        }

        if (!loggedIn) {
            cout << "\033[1;31mInvalid credentials\033[0m" << endl;
            return 0;
        }

        // Tambahkan daftar film
        cinema.addMovie(new Movie("When I Fly Towards You", "10:00 AM", "Monday", 10));
        cinema.addMovie(new Movie("Hidden Love", "12.30 PM", "Tuesday", 12));
        cinema.addMovie(new Movie("Math Teacher, My Soulmate", "03.00 PM", "Wednesday", 20));
        cinema.addMovie(new Movie("Lovely Runner", "05.30 PM", "Thursday", 13));
        cinema.addMovie(new Movie("Death's Game", "08.00 PM", "Friday", 17));

        // Proses booking
        size_t movieID;
        int seatNumber;
        cinema.displayMovies();
        cout << "Select a movie by ID: ";
        cin >> movieID;
        movieID--;

        if (movieID >= cinema.getNumberOfMovies()) {
            cout << "\033[1;31mInvalid movie ID\033[0m" << endl;
            return 0;
        }

        string movieTitle = cinema.getMovie(movieID)->getTitle();
        set<int> booked = getBookedSeats(movieTitle);
        displaySeats(booked, 50, 10);

        cout << "Select a seat number (0-49): ";
        cin >> seatNumber;

        if (seatNumber < 0 || seatNumber >= 50) {
            cout << "\033[1;31mInvalid seat number\033[0m" << endl;
            return 0;
        }
        if (booked.count(seatNumber)) {
            cout << "\033[1;31mSeat already booked!\033[0m" << endl;
            return 0;
        }

        if (cinema.selectSeat(movieID, seatNumber)) {
            saveBooking(currentUser->username, movieTitle, seatNumber); // Simpan ke file
            bookingActions.push("User " + currentUser->username + " booked seat " + to_string(seatNumber) + " for movie " + movieTitle);
            Booking::confirmBooking(currentUser, cinema.getMovie(movieID), seatNumber);
            cinema.displayTicket(currentUser, cinema.getMovie(movieID), seatNumber);
        } else {
            cout << "\033[1;31mSeat is already taken. Adding to the waiting list.\033[0m" << endl;
            waitingList.push(currentUser);
        }
    } 
    // =====================
    // Proses Login
    // =====================
    else if (choice == "2") {
        string username, password;
        cout << "Username: ";
        cin >> username;
        cout << "Password: ";
        cin >> password;
        cout << endl;

        bool loggedIn = false;
        User* currentUser = nullptr;
        for (User* user : users) {
            if (user->login(username, password)) {
                loggedIn = true;
                currentUser = user;
                break;
            }
        }

        if (!loggedIn) {
            cout << "\033[1;31mInvalid credentials\033[0m" << endl;
            return 0;
        }

        // Tambahkan daftar film
        cinema.addMovie(new Movie("When I Fly Towards You", "10:00 AM", "Monday", 10));
        cinema.addMovie(new Movie("Hidden Love", "12.30 PM", "Tuesday", 12));
        cinema.addMovie(new Movie("Math Teacher, My Soulmate", "03.00 PM", "Wednesday", 20));
        cinema.addMovie(new Movie("Lovely Runner", "05.30 PM", "Thursday", 13));
        cinema.addMovie(new Movie("Death's Game", "08.00 PM", "Friday", 17));

        // Proses booking
        size_t movieID;
        int seatNumber;
        cinema.displayMovies();
        cout << "Select a movie by ID: ";
        cin >> movieID;
        movieID--;

        if (movieID >= cinema.getNumberOfMovies()) {
            cout << "\033[1;31mInvalid movie ID\033[0m" << endl;
            return 0;
        }

        string movieTitle = cinema.getMovie(movieID)->getTitle();
        set<int> booked = getBookedSeats(movieTitle);
        displaySeats(booked, 50, 10);

        cout << "Select a seat number (0-49): ";
        cin >> seatNumber;

        if (seatNumber < 0 || seatNumber >= 50) {
            cout << "\033[1;31mInvalid seat number\033[0m" << endl;
            return 0;
        }
        if (booked.count(seatNumber)) {
            cout << "\033[1;31mSeat already booked!\033[0m" << endl;
            return 0;
        }

        if (cinema.selectSeat(movieID, seatNumber)) {
            saveBooking(currentUser->username, movieTitle, seatNumber); // Simpan ke file
            bookingActions.push("User " + currentUser->username + " booked seat " + to_string(seatNumber) + " for movie " + movieTitle);
            Booking::confirmBooking(currentUser, cinema.getMovie(movieID), seatNumber);
            cinema.displayTicket(currentUser, cinema.getMovie(movieID), seatNumber);
        } else {
            cout << "\033[1;31mSeat is already taken. Adding to the waiting list.\033[0m" << endl;
            waitingList.push(currentUser);
        }
    } 
    // =====================
    // Pilihan menu tidak valid
    // =====================
    else {
        cout << "\033[1;31mInvalid option selected\033[0m" << endl;
        return 0;
    }

    // Dealokasi user
    for (User* user : users) {
        delete user;
    }

    // =====================
    // Menampilkan barcode tiket
    // =====================
    cout << endl;
    cout << "            Scan Barcode:            " << endl;
    cout << " __                               __ " << endl;
    cout << "|  ===============================  |" << endl;
    cout << "   []||||||||[]|||||||[]||||||||[]   " << endl;
    cout << "   []||||||||[]|||||||[]||||||||[]   " << endl;
    cout << "   []||||||||[]|||||||[]||||||||[]   " << endl;
    cout << "   []||||||||[]|||||||[]||||||||[]   " << endl;
    string barcode = generateBarcode(16);
    cout << "   ";
    for (char c : barcode) {
        cout << c << " ";
    }
    cout << "  " << endl;
    cout << "|===============================|" << endl;

    // =====================
    // Menampilkan riwayat booking (stack)
    // =====================
    cout << endl;
    cout << "\033[1;33mRecent Booking Actions:\033[0m" << endl;
    while (!bookingActions.empty()) {
        cout << bookingActions.top() << endl;
        bookingActions.pop();
    }

    return 0;
}
