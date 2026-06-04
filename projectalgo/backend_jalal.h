#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>

using namespace std;

// 1. Setup Struct
struct Barang {
    string ID_Barang;
    string Nama_Barang;
    string Kategori;
    int Stok;
    int Harga_Barang;
};

// Trick MSVC biar gak memicu C7525 atau multi-definisi LNK2005 di GUI
__declspec(selectany) vector<Barang> inventaris;
__declspec(selectany) string namaFile = "inventaristoko.csv";

// Fungsi pembantu ambil angka ID
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

// Fungsi format Rupiah
inline string formatRupiah(int nominal) {
    string hasil = to_string(nominal);
    int panjang = hasil.length();
    for (int i = panjang - 3; i > 0; i -= 3) {
        hasil.insert(i, ".");
    }
    return "Rp" + hasil;
}

// Fungsi perbandingan ID
inline bool apakahLebihKecil(string a, string b) {
    int angkaA = ambilAngkaID(a);
    int angkaB = ambilAngkaID(b);
    if (angkaA != angkaB) {
        return angkaA < angkaB;
    }
    return a < b;
}

// Sorting Insertion Sort
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

// Baca CSV
inline void bacaDataCSV() {
    ifstream file(namaFile);
    string baris, id, nama, kategori, stok_str, harga_str;

    if (!file.is_open() || file.peek() == std::ifstream::traits_type::eof()) {
        if (file.is_open()) file.close();
        ofstream fileBaru(namaFile);
        fileBaru.close();
        file.open(namaFile);
    }

    inventaris.clear(); // Bersihkan memori sebelum load ulang
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

// Simpan CSV
inline void simpanDataCSV() {
    ofstream file(namaFile);
    if (!file.is_open()) return;
    for (const auto& item : inventaris) {
        file << item.ID_Barang << ","
            << item.Nama_Barang << ","
            << item.Kategori << ","
            << item.Stok << ","
            << item.Harga_Barang << "\n";
    }
    file.close();
}

// Generator Dummy
inline void generateSeribuDataDummy() {
    inventaris.clear();
    for (int i = 1; i <= 100; i++) {
        Barang b;
        b.ID_Barang = "BRG" + to_string(i);
        b.Nama_Barang = "Barang_Toko_"  + to_string(i);
        b.Kategori = "Random" + to_string(i);
        b.Stok = ((rand() % 1000) + 1) * 100;
        b.Harga_Barang = ((rand() % 1000) + 1) * 100;
        inventaris.push_back(b);
    }
    urutkanInventarisInsertionSort();
    simpanDataCSV();
}

// ========================================================================
// FUNGSI JEMBATAN KE GUI (Wajib Ada Biar MyForm.h Kagak Error)
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

// FITUR BARU: Jembatan Update Data untuk GUI Visual Studio
inline bool backendUbahBarang(string targetID, string namaBaru, string kategoriBaru, string stokStr, string hargaStr) {
    auto it = find_if(inventaris.begin(), inventaris.end(), [&](const Barang& b) {
        return b.ID_Barang == targetID;
        });

    if (it == inventaris.end()) return false; // ID Gak ketemu

    if (!namaBaru.empty()) it->Nama_Barang = namaBaru;
    if (!kategoriBaru.empty()) it->Kategori = kategoriBaru;

    if (!stokStr.empty()) {
        string bersih = "";
        for (char c : stokStr) if (isdigit(c)) bersih += c;
        if (!bersih.empty()) it->Stok = stoi(bersih);
    }

    if (!hargaStr.empty()) {
        string bersih = "";
        for (char c : hargaStr) if (isdigit(c)) bersih += c;
        if (!bersih.empty()) it->Harga_Barang = stoi(bersih);
    }

    urutkanInventarisInsertionSort(); // Urutkan ulang kali aja ada perubahan struktural
    simpanDataCSV(); // Langsung auto-save ke CSV berkala
    return true;
}