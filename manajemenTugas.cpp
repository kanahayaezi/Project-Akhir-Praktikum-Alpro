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

    return 1;
}

int inputAngka(const char *label, int min, int max) {
    int nilai;

    do {
        cout << label << ": ";
        cin >> nilai;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(100, '\n');

            cout << "[!] Masukan harus berupa angka." << endl;
            nilai = min - 1;
        }

    } while (nilai < min || nilai > max);

    cin.ignore();
    return nilai;
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

int main() {
    cout << "Program Manajemen Tugas Kuliah" << endl;
    return 0;
}