#pragma once
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <msclr\marshal_cppstd.h>
#include "backend_jalal.h" // <-- Panggil file ini

// Kenalin fungsi & variabel global backend ke MyForm.h
extern void bacaDataCSV();
extern void backendTambahBarang(std::string id, std::string nama, std::string kategori, int stok, int harga);
extern void simpanDataCSV();
extern std::string formatRupiah(int nominal);
extern std::vector<Barang> inventaris;

namespace projectalgo {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();

			// Baca data awal dari CSV backend
			bacaDataCSV();

			// Setup paksa tabel biar kolomnya rapi (5 kolom)
			dataGridView1->Columns->Clear();
			dataGridView1->Columns->Add("id", "ID Barang");
			dataGridView1->Columns->Add("nama", "Nama Barang");
			dataGridView1->Columns->Add("kategori", "Kategori");
			dataGridView1->Columns->Add("jumlah", "Jumlah");
			dataGridView1->Columns->Add("harga", "Harga");

			// Tampilkan data ke grid
			refreshGrid();

			// Daftarkan event Load
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
		}

	protected:
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::TextBox^ textBox3;
	private: System::Windows::Forms::DataGridView^ dataGridView1;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::TextBox^ textBox4;
	private: System::Windows::Forms::TextBox^ textBox5;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::Label^ label7;

	private:
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->textBox5 = (gcnew System::Windows::Forms::TextBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			this->SuspendLayout();
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->BackColor = System::Drawing::SystemColors::ScrollBar;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12));
			this->label2->Location = System::Drawing::Point(139, 358);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(69, 25);
			this->label2->TabIndex = 14;
			this->label2->Text = L"jumlah";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->BackColor = System::Drawing::SystemColors::ScrollBar;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12));
			this->label3->Location = System::Drawing::Point(146, 398);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(62, 25);
			this->label3->TabIndex = 13;
			this->label3->Text = L"harga";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->BackColor = System::Drawing::SystemColors::ScrollBar;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12));
			this->label4->Location = System::Drawing::Point(115, 250);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(93, 25);
			this->label4->TabIndex = 12;
			this->label4->Text = L"id barang";
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(236, 361);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(206, 22);
			this->textBox1->TabIndex = 11;
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(236, 285);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(206, 22);
			this->textBox2->TabIndex = 10;
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(236, 399);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(206, 22);
			this->textBox3->TabIndex = 9;
			// 
			// dataGridView1
			// 
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->Location = System::Drawing::Point(86, 553);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->RowHeadersWidth = 51;
			this->dataGridView1->Size = System::Drawing::Size(506, 531);
			this->dataGridView1->TabIndex = 8;
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Bold));
			this->button1->Location = System::Drawing::Point(86, 465);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(153, 56);
			this->button1->TabIndex = 7;
			this->button1->Text = L"btnadd";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// button2
			// 
			this->button2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold));
			this->button2->Location = System::Drawing::Point(450, 465);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(142, 56);
			this->button2->TabIndex = 6;
			this->button2->Text = L"btnremove";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// label1
			// 
			this->label1->BackColor = System::Drawing::SystemColors::ScrollBar;
			this->label1->Font = (gcnew System::Drawing::Font(L"Monotype Corsiva", 72, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic))));
			this->label1->Location = System::Drawing::Point(41, 41);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(550, 161);
			this->label1->TabIndex = 5;
			this->label1->Text = L"SIJALAL";
			this->label1->Click += gcnew System::EventHandler(this, &MyForm::label1_Click);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Uighur", 25.8F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Underline))));
			this->label5->Location = System::Drawing::Point(148, 169);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(369, 51);
			this->label5->TabIndex = 4;
			this->label5->Text = L"Sistem Inventaris Jalaludin";
			// 
			// textBox4
			// 
			this->textBox4->Location = System::Drawing::Point(236, 326);
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(206, 22);
			this->textBox4->TabIndex = 3;
			// 
			// textBox5
			// 
			this->textBox5->Location = System::Drawing::Point(236, 250);
			this->textBox5->Name = L"textBox5";
			this->textBox5->Size = System::Drawing::Size(206, 22);
			this->textBox5->TabIndex = 2;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->BackColor = System::Drawing::SystemColors::ScrollBar;
			this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12));
			this->label6->Location = System::Drawing::Point(81, 285);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(127, 25);
			this->label6->TabIndex = 1;
			this->label6->Text = L"nama barang";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->BackColor = System::Drawing::SystemColors::ScrollBar;
			this->label7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12));
			this->label7->Location = System::Drawing::Point(127, 322);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(81, 25);
			this->label7->TabIndex = 0;
			this->label7->Text = L"kategori";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(715, 1085);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->textBox5);
			this->Controls->Add(this->textBox4);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->dataGridView1);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Name = L"MyForm";
			this->Text = L"SIJALAL - Inventaris";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load_1);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private:
		// Fungsi render ulang grid UI dari data Vector Backend
		System::Void refreshGrid() {
			dataGridView1->Rows->Clear();
			for (size_t i = 0; i < inventaris.size(); i++) {
				dataGridView1->Rows->Add(
					gcnew String(inventaris[i].ID_Barang.c_str()),
					gcnew String(inventaris[i].Nama_Barang.c_str()),
					gcnew String(inventaris[i].Kategori.c_str()),
					inventaris[i].Stok,
					gcnew String(formatRupiah(inventaris[i].Harga_Barang).c_str())
				);
			}
		}

		System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
			refreshGrid();
		}

		// Tambah data ke Backend gudang
		System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
			String^ idStr = textBox5->Text->Trim();
			String^ namaStr = textBox2->Text->Trim();
			String^ kategoriStr = textBox4->Text->Trim();
			String^ jumlahStr = textBox1->Text->Trim();
			String^ hargaStr = textBox3->Text->Trim();

			if (idStr == "" || namaStr == "" || kategoriStr == "" || jumlahStr == "" || hargaStr == "") {
				MessageBox::Show("Semua kolom wajib diisi dulu ya Jalal!", "Peringatan", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				return;
			}

			try {
				std::string id = msclr::interop::marshal_as<std::string>(idStr);
				std::string nama = msclr::interop::marshal_as<std::string>(namaStr);
				std::string kategori = msclr::interop::marshal_as<std::string>(kategoriStr);
				int stok = System::Convert::ToInt32(jumlahStr);
				int harga = System::Convert::ToInt32(hargaStr);

				for (const auto& item : inventaris) {
					if (item.ID_Barang == id) {
						MessageBox::Show("ID Barang '" + idStr + "' udah ada di gudang, bre!", "Error Duplikat", MessageBoxButtons::OK, MessageBoxIcon::Error);
						return;
					}
				}

				backendTambahBarang(id, nama, kategori, stok, harga);
				refreshGrid();

				MessageBox::Show("Mantap Jalal! Barang berhasil disimpan dan otomatis diurutkan!", "Sukses", MessageBoxButtons::OK, MessageBoxIcon::Information);

				textBox5->Clear(); textBox2->Clear(); textBox4->Clear(); textBox1->Clear(); textBox3->Clear();
				textBox5->Focus();
			}
			catch (...) {
				MessageBox::Show("Kolom Jumlah Stok dan Harga harus diisi pake angka murni, bre!", "Error Input", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}

		// Hapus data dari Backend gudang
		System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
			if (dataGridView1->SelectedRows->Count > 0) {
				DataGridViewRow^ row = dataGridView1->SelectedRows[0];
				if (row->IsNewRow) return;

				String^ idTargetStr = row->Cells[0]->Value->ToString();
				std::string idTarget = msclr::interop::marshal_as<std::string>(idTargetStr);

				bool ketemu = false;
				for (auto it = inventaris.begin(); it != inventaris.end(); ++it) {
					if (it->ID_Barang == idTarget) {
						inventaris.erase(it);
						ketemu = true;
						break;
					}
				}

				if (ketemu) {
					simpanDataCSV();
					refreshGrid();
					MessageBox::Show("Barang dengan ID '" + idTargetStr + "' resmi dihapus!", "Sukses", MessageBoxButtons::OK, MessageBoxIcon::Information);
				}
			}
			else {
				MessageBox::Show("Klik/Pilih dulu salah satu baris di tabel bawah yang mau dihapus!", "Info");
			}
		}

	private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {}
	private: System::Void MyForm_Load_1(System::Object^ sender, System::EventArgs^ e) {}
	};
}