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

int main() {
    cout << "Program Manajemen Tugas Kuliah" << endl;
    return 0;
}