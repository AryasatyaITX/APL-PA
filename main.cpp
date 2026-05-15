#include <iostream>
#include <iomanip>
#include <limits>
#include <stdexcept>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <conio.h>
using namespace std;
#define MAX 100

// Warna
string reset = "\033[0m";
string bold = "\033[1m";
string merah = "\033[31m";
string hijau = "\033[32m";
string kuning = "\033[33m";


struct User{
    string username;
    string password;
};
User userList[MAX];
int jumlahUser = 0;

struct Login{
    string username;
    string password;
};
struct DetailHero{
    string role;
    string kesulitan;
    int level;
    string patch;
};
struct Hero{
    int id;
    string nama;
    bool meta;
    DetailHero detail;
};
struct Spell{
    int id;
    string nama;
};
struct Emblem{
    int id;
    string nama;
};
struct Map{
    int id;
    string nama;
};
struct Favorit{
    string nama;
    string role;
    int level;
    int match;
    float winrate;
};

Hero hero[MAX] = {
    {1,"Ling",true,{"Assassin","Hard",15,"Buff"}},
    {2,"Tigreal",false,{"Tank","Easy",10,"Normal"}},
    {3,"Kagura",true,{"Mage","Hard",14,"Buff"}},
    {4,"Beatrix",false,{"Marksman","Medium",13,"Nerf"}}
};

Spell spell[MAX] = {
    {1,"Flicker"},
    {2,"Retribution"}
};

Emblem emblem[MAX] = {
    {1,"Assassin"},
    {2,"Tank"}
};

Map mapGame[MAX] = {
    {1,"Broken Wall"},
    {2,"Flying Clouds"}
};

// Overloading pesan
string pesan(string nama) {
    string msg = " Anda Keluar Dari Menu : " + nama;
    cout << kuning << msg << reset << endl;
    return msg;
}
string pesan(string nama, string status) {
    string msg = " Anda Keluar Dari Menu : " + nama + " , " + status;
    cout << kuning << msg << reset << endl;
    return msg;
}

Favorit favorit[MAX];

int jumlahHero   = 4;
int jumlahSpell  = 2;
int jumlahEmblem = 2;
int jumlahMap    = 2;
int jumlahFavorit = 0;

void clearBuffer(){
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void pause(){
    cout << kuning << "Press any key to continue...\n" << reset;
    getch();
}

static bool isAllDigits(const string& s){
    if(s.empty()) return false;
    for(unsigned char c : s){
        if(!isdigit(c)) return false;
    }
    return true;
}
static bool isAllAlpha(const string& s){
    if(s.empty()) return false;
    for(unsigned char c : s){
        if(!isalpha(c)) return false;
    }
    return true;
}

int inputMenu(){
    string input;
    getline(cin, input);

    if(input.empty()){
        cout << merah << bold << "+-----------------------------+\n"
                              << "|  Input tidak boleh kosong!  |\n"
                              << "+-----------------------------+\n" << reset;
        pause();
        return -1;
    }
    if(!isAllDigits(input)){
        cout << merah << bold << "+----------------------+\n"
                              << "|  Input harus angka!  |\n"
                              << "+----------------------+\n" << reset;
        pause();
        return -1;
    }
    try{
        return stoi(input);
    }catch(...){
        cout << merah << bold << "+----------------------+\n"
                              << "|  Input tidak valid!  |\n"
                              << "+----------------------+\n" << reset;
        pause();
        return -1;
    }
}


int inputIntThrow(const string& field){
    string s;
    getline(cin, s);
    if(s.empty()) throw invalid_argument(field + " tidak boleh kosong!");
    if(!isAllDigits(s)) throw invalid_argument(field + " harus angka!");
    try{
        return stoi(s);
    }catch(...){
        throw invalid_argument(field + " tidak valid!");
    }
}

int inputIntRangeThrow(const string& field, int lo, int hi){
    int v = inputIntThrow(field);
    if(v < lo || v > hi){
        throw out_of_range(field + " harus " + to_string(lo) + "-" + to_string(hi) + "!");
    }
    return v;
}

string inputLineThrow(const string& field){
    string s;
    getline(cin, s);
    if(s.empty()) throw invalid_argument(field + " tidak boleh kosong!");
    return s;
}

void headerHero(){
    cout << hijau << bold << "========================================================================================================\n";
    cout << "|" << setw(3)  << "ID"
         << "|" << setw(20) << "Hero"
         << "|" << setw(15) << "Role"
         << "|" << setw(15) << "Kesulitan"
         << "|" << setw(8)  << "Level"
         << "|" << setw(12) << "Patch"
         << "|" << setw(10) << "Meta"
         << " |\n";
    cout << hijau << bold << "========================================================================================================\n" << reset;
}

bool loginAdmin(Login admin){
    string username, password;

        system("cls");
        cout << hijau << bold << "+---------------------------------+\n";
        cout <<                  "|           LOGIN ADMIN           |\n";
        cout <<                  "+---------------------------------+\n";

        cout << "Username : ";
        getline(cin, username);

        if(username.empty()){
            system("cls");
            cout << merah << bold << "+--------------------------------+\n"
                                  << "|  Username tidak boleh kosong!  |\n" 
                                  << "+--------------------------------+\n" << reset;
            pause();
            return false;
        }
        if(!isAllAlpha(username)){
            system("cls");
            cout << merah << bold << "+--------------------------------+\n"
                                  << "|  Username hanya boleh huruf!   |\n"
                                  << "+--------------------------------+\n" << reset;
            pause();
            return false;
        }

        cout << "Password : ";
        getline(cin, password);

        if(password.empty()){
            system("cls");
            cout << merah << bold << "+--------------------------------+\n"
                                  << "|  Password tidak boleh kosong!  |\n"
                                  << "+--------------------------------+\n" << reset;
            pause();
            return false;
        }
        if(!isAllDigits(password)){
            system("cls");
            cout << merah << bold << "+--------------------------------+\n"
                                  << "|  Password hanya boleh angka!   |\n"
                                  << "+--------------------------------+\n" << reset;
            pause();
            return false;
        }

        if(username == admin.username && password == admin.password){
            system("cls");
            cout << hijau << bold << "+-------------------+\n"
                                  << "|  Login berhasil!  |\n" 
                                  << "+-------------------+\n" << reset;
            pause();
            return true;
        }
        system("cls");
        cout << merah << bold << "+----------------+\n"
                              << "|  Login gagal!  |\n" 
                              << "+----------------+\n" << reset;
        pause();
    return false;
    }

void lihatHero(Hero *heroArr, int jml){
    if(jml == 0){
        cout << merah << bold << "+-----------------------+|\n"
                              << "|  Belum ada data hero  |\n"
                              << "+-----------------------+|\n" << reset;
        return;
    }
    headerHero();
    for(int i = 0; i < jml; i++){
        cout << hijau << bold << "|"
             << setw(3)  << heroArr[i].id
             << "|" << setw(20) << heroArr[i].nama
             << "|" << setw(15) << heroArr[i].detail.role
             << "|" << setw(15) << heroArr[i].detail.kesulitan
             << "|" << setw(8)  << heroArr[i].detail.level
             << "|" << setw(12) << heroArr[i].detail.patch
             << "|" << setw(10) << (heroArr[i].meta ? "Yes" : "No")
             << " |\n";
    }
    cout << "========================================================================================================\n" << reset;
}

void tambahHero(Hero heroArr[], int *jml){
    if(*jml >= MAX){
        throw runtime_error("Data hero penuh!");
    }

    Hero heroBaru;
    heroBaru.id = *jml + 1;

    cout << hijau << "Nama Hero        : ";
    heroBaru.nama = inputLineThrow("Nama hero");

    cout << "Role Hero        : ";
    heroBaru.detail.role = inputLineThrow("Role hero");

    cout << "Kesulitan Hero   : ";
    heroBaru.detail.kesulitan = inputLineThrow("Kesulitan hero");

    cout << "Level Hero (1-15): ";
    heroBaru.detail.level = inputIntRangeThrow("Level hero", 1, 15);

    heroBaru.detail.patch = "Normal";
    heroBaru.meta = false;

    heroArr[*jml] = heroBaru;
    (*jml)++;
    cout << reset;
    system("cls");
    cout << hijau << bold << "+------------------------------+\n"
                          << "|  Hero berhasil ditambahkan!  |\n"
                          << "+------------------------------+\n" << reset;
}


void updateHero(Hero *heroArr, int jml){
    if(jml == 0){
        throw runtime_error("Belum ada data hero.");
    }

    lihatHero(heroArr, jml);

    cout << hijau << bold << "Masukkan ID Hero : \n";
    int id = inputIntRangeThrow("ID hero", 1, jml);

    int index = -1;
    for(int i = 0; i < jml; i++){
        if(heroArr[i].id == id){
            index = i;
            break;
        }
    }
    if(index == -1){
        throw out_of_range("ID tidak ditemukan!");
    }

    Hero *target = &heroArr[index];
    system("cls");
    cout << hijau << bold << "+---------------------------+\n"
                          << "|        MENU UPDATE        |\n"
                          << "+---------------------------+\n"
                          << "|1. Nama                    |\n"
                          << "|2. Role                    |\n"
                          << "|3. Kesulitan               |\n"
                          << "|4. Level                   |\n"
                          << "|5. Patch                   |\n"
                          << "+---------------------------+\n";
    cout << "Pilih : ";
    int pilih = inputIntRangeThrow("Pilihan", 1, 5);

    switch(pilih){
        case 1:
            cout << "Nama baru : ";
            target->nama = inputLineThrow("Nama baru");
            break;
        case 2:
            cout << "Role baru : ";
            target->detail.role = inputLineThrow("Role baru");
            break;
        case 3:
            cout << "Kesulitan baru : ";
            target->detail.kesulitan = inputLineThrow("Kesulitan baru");
            break;
        case 4:
            cout << "Level baru (1-15): ";
            target->detail.level = inputIntRangeThrow("Level baru", 1, 15);
            break;
        case 5:
            cout << "Patch baru (Buff/Nerf/Normal): ";
            target->detail.patch = inputLineThrow("Patch baru");
            target->meta = (target->detail.patch == "Buff");
            break;
    }
    system("cls");
    cout << hijau << bold << "+---------------------------+\n"
                          << "|  Data berhasil diupdate!  |\n"
                          << "+---------------------------+\n" << reset;
}

int hapusHero(Hero heroArr[], int *jml){
    if(*jml == 0){
        cout << merah << bold << "+------------------------+\n"
                              << "|  Belum ada data hero.  |\n"
                              << "+------------------------+\n" << reset;
        return 0;
    }

    lihatHero(heroArr, *jml);

    cout << hijau << bold << "Masukkan ID Hero : \n";
    int id = inputMenu();
    if(id == -1) return 0;

    int index = -1;
    for(int i = 0; i < *jml; i++){
        if(heroArr[i].id == id){
            index = i;
            break;
        }
    }
    if(index == -1){
        cout << merah << bold << "+-----------------------+\n"
                              << "|  ID tidak ditemukan!  |\n"
                              << "+-----------------------+\n" << reset;
        return 0;
    }

    for(int i = index; i < *jml - 1; i++){
        heroArr[i] = heroArr[i + 1];
        heroArr[i].id = i + 1;
    }
    (*jml)--;
    system("cls");
    cout << hijau << bold << "+--------------------------+\n"
                          << "|  Data berhasil dihapus!  |\n"
                          << "+--------------------------+\n" << reset;
    return 1;
}

void lihatSpell(){
    cout << hijau << bold << "+-------------------------+\n";
    cout <<                  "|         DATA SPELL      |\n";
    cout <<                  "+-------------------------+\n";
    for(int i = 0; i < jumlahSpell; i++){
        cout << spell[i].id << ". " << spell[i].nama << endl;
    }
    cout << "+-------------------------+\n" << reset;
}

void tambahSpell(){
    if(jumlahSpell >= MAX){
        cout << "Data spell penuh!\n";
        return;
    }
    spell[jumlahSpell].id = jumlahSpell + 1;
    cout << "Nama Spell : ";
    getline(cin, spell[jumlahSpell].nama);

    if(spell[jumlahSpell].nama.empty()){
        cout << merah << bold << "+----------------------------------+\n"
                              << "|  Nama spell tidak boleh kosong!  |\n"
                              << "+----------------------------------+\n" << reset;
        return;
    }

    jumlahSpell++;
    system("cls");
    cout << hijau << bold << "+-------------------------------+\n"
                          << "|  Spell berhasil ditambahkan!  |\n"
                          << "+-------------------------------+\n" << reset;
}

void lihatEmblem(){
    cout << hijau << bold << "+-------------------------+\n";
    cout <<                  "|       DATA EMBLEM       |\n";
    cout <<                  "+-------------------------+\n";
    for(int i = 0; i < jumlahEmblem; i++){
        cout << emblem[i].id << ". " << emblem[i].nama << endl;
    }
    cout << "+-------------------------+\n" << reset;
}

void tambahEmblem(){
    if(jumlahEmblem >= MAX){
        cout << merah << bold << "+----------------------+\n"
                              << "|  Data emblem penuh!  |\n"
                              << "+----------------------+\n" << reset;
        return;
    }
    emblem[jumlahEmblem].id = jumlahEmblem + 1;
    cout << hijau << bold << "+------------------------+\n"
                          << "|   Tambah Emblem Baru   |\n"
                          << "+------------------------+\n";
    cout << "Nama Emblem : ";
    getline(cin, emblem[jumlahEmblem].nama);
    cout << reset;

    if(emblem[jumlahEmblem].nama.empty()){
        cout << merah << bold << "+-----------------------------------+\n"
                              << "|  Nama emblem tidak boleh kosong!  |\n"
                              << "+-----------------------------------+\n" << reset;
        return;
    }

    jumlahEmblem++;
    system("cls");
    cout << hijau << bold << "+--------------------------------+\n"
                          << "|  Emblem berhasil ditambahkan!  |\n"
                          << "+--------------------------------+\n" << reset;
}

void lihatMap(){
    cout << hijau << bold << "+-------------------------+\n";
    cout <<                  "|          DATA MAP       |\n";
    cout <<                  "+-------------------------+\n";
    for(int i = 0; i < jumlahMap; i++){
        cout << mapGame[i].id << ". " << mapGame[i].nama << endl;
    }
    cout << "+-------------------------+\n" << reset;
}

void tambahMap(){
    if(jumlahMap >= MAX){
        cout << merah << bold << "+-------------------+\n"
                              << "|  Data map penuh!  |\n"
                              << "+-------------------+\n" << reset;
        return;
    }
    mapGame[jumlahMap].id = jumlahMap + 1;
    cout << hijau << bold << "+-------------------+\n"
                          << "|  TAMBAH MAP BARU  |\n"
                          << "+-------------------+\n";
    cout << "Nama Map : ";
    getline(cin, mapGame[jumlahMap].nama);
    cout << reset;

    if(mapGame[jumlahMap].nama.empty()){
        cout << merah << bold << "+--------------------------------+\n"
                              << "|  Nama map tidak boleh kosong!  |\n"
                              << "+--------------------------------+\n" << reset;
        return;
    }

    jumlahMap++;
    system("cls");
    cout << hijau << bold << "+-----------------------------+\n"
                          << "|  Map berhasil ditambahkan!  |\n"
                          << "+-----------------------------+\n" << reset;
}

void sortingNama(){
    for(int i = 0; i < jumlahHero - 1; i++){
        for(int j = 0; j < jumlahHero - i - 1; j++){
            if(hero[j].nama > hero[j + 1].nama){
                swap(hero[j], hero[j + 1]);
            }
        }
    }
}

void sortingLevel(){
    for(int i = 0; i < jumlahHero - 1; i++){
        int minIdx = i;
        for(int j = i + 1; j < jumlahHero; j++){
            if(hero[j].detail.level < hero[minIdx].detail.level){
                minIdx = j;
            }
        }
        swap(hero[i], hero[minIdx]);
    }
}

void menuSorting(){
    int pilihan = 1;
    int totalPilihan = 3;
    char tombol;
    bool running = true;

    do{
        system("cls");
        cout << hijau << bold << "+-------------------------------------------+\n"
             << "|                MENU SORTING               |\n"
             << "+-------------------------------------------+\n"
             << "|1. Sorting Nama Hero" << (pilihan == 1 ? " <" : "  ") << "                     |\n"
             << "|2. Sorting Level Hero" << (pilihan == 2 ? " <" : "  ") << "                    |\n"
             << "|3. Kembali" << (pilihan == 3 ? " <" : "  ") << "                               |\n"
             << "+-------------------------------------------+\n";
        cout << kuning << bold << "Gunakan Panah Atas/Bawah, Enter untuk pilih." << reset << endl;
        tombol = getch();
        if(tombol == 72) {
            if(pilihan > 1) pilihan++;
        } else if(tombol == 80) {
             if(pilihan < totalPilihan) pilihan++;
        } else if(tombol == 13){
            switch(pilihan){
                case 1:
                    system("cls");
                    sortingNama();
                    lihatHero(hero, jumlahHero);
                    pause();
                    break;
                case 2:
                    system("cls");
                    sortingLevel();
                    lihatHero(hero, jumlahHero);
                    pause();
                    break;
                case 3:
                    system("cls");
                    pesan("Menu Sorting", "Kembali ke Menu Hero");
                    pause();
                    running = false;
                    break;
            }
        }
    }while(running == true);
return;
}

int binarySearchNama(string target){
    sortingNama();
    int low  = 0;
    int high = jumlahHero - 1;
    while(low <= high){
        int mid = (low + high) / 2;
        if(hero[mid].nama == target){
            return mid;
        } else if(hero[mid].nama < target){
            low = mid + 1;
        } else{
            high = mid - 1;
        }
    }
    return -1;
}

void cariRole(){
     int pilihan = 1;
    int totalPilihan = 6;
    char tombol;
    bool running = true;

    do{
        system("cls");
        cout << hijau << bold << "+---------------------------------+\n"
                              << "|          PILIH ROLE             |\n"
                              << "+---------------------------------+\n"
             << "|1. Mage" << (pilihan == 1 ? " <" : "  ") << "                        |\n"
             << "|2. Assassin" << (pilihan == 2 ? " <" : "  ") << "                    |\n"
             << "|3. Tank" << (pilihan == 3 ? " <" : "  ") << "                        |\n"
             << "|4. Support" << (pilihan == 4 ? " <" : "  ") << "                     |\n"
             << "|5. Marksman" << (pilihan == 5 ? " <" : "  ") << "                    |\n"
             << "|6. Kembali" << (pilihan == 6 ? " <" : "  ") << "                     |\n"
             << "+---------------------------------+\n";
        cout << kuning << bold << "gunakan Panah Atas/Bawah, Enter untuk pilih." << reset << endl;
        tombol = getch();
        if(tombol == 72) {
            if (pilihan > 1) pilihan--;
        } else if(tombol == 80) {
            if (pilihan < totalPilihan) pilihan++;
        } else if(tombol == 13){
        string roleCari;
        switch(pilihan){
            case 1:
                roleCari = "Mage";
                break;
            case 2:
                roleCari = "Assassin";
                break;
            case 3:
                roleCari = "Tank";
                break;
            case 4:
                roleCari = "Support";
                break;
            case 5:
                roleCari = "Marksman";
                break;
            case 6:
                system("cls");
                pesan("Menu Searching", "Kembali ke Menu Hero");
                running = false;
                pause();
                return;
        }

        bool ditemukan = false;
        system("cls");
        cout << hijau << bold << "+----------------------------------------------------------------+\n"
                              << "|                      HASIL SEARCH ROLE                         |\n"
                              << "+----------------------------------------------------------------+\n"
             << "|"
             << setw(3)  << "ID"
             << "|" << setw(20) << "Hero"
             << "|" << setw(15) << "Role"
             << "|" << setw(10) << "Level"
             << "|" << setw(10) << "Patch"
             << " |\n"
                << "+----------------------------------------------------------------+\n";
            for(int i = 0; i < jumlahHero; i++){
            if(hero[i].detail.role == roleCari){
                cout << "|"
                     << setw(3)  << hero[i].id
                     << "|" << setw(20) << hero[i].nama
                     << "|" << setw(15) << hero[i].detail.role
                     << "|" << setw(10) << hero[i].detail.level
                     << "|" << setw(10) << hero[i].detail.patch
                     << " |\n";
                ditemukan = true;
            }
        }
        cout << "+----------------------------------------------------------------+\n" << reset;
        if(!ditemukan){
            cout << "" << merah << bold << "+------------------------------------------------------+\n"
                                        << "| Hero dengan role " << roleCari << " tidak ditemukan. |\n"
                                        << "+------------------------------------------------------+\n" << reset;
        }
        pause();
        }
    }while(running == true);
return;
}

void menuSearching(){
    int pilihan = 1;
    int totalPilihan = 3;
    char tombol;
    bool running = true;

    do{
        system("cls");
        cout << hijau << bold << "+-------------------------------------------+\n"
             << "|               MENU SEARCHING              |\n"
             << "+-------------------------------------------+\n"
             << "|1. Search Hero Nama" << (pilihan == 1 ? " <" : "  ") << "                      |\n"
             << "|2. Search Hero Role" << (pilihan == 2 ? " <" : "  ") << "                      |\n"
             << "|3. Kembali" << (pilihan == 3 ? " <" : "  ") << "                               |\n"
             << "+-------------------------------------------+\n";
        cout << kuning << "gunakan Panah Atas/Bawah, Enter untuk pilih." << reset << endl;
        tombol = getch();
        if(tombol == 72) {
            if (pilihan > 1) pilihan--;
        } else if(tombol == 80) {
            if (pilihan < totalPilihan) pilihan++;
        } else if (tombol == 13) {
            switch(pilihan){
                case 1:{
                    system("cls");
                    string cari;
                     cout << hijau << bold << "+-------------------------------------------+\n"
                          << "|               MENU SEARCHING              |\n"
                          << "+-------------------------------------------+\n" 
                          << "Masukkan nama hero : ";
                    getline(cin, cari);
    
                    if(cari.empty()){
                        cout << merah << bold << "+---------------------------------+\n"
                             << "|  Nama hero tidak boleh kosong!  |\n"
                             << "+---------------------------------+\n" << reset;
                        pause();
                        break;
                    }
    
                    int hasil = binarySearchNama(cari);
                    if(hasil != -1){
                        cout << hijau << bold << "+--------------------------------+\n"
                             << "Hero ditemukan : " << hero[hasil].nama << endl
                             << "+--------------------------------+\n" << reset;
                    } else{
                        cout << merah << bold << "+---------------------------------+\n"
                             << "|     Hero tidak ditemukan!       |\n"
                             << "+---------------------------------+\n" << reset;
                    }
                    pause();
                    break;
                }
                case 2:
                    system("cls");
                    cariRole();
                    pause();
                    break;
                case 3:
                    system("cls");
                    pesan("Menu Searching", "Kembali ke Menu Hero");
                    running = false;
                    pause();
                    break;
            }
        }
    }while(running == true);
return;
}

void heroMeta(){
    cout << hijau << bold << "+---------------------------+\n"
         << "|         HERO META         |\n"
         << "+---------------------------+\n";
    for(int i = 0; i < jumlahHero; i++){
        if(hero[i].meta){
            cout << hero[i].nama << " | " << hero[i].detail.patch << endl;
        }
    }
    cout << "+---------------------------+\n" << reset;
}

void compareHero(){
    if(jumlahHero < 2){
        throw runtime_error("Minimal harus ada 2 hero untuk compare.");
    }

    lihatHero(hero, jumlahHero);

    cout << "\nPilih Hero 1 (ID): ";
    int aId = inputIntRangeThrow("ID hero 1", 1, jumlahHero);

    cout << "Pilih Hero 2 (ID): ";
    int bId = inputIntRangeThrow("ID hero 2", 1, jumlahHero);

    if(aId == bId){
        throw invalid_argument("Tidak bisa membandingkan hero yang sama!");
    }

    int a = aId - 1;
    int b = bId - 1;

    int powerA = hero[a].detail.level;
    int powerB = hero[b].detail.level;

    if(hero[a].detail.patch == "Buff") powerA += 5;
    if(hero[b].detail.patch == "Buff") powerB += 5;
    if(hero[a].detail.patch == "Nerf") powerA -= 5;
    if(hero[b].detail.patch == "Nerf") powerB -= 5;

    system("cls");

    cout << hijau << bold << "+================================================+\n"
         << "|                 HASIL COMPARE                  |\n"
         << "+================================================+\n\n";

    cout << "+------------------------------------------------+\n"
         << "|              BERDASARKAN POWER                 |\n"
         << "+------------------------------------------------+\n"
         << "| Hero : " << hero[a].nama
         << string(33 - hero[a].nama.length(), ' ') << "|\n"
         << "| Power: " << powerA
         << string(33 - to_string(powerA).length(), ' ') << "|\n"
         << "+------------------------------------------------+\n"
         << "| Hero : " << hero[b].nama
         << string(33 - hero[b].nama.length(), ' ') << "|\n"
         << "| Power: " << powerB
         << string(33 - to_string(powerB).length(), ' ') << "|\n"
         << "+------------------------------------------------+\n";
    if(powerA > powerB)
        cout << "| Hero lebih kuat : " << hero[a].nama
             << string(25 - hero[a].nama.length(), ' ') << "|\n";
    else if(powerB > powerA)
        cout << "| Hero lebih kuat : " << hero[b].nama
             << string(25 - hero[b].nama.length(), ' ') << "|\n";
    else
        cout << "| Kedua hero seimbang                           |\n";
    cout << "+------------------------------------------------+\n\n";

    cout << "+------------------------------------------------+\n"
         << "|         BERDASARKAN TINGKAT KESULITAN          |\n"
         << "+------------------------------------------------+\n"
         << "| Hero      : " << hero[a].nama
         << string(28 - hero[a].nama.length(), ' ') << "|\n"
         << "| Kesulitan : " << hero[a].detail.kesulitan
         << string(28 - hero[a].detail.kesulitan.length(), ' ') << "|\n"
         << "+------------------------------------------------+\n"
         << "| Hero      : " << hero[b].nama
         << string(28 - hero[b].nama.length(), ' ') << "|\n"
         << "| Kesulitan : " << hero[b].detail.kesulitan
         << string(28 - hero[b].detail.kesulitan.length(), ' ') << "|\n"
         << "+------------------------------------------------+\n";
    auto nilai = [](const string& k){
        if(k == "Easy") return 1;
        if(k == "Medium") return 2;
        if(k == "Hard") return 3;
        return 0;
    };

    int na = nilai(hero[a].detail.kesulitan);
    int nb = nilai(hero[b].detail.kesulitan);

    if(na > nb)
        cout << "| Hero lebih sulit : " << hero[a].nama
             << string(24 - hero[a].nama.length(), ' ') << "|\n";
    else if(nb > na)
        cout << "| Hero lebih sulit : " << hero[b].nama
             << string(24 - hero[b].nama.length(), ' ') << "|\n";
    else
        cout << "| Tingkat kesulitan kedua hero sama             |\n";
    cout << "+------------------------------------------------+\n";
    cout << reset;
}

void tambahFavorit(){
    if(jumlahFavorit >= MAX){
        cout << merah << bold << "+------------------------+\n"
             << "|  Data favorit penuh!   |\n"
             << "+------------------------+\n" << reset;
        return;
    }

    if(jumlahHero == 0){
        cout << merah << bold << "+-------------------+\n"
             << "|  Belum ada hero!  |\n"
             << "+-------------------+\n" << reset;
        return;
    }

    lihatHero(hero, jumlahHero);

    cout << hijau << bold << "Pilih Hero Favorit (1-" << jumlahHero << ") : \n" << reset;

    int key = _getch();
    cout << (char)key;

    if(key == 32){
        system("cls");
        cout << kuning << bold << "+--------------+\n"
             << "|  Dibatalkan  |\n"
             << "+--------------+\n" << reset;
        return;
    }

    if(!isdigit(key)){
        system("cls");
        cout << merah << bold << "+----------------------+\n"
             << "|  Input harus angka!  |\n"
             << "+----------------------+\n" << reset;
        return;
    }

    int pilih = key - '0';

    if(pilih < 1 || pilih > jumlahFavorit){
        cout << merah << bold << "+------------------------+\n"
             << "|  Pilihan tidak valid!  |\n"
             << "+------------------------+\n" << reset;
        return;
    }

    favorit[jumlahFavorit].nama = hero[pilih - 1].nama;
    favorit[jumlahFavorit].role = hero[pilih - 1].detail.role;
    favorit[jumlahFavorit].level = hero[pilih - 1].detail.level;
    favorit[jumlahFavorit].match = rand() % 100;
    favorit[jumlahFavorit].winrate = rand() % 100;
    jumlahFavorit++;

    cout << hijau << bold << "+---------------------------------+\n"
         << "|  Favorit berhasil ditambahkan!  |\n"
         << "+---------------------------------+\n" << reset;
}

void updateRealtimeFavorit(){
    for(int i = 0; i < jumlahFavorit; i++){
        favorit[i].match += rand() % 5;
        favorit[i].winrate += (rand() % 11 - 5);
        if(favorit[i].winrate < 0)
            favorit[i].winrate = 0;
        if(favorit[i].winrate > 100)
            favorit[i].winrate = 100;
    }
}

void lihatFavorit(){
    if(jumlahFavorit == 0){
        cout << merah << bold << "+-----------------------------------------+\n"
             << "|  Belum ada hero favorit untuk dihapus!  |\n"
             << "+-----------------------------------------+\n";
        cout << kuning << bold <<"Tekan SPACE untuk kembali...\n" << reset;
        while(_getch() != 32);
        return;
    }

    while(true){
        system("cls");
        cout << kuning << bold << "+----------------------------------+\n"
             << "|            HERO FAVORIT          |\n"
             << "+----------------------------------+\n";
        for(int i = 0; i < jumlahFavorit; i++){
            cout << i + 1 << ". "
                 << favorit[i].nama
                 << " | "
                 << favorit[i].role
                 << " | Match : "
                 << favorit[i].match
                 << " | WR : "
                 << favorit[i].winrate
                 << "%\n";
        }
        cout << kuning << "Tekan SPACE untuk kembali...\n" << reset;
        for(int i = 0; i < 30; i++){
            if(_kbhit()){
                int key = _getch();
                if(key == 32){
                    return;
                }
            }
            this_thread::sleep_for(chrono::milliseconds(300)
            );
        }
        updateRealtimeFavorit();
    }
}

void hapusFavorit(){
    if(jumlahFavorit == 0){
        cout << merah << bold << "+-----------------------------------------+\n"
             << "|  Belum ada hero favorit untuk dihapus!  |\n"
             << "+-----------------------------------------+\n";
        cout << kuning << bold <<"Tekan SPACE untuk kembali...\n" << reset;
        while(_getch() != 32);
        return;
    }

    system("cls");
    cout << hijau << bold <<"+----------------------------------+\n"
         << "|        HAPUS HERO FAVORIT        |\n"
         << "+----------------------------------+\n";

    for(int i = 0; i < jumlahFavorit; i++){
        cout << i + 1 << ". " << favorit[i].nama << endl;
    }

    cout << "+----------------------------------+\n"
         << "Pilih nomor (SPACE = batal): \n"
         << "+----------------------------------+\n" << reset;

    int key = _getch();
    cout << (char)key;

    if(key == 32){
        system("cls");
        cout << kuning << bold << "+--------------+\n"
             << "|  Dibatalkan  |\n"
             << "+--------------+\n" << reset;
        return;
    }

    if(!isdigit(key)){
        system("cls");
        cout << merah << bold << "+----------------------+\n"
             << "|  Input harus angka!  |\n"
             << "+----------------------+\n" << reset;
        return;
    }

    int no = key - '0';

    if(no < 1 || no > jumlahFavorit){
        cout << merah << bold << "+------------------------+\n"
             << "|  Pilihan tidak valid!  |\n"
             << "+------------------------+\n" << reset;
        return;
    }

    for(int i = no - 1; i < jumlahFavorit - 1; i++){
        favorit[i] = favorit[i + 1];
    }

    jumlahFavorit--;

    cout << kuning << bold << "+----------------------------------+\n"
         << "|  Hero favorit berhasil dihapus!  |\n"
         << "+----------------------------------+\n" << reset;
}

void menuFav(){
    int pilihan = 1;
    int totalPilihan = 4;
    char tombol;
    bool running = true;

    do{
        system("cls");
        cout << hijau << bold << "+-------------------------------------------+\n"
             << "|              MENU FAVORIT                 |\n"
             << "+-------------------------------------------+\n"
             << "|1. Buat Hero Favorit"  << (pilihan == 1 ? " <" : "  ") << "                     |\n"
             << "|2. Lihat Hero Favorit" << (pilihan == 2 ? " <" : "  ") << "                    |\n"
             << "|3. Hapus Hero Favorit" << (pilihan == 3 ? " <" : "  ") << "                    |\n"
             << "|4. Kembali" << (pilihan == 4 ? " <" : "  ") << "                               |\n"
             << "+-------------------------------------------+\n";
        cout << kuning << bold << "Gunakan Panah Atas/Bawah, Enter untuk pilih." << reset << endl;
        tombol = getch();
        if(tombol == 72) {
            if (pilihan > 1) pilihan--;
        } else if(tombol == 80) {
            if (pilihan < totalPilihan) pilihan++;
        } else if (tombol == 13) {
            switch(pilihan){
                case 1:
                    system("cls");
                    try{
                        tambahFavorit();
                    }catch(exception &e){
                        cout << "\nError: " << e.what() << endl;
                    }
                    pause();
                    break;
                case 2:
                    system("cls");
                    lihatFavorit();
                    break;
                case 3:
                    system("cls");
                    try{
                        hapusFavorit();
                    }catch(exception &e){
                        cout << "\nError: " << e.what() << endl;
                    }
                    pause();
                    break;
                case 4:
                    system("cls");
                    pesan("Favorit", "Kembali ke Menu User");
                    running = false;
                    pause();
                    break;
            }
        }
    }while(running == true);
return;
}

void menuHero(){
    int pilihan = 1;
    int totalPilihan = 4;
    char tombol;
    bool running = true;

    do{
        system("cls");
        cout << hijau << bold <<"+----------------------------------------------+\n"
             << "|                 MENU HERO                    |\n"
             << "+----------------------------------------------+\n"
             << "|1. Lihat Hero" << (pilihan == 1 ? " <" : "  ") << "                               |\n"
             << "|2. Fitur Sorting" << (pilihan == 2 ? " <" : "  ") << "                            |\n"
             << "|3. Fitur Searching" << (pilihan == 3 ? " <" : "  ") << "                          |\n"
             << "|4. Kembali" << (pilihan == 4 ? " <" : "  ") << "                                  |\n"
             << "+----------------------------------------------+\n";
        cout << kuning << bold << "Gunakan Panah Atas/Bawah, Enter untuk pilih." << reset << endl;
        tombol = getch();
        if(tombol == 72) {
            if (pilihan > 1) pilihan--;
        } else if(tombol == 80) {
            if (pilihan < totalPilihan) pilihan++;
         } else if(tombol == 13) {
             switch(pilihan){
                case 1:
                    system("cls");
                    lihatHero(hero, jumlahHero);
                    pause();
                    break;
                case 2:
                    system("cls");
                    menuSorting();
                    break;
                case 3:
                    system("cls");
                    menuSearching();
                    break;
                case 4:
                    system("cls");
                    pesan("Menu Hero", "Kembali ke Menu User");
                    pause();
                    running = false;
                    break;
             }
        }
    }while(running == true);
return;
}

void menuCreate(){
    int pilihan = 1;
    int totalPilihan = 5;
    char tombol;
    bool running = true;

    do{
        system("cls");
        cout << hijau << bold << "+-------------------------------------------+\n"
             << "|               MENU CREATE                 |\n"
             << "+-------------------------------------------+\n"
             << "|1. Tambah Hero" << (pilihan == 1 ? " <" : "  ") << "                            |\n"
             << "|2. Tambah Spell" << (pilihan == 2 ? " <" : "  ") << "                           |\n"
             << "|3. Tambah Emblem" << (pilihan == 3 ? " <" : "  ") << "                          |\n"
             << "|4. Tambah Map" << (pilihan == 4 ? " <" : "  ") << "                             |\n"
             << "|5. Kembali" << (pilihan == 5 ? " <" : "  ") << "                                |\n"
             << "+-------------------------------------------+\n";
        cout << kuning << bold << "gunakan Panah Atas/Bawah, Enter untuk pilih." << reset << endl;
        tombol = getch();
        if(tombol == 72) {
            if(pilihan > 1) pilihan--;
        } else if(tombol == 80) {
            if(pilihan < totalPilihan) pilihan++;
        } else if(tombol == 13){
            
            switch(pilihan){
                case 1:
                    system("cls");
                    try{
                        tambahHero(hero, &jumlahHero);
                        pesan("Create", "Hero berhasil ditambahkan");
                    }catch(exception &e){
                        cout << "\nError: " << e.what() << endl;
                    }
                    pause();
                    break;
                case 2:
                    system("cls");
                    tambahSpell();
                    pause();
                    break;
                case 3:
                    system("cls");
                    tambahEmblem();
                    pause();
                    break;
                case 4:
                    system("cls");
                    tambahMap();
                    pause();
                    break;
                case 5:
                    system("cls");
                    pesan("Create");
                    pause();
                    running = false;
                    break;
                }
        }
    }while(running == true);
return;
}

void menuRead(){
    int pilihan = 1;
    int totalPilihan = 5;
    char tombol;
    bool running = true;

    do{
        system("cls");
        cout << hijau << bold << "+------------------------------+\n"
             << "|            MENU READ         |\n"
             << "+------------------------------+\n"
             << "|1. Read Hero" << (pilihan == 1 ? " <" : "  ") << "                |\n"
             << "|2. Read Spell" << (pilihan == 2 ? " <" : "  ") << "               |\n"
             << "|3. Read Emblem" << (pilihan == 3 ? " <" : "  ") << "              |\n"
             << "|4. Read Map" << (pilihan == 4 ? " <" : "  ") << "                 |\n"
             << "|5. Kembali" << (pilihan == 5 ? " <" : "  ") << "                  |\n"
             << "+------------------------------+\n";
        cout << kuning << bold << "Gunakan Panah Atas/Bawah, Enter untuk pilih." << reset << endl;
        tombol = getch();
        if(tombol == 72) {
            if(pilihan > 1) pilihan--;
        } else if(tombol == 80) {
             if(pilihan < totalPilihan) pilihan++;
        } else if(tombol == 13){
            switch(pilihan){
                case 1:
                    system("cls");
                    menuHero();
                    break;
                case 2:
                    system("cls");
                    lihatSpell();
                    pause();
                    break;
                case 3:
                    system("cls");
                    lihatEmblem();
                    pause();
                    break;
                case 4:
                    system("cls");
                    lihatMap();
                    pause();
                    break;
                case 5:
                    system("cls");
                    pesan("Admin");
                    running = false;
                    pause();
                    break;
            }
        }
    }while(running == true);
return;
}

void menuAdmin(){
    int pilihan = 1;
    int totalPilihan = 5;
    char tombol;
    bool running = true;

    do{
        system("cls");
        cout << hijau << bold << "+-------------------------------------------+\n"
             << "|                   MENU ADMIN              |\n"
             << "+-------------------------------------------+\n"
             << "|1. Create Data" << (pilihan == 1 ? " <" : "  ") << "                           |\n"
             << "|2. Read Data" << (pilihan == 2 ? " <" : "  ") << "                             |\n"
             << "|3. Update Hero" << (pilihan == 3 ? " <" : "  ") << "                           |\n"
             << "|4. Delete Hero" << (pilihan == 4 ? " <" : "  ") << "                           |\n"
             << "|5. Keluar" << (pilihan == 5 ? " <" : "  ") << "                                |\n"
             << "+-------------------------------------------+\n";
        cout << kuning << bold << "Gunakan Panah Atas/Bawah, Enter untuk pilih." << reset << endl;
        tombol = _getch();
        if(tombol == 72){
            if(pilihan > 1) pilihan--;
        } else if(tombol == 80){
            if(pilihan < totalPilihan) pilihan++;
        } else if(tombol == 13){
            switch(pilihan){
                case 1:
                    menuCreate();
                    break;
                case 2:
                    menuRead();
                    break;
                case 3:
                system("cls");
                try{
                    updateHero(hero, jumlahHero);
                }catch(exception &e){
                    cout << "\nError: " << e.what() << endl;
                }
                pause();
                break;
            case 4:
                system("cls");
                if(hapusHero(hero, &jumlahHero)){
                    pesan("Admin", "Data berhasil dihapus");
                }
                pause();
                break;
            case 5:
                system("cls");
                pesan("Admin");
                running = false;
                pause();
                break;
            }
        }
    }while(running == true);
return;
}

void menuUser(){
    int pilihan = 1;
    int totalPilihan = 6;
    char tombol;
    bool running = true;

    do{
        system("cls");
        cout << hijau << bold << "+-------------------------------------------+\n"
             << "|                  MENU USER                |\n"
             << "+-------------------------------------------+\n"
             << "|1. Lihat Hero" << (pilihan == 1 ? " <" : "  ") << "                            |\n"
             << "|2. Hero Meta" << (pilihan == 2 ? " <" : "  ") << "                             |\n"
             << "|3. Cari Berdasarkan Role" << (pilihan == 3 ? " <" : "  ") << "                 |\n"
             << "|4. Compare Hero" << (pilihan == 4 ? " <" : "  ") << "                          |\n"
             << "|5. Hero Favorit" << (pilihan == 5 ? " <" : "  ") << "                          |\n"
             << "|6. Keluar" << (pilihan == 6 ? " <" : "  ") << "                                |\n"
             << "+-------------------------------------------+\n";
        cout << kuning << bold << "Gunakan Panah Atas/Bawah, Enter untuk pilih."<< reset << endl;
        tombol = _getch();
        if(tombol == 72){
            if(pilihan > 1) pilihan--;
        } else if(tombol == 80){
            if(pilihan < totalPilihan) pilihan++;
        } else if(tombol == 13){
            switch(pilihan){
                case 1:
                    system("cls");
                    lihatHero(hero, jumlahHero);
                    pause();
                    break;
                case 2:
                    system("cls");
                    heroMeta();
                    pause();
                    break;
                case 3:
                    system("cls");
                    cariRole();
                    pause();
                    break;
                case 4:
                    system("cls");
                    try{
                        compareHero();
                    }catch(exception &e){
                        cout << "\nError: " << e.what() << endl;
                    }
                    pause();
                    break;
                case 5:
                    system("cls");
                    menuFav();
                    break;
                case 6:
                    system("cls");
                    pesan("User");
                    pause();
                    running = false;
                    break;
            }
        }
    }while(running == true);
return;
}

bool validUsername(const string& username){
    if(username.empty() || username.length() > 20) return false;
    return isAllAlpha(username);
}
bool validPassword(const string& password){
    if(password.empty() || password.length() > 10) return false;
    return isAllDigits(password);
}

void registrasiUser(){
    User baru;
    bool sudahAda = false;

    system("cls");
    cout << hijau << bold << "+----------------------------------+\n";
    cout <<          "|         REGISTRASI USER          |\n";
    cout <<          "+----------------------------------+\n";

    cout << "Username : "; getline(cin, baru.username);
    if(!validUsername(baru.username)){
        system("cls");
        cout << merah << bold<< "+------------------------------------------------------+\n"
             <<          "|  Username hanya boleh huruf & maksimal 20 karakter!  |\n"
             <<          "+------------------------------------------------------+\n" << reset;  
        pause();
        return;
    }
    for(int i = 0; i < jumlahUser; i++){
        if(userList[i].username == baru.username){
            sudahAda = true;
            break;
        }
    }
    if(sudahAda){
        system("cls");
        cout << merah << bold << "+-------------------------------------------+\n"
             <<          "|         Username sudah digunakan!         |\n"
             <<          "+-------------------------------------------+\n" << reset;
        pause();
        return;
    }

    cout << "Password : "; getline(cin, baru.password);
    cout << "+----------------------------------+\n" << reset;
    if(!validPassword(baru.password)){
        system("cls");
        cout << merah << bold << "+-------------------------------------------------------+\n"
             <<          "|    Password hanya boleh angka & maksimal 10 digit!    |\n"
             <<          "+-------------------------------------------------------+\n" << reset;
        pause();
        return;
    }
    if(jumlahUser >= MAX){
        system("cls");
        cout << merah << bold << "+----------------------------------+\n"
             <<          "|         Data user penuh!         |\n"
             <<          "+----------------------------------+\n" << reset;
        pause();
        return;
    }
    userList[jumlahUser++] = baru;
    system("cls");
    cout << hijau << bold << "+----------------------------+\n"
         <<          "|    Registrasi berhasil!    |\n"
         <<          "+----------------------------+\n" << reset;
    pause();
    return;
}

bool loginUser(){
    string username, password;


    system("cls");
    cout << hijau << bold << "+----------------------------------+\n";
    cout <<          "|            LOGIN USER            |\n";
    cout <<          "+----------------------------------+\n";

    cout << "Username : "; getline(cin, username);
    if(username.empty()){
        system("cls");
        cout << merah << bold << "+----------------------------------+\n"
                << "|   Username tidak boleh kosong!   |\n"
                << "+----------------------------------+\n" << reset;
        pause();
    }

    cout << "Password : "; getline(cin, password);
    cout << "+----------------------------------+\n" << reset;  
    if(password.empty()){
        system("cls");
        cout << merah << bold << "+----------------------------------+\n"
                << "|   Password tidak boleh kosong!   |\n"
                << "+----------------------------------+\n" << reset;
        pause();
    }

    bool berhasil = false;
    for(int i = 0; i < jumlahUser; i++){
        if(userList[i].username == username && userList[i].password == password){
            berhasil = true;
            break;
        }
    }

    if(berhasil){
        system("cls");
        cout << hijau << bold << "+---------------------------+\n"
                              << "|       Login berhasil!     |\n"
                              << "+---------------------------+\n" << reset;
        pause();
        return true;
    }
    system("cls");
    cout << merah << bold << "+-------------------------------------+\n"
                          << "|    Username atau Password salah!    |\n"
                          << "+-------------------------------------+\n" << reset;
    pause();

    return false;
}

int main(){
    srand((unsigned)time(0));
    Login admin = {"admin","01123"};

    int pilihan = 1;
    int totalPilihan = 4;
    char tombol;
    bool running = true;

    do{
        system("cls");
        cout << hijau << bold << "+--------------------------------------------------+\n"
             << "|  SISTEM MANAJEMEN HERO META PATCH UPDATE MOBILE  |\n"
             << "|            MOBILE LEGENDS : BANG BANG            |\n"
             << "+--------------------------------------------------+\n"
             << "|1. Admin" << (pilihan == 1 ? " <" : "  ") << "                                        |\n"
             << "|2. Login User" << (pilihan == 2 ? " <" : "  ") << "                                   |\n"
             << "|3. Registrasi User" << (pilihan == 3 ? " <" : "  ") << "                              |\n"
             << "|4. Keluar" << (pilihan == 4 ? " <" : "  ") << "                                       |\n"
             << "+--------------------------------------------------+\n";
        cout << kuning << bold << "Gunakan Panah Atas/Bawah, Enter untuk pilih." << reset << endl;
        tombol = _getch();
        if (tombol == 72) {
            if (pilihan > 1) pilihan--;
        } else if (tombol == 80) {
            if (pilihan < totalPilihan) pilihan++;
        } else if (tombol == 13) {
            switch(pilihan){
                case 1:
                    if(loginAdmin(admin)){
                        menuAdmin();
                    }
                    break;
                case 2:
                    if(loginUser()){
                        menuUser();
                    }
                    break;
                case 3:
                    registrasiUser();
                    break;
                case 4:
                    system("cls");
                    cout << kuning << bold << "+----------------------------------------------+\n"
                         << "|  Terima kasih telah menggunakan sistem ini   |\n"
                         << "+----------------------------------------------+" << reset << endl;
                        running = false;
                        break;
                }
            }
        }while(running == true);
return 0;
}