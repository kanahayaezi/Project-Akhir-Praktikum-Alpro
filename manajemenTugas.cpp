#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std;

// struct untuk menyimpan data satu tugas
struct DataTugas {
    int id;
    char matakuliah[30];
    char judul[50];
    char deadline[11];
    int selesai;
};

// node untuk linked list singly
typedef struct Node *NodePtr;
typedef struct Node {
    DataTugas data;
    NodePtr next;
} Node;

NodePtr head = NULL;
int idCounter = 1;

void bersihLayar() { system("cls"); }
void jedaLayar() { system("pause"); }

// cek apakah string hanya berisi spasi atau kosong
int kosongString(char str[]) {
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] != ' ') return 0;
        i++;
    }
    return 1;
}

// validasi format deadline DD/MM/YYYY dan rentang nilainya
int validDeadline(char dl[]) {
    int i;

    if ((int)strlen(dl) != 10) return 0;
    if (dl[2] != '/' || dl[5] != '/') return 0;

    for (i = 0; i < 10; i++) {
        if (i == 2 || i == 5) continue;
        if (dl[i] < '0' || dl[i] > '9') return 0;
    }

    int dd = (dl[0]-'0')*10 + (dl[1]-'0');
    int mm = (dl[3]-'0')*10 + (dl[4]-'0');
    int yy = (dl[6]-'0')*1000 + (dl[7]-'0')*100 + (dl[8]-'0')*10 + (dl[9]-'0');

    if (dd < 1 || dd > 31) return 0;
    if (mm < 1 || mm > 12) return 0;
    if (yy < 2000 || yy > 2099) return 0;

    // batas hari tiap bulan, februari dianggap 29 hari
    int maxHari[13] = {0,31,29,31,30,31,30,31,31,30,31,30,31};
    if (dd > maxHari[mm]) return 0;

    return 1;
}

// input angka dengan validasi tipe dan rentang
int inputAngka(const char *label, int min, int max) {
    int nilai;

    do {
        cout << label << ": ";
        cin >> nilai;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(100, '\n');
            cout << "[!] Masukan harus berupa angka. Ulangi." << endl;
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

// input konfirmasi y/t dari pengguna
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

// input teks wajib isi, tidak boleh hanya spasi
void inputTeks(const char *label, char hasil[], int batas) {
    cout << label;
    cin.getline(hasil, batas);

    while (kosongString(hasil)) {
        cout << "[!] Data tidak boleh kosong. Ulangi." << endl;
        cout << label;
        cin.getline(hasil, batas);
    }
}

// input deadline dengan validasi format
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

// input pilihan menu 0-7 dengan validasi
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

// cetak garis pembatas tabel
void garis() {
    printf("+----+------------------------------+----------------------------------------+------------+----------+\n");
}

// cetak header kolom tabel
void headerTabel() {
    garis();
    printf("| %-2s | %-28s | %-38s | %-10s | %-8s |\n",
           "ID", "Mata Kuliah", "Judul Tugas", "Deadline", "Status");
    garis();
}

// cetak satu baris data tugas ke tabel
void barisTabel(NodePtr p) {
    printf("| %-2d | %-28s | %-38s | %-10s | %-8s |\n",
           p->data.id,
           p->data.matakuliah,
           p->data.judul,
           p->data.deadline,
           (p->data.selesai == 1) ? "Selesai" : "Aktif");
}

// cetak seluruh isi list beserta ringkasan jumlah tugas
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

// tampilkan menu utama
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

// cek apakah list kosong
int kosongList() {
    return (head == NULL) ? 1 : 0;
}

// cari node berdasarkan id, kembalikan NULL jika tidak ada
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

// tambah node baru di akhir list
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

// hapus node berdasarkan id
void hapusTugas(int idCari) {
    NodePtr hapus, bantu;

    // kasus hapus node pertama
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

// urutkan list berdasarkan deadline menggunakan bubble sort
// deadline dikonversi ke format YYYYMMDD untuk perbandingan string
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

            // susun ulang karakter dari DD/MM/YYYY menjadi YYYYMMDD
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

// cari tugas berdasarkan substring nama mata kuliah, case-insensitive
void cariMK(char keyword[]) {
    if (kosongList()) {
        cout << "Daftar tugas masih kosong." << endl;
        return;
    }

    int ditemukan = 0;
    NodePtr bantu = head;
    char mk_kecil[30], kw_kecil[30];
    int j;

    // ubah keyword ke huruf kecil
    strcpy(kw_kecil, keyword);
    for (j = 0; kw_kecil[j] != '\0'; j++) {
        if (kw_kecil[j] >= 'A' && kw_kecil[j] <= 'Z') kw_kecil[j] += 32;
    }

    headerTabel();

    while (bantu != NULL) {
        // ubah nama mk node ke huruf kecil untuk dibandingkan
        strcpy(mk_kecil, bantu->data.matakuliah);

        for (j = 0; mk_kecil[j] != '\0'; j++) {
            if (mk_kecil[j] >= 'A' && mk_kecil[j] <= 'Z') mk_kecil[j] += 32;
        }

        if (strstr(mk_kecil, kw_kecil) != NULL) {
            barisTabel(bantu);
            ditemukan++;
        }

        bantu = bantu->next;
    }

    garis();

    if (ditemukan == 0) {
        cout << "Tidak ada tugas untuk mata kuliah \"" << keyword << "\"." << endl;
    } else {
        cout << "Ditemukan " << ditemukan << " tugas." << endl;
    }
}

// toggle status selesai/aktif berdasarkan id
void ubahStatus(int idCari) {
    NodePtr bantu = head;

    while (bantu != NULL) {
        if (bantu->data.id == idCari) {
            if (bantu->data.selesai == 0) {
                bantu->data.selesai = 1;
                cout << endl << "[OK] Tugas \"" << bantu->data.judul << "\" ditandai selesai." << endl;
            } else {
                bantu->data.selesai = 0;
                cout << endl << "[OK] Tugas \"" << bantu->data.judul << "\" diaktifkan kembali." << endl;
            }
            return;
        }

        bantu = bantu->next;
    }

    cout << endl << "[!] ID tidak ditemukan." << endl;
}

// simpan seluruh data list ke file biner
void simpanFile() {
    if (kosongList()) {
        cout << "Tidak ada data untuk disimpan." << endl;
        return;
    }

    FILE *pf = fopen("tugas_kuliah.dat", "wb");

    if (pf == NULL) {
        cout << "[!] Berkas tidak dapat dibuat." << endl;
        return;
    }

    int jumlah = 0;
    NodePtr bantu = head;

    while (bantu != NULL) {
        fwrite(&bantu->data, sizeof(DataTugas), 1, pf);
        jumlah++;
        bantu = bantu->next;
    }

    fclose(pf);
    cout << "[OK] " << jumlah << " tugas berhasil disimpan." << endl;
}

// muat data dari file biner ke list, validasi tiap rekaman
void muatFile() {
    FILE *pf = fopen("tugas_kuliah.dat", "rb");

    if (pf == NULL) {
        cout << "[i] Berkas data belum ada. Mulai dengan daftar kosong." << endl;
        return;
    }

    // bersihkan list lama sebelum memuat
    while (head != NULL) {
        NodePtr hapus = head;
        head = head->next;
        free(hapus);
    }

    idCounter = 1;

    DataTugas temp;
    int jumlah = 0, dilewati = 0;

    while (fread(&temp, sizeof(DataTugas), 1, pf) == 1) {
        // lewati rekaman yang datanya tidak valid
        if (temp.id <= 0 || kosongString(temp.matakuliah) || !validDeadline(temp.deadline)) {
            dilewati++;
            continue;
        }

        NodePtr baru = (Node *) malloc(sizeof(Node));

        if (baru == NULL) {
            cout << "[!] Gagal mengalokasi memori." << endl;
            break;
        }

        baru->data = temp;
        baru->next = NULL;

        if (head == NULL) {
            head = baru;
        } else {
            NodePtr bantu = head;
            while (bantu->next != NULL) bantu = bantu->next;
            bantu->next = baru;
        }

        // sesuaikan idCounter agar tidak bentrok dengan id yang dimuat
        if (temp.id >= idCounter) idCounter = temp.id + 1;
        jumlah++;
    }

    fclose(pf);

    if (jumlah == 0 && dilewati == 0) {
        cout << "[i] Berkas data kosong. Mulai dengan daftar kosong." << endl;
    } else if (jumlah == 0 && dilewati > 0) {
        cout << "[!] Berkas data tidak dapat dibaca (kemungkinan rusak)." << endl;
    } else {
        cout << "[OK] " << jumlah << " tugas berhasil dimuat." << endl;
        if (dilewati > 0) {
            cout << "[!] " << dilewati << " rekaman dilewati karena data tidak valid." << endl;
        }
    }
}

// tampilkan seluruh daftar tugas
void menuLihat() {
    cout << "----- DAFTAR SEMUA TUGAS -----" << endl << endl;
    cetakTugas();
    jedaLayar();
}

// input data tugas baru lalu tambahkan ke list
void menuTambah() {
    char mk[30], judulTgs[50], dl[11];

    cout << "----- TAMBAH TUGAS BARU -----" << endl << endl;

    inputTeks("Mata Kuliah           : ", mk, 30);
    inputTeks("Judul Tugas           : ", judulTgs, 50);
    inputDeadline(dl);

    tambahTugas(mk, judulTgs, dl);
    jedaLayar();
}

// edit data tugas yang sudah ada berdasarkan id
void menuUbah() {
    cout << "----- UBAH DATA TUGAS -----" << endl << endl;

    if (kosongList()) {
        cout << "Daftar tugas masih kosong." << endl;
        jedaLayar();
        return;
    }

    cetakTugas();

    NodePtr target = NULL;

    do {
        int idInput = inputAngka("ID Tugas yang diubah ", 1, idCounter - 1);
        target = cariID(idInput);

        if (target == NULL) {
            cout << "[!] ID tidak ditemukan. Ulangi." << endl;
        }

    } while (target == NULL);

    cout << endl << "Data saat ini:" << endl;
    cout << "Mata Kuliah           : " << target->data.matakuliah << endl;
    cout << "Judul Tugas           : " << target->data.judul << endl;
    cout << "Deadline              : " << target->data.deadline << endl;
    cout << endl << "(Biarkan kosong jika tidak ingin diubah)" << endl << endl;

    char mkBaru[30], judulBaru[50], dlBaru[11];

    cout << "Mata Kuliah Baru      : ";
    cin.getline(mkBaru, 30);
    if (!kosongString(mkBaru)) strcpy(target->data.matakuliah, mkBaru);

    cout << "Judul Tugas Baru      : ";
    cin.getline(judulBaru, 50);
    if (!kosongString(judulBaru)) strcpy(target->data.judul, judulBaru);

    cout << "Deadline Baru         : ";
    cin.getline(dlBaru, 11);

    while (!kosongString(dlBaru) && !validDeadline(dlBaru)) {
        cout << "[!] Format tidak valid. Gunakan DD/MM/YYYY atau kosongkan." << endl;
        cout << "Deadline Baru         : ";
        cin.getline(dlBaru, 11);
    }

    if (!kosongString(dlBaru)) strcpy(target->data.deadline, dlBaru);

    cout << endl << "[OK] Tugas berhasil diperbarui." << endl;
    jedaLayar();
}

// pilih tugas dan konfirmasi sebelum mengubah statusnya
void menuStatus() {
    cout << "----- UBAH STATUS TUGAS -----" << endl << endl;

    if (kosongList()) {
        cout << "Daftar tugas masih kosong." << endl;
        jedaLayar();
        return;
    }

    cetakTugas();
    cout << "Keterangan: Aktif -> Selesai, atau Selesai -> Aktif kembali." << endl << endl;

    NodePtr target = NULL;
    int idInput;

    do {
        idInput = inputAngka("ID Tugas             ", 1, idCounter - 1);
        target = cariID(idInput);

        if (target == NULL) {
            cout << "[!] ID tidak ditemukan. Ulangi." << endl;
        }

    } while (target == NULL);

    cout << endl;
    cout << "Status saat ini : " << (target->data.selesai == 0 ? "Aktif" : "Selesai") << endl;
    cout << "Akan diubah ke  : " << (target->data.selesai == 0 ? "Selesai" : "Aktif") << endl << endl;

    char konfirm = inputKonfirm("Yakin ingin mengubah status?");

    if (konfirm == 'y' || konfirm == 'Y') {
        ubahStatus(idInput);
    } else {
        cout << endl << "[i] Perubahan status dibatalkan." << endl;
    }

    jedaLayar();
}

// konfirmasi lalu hapus tugas berdasarkan id
void menuHapus() {
    cout << "----- HAPUS TUGAS -----" << endl << endl;

    if (kosongList()) {
        cout << "Daftar tugas masih kosong." << endl;
        jedaLayar();
        return;
    }

    cetakTugas();

    NodePtr target = NULL;
    int idHapus;

    do {
        idHapus = inputAngka("ID Tugas yang dihapus", 1, idCounter - 1);
        target = cariID(idHapus);

        if (target == NULL) {
            cout << "[!] ID tidak ditemukan. Ulangi." << endl;
        }

    } while (target == NULL);

    cout << endl << "Tugas yang akan dihapus: \"" << target->data.judul << "\"" << endl << endl;

    char konfirm = inputKonfirm("Yakin ingin menghapus?");

    if (konfirm == 'y' || konfirm == 'Y') {
        hapusTugas(idHapus);
    } else {
        cout << endl << "[i] Penghapusan dibatalkan." << endl;
    }

    jedaLayar();
}

// input keyword lalu tampilkan hasil pencarian mata kuliah
void menuCari() {
    cout << "----- CARI TUGAS BERDASARKAN MATA KULIAH -----" << endl << endl;

    if (kosongList()) {
        cout << "Daftar tugas masih kosong." << endl;
        jedaLayar();
        return;
    }

    char keyword[30];

    inputTeks("Nama Mata Kuliah      : ", keyword, 30);

    cout << endl;
    cariMK(keyword);
    jedaLayar();
}

// urutkan list lalu tampilkan hasilnya
void menuUrut() {
    cout << "----- URUTKAN BERDASARKAN DEADLINE -----" << endl << endl;

    urutDeadline();
    cetakTugas();
    jedaLayar();
}

// simpan data ke file sebelum keluar
void menuKeluar() {
    cout << "Menyimpan data..." << endl;
    simpanFile();
    cout << endl << "Sampai jumpa!" << endl << endl;
    jedaLayar();
}

// muat data, tampilkan menu, dan proses pilihan hingga keluar
int main() {
    int pilihan;

    muatFile();

    do {
        tampilMenu();
        pilihan = inputPilihan();

        if (pilihan == -1) {
            continue;
        }

        bersihLayar();

        switch (pilihan) {
            case 1: menuLihat(); break;
            case 2: menuTambah(); break;
            case 3: menuUbah(); break;
            case 4: menuStatus(); break;
            case 5: menuHapus(); break;
            case 6: menuCari(); break;
            case 7: menuUrut(); break;
            case 0: menuKeluar(); break;
        }

    } while (pilihan != 0);

    return 0;
}
