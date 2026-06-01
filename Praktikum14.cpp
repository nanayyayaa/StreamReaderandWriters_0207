#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <string>

using namespace std;

class TokoElektronik {
private:
    array<string, 3> barang;

public:
    TokoElektronik() {
        barang[0] = "Laptop";
        barang[1] = "Handphone";
        barang[2] = "Printer";
    }

    string ambilBarang(size_t nomorRak) {
        try {
            return barang.at(nomorRak);
        }
        catch (out_of_range&) {
            throw string("Gagal Mengambil Barang : Rak nomor " +
                         to_string(nomorRak) +
                         " kosong atau tidak tersedia!");
        }
    }
};

int main() {
    TokoElektronik toko;
    int pilihan;

    do {
        cout << "\n===== TOKO ELEKTRONIK GIBRAN JAYA =====" << endl;

        // READ
        cout << "\nData Barang di Gudang :" << endl;
        ifstream baca("gudang.txt");
        string data;
        int no = 1;

        while (getline(baca, data)) {
            cout << no << ". " << data << endl;
            no++;
        }
        baca.close();

        cout << "\nMenu :" << endl;
        cout << "1. Tambah Barang" << endl;
        cout << "2. Update Barang" << endl;
        cout << "3. Hapus Barang" << endl;
        cout << "4. Simulasi Etalase" << endl;
        cout << "5. Keluar" << endl;
        cout << "Pilihan : ";
        cin >> pilihan;
        cin.ignore();

        if (pilihan == 1) {
            // CREATE
            ofstream tulis("gudang.txt", ios::app);

            string barangBaru;
            cout << "Masukkan nama barang : ";
            getline(cin, barangBaru);

            tulis << barangBaru << endl;
            tulis.close();

            cout << "Barang berhasil ditambahkan." << endl;
        }

        else if (pilihan == 2) {
            // UPDATE
            vector<string> daftarBarang;

            ifstream baca("gudang.txt");
            while (getline(baca, data)) {
                daftarBarang.push_back(data);
            }
            baca.close();

            int nomor;
            cout << "Nomor barang yang ingin diubah : ";
            cin >> nomor;
            cin.ignore();

            if (nomor >= 1 && nomor <= daftarBarang.size()) {
                cout << "Nama barang baru : ";
                getline(cin, data);

                daftarBarang[nomor - 1] = data;

                ofstream tulis("gudang.txt");

                for (int i = 0; i < daftarBarang.size(); i++) {
                    tulis << daftarBarang[i] << endl;
                }

                tulis.close();
                cout << "Data berhasil diupdate." << endl;
            }
            else {
                cout << "Nomor tidak ditemukan." << endl;
            }
        }

        else if (pilihan == 3) {
            // DELETE
            vector<string> daftarBarang;

            ifstream baca("gudang.txt");
            while (getline(baca, data)) {
                daftarBarang.push_back(data);
            }
            baca.close();

            int nomor;
            cout << "Nomor barang yang ingin dihapus : ";
            cin >> nomor;

            if (nomor >= 1 && nomor <= daftarBarang.size()) {
                daftarBarang.erase(daftarBarang.begin() + nomor - 1);

                ofstream tulis("gudang.txt");

                for (int i = 0; i < daftarBarang.size(); i++) {
                    tulis << daftarBarang[i] << endl;
                }

                tulis.close();
                cout << "Data berhasil dihapus." << endl;
            }
            else {
                cout << "Nomor tidak ditemukan." << endl;
            }
        }

        else if (pilihan == 4) {
            cout << "\n=== Simulasi Etalase ===" << endl;

            try {
                cout << "Skenario 1 (Rak 1)" << endl;
                cout << "Barang : " << toko.ambilBarang(1) << endl;
            }
            catch (string pesan) {
                cout << pesan << endl;
            }

            try {
                cout << "\nSkenario 2 (Rak 5)" << endl;
                cout << "Barang : " << toko.ambilBarang(5) << endl;
            }
            catch (string pesan) {
                cout << pesan << endl;
            }
        }

    } while (pilihan != 5);

    cout << "\nProgram selesai." << endl;

    return 0;
}