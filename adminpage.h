#ifndef ADMINPAGE_H
#define ADMINPAGE_H

#include <QWidget>
#include <QPushButton>
#include <QTextEdit>
#include <QLineEdit>
#include <QListWidget>
#include <QTableWidget>
#include "hospital.h"

namespace Ui {
class AdminPage;
}

class AdminPage : public QWidget
{
    Q_OBJECT

public:
    explicit AdminPage(QWidget *parent = nullptr);
    ~AdminPage();

private slots:
    void on_lihatPasienButton_clicked();
    void on_cariPasienButton_clicked();
    void on_hapusPasienButton_clicked();
    void on_tambahButton_clicked();
    void on_tambahRiwayatButton_clicked();
    void on_itemClicked(QListWidgetItem *item) {
        QString namaP = item->text();
        tambahRiwayat(riwayatIDDokterLine->text(), namaP);
    }
    void on_hapusDokterButton_clicked();
    void on_tambahDokterButton_clicked();
    void on_tableItem_clicked(QTableWidgetItem *item) {
        cariPasienAdmin(item->text());
    }
    void on_logoutButton_clicked();

private:
    Ui::AdminPage *ui;
    int jumlahPasienLog();
    void lihatPasienAdmin();
    void cariPasienAdmin(QString namaP);
    void hapusPasien(QString tempID);
    void hapusPasienLog(QString tempID);
    void tambahPasien(QString tempID);
    void tambahRiwayat(QString tempID, QString namaP);
    void tampilPasien(QString IDDokter);
    void hapusDokter();
    void tambahDokter();
    QWidget *halamanLihatPasien;
    QPushButton *lihatPasienButton;
    QPushButton *cariPasienButton;
    QLineEdit *cariPasien;
    QTextEdit *textEditPasien;
    QPushButton *hapusPasienButton;
    QLineEdit *hapusPasienLine;
    QLineEdit *hapusDokterLine;
    QTableWidget *tabelDataPasien;
    QPushButton *logoutButton;
    // HALAMAN TAMBAH
    QLineEdit *tambahPasienLine;
    QLineEdit *tambahDokterLine;
    QLineEdit *tambahUmurLine;
    QLineEdit *tambahGenderLine;
    QLineEdit *tambahAlamatLine;
    QPushButton *tambahButton;
    // HALAMAN TAMBAH RIWAYAT
     QLineEdit *riwayatIDDokterLine;
     QLineEdit *riwayatNamaDokterLine;
     QLineEdit *riwayatPasienLine;
     QLineEdit *riwayatSakitPasienLine;
     QLineEdit *riwayatTanggalMasukPasienLine;
     QLineEdit *riwayatTanggalKeluarPasienLine;
     QPushButton *tambahRiwayatButton;
     QListWidget *listPasien;
     // HALAMAN HAPUS DOKTER
     QLineEdit *hapusIdDokterLine;
     QPushButton *hapusDokterButton;
     // HALAMAN TAMBAH DOKTER
     QLineEdit *tambahDokterId;
     QLineEdit *tambahDokterPass;
     QLineEdit *tambahDokterNama;
     QPushButton *tambahDokterButton;

};

#endif // ADMINPAGE_H
