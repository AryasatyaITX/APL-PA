#include <iostream>
#include <iomanip>
#include <limits>
#include <stdexcept>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <atomic>
#include <cctype>
#include <conio.h>
using namespace std;

#define MAX 100

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
    cout << msg << endl;
    return msg;
}
string pesan(string nama, string status) {
    string msg = " Anda Keluar Dari Menu : " + nama + " , " + status;
    cout << msg << endl;
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
    system("pause");
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
        cout << "\nInput tidak boleh kosong!\n";
        pause();
        return -1;
    }
    if(!isAllDigits(input)){
        cout << "\nInput harus angka!\n";
        pause();
        return -1;
    }
    try{
        return stoi(input);
    }catch(...){
        cout << "\nInput tidak valid!\n";
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
    cout << "\n========================================================================================================\n";
    cout << "|" << setw(3)  << "ID"
         << "|" << setw(20) << "Hero"
         << "|" << setw(15) << "Role"
         << "|" << setw(15) << "Kesulitan"
         << "|" << setw(8)  << "Level"
         << "|" << setw(12) << "Patch"
         << "|" << setw(10) << "Meta"
         << " |\n";
    cout << "========================================================================================================\n";
}

bool loginAdmin(Login admin){
    string username, password;
    int kesempatan = 0;

    while(kesempatan < 3){
        system("cls");
        cout << "====================================\n";
        cout << "|           LOGIN ADMIN           |\n";
        cout << "====================================\n";

        cout << "Username : ";
        getline(cin, username);

        if(username.empty()){
            cout << "\nUsername tidak boleh kosong!\n";
            kesempatan++;
            pause();
            continue;
        }
        if(!isAllAlpha(username)){
            cout << "\nUsername hanya boleh huruf!\n";
            kesempatan++;
            pause();
            continue;
        }

        cout << "Password : ";
        getline(cin, password);

        if(password.empty()){
            cout << "\nPassword tidak boleh kosong!\n";
            kesempatan++;
            pause();
            continue;
        }
        if(!isAllDigits(password)){
            cout << "\nPassword hanya boleh angka!\n";
            kesempatan++;
            pause();
            continue;
        }

        if(username == admin.username && password == admin.password){
            cout << "\nLogin berhasil!\n";
            pause();
            return true;
        }

        kesempatan++;
        cout << "\nUsername atau Password salah!\n";
        cout << "Percobaan ke-" << kesempatan << " dari 3\n";
        pause();
    }

    cout << "\nLogin gagal 3 kali!\n";
    pause();
    return false;
}

void lihatHero(Hero *heroArr, int jml){
    if(jml == 0){
        cout << "Belum ada data hero\n";
        return;
    }
    headerHero();
    for(int i = 0; i < jml; i++){
        cout << "|"
             << setw(3)  << heroArr[i].id
             << "|" << setw(20) << heroArr[i].nama
             << "|" << setw(15) << heroArr[i].detail.role
             << "|" << setw(15) << heroArr[i].detail.kesulitan
             << "|" << setw(8)  << heroArr[i].detail.level
             << "|" << setw(12) << heroArr[i].detail.patch
             << "|" << setw(10) << (heroArr[i].meta ? "Yes" : "No")
             << " |\n";
    }
    cout << "========================================================================================================\n";
}

void tambahHero(Hero heroArr[], int *jml){
    if(*jml >= MAX){
        throw runtime_error("Data hero penuh!");
    }

    Hero heroBaru;
    heroBaru.id = *jml + 1;

    cout << "Nama Hero        : ";
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

    cout << "\nHero berhasil ditambahkan!\n";
}


void updateHero(Hero *heroArr, int jml){
    if(jml == 0){
        throw runtime_error("Belum ada data hero.");
    }

    lihatHero(heroArr, jml);

    cout << "\nMasukkan ID Hero : ";
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

    cout << "\n1. Nama\n";
    cout << "2. Role\n";
    cout << "3. Kesulitan\n";
    cout << "4. Level\n";
    cout << "5. Patch\n";
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

    cout << "\nData berhasil diupdate!\n";
}

int hapusHero(Hero heroArr[], int *jml){
    if(*jml == 0){
        cout << "Belum ada data hero.\n";
        return 0;
    }

    lihatHero(heroArr, *jml);

    cout << "\nMasukkan ID Hero : ";
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
        cout << "ID tidak ditemukan!\n";
        return 0;
    }

    for(int i = index; i < *jml - 1; i++){
        heroArr[i] = heroArr[i + 1];
        heroArr[i].id = i + 1;
    }
    (*jml)--;

    cout << "\nData berhasil dihapus!\n";
    return 1;
}

void lihatSpell(){
    cout << "===========================\n";
    cout << "|         DATA SPELL      |\n";
    cout << "===========================\n";
    for(int i = 0; i < jumlahSpell; i++){
        cout << spell[i].id << ". " << spell[i].nama << endl;
    }
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
        cout << "\nNama spell tidak boleh kosong!\n";
        return;
    }

    jumlahSpell++;
    cout << "Spell berhasil ditambahkan!\n";
}

void lihatEmblem(){
    cout << "===========================\n";
    cout << "|       DATA EMBLEM       |\n";
    cout << "===========================\n";
    for(int i = 0; i < jumlahEmblem; i++){
        cout << emblem[i].id << ". " << emblem[i].nama << endl;
    }
}

void tambahEmblem(){
    if(jumlahEmblem >= MAX){
        cout << "Data emblem penuh!\n";
        return;
    }
    emblem[jumlahEmblem].id = jumlahEmblem + 1;
    cout << "Nama Emblem : ";
    getline(cin, emblem[jumlahEmblem].nama);

    if(emblem[jumlahEmblem].nama.empty()){
        cout << "\nNama emblem tidak boleh kosong!\n";
        return;
    }

    jumlahEmblem++;
    cout << "Emblem berhasil ditambahkan!\n";
}

void lihatMap(){
    cout << "===========================\n";
    cout << "|          DATA MAP       |\n";
    cout << "===========================\n";
    for(int i = 0; i < jumlahMap; i++){
        cout << mapGame[i].id << ". " << mapGame[i].nama << endl;
    }
}

void tambahMap(){
    if(jumlahMap >= MAX){
        cout << "Data map penuh!\n";
        return;
    }
    mapGame[jumlahMap].id = jumlahMap + 1;
    cout << "Nama Map : ";
    getline(cin, mapGame[jumlahMap].nama);

    if(mapGame[jumlahMap].nama.empty()){
        cout << "\nNama map tidak boleh kosong!\n";
        return;
    }

    jumlahMap++;
    cout << "Map berhasil ditambahkan!\n";
}

void sortingNama(){
    for(int i = 0; i < jumlahHero - 1; i++){
        for(int j = 0; j < jumlahHero - i - 1; j++){
            if(hero[j].nama > hero[j + 1].nama){
                swap(hero[j], hero[j + 1]);
            }
        }
    }
    cout << "\nSorting nama berhasil!\n";
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
    cout << "\nSorting level berhasil!\n";
}

void menuSorting(){
    int pilih;
    do{
        system("cls");
        cout << "=============================================\n";
        cout << "|                MENU SORTING               |\n";
        cout << "=============================================\n";
        cout << "|1. Sorting Nama Hero                       |\n";
        cout << "|2. Sorting Level Hero                      |\n";
        cout << "|3. Kembali                                 |\n";
        cout << "=============================================\n";
        cout << "Pilih : ";

        pilih = inputMenu();
        if(pilih == -1) continue;

        switch(pilih){
            case 1:
                sortingNama();
                lihatHero(hero, jumlahHero);
                pause();
                break;
            case 2:
                sortingLevel();
                lihatHero(hero, jumlahHero);
                pause();
                break;
            case 3:
                break;
            default:
                cout << "Pilihan tidak valid!\n";
                pause();
        }
    }while(pilih != 3);
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
    int pilih;
    do{
        system("cls");
        cout << "====================================\n";
        cout << "|          PILIH ROLE             |\n";
        cout << "====================================\n";
        cout << "|1. Mage                          |\n";
        cout << "|2. Assassin                      |\n";
        cout << "|3. Tank                          |\n";
        cout << "|4. Support                       |\n";
        cout << "|5. Marksman                      |\n";
        cout << "|6. Kembali                       |\n";
        cout << "====================================\n";
        cout << "Pilih : ";
        pilih = inputMenu();
        if(pilih == -1)
            continue;
        string roleCari;
        switch(pilih){
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
                return;

            default:
                cout << "\nPilihan tidak valid!\n";
                pause();
                continue;
        }

        bool ditemukan = false;
        system("cls");
        cout << "==============================================================\n";
        cout << "|                HASIL SEARCH ROLE                          |\n";
        cout << "==============================================================\n";
        cout << "|"
             << setw(3)  << "ID"
             << "|" << setw(20) << "Hero"
             << "|" << setw(15) << "Role"
             << "|" << setw(10) << "Level"
             << "|" << setw(10) << "Patch"
             << " |\n";
        cout << "==============================================================\n";
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
        cout << "==============================================================\n";
        if(!ditemukan){
            cout << "\nHero dengan role "
                 << roleCari
                 << " tidak ditemukan.\n";
        }
        pause();
    }while(true);
}

void menuSearching(){
    int pilih;
    do{
        system("cls");
        cout << "=============================================\n";
        cout << "|               MENU SEARCHING              |\n";
        cout << "=============================================\n";
        cout << "|1. Search Hero Nama                        |\n";
        cout << "|2. Search Hero Role                        |\n";
        cout << "|3. Kembali                                 |\n";
        cout << "=============================================\n";
        cout << "Pilih : ";

        pilih = inputMenu();
        if(pilih == -1) continue;

        switch(pilih){
            case 1:{
                string cari;
                cout << "Masukkan nama hero : ";
                getline(cin, cari);

                if(cari.empty()){
                    cout << "\nNama hero tidak boleh kosong!\n";
                    pause();
                    break;
                }

                int hasil = binarySearchNama(cari);
                if(hasil != -1){
                    cout << "\nHero ditemukan : " << hero[hasil].nama << endl;
                } else{
                    cout << "\nHero tidak ditemukan\n";
                }
                pause();
                break;
            }
            case 2:
                cariRole();
                pause();
                break;
            case 3:
                break;
            default:
                cout << "Pilihan tidak valid!\n";
                pause();
        }
    }while(pilih != 3);
}

void heroMeta(){
    cout << "=============================\n";
    cout << "|           HERO META       |\n";
    cout << "=============================\n";
    for(int i = 0; i < jumlahHero; i++){
        if(hero[i].meta){
            cout << hero[i].nama << " | " << hero[i].detail.patch << endl;
        }
    }
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
    cout << "=============================\n";
    cout << "|           HASIL           |\n";
    cout << "=============================\n";
    cout << "=== BERDASARKAN HERO POWER ===\n";
    cout << hero[a].nama << " Power : " << powerA << endl;
    cout << hero[b].nama << " Power : " << powerB << endl;

    if(powerA > powerB) cout << "Hero lebih kuat : " << hero[a].nama << endl;
    else if(powerB > powerA) cout << "Hero lebih kuat : " << hero[b].nama << endl;
    else cout << "Kedua hero seimbang\n";

    cout << "\n=== BERDASARKAN TINGKAT KESULITAN ===\n";
    cout << hero[a].nama << ", Kesulitan : " << hero[a].detail.kesulitan << endl;
    cout << hero[b].nama << ", Kesulitan : " << hero[b].detail.kesulitan << endl;

    auto nilai = [](const string& k){
        if(k == "Easy") return 1;
        if(k == "Medium") return 2;
        if(k == "Hard") return 3;
        return 0; 
    };

    int na = nilai(hero[a].detail.kesulitan);
    int nb = nilai(hero[b].detail.kesulitan);

    if(na > nb) cout << "Hero lebih sulit : " << hero[a].nama << endl;
    else if(nb > na) cout << "Hero lebih sulit : " << hero[b].nama << endl;
    else cout << "Kedua hero memiliki tingkat kesulitan yang sama\n";
}

void tambahFavorit(){
    if(jumlahFavorit >= MAX){
        cout << "\nData favorit penuh!\n";
        return;
    }

    if(jumlahHero == 0){
        cout << "\nBelum ada hero!\n";
        return;
    }

    lihatHero(hero, jumlahHero);

    cout << "\nPilih Hero Favorit (1-" << jumlahHero << ") : ";

    int key = _getch();
    cout << (char)key;

    if(key == 32){
        cout << "\nDibatalkan.\n";
        return;
    }

    if(!isdigit(key)){
        cout << "\n\nInput harus angka!\n";
        return;
    }

    int pilih = key - '0';

    if(pilih < 1 || pilih > jumlahHero){
        cout << "\n\nPilihan tidak valid!\n";
        return;
    }

    favorit[jumlahFavorit].nama = hero[pilih - 1].nama;
    favorit[jumlahFavorit].role = hero[pilih - 1].detail.role;
    favorit[jumlahFavorit].level = hero[pilih - 1].detail.level;
    favorit[jumlahFavorit].match = rand() % 100;
    favorit[jumlahFavorit].winrate = rand() % 100;
    jumlahFavorit++;

    cout << "\n\nFavorit berhasil ditambahkan!\n";
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
        cout << "\nBelum ada hero favorit!\n";
        cout << "Tekan SPACE untuk kembali...\n";
        while(_getch() != 32);
        return;
    }

    atomic<bool> keluar(false);

    thread t([&](){
        while(true){
            int key = _getch();
            if(key == 32){
                keluar = true;
                break;
            }
        }
    });

    while(!keluar){
        system("cls");
        cout << "====================================\n";
        cout << "|            HERO FAVORIT          |\n";
        cout << "====================================\n";

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

        cout << "\nTEKAN SPACE UNTUK KEMBALI\n";

        for(int i = 0; i < 100 && !keluar; i++){
            this_thread::sleep_for(chrono::milliseconds(100));
        }

        if(!keluar){
            updateRealtimeFavorit();
        }
    }

    if(t.joinable()) t.join();
}

void hapusFavorit(){
    if(jumlahFavorit == 0){
        cout << "\nBelum ada hero favorit untuk dihapus!\n";
        cout << "Tekan SPACE untuk kembali...\n";
        while(_getch() != 32);
        return;
    }

    system("cls");

    cout << "====================================\n";
    cout << "|        HAPUS HERO FAVORIT       |\n";
    cout << "====================================\n";

    for(int i = 0; i < jumlahFavorit; i++){
        cout << i + 1 << ". " << favorit[i].nama << endl;
    }

    cout << "\nPilih nomor (SPACE = batal): ";

    int key = _getch();
    cout << (char)key;

    if(key == 32){
        cout << "\n\nDibatalkan.\n";
        return;
    }

    if(!isdigit(key)){
        cout << "\n\nInput harus angka!\n";
        return;
    }

    int no = key - '0';

    if(no < 1 || no > jumlahFavorit){
        cout << "\n\nPilihan tidak valid!\n";
        return;
    }

    for(int i = no - 1; i < jumlahFavorit - 1; i++){
        favorit[i] = favorit[i + 1];
    }

    jumlahFavorit--;

    cout << "\n\nHero favorit berhasil dihapus!\n";
}

void menuFav(){
    int pilih;
    do{
        system("cls");
        cout << "=============================================\n";
        cout << "|              MENU FAVORIT                 |\n";
        cout << "=============================================\n";
        cout << "|1. Buat Hero Favorit                       |\n";
        cout << "|2. Lihat Hero Favorit                      |\n";
        cout << "|3. Hapus Hero Favorit                      |\n";
        cout << "|4. Kembali                                 |\n";
        cout << "=============================================\n";
        cout << "Pilih : ";

        pilih = inputMenu();
        if(pilih == -1) continue;

        switch(pilih){
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
                pause();
                break;
            default:
                cout << "Pilihan tidak valid!\n";
                pause();
        }
    }while(pilih != 4);
}

void menuHero(){
    int pilih;
    do{
        system("cls");
        cout << "================================================\n";
        cout << "|                 MENU HERO                    |\n";
        cout << "================================================\n";
        cout << "|1. Lihat Hero                                 |\n";
        cout << "|2. Fitur Sorting                              |\n";
        cout << "|3. Fitur Searching                            |\n";
        cout << "|4. Kembali                                    |\n";
        cout << "================================================\n";
        cout << "Pilih : ";

        pilih = inputMenu();
        if(pilih == -1) continue;

        switch(pilih){
            case 1:
                lihatHero(hero, jumlahHero);
                pause();
                break;
            case 2:
                menuSorting();
                break;
            case 3:
                menuSearching();
                break;
            case 4:
                break;
            default:
                cout << "Pilihan tidak valid!\n";
                pause();
        }
    }while(pilih != 4);
}

void menuCreate(){
    int pilih;
    do{
        system("cls");
        cout << "=============================================\n";
        cout << "|               MENU CREATE                 |\n";
        cout << "=============================================\n";
        cout << "|1. Tambah Hero                             |\n";
        cout << "|2. Tambah Spell                            |\n";
        cout << "|3. Tambah Emblem                           |\n";
        cout << "|4. Tambah Map                              |\n";
        cout << "|5. Kembali                                 |\n";
        cout << "=============================================\n";
        cout << "Pilih : ";

        pilih = inputMenu();
        if(pilih == -1) continue;

        switch(pilih){
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
                pesan("Create");
                pause();
                break;
            default:
                cout << "Pilihan tidak valid!\n";
                pause();
        }
    }while(pilih != 5);
}

void menuRead(){
    int pilih;
    do{
        system("cls");
        cout << "================================\n";
        cout << "|            MENU READ         |\n";
        cout << "================================\n";
        cout << "|1. Read Hero                  |\n";
        cout << "|2. Read Spell                 |\n";
        cout << "|3. Read Emblem                |\n";
        cout << "|4. Read Map                   |\n";
        cout << "|5. Kembali                    |\n";
        cout << "================================\n";
        cout << "Pilih : ";

        pilih = inputMenu();
        if(pilih == -1) continue;

        switch(pilih){
            case 1:
                menuHero();
                break;
            case 2:
                lihatSpell();
                pause();
                break;
            case 3:
                lihatEmblem();
                pause();
                break;
            case 4:
                lihatMap();
                pause();
                break;
            case 5:
                break;
            default:
                cout << "Pilihan tidak valid!\n";
                pause();
        }
    }while(pilih != 5);
}

void menuAdmin(){
    int pilih;
    do{
        system("cls");
        cout << "=============================================\n";
        cout << "|                   MENU ADMIN              |\n";
        cout << "=============================================\n";
        cout << "|1. Create Data                             |\n";
        cout << "|2. Read Data                               |\n";
        cout << "|3. Update Hero                             |\n";
        cout << "|4. Delete Hero                             |\n";
        cout << "|5. Keluar                                  |\n";
        cout << "=============================================\n";
        cout << "Pilih : ";

        pilih = inputMenu();
        if(pilih == -1) continue;

        switch(pilih){
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
                pesan("Admin");
                pause();
                break;
            default:
                cout << "Pilihan tidak tersedia!\n";
                pause();
        }
    }while(pilih != 5);
}

void menuUser(){
    int pilih;
    do{
        system("cls");
        cout << "=============================================\n";
        cout << "|                  MENU USER                |\n";
        cout << "=============================================\n";
        cout << "|1. Lihat Hero                              |\n";
        cout << "|2. Hero Meta                               |\n";
        cout << "|3. Cari Berdasarkan Role                   |\n";
        cout << "|4. Compare Hero                            |\n";
        cout << "|5. Hero Favorit                            |\n";
        cout << "|6. Keluar                                  |\n";
        cout << "=============================================\n";
        cout << "Pilih : ";

        pilih = inputMenu();
        if(pilih == -1) continue;

        switch(pilih){
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
                break;
            default:
                cout << "Pilihan tidak valid!\n";
                pause();
        }
    }while(pilih != 6);
}

struct User{
    string username;
    string password;
};
User userList[MAX];
int jumlahUser = 0;

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
    int percobaan = 0;

    while(percobaan < 3){
        system("cls");
        cout << "====================================\n";
        cout << "|         REGISTRASI USER          |\n";
        cout << "====================================\n";

        cout << "Username : ";
        getline(cin, baru.username);

        if(!validUsername(baru.username)){
            cout << "\nUsername hanya boleh huruf & maksimal 20 karakter!\n";
            percobaan++;
            pause();
            continue;
        }

        bool sudahAda = false;
        for(int i = 0; i < jumlahUser; i++){
            if(userList[i].username == baru.username){
                sudahAda = true;
                break;
            }
        }
        if(sudahAda){
            cout << "\nUsername sudah digunakan!\n";
            percobaan++;
            pause();
            continue;
        }

        cout << "Password : ";
        getline(cin, baru.password);

        if(!validPassword(baru.password)){
            cout << "\nPassword hanya boleh angka & maksimal 10 digit!\n";
            percobaan++;
            pause();
            continue;
        }

        if(jumlahUser >= MAX){
            cout << "\nData user penuh!\n";
            pause();
            return;
        }

        userList[jumlahUser++] = baru;
        cout << "\nRegistrasi berhasil!\n";
        pause();
        return;
    }

    cout << "\nRegistrasi gagal 3 kali!\n";
    pause();
}

bool loginUser(){
    string username, password;
    int kesempatan = 0;

    while(kesempatan < 3){
        system("cls");
        cout << "====================================\n";
        cout << "|            LOGIN USER            |\n";
        cout << "====================================\n";

        cout << "Username : ";
        getline(cin, username);

        if(username.empty()){
            cout << "\nUsername tidak boleh kosong!\n";
            kesempatan++;
            pause();
            continue;
        }

        cout << "Password : ";
        getline(cin, password);

        if(password.empty()){
            cout << "\nPassword tidak boleh kosong!\n";
            kesempatan++;
            pause();
            continue;
        }

        bool berhasil = false;
        for(int i = 0; i < jumlahUser; i++){
            if(userList[i].username == username && userList[i].password == password){
                berhasil = true;
                break;
            }
        }

        if(berhasil){
            cout << "\nLogin berhasil!\n";
            pause();
            return true;
        }

        kesempatan++;
        cout << "\nUsername atau Password salah! (" << kesempatan << "/3)\n";
        pause();
    }

    cout << "\nGagal login 3 kali!\n";
    pause();
    return false;
}

int main(){
    srand((unsigned)time(0));
    Login admin = {"admin","01123"};

    int pilih;
    bool running = true;

    do{
        system("cls");
        cout << "====================================================\n";
        cout << "|  SISTEM MANAJEMEN HERO META PATCH UPDATE MOBILE  |\n";
        cout << "|            MOBILE LEGENDS : BANG BANG            |\n";
        cout << "====================================================\n";
        cout << "|1. Admin                                          |\n";
        cout << "|2. Login User                                     |\n";
        cout << "|3. Registrasi User                                |\n";
        cout << "|4. Keluar                                         |\n";
        cout << "====================================================\n";
        cout << "Pilih : ";

        pilih = inputMenu();
        if(pilih == -1) continue;

        switch(pilih){
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
                cout << "Terima kasih telah menggunakan sistem ini.\n";
                running = false;
                break;
            default:
                cout << "\nPilihan tidak valid!\n";
                pause();
        }
    }while(running);

    return 0;
}