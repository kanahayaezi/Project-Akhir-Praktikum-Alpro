#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std;

// struct data tugas
struct DataTugas {
    int id;
    char matakuliah[30];
    char judul[50];
    char deadline[11];
    int selesai;
};

// node linked list
typedef struct Node *NodePtr;
typedef struct Node {
    DataTugas data;
    NodePtr next;
} Node;

NodePtr head = NULL;
int idCounter = 1;

void bersihLayar() { system("cls"); }
void jedaLayar() { system("pause"); }

int kosongString(char str[]) {
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] != ' ') return 0;
        i++;
    }
    return 1;
}

int validDeadline(char dl[]) {
    int i;

    if ((int)strlen(dl) != 10) return 0;
    if (dl[2] != '/' || dl[5] != '/') return 0;

    for (i = 0; i < 10; i++) {
        if (i == 2 || i == 5) continue;

        if (dl[i] < '0' || dl[i] > '9')
            return 0;
    }

    int dd = (dl[0]-'0')*10 + (dl[1]-'0');
    int mm = (dl[3]-'0')*10 + (dl[4]-'0');
    int yy = (dl[6]-'0')*1000 + (dl[7]-'0')*100 + (dl[8]-'0')*10 + (dl[9]-'0');

    if (dd < 1 || dd > 31) return 0;
    if (mm < 1 || mm > 12) return 0;
    if (yy < 2000 || yy > 2099) return 0;

    int maxHari[13] = {0,31,29,31,30,31,30,31,31,30,31,30,31};
    if (dd > maxHari[mm]) return 0;

    return 1;
}

int inputAngka(const char *label, int min, int max) {
    int nilai;

    do {
        cout << label << ": ";

        if (cin.fail()) {
            cin.clear();
            cin.ignore(100, '\n');

            cout << "[!] Masukan harus berupa angka." << endl;
            nilai = min - 1;
            continue;
        }

        cin.ignore();

        if (nilai < min || nilai > max) {
            cout << "[!] Masukkan angka antara " << min << " sampai " << max << ". Ulangi." << endl;
        }

    } while (nilai < min || nilai > max);

    return nilai;
}

char inputKonfirm(const char *pertanyaan) {
    char jawab[10];

    do {
        cout << pertanyaan << " (y/t): ";
        cin.getline(jawab, 10);

        if (jawab[0] != 'y' && jawab[0] != 'Y' && jawab[0] != 't' && jawab[0] != 'T') {
            cout << "[!] Masukkan 'y' untuk ya atau 't' untuk tidak. Ulangi." << endl;
        }

    } while (jawab[0] != 'y' && jawab[0] != 'Y' && jawab[0] != 't' && jawab[0] != 'T');

    return jawab[0];
}

void inputTeks(const char *label, char hasil[], int batas) {
    cout << label;
    cin.getline(hasil, batas);

    while (kosongString(hasil)) {
        cout << "[!] Data tidak boleh kosong." << endl;
        cout << label;
        cin.getline(hasil, batas);
    }
}

void inputDeadline(char dl[]) {
    cout << "Deadline (DD/MM/YYYY) : ";
    cin.getline(dl, 11);

    while (!validDeadline(dl)) {
        cout << "[!] Format tidak valid. Gunakan DD/MM/YYYY, contoh: 25/06/2025." << endl;
        cout << "    Hari 01-31, Bulan 01-12, Tahun 2000-2099." << endl;
        cout << "Deadline (DD/MM/YYYY) : ";
        cin.getline(dl, 11);
    }
}

int inputPilihan() {
    int pilihan;

    cin >> pilihan;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(100, '\n');
        cout << "[!] Pilihan harus berupa angka." << endl;
        jedaLayar();
        return -1;
    }

    cin.ignore();

    if (pilihan < 0 || pilihan > 7) {
        cout << "[!] Pilihan tidak valid. Masukkan angka 0-7." << endl;
        jedaLayar();
        return -1;
    }

    return pilihan;
}

int main() {
    cout << "Program Manajemen Tugas Kuliah" << endl;
    return 0;
}