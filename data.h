#ifndef GLOBAL_H
#define GLOBAL_H

#include <iostream>
#include <iomanip>
#include <limits>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <atomic>
using namespace std;

#define MAX 100

struct Login {
    string username;
    string password;
};

struct DetailHero {
    string role;
    string kesulitan;
    int level;
    string patch;
};

struct Hero {
    int id;
    string nama;
    bool meta;
    DetailHero detail;
};

struct Spell {
    int id;
    string nama;
};

struct Emblem {
    int id;
    string nama;
};

struct Map {
    int id;
    string nama;
};

struct Favorit {
    string nama;
    string role;
    int level;
    int match;
    float winrate;
};

struct User {
    string username;
    string password;
};

Hero hero[MAX] = {
    {1, "Ling",    true,  {"Assassin",  "Hard",   15, "Buff"}},
    {2, "Tigreal", false, {"Tank",      "Easy",   10, "Normal"}},
    {3, "Kagura",  true,  {"Mage",      "Hard",   14, "Buff"}},
    {4, "Beatrix", false, {"Marksman",  "Medium", 13, "Nerf"}}
};

Spell spell[MAX] = {
    {1, "Flicker"},
    {2, "Retribution"}
};

Emblem emblem[MAX] = {
    {1, "Assassin"},
    {2, "Tank"}
};

Map mapGame[MAX] = {
    {1, "Broken Wall"},
    {2, "Flying Clouds"}
};

Favorit favorit[MAX];
User    userList[MAX];

int jumlahHero    = 4;
int jumlahSpell   = 2;
int jumlahEmblem  = 2;
int jumlahMap     = 2;
int jumlahFavorit = 0;
int jumlahUser    = 0;

void clearBuffer();
void pause();
void headerHero();
string pesan(string nama);
string pesan(string nama, string status);
void lihatHero(Hero *heroArr, int jml);
void lihatSpell();
void lihatEmblem();
void lihatMap();
void datafavorit();

bool loginAdmin(Login admin);
void registrasiUser();
bool loginUser();


int  tambahHero(Hero heroArr[], int *jml);
void updateHero(Hero *heroArr, int jml);
int  hapusHero(Hero heroArr[], int *jml);
void tambahSpell();
void tambahEmblem();
void tambahMap();
void sortingNama();
void sortingLevel();
int  binarySearchNama(string target);
void cariRole();
void menuSorting();
void menuSearching();
void menuHero();
void menuCreate();
void menuRead();
void menuAdmin();


void heroMeta();
void compareHero();
void tambahFavorit();
void updateRealtimeFavorit();
void lihatFavorit();
void hapusFavorit();
void menuFav();
void menuUser();

#endif // GLOBAL_H