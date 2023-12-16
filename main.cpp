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

void saveData(){
    fstream extFile;
    extFile.open("data.txt");
    extFile << counter << endl;
    if(extFile.is_open()){
        for(int i=0; i<counter; i++){
            extFile << kelasa[i].nama << endl;
            extFile << kelasa[i].nim << endl;
            extFile << kelasa[i].kehadiran << endl;
            extFile << kelasa[i].izin << endl;
            extFile << kelasa[i].sakit << endl;
            extFile << kelasa[i].alpa << endl;
        }
        extFile.close();
        cout << "\n\nData Berhasil Disimpan!\n\n";
    } else {
        cout << "\n\nFile Tidak Ditemukan!\n\n";
    }
}

void loadData(){
    fstream extFile;
    extFile.open("data.txt");
    if(extFile.is_open()){
        extFile >> counter;
        if(counter>0){
            for(int i=0; i<counter; i++){
                extFile >> kelasa[i].nama;
                extFile >> kelasa[i].nim;
                extFile >> kelasa[i].kehadiran;
                extFile >> kelasa[i].izin;
                extFile >> kelasa[i].sakit;
                extFile >> kelasa[i].alpa;
            }
            extFile.close();
            cout << "\n\nData Berhasil Dimuat!\n\n";
        } else {
            cout << "\n\nDatabase Kosong!\n\n";
        }
    } else {
        cout << "\n\nFile Tidak Ditemukan!\n\n";
    }
}
int main()
{
    char menuSelect, dashSelect;
    do{
        cout << "JUMLAH PERTEMUAN = " << pertemuan << endl;
        cout << "JUMLAH MAHASISWA = " << counter << endl;
        cout << "======== MENU =======\n";
        cout << "1. DASHBOARD\n";
        cout << "2. REKAP PRESENSI\n";
        cout << "3. KELUAR\n";
        cout << "PILIH MENU = ";
        cin >> menuSelect;
        cin.ignore();
        cout << "\n\n";
        switch(menuSelect){
        case '1':
            do{
                cout << "======== DASHBOARD =======\n";
                cout << "1. TAMBAH DATA MAHASISWA\n";
                cout << "2. PRESENSI MAHASISWA\n";
                cout << "3. SIMPAN DATA MAHASISWA\n";
                cout << "4. MUAT DATA MAHASISWA\n";
                cout << "5. KEMBALI\n";
                cout << "PILIH MENU = ";
                cin >> dashSelect;
                cin.ignore();
                cout << "\n\n";

                if(dashSelect == '1'){
                    addMahasiswa();
                    system("pause");
                    system("cls");
                } else if(dashSelect == '2'){
                    addPresensi();
                    system("pause");
                    system("cls");
                } else if(dashSelect == '3'){
                    saveData();
                    system("pause");
                    system("cls");
                } else if(dashSelect == '4'){
                    loadData();
                    system("pause");
                    system("cls");
                } else if(dashSelect == '5'){
                    break;
                }
            } while(true);
            break;
        case '2':
            showRekap();
            system("pause");
            system("cls");
            break;
        case '3':
            exit(0);
        }
    } while (true);
    return 0;
}
