// Nama [NIM] : Kanahaya Ezi     [124250046]
//              Failasufa Elsya  [124250050]
// Kelas      : SI - C
// Tema       : Sistem Manajemen Tugas Kuliah

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;

// -------------------------------------------------------
// HELPER
void clearScreen() { system("cls"); }

void pause() {
    cout << "\n  Tekan Enter untuk lanjut...";
    cin.sync(); cin.get();
}

string angkaKeStr(int n) { char b[20]; sprintf(b, "%d", n); return string(b); }

string getTanggalHariIni() {
    time_t t = time(0); tm* now = localtime(&t); char b[40];
    sprintf(b, "%04d-%02d-%02d", now->tm_year+1900, now->tm_mon+1, now->tm_mday);
    return string(b);
}

// positif = belum lewat, negatif = sudah lewat
int selisihHari(const string& dl, const string& hr) {
    int ty,tm2,td,dy,dm,dd;
    sscanf(dl.c_str(), "%d-%d-%d", &ty,&tm2,&td);
    sscanf(hr.c_str(), "%d-%d-%d", &dy,&dm, &dd);
    return (ty*365+tm2*30+td)-(dy*365+dm*30+dd);
}

// error handling: validasi format tanggal YYYY-MM-DD
bool validasiTanggal(const string& tgl) {
    if ((int)tgl.size()!=10 || tgl[4]!='-' || tgl[7]!='-') return false;
    for (int i=0;i<10;i++) {
        if (i==4||i==7) continue;
        if (tgl[i]<'0'||tgl[i]>'9') return false;
    }
    int b=atoi(tgl.substr(5,2).c_str()), d=atoi(tgl.substr(8,2).c_str());
    return (b>=1&&b<=12&&d>=1&&d<=31);
}

string prioritasStr(int p) { return p==1?"Tinggi":p==2?"Sedang":"Rendah"; }

void garis(int p, char c='-') { cout<<"  "; for(int i=0;i<p;i++) cout<<c; cout<<"\n"; }

// -------------------------------------------------------
// MAIN
int main() {
    cout << "Sistem Manajemen Tugas Kuliah" << endl;
    cout << "Program berhasil dijalankan." << endl;

    return 0;
}