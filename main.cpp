/* BUG:
1. NAMA SAAT MELOAD DATA TIDAK BISA MEMBACA SPASI
2. BELUM ADA POINT KE 5 (SORTING/SEARCH/POINTER)
3. MERAPIHKAN KODINGAN
*/
#include <iostream>
#include <fstream>
#include <conio.h>
#include <cstdlib>
using namespace std;

struct mahasiswa{
    string nama;
    long nim;
    float kehadiran;
    int izin;
    int sakit;
    int alpa;
};
mahasiswa kelasa[100];
int counter, pertemuan=0;

void addMahasiswa(){
    cout << "\nNama Mahasiswa: \n";
    getline(cin, kelasa[counter].nama).ignore();
    cin.ignore();
    cout << "\nNIM Mahasiswa: \n";
    cin >> kelasa[counter].nim;
    cin.ignore();
    cout << "\nDATA BERHASIL DITAMBAH\n\n";
    counter++;
}

void showRekap(){
    for(int i=0; i<counter; i++){
        float persentase = kelasa[i].kehadiran / pertemuan * 100;
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
        cin.ignore();
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
    ofstream extFile;
    extFile.open("data.txt");
    extFile << counter << endl;
    extFile << pertemuan << endl;
    for(int i=0; i<counter; i++){
        extFile << kelasa[i].nama << endl;
        extFile << kelasa[i].nim << endl;
        extFile << kelasa[i].kehadiran << endl;
        extFile << kelasa[i].izin << endl;
        extFile << kelasa[i].sakit << endl;
        extFile << kelasa[i].alpa << endl;
    }
    extFile.close();
}

void loadData(){
    fstream extFile;
    extFile.open("data.txt");
    if(extFile.is_open()){
        extFile >> counter;
        extFile >> pertemuan;
        if(counter>0){
            for(int i=0; i<counter; i++){
                extFile >> kelasa[i].nama;
                extFile >> kelasa[i].nim;
                extFile >> kelasa[i].kehadiran;
                extFile >> kelasa[i].izin;
                extFile >> kelasa[i].sakit;
                extFile >> kelasa[i].alpa;
            }
        }
    }
    extFile.close();
}

void deleteMahasiswa(){
    string namatoDelete;
    cout << "Masukkan Nama Mahasiswa yang Ingin Dihapus: ";
    getline(cin, namatoDelete);

    int indexToDelete = -1;
    for(int i=0; i<counter; i++){
        if(kelasa[i].nama == namatoDelete){
            indexToDelete = i;
            break;
        }
    }

    if(indexToDelete != -1){
        // Geser elemen array untuk menutup celah
        for(int i=indexToDelete; i<counter-1; i++){
            kelasa[i] = kelasa[i+1];
        }
        counter--;
        cout << "Data Mahasiswa Berhasil Dihapus!\n\n";
    } else {
        cout << "Mahasiswa dengan Nama Tersebut Tidak Ditemukan.\n\n";
    }
}

void dataMahasiswa(){
    cout << "LIST MAHASISWA:\n";
    for(int i =0;i<counter;i++){
        cout<< i+1 << ". " << kelasa[i].nama;
        cout << "(" << kelasa[i].nim << ")\n";
    }
}


int main()
{
    char menuSelect;
    do{
        cout << "======== MENU =======\n";
        cout << "1. MENAMBAH DATA MAHASISWA\n";
        cout << "2. REKAP PRESENSI\n";
        cout << "3. PRESENSI MAHASISWA\n";
        cout << "4. KELUAR\n";
        cout << "PILIH MENU = ";
        cin >> menuSelect;
        cin.ignore();
        cout << "\n\n";
        switch(menuSelect){
        case '1':
            char confirm;
            system("cls");
            loadData();
            cout << "JUMLAH MAHASISWA = " << counter << endl;
            dataMahasiswa();
            cout <<"\n\nMasukkan data mahasiswa? (y/n) = ";
            cin  >> confirm;
            cin.ignore();
            if(confirm == 'Y'||confirm == 'y'){
                addMahasiswa();
                saveData();
                system("pause");
                system("cls");
                break;
            } else {
                system("cls");
                break;
            }
        case '2':
            loadData();
            cout << "JUMLAH PERTEMUAN = " << pertemuan << endl;
            showRekap();
            system("pause");
            system("cls");
            break;
        case '3':
            loadData();
            addPresensi();
            saveData();
            system("pause");
            system("cls");
            break;
        case '4':
            exit(0);
        }
    } while (true);
    return 0;
}
