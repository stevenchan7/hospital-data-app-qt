#ifndef DOKTERPAGE_H
#define DOKTERPAGE_H

#include <QWidget>
#include <QTableWidgetItem>

namespace Ui {
class DokterPage;
}

class DokterPage : public QWidget
{
    Q_OBJECT

public:
    explicit DokterPage(QWidget *parent = nullptr);
    ~DokterPage();

private slots:
    void on_semuaPasienButton_clicked();

    void on_cariPasienButton_clicked();

    void on_logoutButton_clicked();
    void on_tableItem_clicked(QTableWidgetItem *item);
private:
    Ui::DokterPage *ui;
    int jumlahPasiendokter(QString tempID);
    void lihatPasienDokter(QString tempID);
    void cariPasienDokter (QString tempID, QString namaP);
};

#endif // DOKTERPAGE_H
