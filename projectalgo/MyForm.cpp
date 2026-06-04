#include "MyForm.h"
using namespace System;
using namespace System::Windows::Forms;

// ALOKASI FISIK VARIABEL GLOBAL (Solusi mutlak LNK2001) - Udah bener!
std::vector<Barang> inventaris;
std::string namaFile = "inventaris.csv";

[STAThread]
int main(cli::array<System::String^>^ args) { // <-- UBAH DI BARIS INI
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    // Sesuaikan projectalgo dengan nama project lu yang aktif
    projectalgo::MyForm form;
    Application::Run(% form);

    return 0;
}