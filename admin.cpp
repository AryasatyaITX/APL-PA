#include "data.h"

int tambahHero(Hero heroArr[], int *jml) {
    if (*jml >= MAX) {
        cout << "Data hero penuh!\n";
        return 0;
    }
    Hero heroBaru;
    Hero *ptr = &heroBaru;
    ptr->id = *jml + 1;

    cout << "Nama Hero        : ";
    getline(cin, ptr->nama);
    cout << "Role Hero        : ";
    getline(cin, ptr->detail.role);
    cout << "Kesulitan Hero   : ";
    getline(cin, ptr->detail.kesulitan);
    cout << "Level Hero (1-15): ";
    cin >> ptr->detail.level;
    clearBuffer();

    ptr->detail.patch = "Normal";
    ptr->meta         = false;
    heroArr[*jml]     = heroBaru;
    (*jml)++;
    cout << "\nHero berhasil ditambahkan!\n";
    return 1;
}

void updateHero(Hero *heroArr, int jml) {
    if (jml == 0) {
        cout << "Belum ada data hero.\n";
        return;
    }
    lihatHero(heroArr, jml);

    int id;
    cout << "\nMasukkan ID Hero : ";
    cin >> id;
    clearBuffer();

    int index = -1;
    for (int i = 0; i < jml; i++) {
        if (heroArr[i].id == id) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        cout << "ID tidak ditemukan!\n";
        return;
    }

    Hero *target = &heroArr[index];
    cout << "\n1. Nama\n";
    cout << "2. Role\n";
    cout << "3. Kesulitan\n";
    cout << "4. Level\n";
    cout << "5. Patch\n";
    cout << "Pilih : ";
    int pilih;
    cin >> pilih;
    clearBuffer();

    switch (pilih) {
        case 1:
            cout << "Nama baru : ";
            getline(cin, target->nama);
            break;
        case 2:
            cout << "Role baru : ";
            getline(cin, target->detail.role);
            break;
        case 3:
            cout << "Kesulitan baru : ";
            getline(cin, target->detail.kesulitan);
            break;
        case 4:
            cout << "Level baru : ";
            cin >> target->detail.level;
            clearBuffer();
            break;
        case 5:
            cout << "Patch baru : ";
            getline(cin, target->detail.patch);
            target->meta = (target->detail.patch == "Buff");
            break;
        default:
            cout << "Pilihan tidak tersedia.\n";
    }
    cout << "\nData berhasil diupdate!\n";
}

int hapusHero(Hero heroArr[], int *jml) {
    if (*jml == 0) {
        cout << "Belum ada data hero.\n";
        return 0;
    }
    lihatHero(heroArr, *jml);

    int id;
    cout << "\nMasukkan ID Hero : ";
    cin >> id;
    clearBuffer();

    int index = -1;
    for (int i = 0; i < *jml; i++) {
        if (heroArr[i].id == id) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        cout << "ID tidak ditemukan!\n";
        return 0;
    }
    for (int i = index; i < *jml - 1; i++) {
        heroArr[i]    = heroArr[i + 1];
        heroArr[i].id = i + 1;
    }
    (*jml)--;
    cout << "\nData berhasil dihapus!\n";
    return 1;
}

void tambahSpell() {
    if (jumlahSpell >= MAX) {
        cout << "Data spell penuh!\n";
        return;
    }
    spell[jumlahSpell].id = jumlahSpell + 1;
    cout << "Nama Spell : ";
    getline(cin, spell[jumlahSpell].nama);
    jumlahSpell++;
    cout << "Spell berhasil ditambahkan!\n";
}

void tambahEmblem() {
    if (jumlahEmblem >= MAX) {
        cout << "Data emblem penuh!\n";
        return;
    }
    emblem[jumlahEmblem].id = jumlahEmblem + 1;
    cout << "Nama Emblem : ";
    getline(cin, emblem[jumlahEmblem].nama);
    jumlahEmblem++;
    cout << "Emblem berhasil ditambahkan!\n";
}

void tambahMap() {
    if (jumlahMap >= MAX) {
        cout << "Data map penuh!\n";
        return;
    }
    mapGame[jumlahMap].id = jumlahMap + 1;
    cout << "Nama Map : ";
    getline(cin, mapGame[jumlahMap].nama);
    jumlahMap++;
    cout << "Map berhasil ditambahkan!\n";
}

void sortingNama() {
    for (int i = 0; i < jumlahHero - 1; i++) {
        for (int j = 0; j < jumlahHero - i - 1; j++) {
            if (hero[j].nama > hero[j + 1].nama) {
                swap(hero[j], hero[j + 1]);
            }
        }
    }
    cout << "\nSorting nama berhasil!\n";
}

void sortingLevel() {
    for (int i = 0; i < jumlahHero - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < jumlahHero; j++) {
            if (hero[j].detail.level < hero[minIdx].detail.level) {
                minIdx = j;
            }
        }
        swap(hero[i], hero[minIdx]);
    }
    cout << "\nSorting level berhasil!\n";
}

int binarySearchNama(string target) {
    sortingNama();
    int low  = 0;
    int high = jumlahHero - 1;

    while (low <= high) {
        int mid = (low + high) / 2;
        if (hero[mid].nama == target)      return mid;
        else if (hero[mid].nama < target)  low  = mid + 1;
        else                               high = mid - 1;
    }
    return -1;
}

void cariRole() {
    string role;
    cout << "Masukkan role : ";
    getline(cin, role);

    bool ditemukan = false;
    for (int i = 0; i < jumlahHero; i++) {
        if (hero[i].detail.role == role) {
            cout << hero[i].nama << endl;
            ditemukan = true;
        }
    }
    if (!ditemukan) cout << "Role tidak ditemukan\n";
}

void menuSorting() {
    int pilih;
    do {
        system("cls");
        cout << "=============================================\n";
        cout << "|                MENU SORTING               |\n";
        cout << "=============================================\n";
        cout << "|1. Sorting Nama Hero                       |\n";
        cout << "|2. Sorting Level Hero                      |\n";
        cout << "|3. Kembali                                 |\n";
        cout << "=============================================\n";
        cout << "Pilih : ";
        cin >> pilih;
        clearBuffer();

        switch (pilih) {
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
    } while (pilih != 3);
}

void menuSearching() {
    int pilih;
    do {
        system("cls");
        cout << "=============================================\n";
        cout << "|               MENU SEARCHING              |\n";
        cout << "=============================================\n";
        cout << "|1. Search Hero Nama                        |\n";
        cout << "|2. Search Hero Role                        |\n";
        cout << "|3. Kembali                                 |\n";
        cout << "=============================================\n";
        cout << "Pilih : ";
        cin >> pilih;
        clearBuffer();

        switch (pilih) {
            case 1: {
                string cari;
                cout << "Masukkan nama hero : ";
                getline(cin, cari);
                int hasil = binarySearchNama(cari);
                if (hasil != -1)
                    cout << "\nHero ditemukan : " << hero[hasil].nama << endl;
                else
                    cout << "\nHero tidak ditemukan\n";
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
    } while (pilih != 3);
}

void menuHero() {
    int pilih;
    do {
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
        cin >> pilih;
        clearBuffer();

        switch (pilih) {
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
    } while (pilih != 4);
}

void menuCreate() {
    int pilih;
    do {
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
        cin >> pilih;
        clearBuffer();

        switch (pilih) {
            case 1:
                system("cls");
                if (tambahHero(hero, &jumlahHero)) {
                    pesan("Create", "Hero berhasil ditambahkan");
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
    } while (pilih != 5);
}

void menuRead() {
    int pilih;
    do {
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
        cin >> pilih;
        clearBuffer();

        switch (pilih) {
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
    } while (pilih != 5);
}

void menuAdmin() {
    int pilih;
    do {
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
        cin >> pilih;
        clearBuffer();

        switch (pilih) {
            case 1:
                menuCreate();
                break;
            case 2:
                menuRead();
                break;
            case 3:
                system("cls");
                updateHero(hero, jumlahHero);
                pause();
                break;
            case 4:
                system("cls");
                if (hapusHero(hero, &jumlahHero)) {
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
    } while (pilih != 5);
}