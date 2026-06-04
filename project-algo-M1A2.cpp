#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
using namespace std;

struct Barang {
    string ID_Barang;
    string Nama_Barang;
    string Kategori;
    int Stok;
    int Harga_Barang;
};

vector<Barang> inventaris;
string namaFile = "inventaristoko.csv";

int ambilAngkaID(string id) {
    string kumpulAngka = "";
    
    for (char c : id) {
        if (isdigit(c)) {
            kumpulAngka += c;
        }
    }
    
    try {
        if (kumpulAngka.empty()) return -1;
        return stoi(kumpulAngka);
    } catch (...) {
        return -1; 
    }
}

string formatRupiah(int nominal) {
    string hasil = to_string(nominal);
    int panjang = hasil.length();
    
    for (int i = panjang - 3; i > 0; i -= 3) {
        hasil.insert(i, ".");
    }
    return "Rp" + hasil;
}

bool apakahLebihKecil(string a, string b) {
    int angkaA = ambilAngkaID(a);
    int angkaB = ambilAngkaID(b);
    
    if (angkaA != angkaB) {
        return angkaA < angkaB;
    }
    return a < b; 
}

void urutkanInventarisInsertionSort() {
    int n = (int)inventaris.size();
    for (int i = 1; i < n; i++) {
        Barang key = inventaris[i];
        int j = i - 1;

        while (j >= 0 && apakahLebihKecil(key.ID_Barang, inventaris[j].ID_Barang)) {
            inventaris[j + 1] = inventaris[j];
            j = j - 1;
        }
        inventaris[j + 1] = key;
    }
}

void bacaDataCSV() {
    ifstream file(namaFile); 
    string baris, id, nama,kategori, stok_str, harga_str;

    if (!file.is_open() || file.peek() == std::ifstream::traits_type::eof()) {
        if (file.is_open()) file.close(); 

        cout << "[WARNING]: File " << namaFile << " tidak ditemukan atau kosong!" << endl;
        cout << "[SYSTEM]: Membuat File Inventaris Toko ..." << endl;
        
        ofstream fileBaru(namaFile);
        // for (int i = 1; i <= 500; i++) {
        //     string idGen = "BRG" + to_string(i);
        //     string namaGen = "Barang_Toko_" + to_string(i);
        //     string kategoriUmum = "Random" + to_string(i);
        //     int stokGen = ((rand() %1000) + 5) * 1000;
        //     int hargaGen = ((rand() % 100) + 5) * 1000; 
            
        //     fileBaru << "BRG" << i << "," << "Barang_Toko_" << i << "," << "KategoriUmum" << "," << stokGen << "," << hargaGen << "\n";
        // }
        // fileBaru.close();
        cout << "[SYSTEM]: File Inventaris Toko berhasil dibuat!\n" << endl;
        
        file.open(namaFile);
    }

    while (getline(file, baris)) {
        stringstream ss(baris); 
        getline(ss, id, ',');
        getline(ss, nama, ',');
        getline(ss, kategori, ',');
        getline(ss, stok_str, ',');
        getline(ss, harga_str, ',');

        if (!id.empty() && !nama.empty() && !kategori.empty() && !stok_str.empty() && !harga_str.empty()) {
            Barang barangBaru;
            barangBaru.ID_Barang = id;
            barangBaru.Nama_Barang = nama;
            barangBaru.Kategori = kategori;
            barangBaru.Stok = (stok_str.find_first_not_of("0123456789") == string::npos) ? stoi(stok_str) : 0; 
            barangBaru.Harga_Barang = (harga_str.find_first_not_of("0123456789") == string::npos) ? stoi(harga_str) : 0; 
            inventaris.push_back(barangBaru); 
        }
    }
    file.close();
    
    urutkanInventarisInsertionSort();
}

void simpanDataCSV() {
    ofstream file(namaFile); 

    if (!file.is_open()) {
        cout << "[ERROR]: Gagal menyimpan file " << namaFile << " !" << endl;
        return;
    }

    for (const auto& item : inventaris) {
        file << item.ID_Barang << "," 
             << item.Nama_Barang << "," 
             << item.Kategori << ","
             << item.Stok << ","
             << item.Harga_Barang << "\n";
    }
    
    file.close();
    cout << "[SYSTEM]: Mantap! " << inventaris.size() << " data berhasil diamankan ke " << namaFile << "." << endl;
}

void cariBarangBinarySearch() {
    if (inventaris.empty()) {
        cout << "[ERROR]: Inventaris kosong, gak ada yang bisa dicari!" << endl;
        return;
    }

    string targetID;
    cout << "\n=== CARI BARANG ===" << endl;
    cout << "Masukkan ID Barang (contoh: BRG50): ";
    getline(cin, targetID);

    int kiri = 0;
    int kanan = (int)inventaris.size() - 1;
    bool ketemu = false;

    while (kiri <= kanan) {
        int tengah = kiri + (kanan - kiri) / 2;

        if (inventaris[tengah].ID_Barang == targetID) {
            cout << "\n[SYSTEM]: Barang Ditemukan!" << endl;
            cout << "ID    : " << inventaris[tengah].ID_Barang << endl;
            cout << "Nama  : " << inventaris[tengah].Nama_Barang << endl;
            cout << "Kategori : " << inventaris[tengah].Kategori << endl;
            cout << "Stok     : " << inventaris[tengah].Stok << " pcs" << endl;
            cout << "Harga : " << formatRupiah(inventaris[tengah].Harga_Barang) << endl; 
            ketemu = true;
            break;
        }

        else if (apakahLebihKecil(inventaris[tengah].ID_Barang, targetID)) {
            kiri = tengah + 1;
        }
        else {
            kanan = tengah - 1;
        }
    }

    if (!ketemu) {
        cout << "\n[ERROR]: Barang dengan ID '" << targetID << "' tidak ditemukan!" << endl;
    }
}

void tambahBarangDenganInsertionSort() {
    Barang barangBaru;
    
    cout << "\n=== TAMBAH BARANG MASUK ===" << endl;
    cout << "Masukkan ID Barang (contoh: BRG501): ";
    getline(cin, barangBaru.ID_Barang);
    
    // Validasi Duplikat Normal
    for (const auto& item : inventaris) {
        if (item.ID_Barang == barangBaru.ID_Barang) {
            cout << "[ERROR]: ID Barang sudah ada di database! Gagal menambahkan." << endl;
            return;
        }
    }
    
    cout << "Masukkan Nama Barang: ";
    getline(cin, barangBaru.Nama_Barang);

    cout << "Masukkan Kategori    : ";
    getline(cin, barangBaru.Kategori);

    string stokInput;
    bool stokValid = false;
    while (!stokValid) {
        cout << "Masukkan Jumlah Stok (Masukkan Angka Saja, Misal 15): ";
        getline(cin, stokInput);
        string stokBersih = "";
        
        for (char c : stokInput) {
            if (isdigit(c)) stokBersih += c;
        }
        
        if (stokBersih.empty()) {
            cout << "[ERROR]: Gunakan Angka!\n";
        } else {
            try {
                barangBaru.Stok = stoi(stokBersih);
                stokValid = true;
            } catch (...) {
                cout << "[ERROR]: Jumlah stoknya terlalu banyak!\n";
            }
        }
    }

    string hargaInput;
    bool hargaValid = false;

    while (!hargaValid) {
        cout << "Masukkan Harga Barang (Boleh pakai titik/koma, misal 25.000): ";
        getline(cin, hargaInput);

        string hargaBersih = "";
        
        for (char c : hargaInput) {
            if (isdigit(c)) {
                hargaBersih += c;
            }
        }

        if (hargaBersih.empty()) {
            cout << "[ERROR]: Gunakan Angka!\n";
        } else {
            try {
                barangBaru.Harga_Barang = stoi(hargaBersih);
                hargaValid = true;
            } catch (...) {
                cout << "[ERROR]: Angka terlalu besar!\n";
            }
        }
    }

    inventaris.push_back(barangBaru);

    urutkanInventarisInsertionSort();
    
    cout << "[SYSTEM]: Barang berhasil ditambahkan dan database telah diurutkan ulang!" << endl;
}

void tampilkanInventaris() {
    if (inventaris.empty()) {
        cout << "Inventaris kosong" << endl;
        return;
    }
    cout << "\n=== DAFTAR BARANG TOKO JALLALUDIN ===" << endl;
    for (const auto& item : inventaris) {
        cout << "ID: " << item.ID_Barang 
             << " | Nama: " << item.Nama_Barang 
             << " | Kategori: " << item.Kategori
             << " | Stok: " << item.Stok << " pcs"
             << " | Harga: " << formatRupiah(item.Harga_Barang) << endl;
    }
}

void hapusBarang() {
    if (inventaris.empty()) {
        cout << "[ERROR]: Inventaris kosong, tidak ada yang dihapus!" << endl;
        return;
    }

    string targetID;
    cout << "\n=== HAPUS BARANG ===" << endl;
    cout << "Masukkan ID Barang (contoh: BRG50): ";
    getline (cin, targetID);

    bool ketemu = false;
    for (auto it = inventaris.begin(); it != inventaris.end(); ++it) {
        if (it->ID_Barang == targetID) {
            cout << "[SISTEM]: Sayonara! Barang '" << it->Nama_Barang << "' (Harga: " << formatRupiah(it->Harga_Barang) << ") resmi dihapus dari gudang!" << endl;
            inventaris.erase(it); 
            ketemu = true;
            break;
        }
    }

    if (!ketemu) {
        cout << "\n[ERROR]: Barang dengan ID '" << targetID << "' tidak ditemukan!" << endl;
    }
}

void ubahdataBarang() {
    if (inventaris.empty()) {
        cout << "[ERROR]: Inventaris kosong, tidak ada yang bisa diubah!" << endl;
        return;
    }

    string targetID;
    cout << "\n=== UBAH DATA BARANG ===" << endl;
    cout << "Masukkan ID Barang yang ingin diubah (contoh: BRG50): ";
    getline(cin, targetID);

    auto it = find_if(inventaris.begin(), inventaris.end(), [&](const Barang& b) {
        return b.ID_Barang == targetID;
    });

    if (it == inventaris.end()) {
        cout << "\n[ERROR]: Barang dengan ID '" << targetID << "' tidak ditemukan!" << endl;
        return;
    }

    cout << "Masukkan Nama Baru (kosongkan jika tidak ingin mengubah): ";
    string namaBaru;
    getline(cin, namaBaru);
    if (!namaBaru.empty()) it->Nama_Barang = namaBaru;

    cout << "Masukkan Kategori Baru (kosongkan jika tidak ingin mengubah): ";
    string kategoriBaru;
    getline(cin, kategoriBaru);
    if (!kategoriBaru.empty()) it->Kategori = kategoriBaru;

    string stokInput;
    cout << "Masukkan Jumlah Stok Baru (kosongkan jika tidak ingin mengubah): ";
    getline(cin, stokInput);
    if (!stokInput.empty()) {
        string stokBersih = "";
        for (char c : stokInput) {
            if (isdigit(c)) stokBersih += c;
        }
        if (!stokBersih.empty()) {
            try {
                it->Stok = stoi(stokBersih);
            } catch (...) {
                cout << "[ERROR]: Jumlah stoknya terlalu banyak! Stok tidak diubah.\n";
            }
        } else {
            cout << "[ERROR]: Gunakan Angka! Stok tidak diubah.\n";
        }
    }

    string hargaInput;
    cout << "Masukkan Harga Baru (kosongkan jika tidak ingin mengubah): ";
    getline(cin, hargaInput);
    if (!hargaInput.empty()) {
        string hargaBersih = "";
        for (char c : hargaInput) {
            if (isdigit(c)) hargaBersih += c;
        }
        if (!hargaBersih.empty()) {
            try {
                it->Harga_Barang = stoi(hargaBersih);
            } catch (...) {
                cout << "[ERROR]: Angka terlalu besar! Harga tidak diubah.\n";
            }
        } else {
            cout << "[ERROR]: Gunakan Angka! Harga tidak diubah.\n";
        }
    }

    cout << "[SYSTEM]: Data barang dengan ID '" << targetID << "' berhasil diperbarui!" << endl;
}

void generateSeribuDataDummy() {
    inventaris.clear(); 
    
    cout << "\n[SISTEM]: Memulai proses pabrikasi 100 data dummy ke dalam memori..." << endl;
    
    for (int i = 1; i <= 100; i++) {
        Barang b;
        b.ID_Barang = "BRG" + to_string(i);
        b.Nama_Barang = "Barang_Ghaib_" + to_string(i);
        b.Kategori = "Sesuatu" + to_string(i);
        b.Stok = ((rand() % 1000) + 1) * 100;
        b.Harga_Barang = ((rand() % 1000) + 1) * 100; 
        
        inventaris.push_back(b);
    }
    
    urutkanInventarisInsertionSort();
    
    cout << "[SISTEM]: ALHAMDULILLAH! 100 Data Dummy berhasil diciptakan dan masuk memori!" << endl;
    cout << "[SISTEM]: Cek Menu 2 buat ngeliat hasilnya, lalu tekan Menu 5 buat nyimpen permanen ke CSV!\n" << endl;
}

int main() {
    cout << "Memuat data dari database CSV..." << endl;
    bacaDataCSV();
    
    if (!inventaris.empty()) {
        cout << "[SISTEM]: Berhasil memuat " << inventaris.size() << " barang ke dalam memori.\n" << endl;
    }
    
    int pilihan;
    bool lanjut = true;
    
    while (lanjut) {
        cout << "\n==== SISTEM INVENTARIS TOKO JALLALUDIN ====" << endl;
        cout << "1. Tambah Barang Masuk" << endl;
        cout << "2. Lihat Semua Inventaris" << endl;
        cout << "3. Cari Barang" << endl;
        cout << "4. Hapus Barang" << endl;
        cout << "5. Update Barang" << endl;
        cout << "6. Keluar & Simpan Data" << endl;
        cout << "7. [DEV] Generate 100 Data Dummy" << endl; 
        cout << "Pilih menu (1-7): ";
        
        while (!(cin >> pilihan)) { 
            cout << "[ERROR]: Pilih menu (1-7)! ";
            cin.clear(); 
            cin.ignore(10000, '\n'); 
        }
        cin.ignore(); 
        
        if (pilihan == 1) {
            tambahBarangDenganInsertionSort();
        } else if (pilihan == 2) {
            tampilkanInventaris();
        } else if (pilihan == 3) {
            cariBarangBinarySearch();
        } else if (pilihan == 4) {
            hapusBarang(); 
        } else if (pilihan == 5) {
            ubahdataBarang(); 
        } else if (pilihan == 6) {
            simpanDataCSV();
            cout << "Menyimpan data..." << endl;
            lanjut = false;
        } else if (pilihan == 7) {               
            generateSeribuDataDummy();           
        } else {
            cout << "[ERROR]: Pilih menu (1-7)!" << endl;
        }
    }
    return 0;
}
