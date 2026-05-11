#include "data.h"

void clearBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void pause() {
    system("pause");
}

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

void headerHero() {
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

void lihatHero(Hero *heroArr, int jml) {
    if (jml == 0) {
        cout << "Belum ada data hero\n";
        return;
    }
    headerHero();
    for (int i = 0; i < jml; i++) {
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

void lihatSpell() {
    cout << "===========================\n";
    cout << "|         DATA SPELL      |\n";
    cout << "===========================\n";
    for (int i = 0; i < jumlahSpell; i++) {
        cout << spell[i].id << ". " << spell[i].nama << endl;
    }
}

void lihatEmblem() {
    cout << "===========================\n";
    cout << "|       DATA EMBLEM       |\n";
    cout << "===========================\n";
    for (int i = 0; i < jumlahEmblem; i++) {
        cout << emblem[i].id << ". " << emblem[i].nama << endl;
    }
}

void lihatMap() {
    cout << "===========================\n";
    cout << "|          DATA MAP       |\n";
    cout << "===========================\n";
    for (int i = 0; i < jumlahMap; i++) {
        cout << mapGame[i].id << ". " << mapGame[i].nama << endl;
    }
}

void datafavorit() {
    cout << "====================================\n";
    cout << "|            HERO FAVORIT          |\n";
    cout << "====================================\n";
    for (int i = 0; i < jumlahFavorit; i++) {
        cout << i + 1 << ". "
             << favorit[i].nama
             << " | " << favorit[i].role
             << " | Match : " << favorit[i].match
             << " | WR : "    << favorit[i].winrate
             << "%\n";
    }
}