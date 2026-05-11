#include "data.h"

int main() {
    srand(time(0));
    Login admin = {"admin", "01123"};
    int pilih;

    do {
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
        cin >> pilih;
        clearBuffer();

        switch (pilih) {
            case 1:
                if (loginAdmin(admin)) {
                    menuAdmin();
                }
                break;
            case 2:
                if (loginUser()) {
                    menuUser();
                }
                break;
            case 3:
                registrasiUser();
                pause();
                break;
            case 4:
                system("cls");
                cout << "Terima kasih telah menggunakan sistem ini.\n";
                break;
            default:
                cout << "\n==System massage==\n";
                cout << "Pilihan gk ada.\n";
                pause();
        }
    } while (pilih != 4);

    return 0;
}