#include <iostream>
#include <fstream>
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
mahasiswa kelas[100];
int jumlahMahasiswa, pertemuan=0;

void saveData(){
    ofstream dataNumerik;
    ofstream dataNama;
    dataNumerik.open("data.txt");
    dataNama.open("datanama.txt");
    dataNumerik << jumlahMahasiswa << endl;
    dataNumerik << pertemuan << endl;
    for(int i=0; i<jumlahMahasiswa; i++){
        dataNama << kelas[i].nama << endl;
        dataNumerik << kelas[i].nim << endl;
        dataNumerik << kelas[i].kehadiran << endl;
        dataNumerik << kelas[i].izin << endl;
        dataNumerik << kelas[i].sakit << endl;
        dataNumerik << kelas[i].alpa << endl;
    }
    dataNumerik.close();
    dataNama.close();
}

void loadData(){
    fstream dataNumerik;
    fstream dataNama;
    dataNumerik.open("data.txt");
    dataNama.open("datanama.txt");
    if(dataNumerik.is_open()){
        dataNumerik >> jumlahMahasiswa;
        dataNumerik >> pertemuan;
        if(jumlahMahasiswa>0){
            for(int i=0; i<jumlahMahasiswa; i++){
                getline(dataNama, kelas[i].nama);
                dataNumerik >> kelas[i].nim;
                dataNumerik >> kelas[i].kehadiran;
                dataNumerik >> kelas[i].izin;
                dataNumerik >> kelas[i].sakit;
                dataNumerik >> kelas[i].alpa;
            }
        }
    }
    dataNama.close();
    dataNumerik.close();
}

void sortByNim(){
    for (int i = 0; i < jumlahMahasiswa - 1; i++) {
        for (int j = 0; j < jumlahMahasiswa - i - 1; j++) {
            if (kelas[j].nim < kelas[j + 1].nim) {
                mahasiswa tempIndex = kelas[j];
                kelas[j] = kelas[j + 1];
                kelas[j + 1] = tempIndex;
            }
        }
    }
}

int searchByNim(long nim){
    int low = 0, high = jumlahMahasiswa - 1;
    while (low <= high) {
        int mid = (high + low) / 2;
        if (kelas[mid].nim == nim) {
            return mid;
        } else if (kelas[mid].nim < nim) {
            low = mid + 1;
        } else if (kelas[mid].nim > nim) {
            high = mid - 1;
        }
    }
    return -1;
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
            char confirmAdd;
            system("cls");
            loadData();
            cout << "JUMLAH MAHASISWA = " << jumlahMahasiswa << endl;
            sortByNim();
            // MENAMPILKAN DATA MAHASISWA START
            cout << "LIST MAHASISWA:\n";
            for(int i =0;i<jumlahMahasiswa;i++){
                cout<< i+1 << ". " << kelas[i].nama;
                cout << "(" << kelas[i].nim << ")\n";
            }
            cout <<"\n\nKonfirmasi Untuk Menambah Mahasiswa (Y/N) = ";
            cin  >> confirmAdd;
            cin.ignore();
            // MENAMBAH DATA MAHASISWA START
            if(confirmAdd == 'Y'||confirmAdd == 'y'){
                cout << "\nNama Mahasiswa: \n";
                getline(cin,kelas[jumlahMahasiswa].nama);
                cout << "\nNIM Mahasiswa: \n";
                cin >> kelas[jumlahMahasiswa].nim;
                cin.ignore();
                int response = searchByNim(kelas[jumlahMahasiswa].nim);
                if(response != -1){
                    cout << "\nMAHASISWA DENGAN NIM TERSEBUT SUDAH ADA\n\n";
                } else {
                    cout << "\nDATA BERHASIL DITAMBAH\n\n";
                    jumlahMahasiswa++;
                    saveData();
                }
            }
            system("pause");
            system("cls");
            break;
        case '2':
            long cariNim;
            char persetujuan;
            loadData();
            cout << "JUMLAH PERTEMUAN = " << pertemuan << endl;
            sortByNim();
            // MENAMPILKAN REKAP PRESENSI START
            for(int i=0; i<jumlahMahasiswa; i++){
                float persentase = kelas[i].kehadiran / pertemuan * 100;
                cout << "Nama : " << kelas[i].nama << endl;
                cout << "NIM : " << kelas[i].nim << endl;
                cout << "Persentase Kehadiran : " << persentase <<"%\n";
                cout << "Jumlah Kehadiran : " << kelas[i].kehadiran << endl;
                cout << "Jumlah Izin : "<<kelas[i].izin<<endl;
                cout << "Jumlah Sakit : "<<kelas[i].sakit<<endl;
                cout << "Jumlah Alpa : " << kelas[i].alpa<< "\n\n";
            }
            cout <<"Cari Mahasiswa Berdasarkan NIM? (Y/N) = ";
            cin >> persetujuan;
            cin.ignore();
            // FITUR MENCARI REKAP MAHASISWA START
            if (persetujuan == 'Y'|| persetujuan == 'y'){
                cout << "NIM Mahasiswa Yang Dicari = ";
                cin >> cariNim;
                cin.ignore();
                cout << "\n\n";
                int response = searchByNim(cariNim);
                if(response != -1){
                    cout << "Mahasiswa Ditemukan:\n";
                    cout << "Nama: " << kelas[response].nama << endl;
                    cout << "NIM : " << kelas[response].nim << endl;
                    cout << "Jumlah Izin : "<< kelas[response].izin<<endl;
                    cout << "Jumlah Sakit : "<< kelas[response].sakit<<endl;
                    cout << "Jumlah Alpa : " << kelas[response].alpa<< endl;
                    cout << "Jumlah Hadir: " << kelas[response].kehadiran << endl;
                    cout << "Persentase Kehadiran: " << (kelas[response].kehadiran/pertemuan*100)<<"%\n\n";
                } else {
                    cout << "Mahasiswa Tidak Ditemukan\n\n";
                }
            }
            system("pause");
            system("cls");
            break;
        case '3':
            loadData();
            sortByNim();
            // FITUR PRESENSI
            for(int i=0; i<jumlahMahasiswa; i++){
                char presensi;
                cout << "Nama: " << kelas[i].nama;
                cout << " (" << kelas[i].nim <<")\n";
                cout << "H/I/S/A = ";
                cin >> presensi;
                cin.ignore();
                if(presensi=='H' || presensi=='h'){
                    kelas[i].kehadiran++;
                } else if(presensi=='I' || presensi=='i'){
                    kelas[i].izin++;
                } else if(presensi=='S' || presensi=='s'){
                    kelas[i].sakit++;
                } else if(presensi=='A' || presensi=='a'){
                    kelas[i].alpa++;
                }
                cout << "\n\n";
            }
            pertemuan++;
            saveData();
            system("pause");
            system("cls");
            break;
        case '4':
            exit(0);
        default :
            cout << "Pilih Menu Sesuai Pilihan Di Atas!\n\n";
            system("pause");
            system("cls");
            break;
        }
    } while (true);
    return 0;
}
