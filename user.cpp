#include "data.h"

void heroMeta() {
    cout << "=============================\n";
    cout << "|           HERO META       |\n";
    cout << "=============================\n";
    for (int i = 0; i < jumlahHero; i++) {
        if (hero[i].meta) {
            cout << hero[i].nama << " | " << hero[i].detail.patch << endl;
        }
    }
}

void compareHero() {
    lihatHero(hero, jumlahHero);
    int a, b;
    cout << "\nPilih Hero 1 : ";
    cin >> a;
    cout << "Pilih Hero 2 : ";
    cin >> b;
    clearBuffer();
    a--;
    b--;

    if (a < 0 || a >= jumlahHero || b < 0 || b >= jumlahHero) {
        cout << "ID tidak valid!\n";
        return;
    }

    int powerA = hero[a].detail.level;
    int powerB = hero[b].detail.level;
    if (hero[a].detail.patch == "Buff") powerA += 5;
    if (hero[b].detail.patch == "Buff") powerB += 5;
    if (hero[a].detail.patch == "Nerf") powerA -= 5;
    if (hero[b].detail.patch == "Nerf") powerB -= 5;

    system("cls");
    cout << "=============================\n";
    cout << "|           HASIL           |\n";
    cout << "=============================\n";
    cout << "=== BERDASARKAN HERO POWER ===\n";
    cout << hero[a].nama << " Power : " << powerA << endl;
    cout << hero[b].nama << " Power : " << powerB << endl;

    if (powerA > powerB)
        cout << "Hero lebih kuat : " << hero[a].nama << endl;
    else if (powerB > powerA)
        cout << "Hero lebih kuat : " << hero[b].nama << endl;
    else
        cout << "Kedua hero seimbang\n";

    cout << "\n=== BERDASARKAN TINGKAT KESULITAN ===\n";
    cout << hero[a].nama << ", Kesulitan : " << hero[a].detail.kesulitan << endl;
    cout << hero[b].nama << ", Kesulitan : " << hero[b].detail.kesulitan << endl;

    if (hero[a].detail.kesulitan == "Hard" && hero[b].detail.kesulitan != "Hard")
        cout << "Hero lebih sulit : " << hero[a].nama << endl;
    if (hero[b].detail.kesulitan == "Hard" && hero[a].detail.kesulitan != "Hard")
        cout << "Hero lebih sulit : " << hero[b].nama << endl;
    if (hero[a].detail.kesulitan == "Medium" && hero[b].detail.kesulitan == "Easy")
        cout << "Hero lebih sulit : " << hero[a].nama << endl;
    if (hero[b].detail.kesulitan == "Medium" && hero[a].detail.kesulitan == "Easy")
        cout << "Hero lebih sulit : " << hero[b].nama << endl;
    if (hero[a].detail.kesulitan == hero[b].detail.kesulitan)
        cout << "Kedua hero memiliki tingkat kesulitan yang sama\n";
}

void tambahFavorit() {
    lihatHero(hero, jumlahHero);
    int pilih;
    cout << "\nPilih Hero Favorit : ";
    cin >> pilih;
    clearBuffer();
    pilih--;

    if (pilih < 0 || pilih >= jumlahHero) {
        cout << "Pilihan tidak valid!\n";
        return;
    }

    favorit[jumlahFavorit].nama    = hero[pilih].nama;
    favorit[jumlahFavorit].role    = hero[pilih].detail.role;
    favorit[jumlahFavorit].level   = hero[pilih].detail.level;
    favorit[jumlahFavorit].match   = rand() % 100;
    favorit[jumlahFavorit].winrate = rand() % 100;
    jumlahFavorit++;
    cout << "\nFavorit berhasil ditambahkan!\n";
}

void updateRealtimeFavorit() {
    for (int i = 0; i < jumlahFavorit; i++) {
        favorit[i].match   += rand() % 5;
        favorit[i].winrate += (rand() % 11 - 5);
        if (favorit[i].winrate < 0)   favorit[i].winrate = 0;
        if (favorit[i].winrate > 100) favorit[i].winrate = 100;
    }
}

void lihatFavorit() {
    atomic<bool> keluar(false);

    thread inputThread([&]() {
        string cmd;
        while (getline(cin, cmd)) {
            if (cmd == "e") {
                keluar = true;
                break;
            }
        }
    });

    while (!keluar) {
        system("cls");
        datafavorit();
        cout << "\nKetik e lalu Enter untuk kembali ke Menu User.\n";
        cout << "Update setiap 10 detik...\n";
        for (int t = 0; t < 100 && !keluar; t++) {
            this_thread::sleep_for(chrono::milliseconds(100));
        }
        if (!keluar) {
            updateRealtimeFavorit();
        }
    }

    if (inputThread.joinable()) inputThread.join();
}

void hapusFavorit() {
    if (jumlahFavorit == 0) {
        cout << "Belum ada data favorit!\n";
        return;
    }
    datafavorit();
    int no;
    cout << "Pilih favorit yang dihapus : ";
    cin >> no;
    clearBuffer();

    if (no < 1 || no > jumlahFavorit) {
        cout << "Pilihan tidak valid!\n";
        return;
    }
    for (int i = no - 1; i < jumlahFavorit - 1; i++) {
        favorit[i] = favorit[i + 1];
    }
    jumlahFavorit--;
    cout << "\nHero favorit berhasil dihapus!\n";
}

void menuFav() {
    int pilih;
    do {
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
        cin >> pilih;
        clearBuffer();

        switch (pilih) {
            case 1:
                system("cls");
                tambahFavorit();
                pause();
                break;
            case 2:
                system("cls");
                lihatFavorit();
                break;
            case 3:
                system("cls");
                hapusFavorit();
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
    } while (pilih != 4);
}

void menuUser() {
    int pilih;
    do {
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
        cin >> pilih;
        clearBuffer();

        switch (pilih) {
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
                compareHero();
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
    } while (pilih != 6);
}