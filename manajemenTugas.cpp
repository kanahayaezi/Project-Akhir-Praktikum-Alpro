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

void garis() {
    printf("+----+------------------------------+----------------------------------------+------------+----------+\n");
}

void headerTabel() {
    garis();
    printf("| %-2s | %-28s | %-38s | %-10s | %-8s |\n",
           "ID", "Mata Kuliah", "Judul Tugas", "Deadline", "Status");
    garis();
}

void barisTabel(NodePtr p) {
    printf("| %-2d | %-28s | %-38s | %-10s | %-8s |\n",
           p->data.id,
           p->data.matakuliah,
           p->data.judul,
           p->data.deadline,
           (p->data.selesai == 1) ? "Selesai" : "Aktif");
}

void cetakTugas() {
    if (head == NULL) {
        cout << "Daftar tugas masih kosong." << endl;
        return;
    }

    int total = 0, selesai = 0;
    NodePtr bantu = head;

    while (bantu != NULL) {
        total++;
        if (bantu->data.selesai == 1) selesai++;
        bantu = bantu->next;
    }

    cout << "Jumlah: " << total << " tugas"
         << "  |  Selesai: " << selesai
         << "  |  Aktif: " << total - selesai << endl << endl;

    headerTabel();

    bantu = head;
    while (bantu != NULL) {
        barisTabel(bantu);
        bantu = bantu->next;
    }

    garis();
}

void tampilMenu() {
    bersihLayar();
    cout << "+-----------------------------+" << endl;
    cout << "|  MANAJEMEN TUGAS KULIAH     |" << endl;
    cout << "+-----------------------------+" << endl;
    cout << "| 1. Lihat Semua Tugas        |" << endl;
    cout << "| 2. Tambah Tugas             |" << endl;
    cout << "| 3. Ubah Data Tugas          |" << endl;
    cout << "| 4. Ubah Status Tugas        |" << endl;
    cout << "| 5. Hapus Tugas              |" << endl;
    cout << "| 6. Cari Berdasarkan MK      |" << endl;
    cout << "| 7. Urutkan Berdasarkan      |" << endl;
    cout << "|    Deadline                 |" << endl;
    cout << "| 0. Keluar                   |" << endl;
    cout << "+-----------------------------+" << endl;
    cout << "Pilihan [0-7]: ";
}

int kosongList() {
    return (head == NULL) ? 1 : 0;
}

NodePtr cariID(int idCari) {
    NodePtr bantu = head;

    while (bantu != NULL) {
        if (bantu->data.id == idCari) {
            return bantu;
        }
        bantu = bantu->next;
    }

    return NULL;
}

void tambahTugas(char mk[], char judulTgs[], char dl[]) {
    NodePtr baru = (Node *) malloc(sizeof(Node));

    if (baru == NULL) {
        cout << "[!] Gagal mengalokasi memori." << endl;
        return;
    }

    baru->data.id = idCounter++;
    strcpy(baru->data.matakuliah, mk);
    strcpy(baru->data.judul, judulTgs);
    strcpy(baru->data.deadline, dl);
    baru->data.selesai = 0;
    baru->next = NULL;

    if (kosongList()) {
        head = baru;
    } else {
        NodePtr bantu = head;
        while (bantu->next != NULL) bantu = bantu->next;
        bantu->next = baru;
    }

    cout << endl << "[OK] Tugas berhasil ditambahkan." << endl;
}

void hapusTugas(int idCari) {
    NodePtr hapus, bantu;

    if (head->data.id == idCari) {
        hapus = head;
        head  = head->next;
        free(hapus);
        cout << endl << "[OK] Tugas berhasil dihapus." << endl;
        return;
    }

    bantu = head;
    while (bantu->next != NULL && bantu->next->data.id != idCari) {
        bantu = bantu->next;
    }

    if (bantu->next == NULL) {
        cout << endl << "[!] ID tidak ditemukan." << endl;
    } else {
        hapus       = bantu->next;
        bantu->next = hapus->next;
        free(hapus);
        cout << endl << "[OK] Tugas berhasil dihapus." << endl;
    }
}

void urutDeadline() {
    if (kosongList()) {
        cout << "Daftar tugas masih kosong." << endl;
        return;
    }

    int ada_tukar;
    NodePtr ptr1, batas = NULL;
    DataTugas temp;

    do {
        ada_tukar = 0;
        ptr1 = head;

        while (ptr1->next != batas) {
            char *d1 = ptr1->data.deadline;
            char *d2 = ptr1->next->data.deadline;

            char key1[9], key2[9];
            key1[0]=d1[6]; key1[1]=d1[7]; key1[2]=d1[8]; key1[3]=d1[9];
            key1[4]=d1[3]; key1[5]=d1[4]; key1[6]=d1[0]; key1[7]=d1[1];
            key1[8]='\0';

            key2[0]=d2[6]; key2[1]=d2[7]; key2[2]=d2[8]; key2[3]=d2[9];
            key2[4]=d2[3]; key2[5]=d2[4]; key2[6]=d2[0]; key2[7]=d2[1];
            key2[8]='\0';

            if (strcmp(key1, key2) > 0) {
                temp = ptr1->data;
                ptr1->data = ptr1->next->data;
                ptr1->next->data = temp;
                ada_tukar = 1;
            }

            ptr1 = ptr1->next;
        }

        batas = ptr1;

    } while (ada_tukar);

    cout << "[OK] Tugas berhasil diurutkan berdasarkan deadline." << endl << endl;
}


int main() {
    cout << "Program Manajemen Tugas Kuliah" << endl;
    return 0;
}
