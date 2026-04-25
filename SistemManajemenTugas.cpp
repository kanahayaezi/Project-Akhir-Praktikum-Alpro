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

void garis(int p, char c='-') { cout<<"  "; for(int i=0;i<p;i++) cout<<c; cout<<"\n"; }

// -------------------------------------------------------
// MAIN
int main() {
    cout << "Sistem Manajemen Tugas Kuliah" << endl;
    cout << "Program berhasil dijalankan." << endl;

    return 0;
}