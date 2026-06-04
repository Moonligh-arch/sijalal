#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream> 
#include <cstdlib>

using namespace std;

// 1. Setup Struct
struct Barang {
    string ID_Barang;
    string Nama_Barang;
    string Kategori;
    int Stok;
    int Harga_Barang;
};

// 2. Vector & File Name (Pake extern biar ramah GUI & ga memicu C7525)
extern vector<Barang> inventaris;
extern string namaFile;

// Fungsi sakti v2.0 (Anti Spasi & Anti Huruf Bebas)
inline int ambilAngkaID(string id) {
    string kumpulAngka = "";
    for (char c : id) {
        if (isdigit(c)) {
            kumpulAngka += c;
        }
    }
    try {
        if (kumpulAngka.empty()) return -1;
        return stoi(kumpulAngka);
    }
    catch (...) {
        return -1;
    }
}

// Fungsi kosmetik buat nambahin titik di duit
inline string formatRupiah(int nominal) {
    string hasil = to_string(nominal);
    int panjang = hasil.length();
    for (int i = panjang - 3; i > 0; i -= 3) {
        hasil.insert(i, ".");
    }
    return "Rp" + hasil;
}

// Fungsi perbandingan 2 Tingkat (Level Sepuh)
inline bool apakahLebihKecil(string a, string b) {
    int angkaA = ambilAngkaID(a);
    int angkaB = ambilAngkaID(b);
    if (angkaA != angkaB) {
        return angkaA < angkaB;
    }
    return a < b;
}

// --- DEKLARASI FUNGSI BACKEND --- //

// Fungsi pembantu buat nyusun data secara ANGKA
inline void urutkanInventarisInsertionSort() {
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

// Fungsi baca data dari CSV (VERSI SUPER - AUTO GENERATE)
inline void bacaDataCSV() {
    ifstream file(namaFile);
    string baris, id, nama, kategori, stok_str, harga_str;

    if (!file.is_open() || file.peek() == std::ifstream::traits_type::eof()) {
        if (file.is_open()) file.close();

        cout << "[WARNING]: File " << namaFile << " gak ketemu atau kosong!" << endl;
        cout << "[SISTEM]: Tenang bre, sistem lagi nge-generate 500 data dummy otomatis..." << endl;

        ofstream fileBaru(namaFile);
        for (int i = 1; i <= 500; i++) {
            int stokGen = ((rand() % 1000) + 5) * 1000;
            int hargaGen = ((rand() % 100) + 5) * 1000;
            fileBaru << "BRG" << i << "," << "Barang_Toko_" << i << "," << "KategoriUmum" << "," << stokGen << "," << hargaGen << "\n";
        }
        fileBaru.close();
        cout << "[SISTEM]: 500 Data Dummy berhasil diciptakan!\n" << endl;
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

// Fungsi simpan 
inline void simpanDataCSV() {
    ofstream file(namaFile);
    if (!file.is_open()) {
        cout << "[ERROR]: Gagal membuka file " << namaFile << " buat nyimpen data!" << endl;
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
    cout << "[SISTEM]: Mantap! " << inventaris.size() << " data berhasil diamankan ke " << namaFile << "." << endl;
}

// Fungsi Searching (Binary Search)
inline void cariBarangBinarySearch() {
    if (inventaris.empty()) {
        cout << "[ERROR]: Inventaris kosong, gak ada yang bisa dicari!" << endl;
        return;
    }

    string targetID;
    cout << "\n=== CARI BARANG (BINARY SEARCH) ===" << endl;
    cout << "Masukkan ID Barang yang mau dicari (contoh: BRG50): ";
    getline(cin, targetID);

    int kiri = 0;
    int kanan = (int)inventaris.size() - 1;
    bool ketemu = false;

    while (kiri <= kanan) {
        int tengah = kiri + (kanan - kiri) / 2;
        if (inventaris[tengah].ID_Barang == targetID) {
            cout << "\n[SISTEM]: Barang Ditemukan!" << endl;
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
        cout << "\n[ERROR]: Barang dengan ID '" << targetID << "' gak ketemu, bre!" << endl;
    }
}

// Fungsi Tambah Barang Konsol
inline void tambahBarangDenganInsertionSort() {
    Barang barangBaru;
    cout << "\n=== TAMBAH BARANG MASUK ===" << endl;
    cout << "Masukkan ID Barang (contoh: BRG501): ";
    getline(cin, barangBaru.ID_Barang);

    for (const auto& item : inventaris) {
        if (item.ID_Barang == barangBaru.ID_Barang) {
            cout << "[ERROR]: ID Barang udah ada! Gagal menambahkan." << endl;
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
        cout << "Masukkan Jumlah Stok: ";
        getline(cin, stokInput);
        string stokBersih = "";
        for (char c : stokInput) {
            if (isdigit(c)) stokBersih += c;
        }
        if (stokBersih.empty()) {
            cout << "[ERROR]: Stok harus pakai angka murni bre!\n";
        }
        else {
            try {
                barangBaru.Stok = stoi(stokBersih);
                stokValid = true;
            }
            catch (...) {
                cout << "[ERROR]: Jumlah stok kelebihan!\n";
            }
        }
    }

    string hargaInput;
    bool hargaValid = false;
    while (!hargaValid) {
        cout << "Masukkan Harga Barang: ";
        getline(cin, hargaInput);
        string hargaBersih = "";
        for (char c : hargaInput) {
            if (isdigit(c)) hargaBersih += c;
        }
        if (hargaBersih.empty()) {
            cout << "[ERROR]: Harganya masukin angka, jangan huruf!\n";
        }
        else {
            try {
                barangBaru.Harga_Barang = stoi(hargaBersih);
                hargaValid = true;
            }
            catch (...) {
                cout << "[ERROR]: Angkanya kegedean bre!\n";
            }
        }
    }

    inventaris.push_back(barangBaru);
    urutkanInventarisInsertionSort();
    cout << "[SISTEM]: Barang berhasil ditambahkan!" << endl;
}

// Fungsi nampilin data ke layar konsol
inline void tampilkanInventaris() {
    if (inventaris.empty()) {
        cout << "Inventaris kosong, bre!" << endl;
        return;
    }
    cout << "\n=== DAFTAR BARANG TOKO JALLALUDIN ===" << endl;
    for (const auto& item : inventaris) {
        cout << "ID: " << item.ID_Barang
            << " | Nama: " << item.Nama_Barang
            << " | Kat: " << item.Kategori
            << " | Stok: " << item.Stok << " pcs"
            << " | Harga: " << formatRupiah(item.Harga_Barang) << endl;
    }
}

// Fungsi tambahan buat Hapus Barang Konsol
inline void hapusBarang() {
    if (inventaris.empty()) {
        cout << "[ERROR]: Inventaris kosong, gak ada yang bisa dihapus bre!" << endl;
        return;
    }
    string targetID;
    cout << "\n=== HAPUS BARANG ===" << endl;
    cout << "Masukkan ID Barang yang mau dihapus: ";
    getline(cin, targetID);

    bool ketemu = false;
    for (auto it = inventaris.begin(); it != inventaris.end(); ++it) {
        if (it->ID_Barang == targetID) {
            cout << "[SISTEM]: Sayonara! Barang '" << it->Nama_Barang << "' resmi dihapus!" << endl;
            inventaris.erase(it);
            ketemu = true;
            break;
        }
    }
    if (!ketemu) cout << "\n[ERROR]: Barang emang gak ada di gudang!" << endl;
}

// Pembuat Data Dummy Massal
inline void generateSeribuDataDummy() {
    inventaris.clear();
    cout << "\n[SISTEM]: Memulai proses pabrikasi 100 data dummy..." << endl;
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
    cout << "[SISTEM]: 100 Data Dummy masuk memori!" << endl;
}

// ========================================================================
// FUNGSI JEMBATAN KE GUI VISUAL STUDIO
// ========================================================================
inline void backendTambahBarang(string id, string nama, string kategori, int stok, int harga) {
    Barang barangBaru;
    barangBaru.ID_Barang = id;
    barangBaru.Nama_Barang = nama;
    barangBaru.Kategori = kategori;
    barangBaru.Stok = stok;
    barangBaru.Harga_Barang = harga;

    inventaris.push_back(barangBaru);
    urutkanInventarisInsertionSort();
    simpanDataCSV();
}