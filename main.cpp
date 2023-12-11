#include <iostream>
#include <fstream>
#include <conio.h>
#include <cstdlib>
using namespace std;

struct mahasiswa{
    string nama;
    long nim;
    int kehadiran;
    int izin;
    int sakit;
    int alpa;
};
mahasiswa kelasa[40];
int counter, pertemuan=1;
void addMahasiswa(){
    cout << "\nNama Mahasiswa: \n";
    getline(cin, kelasa[counter].nama);
    cout << "\nNIM Mahasiswa: \n";
    cin >> kelasa[counter].nim;
    cout << "\nDATA BERHASIL DITAMBAH\n\n";
    counter++;
}

void showRekap(){
    for(int i=0; i<counter; i++){
        int persentase = kelasa[i].kehadiran / 10 * 100;
        cout << "Nama : " << kelasa[i].nama << endl;
        cout << "NIM : " << kelasa[i].nim << endl;
        cout << "Jumlah Kehadiran : " << kelasa[i].kehadiran << endl;
        cout << "Persentase Kehadiran : " << persentase <<"%";
        cout << endl << endl;
    }
}

void addPresensi(){
    for(int i=0; i<counter; i++){
        char presensi;
        cout << "Nama: " << kelasa[i].nama;
        cout << " (" << kelasa[i].nim <<")\n";
        cout << "H/I/S/A = ";
        cin >> presensi;
        if(presensi=='H'){
            kelasa[i].kehadiran++;
        } else if(presensi=='I'){
            kelasa[i].izin++;
        } else if(presensi=='S'){
            kelasa[i].sakit++;
        } else if(presensi=='A'){
            kelasa[i].alpa++;
        }
        cout << "\n\n";
    }
    pertemuan++;
}
int main()
{
    char menuSelect;
    do{
        cout << "JUMLAH PERTEMUAN = " << pertemuan << endl;
        cout << "======== MENU =======\n";
        cout << "1. TAMBAHKAN DATA MAHASISWA\n";
        cout << "2. PRESENSI MAHASISWA\n";
        cout << "3. TAMPILKAN REKAP PRESENSI\n";
        cout << "4. SIMPAN DATA\n";
        cout << "PILIH MENU = ";
        menuSelect = getche();
        cin.ignore();
        cout << "\n\n";
        switch(menuSelect){
        case '1':
            addMahasiswa();
            system("pause");
            system("cls");
            break;
        case '2':
            addPresensi();
            system("pause");
            system("cls");
            break;
        case '3':
            showRekap();
            system("pause");
            system("cls");
            break;
        }
    } while (menuSelect != 27);
    return 0;
}
