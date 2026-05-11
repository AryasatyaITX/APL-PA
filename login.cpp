#include "data.h"

bool loginAdmin(Login admin) {
    string username, password;
    int kesempatan = 0;

    while (kesempatan < 3) {
        cout << "Username : ";
        cin >> username;
        cout << "Password : ";
        cin >> password;

        if (username == admin.username && password == admin.password) {
            cout << "\nLogin berhasil!\n";
            return true;
        }
        kesempatan++;
        cout << "Login gagal (" << kesempatan << "/3)\n";
    }
    return false;
}

void registrasiUser() {
    User baru;
    cout << "=== REGISTRASI USER ===\n";
    cout << "Username : ";
    cin >> baru.username;
    cout << "Password : ";
    cin >> baru.password;
    clearBuffer();

    for (int i = 0; i < jumlahUser; i++) {
        if (userList[i].username == baru.username) {
            cout << "Username sudah digunakan!\n";
            return;
        }
    }
    userList[jumlahUser++] = baru;
    cout << "Registrasi berhasil!\n";
}

bool loginUser() {
    string username, password;
    int kesempatan = 0;

    while (kesempatan < 3) {
        cout << "=== LOGIN USER ===\n";
        cout << "Username : ";
        cin >> username;
        cout << "Password : ";
        cin >> password;
        clearBuffer();

        for (int i = 0; i < jumlahUser; i++) {
            if (userList[i].username == username &&
                userList[i].password == password) {
                cout << "Login berhasil!\n";
                return true;
            }
        }
        kesempatan++;
        cout << "Username atau Password salah! ("
             << kesempatan << "/3)\n";
        pause();
        system("cls");
    }
    cout << "Gagal login 3 kali!\n";
    pause();
    return false;
}