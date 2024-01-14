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
mahasiswa kelasa[100];
int counter, pertemuan=0;

void saveData(){
    ofstream extFile;
    ofstream namaFile;
    extFile.open("data.txt");
    namaFile.open("datanama.txt");
    extFile << counter << endl;
    extFile << pertemuan << endl;
    for(int i=0; i<counter; i++){
        //extFile << kelasa[i].nama << endl;
        namaFile << kelasa[i].nama << endl;
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
    fstream namaFile;
    extFile.open("data.txt");
    namaFile.open("datanama.txt");
    if(extFile.is_open()){
        extFile >> counter;
        extFile >> pertemuan;
        if(counter>0){
            for(int i=0; i<counter; i++){
                getline(namaFile, kelasa[i].nama);
                extFile >> kelasa[i].nim;
                extFile >> kelasa[i].kehadiran;
                extFile >> kelasa[i].izin;
                extFile >> kelasa[i].sakit;
                extFile >> kelasa[i].alpa;
            }
        }
    }
    namaFile.close();
    extFile.close();
}

void bubblesortNIM(){
    for (int i = 0; i < counter - 1; i++) {
        for (int j = 0; j < counter - i - 1; j++) {
            if (kelasa[j].nim > kelasa[j + 1].nim) {
                mahasiswa temp = kelasa[j];
                kelasa[j] = kelasa[j + 1];
                kelasa[j + 1] = temp;
            }
        }
    }
}

int binarysearchNIM(long targetNIM){
    int left = 0, right = counter - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (kelasa[mid].nim == targetNIM) {
            return mid;
        } else if (kelasa[mid].nim < targetNIM) {
            left = mid + 1;
        } else {
            right = mid - 1;
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
            char confirm;
            system("cls");
            loadData();
            cout << "JUMLAH MAHASISWA = " << counter << endl;
            bubblesortNIM();
            // MENAMPILKAN DATA MAHASISWA START
            cout << "LIST MAHASISWA:\n";
            for(int i =0;i<counter;i++){
                cout<< i+1 << ". " << kelasa[i].nama;
                cout << "(" << kelasa[i].nim << ")\n";
            }
            cout <<"\n\nKonfirmasi Untuk Menambah Mahasiswa (Y/N) = ";
            cin  >> confirm;
            cin.ignore();
            // MENAMBAH DATA MAHASISWA START
            if(confirm == 'Y'||confirm == 'y'){
                cout << "\nNama Mahasiswa: \n";
                getline(cin,kelasa[counter].nama);
                cout << "\nNIM Mahasiswa: \n";
                cin >> kelasa[counter].nim;
                cin.ignore();
                int searchNIM = binarysearchNIM(kelasa[counter].nim);
                if(searchNIM != -1){
                    cout << "\nMAHASISWA DENGAN NIM TERSEBUT SUDAH ADA\n\n";
                } else {
                    cout << "\nDATA BERHASIL DITAMBAH\n\n";
                    counter++;
                    saveData();
                }
            }
            system("pause");
            system("cls");
            break;
        case '2':
            long targetNIM;
            char persetujuan;
            cout << "JUMLAH PERTEMUAN = " << pertemuan << endl;
            loadData();
            bubblesortNIM();
            // MENAMPILKAN REKAP PRESENSI START
            for(int i=0; i<counter; i++){
                float persentase = kelasa[i].kehadiran / pertemuan * 100;
                cout << "Nama : " << kelasa[i].nama << endl;
                cout << "NIM : " << kelasa[i].nim << endl;
                cout << "Persentase Kehadiran : " << persentase <<"%\n";
                cout << "Jumlah Kehadiran : " << kelasa[i].kehadiran << endl;
                cout << "Jumlah Izin : "<<kelasa[i].izin<<endl;
                cout << "Jumlah Sakit : "<<kelasa[i].sakit<<endl;
                cout << "Jumlah Alpa : " << kelasa[i].alpa<< "\n\n";
            }
            cout <<"Cari Mahasiswa Berdasarkan NIM? (Y/N) = ";
            cin >> persetujuan;
            cin.ignore();
            // FITUR MENCARI REKAP MAHASISWA START
            if (persetujuan == 'Y'|| persetujuan == 'y'){
                cout << "NIM Mahasiswa Yang Dicari = ";
                cin >> targetNIM;
                cin.ignore();
                cout << "\n\n";
                int searchNIM = binarysearchNIM(targetNIM);
                if(searchNIM != -1){
                    cout << "Mahasiswa Ditemukan:\n";
                    cout << "Nama: " << kelasa[searchNIM].nama << endl;
                    cout << "NIM : " << kelasa[searchNIM].nim << endl;
                    cout << "Jumlah Izin : "<< kelasa[searchNIM].izin<<endl;
                    cout << "Jumlah Sakit : "<< kelasa[searchNIM].sakit<<endl;
                    cout << "Jumlah Alpa : " << kelasa[searchNIM].alpa<< endl;
                    cout << "Jumlah Hadir: " << kelasa[searchNIM].kehadiran << endl;
                    cout << "Persentase Kehadiran: " << (kelasa[searchNIM].kehadiran/pertemuan*100)<<"%\n\n";
                } else {
                    cout << "Mahasiswa Tidak Ditemukan\n\n";
                }
            }
            system("pause");
            system("cls");
            break;
        case '3':
            loadData();
            bubblesortNIM();
            // FITUR PRESENSI
            for(int i=0; i<counter; i++){
                char presensi;
                cout << "Nama: " << kelasa[i].nama;
                cout << " (" << kelasa[i].nim <<")\n";
                cout << "H/I/S/A = ";
                cin >> presensi;
                cin.ignore();
                if(presensi=='H' || presensi=='h'){
                    kelasa[i].kehadiran++;
                } else if(presensi=='I' || presensi=='i'){
                    kelasa[i].izin++;
                } else if(presensi=='S' || presensi=='s'){
                    kelasa[i].sakit++;
                } else if(presensi=='A' || presensi=='a'){
                    kelasa[i].alpa++;
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
