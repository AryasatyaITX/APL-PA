#include <iostream>
#include <conio.h>
using namespace std;

// Note pengingat
// - kasih warna pesan untuk keluar

    string reset = "\033[0m";
    string bold = "\033[1m";
    string merah = "\033[31m";
    string hijau = "\033[32m";
    string kuning = "\033[33m";
    
int main() {
    int pilihan = 1;
    int totalPilihan = 5;
    char tombol;
    bool running = true;

    int pilih;
    do{
        system("cls");
        cout << hijau << bold << "+------------------------------+\n"
             << "|            MENU READ         |\n"
             << "+------------------------------+\n"
             << "|1. Read Hero" << (pilih == 1 ? " <" : "  ") << "                            |\n"
             << "|2. Read Spell" << (pilih == 2 ? " <" : "  ") << "                           |\n"
             << "|3. Read Emblem" << (pilih == 3 ? " <" : "  ") << "                          |\n"
             << "|4. Read Map" << (pilih == 4 ? " <" : "  ") << "                             |\n"
             << "|5. Kembali" << (pilih == 5 ? " <" : "  ") << "                              |\n"
             << "+------------------------------+\n";
        cout << kuning << "Gunakan Panah Atas/Bawah, Enter untuk pilih." << reset << endl;
        tombol = getch();
        if(tombol == 72) {
            if(pilih > 1) pilih--;
        } else if(tombol == 80) {
             if(pilih < totalPilihan) pilih++;
        } else if(tombol == 13){
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
                    system("cls");
                    pesan("Admin");
                    running = false;
                    pause();
                    break;
            }
        }
    }while(running == true);

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
    }while(running == true);


    while (true) {
        system("cls"); // Membersihkan layar (Windows)
        cout << hijau << bold << "\n+--------------------------+"
             << "\n|      MENU NAVIGASI PANAH |"
             << "\n+--------------------------+"
             << "\n|1. Main Game" << (pilihan == 1 ? " <" : "  ") << "            |"
             << "\n|2. Pengaturan" << (pilihan == 2 ? " <" : "  ")<< "           |"
             << "\n|3. Keluar" << (pilihan == 3 ? " <" : "  ")<< "               |"
             << "\n+--------------------------+" << reset
             << kuning << "\nGunakan Panah Atas/Bawah, Enter untuk pilih."<< reset << endl;

        tombol = _getch(); // Membaca input tombol

        if (tombol == 72) { // 72 adalah kode untuk Panah Atas
            if (pilihan > 1) pilihan--;
        } 
        else if (tombol == 80) { // 80 adalah kode untuk Panah Bawah
            if (pilihan < totalPilihan) pilihan++;
        } 
        else if (tombol == 13) { // 13 adalah kode untuk Enter
            system("cls");
            cout << merah << "Anda memilih menu ke-" << pilihan << reset << endl;
            break; 
        }
        return 0;
    }