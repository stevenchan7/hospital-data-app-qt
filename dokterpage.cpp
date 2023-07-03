#include "dokterpage.h"
#include "hospital.h"
#include "ui_dokterpage.h"
#include <QFile>
#include <QTextStream>
#include <bits/stdc++.h>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QMessageBox>

using namespace std;

DokterPage::DokterPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DokterPage)
{
    ui->setupUi(this);
    ui->tabelDataPasien->setRowCount(10);
    ui->tabelDataPasien->setColumnCount(4);
    ui->tabelDataPasien->setHorizontalHeaderLabels({"Nama", "Umur", "Gender", "Alamat"});
    connect(ui->tabelDataPasien, &QTableWidget::itemClicked, this, &DokterPage::on_tableItem_clicked);
}

DokterPage::~DokterPage()
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

int DokterPage::jumlahPasiendokter(QString tempID)
{
    QFile listPasienD(":/"+tempID+".txt");
    listPasienD.open(QIODevice::ReadOnly);
    QTextStream in(&listPasienD);

    int jumlahPasien = 0;
    while(!in.atEnd())
    {
        in.readLine();
        jumlahPasien++;
    }
    listPasienD.close();
    return jumlahPasien;
}

void DokterPage::lihatPasienDokter (QString tempID)
{
    QFile listPasienD(":/"+tempID+".txt");
    listPasienD.open(QIODevice::ReadOnly);
    QTextStream in(&listPasienD);
    struct dataP dataPasienTemp;

    int jml = 1;
    int jumlahriwayat;
    int rowCounter = 0;
    // Hapus teks edit
    ui->textEdit->clear();
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
        ui->tabelDataPasien->setItem(rowCounter, 0, itemTNama);
        ui->tabelDataPasien->setItem(rowCounter, 1, itemTUmur);
        ui->tabelDataPasien->setItem(rowCounter, 2, itemTGender);
        ui->tabelDataPasien->setItem(rowCounter, 3, itemTAlamat);
        rowCounter++;
    /*
        // Data Pasien
        ui->textEdit->insertPlainText("Data pasien ke-" + QString::number(jml));
        ui->textEdit->moveCursor(QTextCursor::End);
        jml++;
        ui->textEdit->insertPlainText("\nNama: " + dataPasienTemp.nama + "\nUmur: " + QString::number(dataPasienTemp.umur) + "\nJenis kelamin: " + dataPasienTemp.gender + "\nAlamat: " + dataPasienTemp.alamat + "\n");
        ui->textEdit->moveCursor(QTextCursor::End);
        // Riwayat pasien
        node=head;
        int jml2 = 1;
        while(node!=NULL){
            ui->textEdit->insertPlainText("Riwayat ke-" + QString::number(jml2));
            ui->textEdit->moveCursor(QTextCursor::End);
            ui->textEdit->insertPlainText("\nDokter: " + node->dokterPasien + "\nPenyakit: " + node->penyakit + "\nTanggal kunjungan: " + node->tanggalKunjungan + "\nTanggal keluar: " + node->tanggalKeluar + "\n");
            ui->textEdit->moveCursor(QTextCursor::End);
            node = node->next;
            jml2++;
        }
        ui->textEdit->insertPlainText("\n\n");
        ui->textEdit->moveCursor(QTextCursor::End);
    */
        //hapus linked list
        while(head!=NULL)
        {
            node = head;
            head = head->next;
            delete node;
        }

    }
    listPasienD.close();
}

void DokterPage::cariPasienDokter (QString tempID, QString namaP)
{
    QFile listPasienD(":/"+tempID+".txt");
    listPasienD.open(QIODevice::ReadOnly);
    QTextStream in(&listPasienD);
    struct dataP dataPasienTemp;

    int jml = 1;
    int jumlahriwayat;
    bool ketemu = false;
    // Hapus teks edit
    ui->textEdit->clear();
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
            ui->textEdit->insertPlainText("Data pasien ke-" + QString::number(jml));
            ui->textEdit->moveCursor(QTextCursor::End);
            jml++;
            ui->textEdit->insertPlainText("\nNama: " + dataPasienTemp.nama + "\nUmur: " + QString::number(dataPasienTemp.umur) + "\nJenis kelamin: " + dataPasienTemp.gender + "\nAlamat: " + dataPasienTemp.alamat + "\n");
            ui->textEdit->moveCursor(QTextCursor::End);
            node=head;
            int jml2 = 1;

            while(node!=NULL){
                ui->textEdit->insertPlainText("Riwayat ke-" + QString::number(jml2));
                ui->textEdit->moveCursor(QTextCursor::End);
                ui->textEdit->insertPlainText("\nDokter: " + node->dokterPasien + "\nPenyakit: " + node->penyakit + "\nTanggal kunjungan: " + node->tanggalKunjungan + "\nTanggal keluar: " + node->tanggalKeluar + "\n");
                ui->textEdit->moveCursor(QTextCursor::End);
                node = node->next;
                jml2++;
            }
            ui->textEdit->insertPlainText("\n\n");
            ui->textEdit->moveCursor(QTextCursor::End);
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
    listPasienD.close();
}

void DokterPage::on_semuaPasienButton_clicked()
{
    if(jumlahPasiendokter(tempIDLogin)==0)
    {
        QMessageBox::warning(this, "Eror", "Tidak ada data pasien");
    } else{
        lihatPasienDokter(tempIDLogin);
    }
}


void DokterPage::on_cariPasienButton_clicked()
{
    if(jumlahPasiendokter(tempIDLogin)==0)
    {
        QMessageBox::warning(this, "Eror", "Tidak ada data pasien");
    }
    else{
        cariPasienDokter(tempIDLogin, ui->cariPasien->text());
    }
}

void DokterPage::on_tableItem_clicked(QTableWidgetItem *item) {
    cariPasienDokter(tempIDLogin, item->text());
}

void DokterPage::on_logoutButton_clicked()
{
    this->close();
    hospital *hospitall = new hospital;
    hospitall->show();
}

