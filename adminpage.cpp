#include "adminpage.h"
#include "ui_adminpage.h"
#include <QWidget>
#include <QFile>
#include <QTextStream>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTextEdit>
#include <QLineEdit>
#include <QStackedWidget>
#include <QComboBox>
#include <QMessageBox>
#include <QListWidget>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <iostream>

AdminPage::AdminPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminPage)
{
    // Jumlah pasien
    int jumlahPasien = jumlahPasienLog();
    // HALAMAN LIHAT DAN CARI PASIEN
    halamanLihatPasien = new QWidget;
    lihatPasienButton = new QPushButton(this);
    cariPasienButton = new QPushButton(this);
    cariPasien = new QLineEdit(this);
    textEditPasien = new QTextEdit(this);
    tabelDataPasien = new QTableWidget(this);
    logoutButton = new QPushButton(this);

    lihatPasienButton->setText("Semua Pasien");
    connect(lihatPasienButton, &QPushButton::clicked, this, &AdminPage::on_lihatPasienButton_clicked);
    cariPasienButton->setText("Cari Pasien");
    connect(cariPasienButton, &QPushButton::clicked, this, &AdminPage::on_cariPasienButton_clicked);
    logoutButton->setText("Logout");
    connect(logoutButton, &QPushButton::clicked, this, &AdminPage::on_logoutButton_clicked);
    cariPasien->setPlaceholderText("Masukkan nama");
        // tabel
    tabelDataPasien->setRowCount(jumlahPasien);
    tabelDataPasien->setColumnCount(4);
    tabelDataPasien->setHorizontalHeaderLabels({"Nama", "Umur", "Gender", "Alamat"});
    connect(tabelDataPasien, &QTableWidget::itemClicked, this, &AdminPage::on_tableItem_clicked);

    QVBoxLayout *kolomKiri = new QVBoxLayout();

    kolomKiri->addWidget(lihatPasienButton);
    kolomKiri->addWidget(cariPasien);
    kolomKiri->addWidget(cariPasienButton);
    kolomKiri->addWidget(logoutButton);

    QVBoxLayout *kolomKanan = new QVBoxLayout();
    kolomKanan->addWidget(tabelDataPasien);
    kolomKanan->addWidget(textEditPasien);

    QHBoxLayout *layoutHalamanLihatPasien = new QHBoxLayout(halamanLihatPasien);
    layoutHalamanLihatPasien->addLayout(kolomKiri);
    layoutHalamanLihatPasien->addLayout(kolomKanan);

    // HALAMAN HAPUS
    QWidget *halamanHapusPasien = new QWidget;
    hapusPasienButton = new QPushButton(this);
    hapusPasienLine = new QLineEdit(this);
    hapusDokterLine = new QLineEdit(this);

    hapusPasienLine->setPlaceholderText("Masukkan nama");
    hapusDokterLine->setPlaceholderText("Masukkan ID dokter");
    hapusPasienButton->setText("Hapus Data");
    connect(hapusPasienButton, &QPushButton::clicked, this, &AdminPage::on_hapusPasienButton_clicked);

    QVBoxLayout *layoutHalamanHapusPasien = new QVBoxLayout(halamanHapusPasien);
    layoutHalamanHapusPasien->addWidget(hapusDokterLine);
    layoutHalamanHapusPasien->addWidget(hapusPasienLine);
    layoutHalamanHapusPasien->addWidget(hapusPasienButton);

    // HALAMAN TAMBAH
    QWidget *halamanTambahPasien = new QWidget;
    tambahPasienLine = new QLineEdit(this);
    tambahDokterLine = new QLineEdit(this);
    tambahUmurLine = new QLineEdit(this);
    tambahGenderLine = new QLineEdit(this);
    tambahAlamatLine = new QLineEdit(this);
    tambahButton = new QPushButton(this);

    tambahPasienLine->setPlaceholderText("Nama Pasien");
    tambahDokterLine->setPlaceholderText("ID Dokter");
    tambahUmurLine->setPlaceholderText("Umur");
    tambahGenderLine->setPlaceholderText("Gender");
    tambahAlamatLine->setPlaceholderText("Alamat");
    tambahButton->setText("Tambah Pasien");
    connect(tambahButton, &QPushButton::clicked, this, &AdminPage::on_tambahButton_clicked);

    QHBoxLayout *layoutDataPasien = new QHBoxLayout();
    QVBoxLayout *layoutHalamanTambahPasien = new QVBoxLayout(halamanTambahPasien);

    layoutDataPasien->addWidget(tambahPasienLine);
    layoutDataPasien->addWidget(tambahUmurLine);
    layoutDataPasien->addWidget(tambahGenderLine);
    layoutDataPasien->addWidget(tambahAlamatLine);
    layoutHalamanTambahPasien->addWidget(tambahDokterLine);
    layoutHalamanTambahPasien->addLayout(layoutDataPasien);
    layoutHalamanTambahPasien->addWidget(tambahButton);

    // HALAMAN TAMBAH RIWAYAT
    QWidget *halamanTambahRiwayat = new QWidget;
    riwayatIDDokterLine = new QLineEdit(this);
    riwayatNamaDokterLine = new QLineEdit(this);
    riwayatPasienLine = new QLineEdit(this);
    riwayatSakitPasienLine = new QLineEdit(this);
    riwayatTanggalMasukPasienLine = new QLineEdit(this);
    riwayatTanggalKeluarPasienLine = new QLineEdit(this);
    tambahRiwayatButton = new QPushButton(this);
    listPasien = new QListWidget(this);

    riwayatIDDokterLine->setPlaceholderText("ID Dokter");
    riwayatNamaDokterLine->setPlaceholderText("Nama Dokter");
    riwayatPasienLine->setPlaceholderText("Nama Pasien");
    riwayatSakitPasienLine->setPlaceholderText("Deskripsi Penyakit");
    riwayatTanggalMasukPasienLine->setPlaceholderText("ddMMyyyy");
    riwayatTanggalKeluarPasienLine->setPlaceholderText("ddMMyyyy");
    tambahRiwayatButton->setText("Tambah Riwayat");
    connect(tambahRiwayatButton, &QPushButton::clicked, this, &AdminPage::on_tambahRiwayatButton_clicked);
    connect(listPasien, &QListWidget::itemClicked, this, &AdminPage::on_itemClicked);

    QHBoxLayout *layoutTanggalRiwayat = new QHBoxLayout();
    QHBoxLayout *layoutDokterRiwayat = new QHBoxLayout();
    QVBoxLayout *layoutHalamanTambahRiwayat = new QVBoxLayout(halamanTambahRiwayat);

    layoutTanggalRiwayat->addWidget(riwayatTanggalMasukPasienLine);
    layoutTanggalRiwayat->addWidget(riwayatTanggalKeluarPasienLine);
    layoutDokterRiwayat->addWidget(riwayatIDDokterLine);
    layoutDokterRiwayat->addWidget(riwayatNamaDokterLine);
    layoutHalamanTambahRiwayat->addLayout(layoutDokterRiwayat);
    layoutHalamanTambahRiwayat->addWidget(riwayatSakitPasienLine);
    layoutHalamanTambahRiwayat->addLayout(layoutTanggalRiwayat);
    layoutHalamanTambahRiwayat->addWidget(riwayatPasienLine);
    layoutHalamanTambahRiwayat->addWidget(tambahRiwayatButton);
    layoutHalamanTambahRiwayat->addWidget(listPasien);

    // HALAMAN HAPUS DOKTER
    QWidget *halamanHapusDokter = new QWidget;
    hapusIdDokterLine = new QLineEdit(this);
    hapusDokterButton = new QPushButton(this);

    hapusIdDokterLine->setPlaceholderText("ID Dokter");;
    hapusDokterButton->setText("Hapus");
    connect(hapusDokterButton, &QPushButton::clicked, this, &AdminPage::on_hapusDokterButton_clicked);

    QVBoxLayout *layoutHalamanHapusDokter = new QVBoxLayout(halamanHapusDokter);

    layoutHalamanHapusDokter->addWidget(hapusIdDokterLine);
    layoutHalamanHapusDokter->addWidget(hapusDokterButton);

    // HALAMAN TAMBAH DOKTER
    QWidget *halamanTambahDokter = new QWidget;
    tambahDokterId = new QLineEdit(this);
    tambahDokterPass = new QLineEdit(this);
    tambahDokterNama = new QLineEdit(this);
    tambahDokterButton = new QPushButton(this);

    tambahDokterId->setPlaceholderText("ID Dokter");
    tambahDokterNama->setPlaceholderText("Nama Dokter");
    tambahDokterPass->setPlaceholderText("Password");
    tambahDokterButton->setText("Tambah");
    connect(tambahDokterButton, &QPushButton::clicked, this, &AdminPage::on_tambahDokterButton_clicked);

    QHBoxLayout *layoutIdPass = new QHBoxLayout();
    QVBoxLayout *layoutHalamanTambahDokter = new QVBoxLayout(halamanTambahDokter);

    layoutIdPass->addWidget(tambahDokterId);
    layoutIdPass->addWidget(tambahDokterPass);
    layoutHalamanTambahDokter->addWidget(tambahDokterNama);
    layoutHalamanTambahDokter->addLayout(layoutIdPass);
    layoutHalamanTambahDokter->addWidget(tambahDokterButton);

    // QStackWidget
    QStackedWidget *stackedWidgetAdmin = new QStackedWidget;
    stackedWidgetAdmin->addWidget(halamanLihatPasien);
    stackedWidgetAdmin->addWidget(halamanHapusPasien);
    stackedWidgetAdmin->addWidget(halamanTambahPasien);
    stackedWidgetAdmin->addWidget(halamanTambahRiwayat);
    stackedWidgetAdmin->addWidget(halamanHapusDokter);
    stackedWidgetAdmin->addWidget(halamanTambahDokter);

    QComboBox *adminComboBox = new QComboBox;
    adminComboBox->addItem("Lihat");
    adminComboBox->addItem("Hapus Pasien");
    adminComboBox->addItem("Tambah Pasien");
    adminComboBox->addItem("Tambah Riwayat");
    adminComboBox->addItem("Hapus Dokter");
    adminComboBox->addItem("Tambah Dokter");
    connect(adminComboBox, &QComboBox::activated, stackedWidgetAdmin, &QStackedWidget::setCurrentIndex);

    QVBoxLayout *layoutAdmin = new QVBoxLayout(this);
    layoutAdmin->addWidget(adminComboBox);
    layoutAdmin->addWidget(stackedWidgetAdmin);

    ui->setupUi(this);
}

AdminPage::~AdminPage()
{
    delete ui;
}

struct riwayatPasien{
    QString dokterPasien;
    QString penyakit;
    QString tanggalKunjungan;
    QString tanggalKeluar;
    struct riwayatPasien *next;
};

struct dataP{
    QString nama;
    int umur;
    QString gender;
    QString alamat;
};

int AdminPage::jumlahPasienLog()
{
    QFile listPasienL("C:/Users/Steven Ciam/Documents/qt-projects/fp-strukdat/log.txt");
    listPasienL.open(QIODevice::ReadOnly);
    QTextStream in(&listPasienL);

    int jumlahPasien = 0;
    while(!in.atEnd())
    {
        in.readLine();
        jumlahPasien++;
    }
    listPasienL.close();

    return jumlahPasien;
}

void AdminPage::lihatPasienAdmin()
{
    QFile listPasienA("C:/Users/Steven Ciam/Documents/qt-projects/fp-strukdat/log.txt");
    listPasienA.open(QIODevice::ReadOnly);
    QTextStream in(&listPasienA);
    struct dataP dataPasienTemp;

    int jml = 1;
    int jumlahriwayat;
    int rowCounter = 0;
    // Hapus teks edit
    textEditPasien->clear();
    while(!in.atEnd())
    {
        struct riwayatPasien *head, *tail, *node;
        head = tail = node = NULL;

        int indexP = 0;
        QString riwayat = in.readLine();
        QStringList riwayatt = riwayat.split(';');
        jumlahriwayat = riwayatt.at(indexP).toInt(); indexP++;
        int counter = 0;
        for(int i = 0; i<jumlahriwayat; i++)
        {
            if(counter==0)
            {
                head = new riwayatPasien;
                head->dokterPasien = riwayatt.at(indexP); indexP++;
                head->penyakit = riwayatt.at(indexP); indexP++;
                head->tanggalKunjungan = riwayatt.at(indexP); indexP++;
                head->tanggalKeluar = riwayatt.at(indexP); indexP++;
                head->next = node;
                tail = head;
                counter++;
                node=NULL;
            }
            else{
                node = new riwayatPasien;
                node->dokterPasien = riwayatt.at(indexP); indexP++;
                node->penyakit = riwayatt.at(indexP); indexP++;
                node->tanggalKunjungan = riwayatt.at(indexP); indexP++; node->tanggalKeluar = riwayatt.at(indexP); indexP++;
                tail->next=node;
                node->next=NULL;
                tail = node;
                node = NULL;
                counter++;
            }
        }
        dataPasienTemp.nama = riwayatt.at(indexP); indexP++;
        dataPasienTemp.umur = riwayatt.at(indexP).toInt(); indexP++;
        dataPasienTemp.gender = riwayatt.at(indexP); indexP++;
        dataPasienTemp.alamat = riwayatt.at(indexP); indexP++;

        // Masukkan nama pasien ke tabel
        QTableWidgetItem *itemTNama = new QTableWidgetItem(dataPasienTemp.nama);
        QTableWidgetItem *itemTUmur = new QTableWidgetItem(QString::number(dataPasienTemp.umur));
        QTableWidgetItem *itemTGender = new QTableWidgetItem(dataPasienTemp.gender);
        QTableWidgetItem *itemTAlamat = new QTableWidgetItem(dataPasienTemp.alamat);
        tabelDataPasien->setItem(rowCounter, 0, itemTNama);
        tabelDataPasien->setItem(rowCounter, 1, itemTUmur);
        tabelDataPasien->setItem(rowCounter, 2, itemTGender);
        tabelDataPasien->setItem(rowCounter, 3, itemTAlamat);
        rowCounter++;
    /*
        // Data pasien
        textEditPasien->insertPlainText("Data pasien ke-" + QString::number(jml));
        textEditPasien->moveCursor(QTextCursor::End);
        jml++;
        textEditPasien->insertPlainText("\nNama: " + dataPasienTemp.nama + "\nUmur: " + QString::number(dataPasienTemp.umur) + "\nJenis kelamin: " + dataPasienTemp.gender + "\nAlamat: " + dataPasienTemp.alamat + "\n");
        textEditPasien->moveCursor(QTextCursor::End);
        // Riwayat
        node=head;
        int jml2 = 1;
        while(node!=NULL){
            textEditPasien->insertPlainText("Riwayat ke-" + QString::number(jml2));
            textEditPasien->moveCursor(QTextCursor::End);
            textEditPasien->insertPlainText("\nDokter: " + node->dokterPasien + "\nPenyakit: " + node->penyakit + "\nTanggal kunjungan: " + node->tanggalKunjungan + "\nTanggal keluar: " + node->tanggalKeluar + "\n");
            textEditPasien->moveCursor(QTextCursor::End);
            node = node->next;
            jml2++;
        }
        textEditPasien->insertPlainText("\n");
        textEditPasien->moveCursor(QTextCursor::End);
    */
        //hapus linked list
        while(head!=NULL)
        {
            node = head;
            head = head->next;
            delete node;
        }

    }
    listPasienA.close();
}

void AdminPage::cariPasienAdmin(QString namaP)
{
    QFile listPasienA("C:/Users/Steven Ciam/Documents/qt-projects/fp-strukdat/log.txt");
    listPasienA.open(QIODevice::ReadOnly);
    QTextStream in(&listPasienA);
    struct dataP dataPasienTemp;

    int jml = 1;
    int jumlahriwayat;
    bool ketemu = false;
    // Hapus teks edit
    textEditPasien->clear();
    while(!in.atEnd())
    {
        struct riwayatPasien *head, *tail, *node;
        head = tail = node = NULL;

        int indexP = 0;
        QString riwayat = in.readLine();
        QStringList riwayatt = riwayat.split(';');
        jumlahriwayat = riwayatt.at(indexP).toInt(); indexP++;
        int counter = 0;
        for(int i = 0; i<jumlahriwayat; i++)
        {
            if(counter==0)
            {
                head = new riwayatPasien;
                head->dokterPasien = riwayatt.at(indexP); indexP++;
                head->penyakit = riwayatt.at(indexP); indexP++;
                head->tanggalKunjungan = riwayatt.at(indexP); indexP++;
                head->tanggalKeluar = riwayatt.at(indexP); indexP++;
                head->next = node;
                tail = head;
                counter++;
                node=NULL;
            }
            else{
                node = new riwayatPasien;
                node->dokterPasien = riwayatt.at(indexP); indexP++;
                node->penyakit = riwayatt.at(indexP); indexP++;
                node->tanggalKunjungan = riwayatt.at(indexP); indexP++; node->tanggalKeluar = riwayatt.at(indexP); indexP++;
                tail->next=node;
                node->next=NULL;
                tail = node;
                node = NULL;
                counter++;
            }
        }
        dataPasienTemp.nama = riwayatt.at(indexP); indexP++;
        dataPasienTemp.umur = riwayatt.at(indexP).toInt(); indexP++;
        dataPasienTemp.gender = riwayatt.at(indexP); indexP++;
        dataPasienTemp.alamat = riwayatt.at(indexP); indexP++;

        if(dataPasienTemp.nama.contains(namaP, Qt::CaseInsensitive)) {
            textEditPasien->insertPlainText("Data pasien ke-" + QString::number(jml));
            textEditPasien->moveCursor(QTextCursor::End);
            jml++;
            textEditPasien->insertPlainText("\nNama: " + dataPasienTemp.nama + "\nUmur: " + QString::number(dataPasienTemp.umur) + "\nJenis kelamin: " + dataPasienTemp.gender + "\nAlamat: " + dataPasienTemp.alamat + "\n");
            textEditPasien->moveCursor(QTextCursor::End);
            node=head;
            int jml2 = 1;

            while(node!=NULL){
                textEditPasien->insertPlainText("Riwayat ke-" + QString::number(jml2));
                textEditPasien->moveCursor(QTextCursor::End);
                textEditPasien->insertPlainText("\n\tDokter: " + node->dokterPasien + "\n\tPenyakit: " + node->penyakit + "\n\tTanggal kunjungan: " + node->tanggalKunjungan + "\n\tTanggal keluar: " + node->tanggalKeluar + "\n");
                textEditPasien->moveCursor(QTextCursor::End);
                node = node->next;
                jml2++;
            }
            textEditPasien->insertPlainText("============================\n");
            textEditPasien->moveCursor(QTextCursor::End);
            ketemu = true;
        }

        //hapus linked list
        while(head!=NULL)
        {
            node = head;
            head = head->next;
            delete node;
        }

    }
    if(!ketemu) {
        QMessageBox::warning(this, "Eror", "Nama pasien tidak ditemukan");
    }
    listPasienA.close();
}

void AdminPage::hapusPasienLog(QString namaPasien)
{
    // Open doctor patient list in read only mode
    QFile listPasienA("C:/Users/Steven Ciam/Documents/qt-projects/fp-strukdat/log.txt");
    listPasienA.open(QIODevice::ReadWrite);
    QTextStream in(&listPasienA);

    // Open new file to write
    QFile temp("C:/Users/Steven Ciam/Documents/qt-projects/fp-strukdat/temp2.txt");
    if(!temp.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "Failed to open" << temp.fileName()<< "for write: " << temp.errorString() << "\n";
        temp.close();
    }
    QTextStream out(&temp);

    struct dataP dataPasienTemp;
    int jumlahriwayat;
    while(!in.atEnd())
    {
        struct riwayatPasien *head, *tail, *node;
        head = tail = node = NULL;

        int indexP = 0;
        QString riwayat = in.readLine();
        QStringList riwayatt = riwayat.split(';');
        jumlahriwayat = riwayatt.at(indexP).toInt(); indexP++;
        int counter = 0;
        for(int i = 0; i<jumlahriwayat; i++)
        {
            if(counter==0)
            {
                head = new riwayatPasien;
                head->dokterPasien = riwayatt.at(indexP); indexP++;
                head->penyakit = riwayatt.at(indexP); indexP++;
                head->tanggalKunjungan = riwayatt.at(indexP); indexP++;
                head->tanggalKeluar = riwayatt.at(indexP); indexP++;
                head->next = node;
                tail = head;
                counter++;
                node=NULL;
            }
            else{
                node = new riwayatPasien;
                node->dokterPasien = riwayatt.at(indexP); indexP++;
                node->penyakit = riwayatt.at(indexP); indexP++;
                node->tanggalKunjungan = riwayatt.at(indexP); indexP++; node->tanggalKeluar = riwayatt.at(indexP); indexP++;
                tail->next=node;
                node->next=NULL;
                tail = node;
                node = NULL;
                counter++;
            }
        }
        dataPasienTemp.nama = riwayatt.at(indexP); indexP++;
        dataPasienTemp.umur = riwayatt.at(indexP).toInt(); indexP++;
        dataPasienTemp.gender = riwayatt.at(indexP); indexP++;
        dataPasienTemp.alamat = riwayatt.at(indexP); indexP++;

        if(QString::compare(dataPasienTemp.nama, namaPasien, Qt::CaseInsensitive) == 0)
        {
            continue;
        }

        else{
            out<<QString::number(jumlahriwayat)<<";";
            node=head;
            while(node!=NULL)
            {
                out << node->dokterPasien << ";" << node->penyakit << ";" << node->tanggalKunjungan << ";" << node->tanggalKeluar << ";";
                node = node->next;
            }
            out << dataPasienTemp.nama << ";" << QString::number(dataPasienTemp.umur) << ";" << dataPasienTemp.gender << ";" << dataPasienTemp.alamat << "\n";

        }
        //hapus linked list
        while(head!=NULL)
        {
            node = head;
            head = head->next;
            delete node;
        }
    }
    listPasienA.close();
    temp.close();
    listPasienA.remove();
    temp.rename("C:/Users/Steven Ciam/Documents/qt-projects/fp-strukdat/log.txt");
}

void AdminPage::hapusPasien(QString tempID)
{
    // Open doctor patient list in read only mode
    QFile listPasienD("C:/Users/Steven Ciam/Documents/qt-projects/fp-strukdat/" + tempID + ".txt");
    listPasienD.open(QIODevice::ReadWrite);
    QTextStream in(&listPasienD);

    // Open new file to write
    QFile temp("C:/Users/Steven Ciam/Documents/qt-projects/fp-strukdat/temp.txt");
    if(!temp.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "Failed to open" << temp.fileName()<< "for write: " << temp.errorString() << "\n";
        temp.close();
    }
    QTextStream out(&temp);

    //input nama pasien
    QString namaPasien = hapusPasienLine->text();
    bool found = false;
    struct dataP dataPasienTemp;
    int jumlahriwayat;
    while(!in.atEnd())
    {
        struct riwayatPasien *head, *tail, *node;
        head = tail = node = NULL;

        int indexP = 0;
        QString riwayat = in.readLine();
        QStringList riwayatt = riwayat.split(';');
        jumlahriwayat = riwayatt.at(indexP).toInt(); indexP++;
        int counter = 0;
        for(int i = 0; i<jumlahriwayat; i++)
        {
            if(counter==0)
            {
                head = new riwayatPasien;
                head->dokterPasien = riwayatt.at(indexP); indexP++;
                head->penyakit = riwayatt.at(indexP); indexP++;
                head->tanggalKunjungan = riwayatt.at(indexP); indexP++;
                head->tanggalKeluar = riwayatt.at(indexP); indexP++;
                head->next = node;
                tail = head;
                counter++;
                node=NULL;
            }
            else{
                node = new riwayatPasien;
                node->dokterPasien = riwayatt.at(indexP); indexP++;
                node->penyakit = riwayatt.at(indexP); indexP++;
                node->tanggalKunjungan = riwayatt.at(indexP); indexP++; node->tanggalKeluar = riwayatt.at(indexP); indexP++;
                tail->next=node;
                node->next=NULL;
                tail = node;
                node = NULL;
                counter++;
            }
        }
        dataPasienTemp.nama = riwayatt.at(indexP); indexP++;
        dataPasienTemp.umur = riwayatt.at(indexP).toInt(); indexP++;
        dataPasienTemp.gender = riwayatt.at(indexP); indexP++;
        dataPasienTemp.alamat = riwayatt.at(indexP); indexP++;

        if(QString::compare(dataPasienTemp.nama, namaPasien, Qt::CaseInsensitive) == 0)
        {
            // Hapus juga data pasien pada log
            // hapusPasienLog(namaPasien);
            found = true;
            continue;
        }
        else{
            out<<QString::number(jumlahriwayat)<<";";
            node=head;
            while(node!=NULL)
            {
                out << node->dokterPasien << ";" << node->penyakit << ";" << node->tanggalKunjungan << ";" << node->tanggalKeluar << ";";
                node = node->next;
            }
            out << dataPasienTemp.nama << ";" << QString::number(dataPasienTemp.umur) << ";" << dataPasienTemp.gender << ";" << dataPasienTemp.alamat << "\n";

        }
        //hapus linked list
        while(head!=NULL)
        {
            node = head;
            head = head->next;
            delete node;
        }
    }
    if(found==false)
    {
        QMessageBox::warning(this, "Eror", "Nama pasien tidak ditemukan");
    } else {
        QMessageBox::about(this, "Info", "Pasien telah dihapus");
    }

    listPasienD.close();
    temp.close();
    listPasienD.remove();
    temp.rename("C:/Users/Steven Ciam/Documents/qt-projects/fp-strukdat/" + tempID + ".txt");
}

void AdminPage::tambahPasien(QString tempID){
    // Open corresponding doctor file
    QFile listPasienD("C:/Users/Steven Ciam/Documents/qt-projects/fp-strukdat/" + tempID + ".txt");
    if(!listPasienD.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qWarning() << "Failed to open" << listPasienD.fileName()<< "for write: " << listPasienD.errorString() << "\n";
        listPasienD.close();
    }
    QTextStream streamD(&listPasienD);
    // Open admin file
    QFile listPasienA("C:/Users/Steven Ciam/Documents/qt-projects/fp-strukdat/log.txt");
    if(!listPasienA.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qWarning() << "Failed to open" << listPasienA.fileName()<< "for write: " << listPasienA.errorString() << "\n";
        listPasienA.close();
    }
    QTextStream streamA(&listPasienA);

    // Get user input from ui
    QString namaP = tambahPasienLine->text();
    QString umurP = tambahUmurLine->text();
    QString genderP = tambahGenderLine->text();
    QString alamatP = tambahAlamatLine->text();

    // Check if name exist, don't add again
    // Loop doctor file and check
    while(!streamD.atEnd()) {
        QString line = streamD.readLine();
        QStringList lineSplit = line.split(';');
        int jumlahRiwayat = lineSplit.at(0).toInt();
        QString namaSplit = lineSplit.at(jumlahRiwayat*4+1);
        // Compare
        if(QString::compare(namaSplit, namaP, Qt::CaseInsensitive) == 0) {
            QMessageBox::warning(this, "Eror", "Pasien sudah terdaftar");
            return;
        }
    }

    // Masukkan data pasien ke file dokter
    QStringList dataPasienList = {"0", namaP, umurP, genderP, alamatP + "\n"};
    QString dataPasienJoin = dataPasienList.join(';');
    streamD << dataPasienJoin;

    // Cek apakah pasien sudah ada di log, jangan double
    bool existAdmin = false;
    while(!streamA.atEnd()) {
        QString line = streamA.readLine();
        QStringList lineSplit = line.split(';');
        int jumlahRiwayat = lineSplit.at(0).toInt();
        QString namaSplit = lineSplit.at(jumlahRiwayat*4+1);
        // Compare, if exist set bool to true
        if(QString::compare(namaSplit, namaP, Qt::CaseInsensitive) == 0) {
            existAdmin = true;
            break;
        }
    }
    // Don't add if already exist
    if(!existAdmin) {
        listPasienA.seek(listPasienA.size());
        streamA << dataPasienJoin;
    }

    // Close files
    listPasienD.close();
    listPasienA.close();

    // Pemberitahuan
    QMessageBox::about(this, "Informasi", "Pasien berhasil ditambah");
}

void AdminPage::tambahRiwayat(QString tempID, QString namaP) {
    // Open corresponding doctor file
    QFile listPasienD("C:/Users/Steven Ciam/Documents/qt-projects/fp-strukdat/" + tempID + ".txt");
    if(!listPasienD.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qWarning() << "Failed to open" << listPasienD.fileName()<< "for write: " << listPasienD.errorString() << "\n";
        listPasienD.close();
    }
    QTextStream streamD(&listPasienD);
    // Open admin file
    QFile listPasienA("C:/Users/Steven Ciam/Documents/qt-projects/fp-strukdat/log.txt");
    if(!listPasienA.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qWarning() << "Failed to open" << listPasienA.fileName()<< "for write: " << listPasienA.errorString() << "\n";
        listPasienA.close();
    }
    QTextStream streamA(&listPasienA);

    QString pasienD = streamD.readAll();
    QStringList pasienDList = pasienD.split("\n");
    QString pasienA = streamA.readAll();
    QStringList pasienAList = pasienA.split("\n");

    // Iterasi file doctor, if found insert new riwayat ke line pasien
    for(int i = 0; i < pasienDList.length(); i++) {
        QString line = pasienDList.at(i);
        if(!line.isEmpty()) {
            QStringList lineSplit = line.split(';');
            int jumlahRiwayat = lineSplit.at(0).toInt();
            QString namaSplit = lineSplit.at(jumlahRiwayat*4+1);
            // Compare
            if(QString::compare(namaSplit, namaP, Qt::CaseInsensitive) == 0) {
                // Insert new riwayat lineSplit
                lineSplit[0] = QString::number(jumlahRiwayat + 1);
                lineSplit.insert(jumlahRiwayat*4+1, riwayatNamaDokterLine->text());
                lineSplit.insert(jumlahRiwayat*4+2, riwayatSakitPasienLine->text());
                lineSplit.insert(jumlahRiwayat*4+3, riwayatTanggalMasukPasienLine->text());
                lineSplit.insert(jumlahRiwayat*4+4, riwayatTanggalKeluarPasienLine->text());
                // replace new lineSplit to i'th index of pasienDList
                line = lineSplit.join(';');
                pasienDList[i] = line;
                // Join pasienDList to become new content
                QString newContent = pasienDList.join("\n");
                // Replace old content with new content
                listPasienD.resize(0);
                streamD << newContent;
            }
        }
    }

    // Iterasi file admin, if found insert new riwayat ke line pasien
    for(int i = 0; i < pasienAList.length(); i++) {
        QString line = pasienAList.at(i);
        if(!line.isEmpty()) {
            QStringList lineSplit = line.split(';');
            int jumlahRiwayat = lineSplit.at(0).toInt();
            QString namaSplit = lineSplit.at(jumlahRiwayat*4+1);
            // Compare
            if(QString::compare(namaSplit, namaP, Qt::CaseInsensitive) == 0) {
                // Insert new riwayat lineSplit
                lineSplit[0] = QString::number(jumlahRiwayat + 1);
                lineSplit.insert(jumlahRiwayat*4+1, riwayatNamaDokterLine->text());
                lineSplit.insert(jumlahRiwayat*4+2, riwayatSakitPasienLine->text());
                lineSplit.insert(jumlahRiwayat*4+3, riwayatTanggalMasukPasienLine->text());
                lineSplit.insert(jumlahRiwayat*4+4, riwayatTanggalKeluarPasienLine->text());
                // replace new lineSplit to i'th index of pasienDList
                line = lineSplit.join(';');
                pasienAList[i] = line;
                // Join pasienAList to become new content
                QString newContent = pasienAList.join("\n");
                // Replace old content with new content
                listPasienA.resize(0);
                streamA << newContent;
            }
        }
    }

    // Close files
    listPasienD.close();
    listPasienA.close();

    // Pemberitahuan
    QMessageBox::about(this, "Informasi", "Riwayat pasien berhasil ditambah");
}

void AdminPage::tampilPasien(QString IDDokter) {
    QFile listPasienD("C:/Users/Steven Ciam/Documents/qt-projects/fp-strukdat/" + IDDokter + ".txt");
    listPasienD.open(QIODevice::ReadOnly);
    QTextStream in(&listPasienD);

    // Ambil nama dari list item
    QString namaP = riwayatPasienLine->text();
    // Clear list widget items
    listPasien->clear();
    bool found = false;

    // Loop through file, if name match add name to list
    while(!in.atEnd()) {
        QString line = in.readLine();
        QStringList lineSplit = line.split(';');
        int jumlahRiwayat = lineSplit.at(0).toInt();
        QString namaSplit = lineSplit.at(jumlahRiwayat*4+1);
        // Compare
        if(namaSplit.contains(namaP, Qt::CaseInsensitive)) {
            listPasien->addItem(namaSplit);
            found = true;
        }
    }

    // Close file
    listPasienD.close();
    // Pemberitahuan jika tidak ada yang cocok
    if(!found) {
        QMessageBox::warning(this, "Eror", "Pasien tidak ditemukan");
    }
}

void AdminPage::hapusDokter() {
    // Open listDokter.txt
    QFile listDokter("C:/Users/Steven Ciam/Documents/qt-projects/fp-strukdat/listDokter.txt");
    if(!listDokter.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qWarning() << "Failed to open" << listDokter.fileName()<< "for read write: " << listDokter.errorString() << "\n";
        listDokter.close();
    }
    // File stream
    QTextStream stream(&listDokter);
    // Convert text to list
    QStringList daftarDokter = stream.readAll().split('\n');
    // Iterate
    QStringList daftarDokterBaruList;
    QString idInput = hapusIdDokterLine->text();
    for(QString dataDokter : daftarDokter) {
        // Ambil id saja
        QString id = dataDokter.split(';')[0];
        // Comapre dengan id inputan user
        if(QString::compare(idInput, id) != 0) {
            // Jika tidak sama, tambah ke list baru
            daftarDokterBaruList.append(dataDokter);
        }
    }
    // Gabung list menjadi satu text
    QString datarDokterBaru = daftarDokterBaruList.join('\n');
    // Hapus data lama, masukkan daftar dokter baru
    listDokter.resize(0);
    stream << datarDokterBaru;
    // Tutup file
    listDokter.close();
    // Pesan
    QMessageBox::about(this, "Info", "Dokter berhasil dihapus");
}

void AdminPage::tambahDokter() {
    // Open listDokter.txt
    QFile listDokter("C:/Users/Steven Ciam/Documents/qt-projects/fp-strukdat/listDokter.txt");
    if(!listDokter.open(QIODevice::Append | QIODevice::Text)) {
        qWarning() << "Failed to open" << listDokter.fileName()<< "for append: " << listDokter.errorString() << "\n";
        listDokter.close();
    }
    // File stream
    QTextStream out(&listDokter);

    QString id = tambahDokterId->text();
    QString nama = tambahDokterNama->text();
    QString pass = tambahDokterPass->text();

    // Tambah ke file
    out << id << ';' << nama << ';' << pass << '\n';
    // Tutup file
    listDokter.close();
    // Pesan
    QMessageBox::about(this, "Info", "Dokter berhasil ditambah");
}

void AdminPage::on_lihatPasienButton_clicked() {
    if(jumlahPasienLog() == 0) {
        QMessageBox::warning(this, "Eror", "Tidak ada data pasien");
    } else {
        lihatPasienAdmin();
    }
}

void AdminPage::on_cariPasienButton_clicked() {
    if(jumlahPasienLog() == 0) {
        QMessageBox::warning(this, "Eror", "Tidak ada data pasien");
    } else {
        cariPasienAdmin(cariPasien->text());
    }
}

void AdminPage::on_hapusPasienButton_clicked() {
    hospital *hospitalA = new hospital();
    QString IDDokter = hapusDokterLine->text();
    int jumlahDokter = hospitalA->inputListDokter();

    if(!hospitalA->Exist(IDDokter, jumlahDokter)) {
        QMessageBox::warning(this, "Eror", "ID Dokter tidak ditemukan");
    } else {
        hapusPasien(IDDokter);
    }
}

void AdminPage::on_tambahButton_clicked() {
    hospital *hospitalA = new hospital();
    QString IDDokter = tambahDokterLine->text();
    int jumlahDokter = hospitalA->inputListDokter();

    if(!hospitalA->Exist(IDDokter, jumlahDokter)) {
        QMessageBox::warning(this, "Eror", "ID Dokter tidak ditemukan");
    } else {
        tambahPasien(IDDokter);
    }
}

void AdminPage::on_tambahRiwayatButton_clicked() {
    QString IDDokter = riwayatIDDokterLine->text();
    tampilPasien(IDDokter);
}

void AdminPage::on_hapusDokterButton_clicked() {
    hospital *hospitalA = new hospital();
    QString IDDokter = hapusIdDokterLine->text();
    int jumlahDokter = hospitalA->inputListDokter();

    if(!hospitalA->Exist(IDDokter, jumlahDokter)) {
        QMessageBox::warning(this, "Eror", "ID Dokter tidak ditemukan");
    } else {
        hapusDokter();
    }
}

void AdminPage::on_tambahDokterButton_clicked() {
    hospital *hospitalA = new hospital();
    QString IDDokter = tambahDokterId->text();
    int jumlahDokter = hospitalA->inputListDokter();

    if(hospitalA->Exist(IDDokter, jumlahDokter)) {
        QMessageBox::warning(this, "Eror", "Dokter sudah terdaftar");
    } else {
        tambahDokter();
    }
}

void AdminPage::on_logoutButton_clicked()
{
    this->close();
    hospital *hospitalA = new hospital;
    hospitalA->show();
}








