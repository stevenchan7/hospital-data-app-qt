#include "hospital.h"
#include "./ui_hospital.h"
#include <QFile>
#include <QTextStream>
#include <QTimer>
#include <bits/stdc++.h>

using namespace std;

hospital::hospital(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::hospital)
{
    ui->setupUi(this);
    loadTextFile();
}

hospital::~hospital()
{
    delete ui;
}

struct dataD{
    QString id;
    QString namaLengkap;
    QString password;
};

struct dataA{
    QString id;
    QString namaLengkap;
    QString password;
};

struct dataD dataDokter[1000];
struct dataA dataAdmin[5];
QString tempIDLogin;
QString tempIDLoginA;

void hospital::loadTextFile(){
    QFile listDokter(":/listDokter.txt");
    listDokter.open(QIODevice::ReadOnly);

    QTextStream in(&listDokter);
    QString line = in.readAll();
    listDokter.close();

    ui->textEdit->setPlainText(line);
}

int hospital::inputListDokter(){
    QFile listDokter(":/listDokter.txt");
    listDokter.open(QIODevice::ReadOnly);
    QTextStream in(&listDokter);

    int counter = 0;

    while(!in.atEnd()) {
        // UDAH MAU NI BOSS
        QString dataDokterr = in.readLine();
        QStringList dataDokterrr = dataDokterr.split(';');
        dataDokter[counter].id = dataDokterrr.at(0);
        dataDokter[counter].namaLengkap = dataDokterrr.at(1);
        dataDokter[counter].password = dataDokterrr.at(2);
        counter++;
    }

    return counter;
    listDokter.close();
}

int hospital::inputListAdmin(){
    QFile listAdmin(":/listAdmin.txt");
    listAdmin.open(QIODevice::ReadOnly);
    QTextStream in(&listAdmin);

    int counter = 0;

    while(!in.atEnd()) {
        // UDAH MAU NI BOSS
        QString dataAdminn = in.readLine();
        QStringList dataAdminnn = dataAdminn.split(';');
        dataAdmin[counter].id = dataAdminnn.at(0);
        dataAdmin[counter].namaLengkap = dataAdminnn.at(1);
        dataAdmin[counter].password = dataAdminnn.at(2);
        counter++;
    }

    return counter;
    listAdmin.close();
}

bool hospital::Exist(QString tempID, int jumlahDokter)
{
    for(int i = 0; i < jumlahDokter; i++)
    {
        if(QString::compare(tempID, dataDokter[i].id, Qt::CaseInsensitive) == 0)
        {
            return 1;
        }
    }
    return 0;
}

bool hospital::Exist2(QString tempID, int jumlahAdmin)
{
    for(int i = 0; i < jumlahAdmin; i++)
    {
        if(QString::compare(tempID, dataAdmin[i].id, Qt::CaseInsensitive) == 0)
        {
            return 1;
        }
    }
    return 0;
}

bool hospital::checkPass(QString tempID, QString tempPass, int jumlahDokter)
{
    for(int i = 0; i < jumlahDokter; i++)
    {
        if(QString::compare(tempID, dataDokter[i].id, Qt::CaseInsensitive) == 0)
        {
            if(QString::compare(tempPass, dataDokter[i].password, Qt::CaseSensitive) == 0)
            {
                return 1;
            }
        }
    }
    return 0;
}

bool hospital::checkPass2(QString tempID, QString tempPass, int jumlahAdmin)
{
    for(int i = 0; i < jumlahAdmin; i++)
    {
        if(QString::compare(tempID, dataAdmin[i].id, Qt::CaseInsensitive) == 0)
        {
            if(QString::compare(tempPass, dataAdmin[i].password, Qt::CaseSensitive) == 0)
            {
                return 1;
            }
        }
    }
    return 0;
}

void hospital::reset(int *tries) {
    ui->loginButton->setEnabled(true);
    *tries = 0;
    qDebug() << "TESSSSSSSSss\n";
}

void hospital::reset2(int *tries2) {
    ui->loginButtonA->setEnabled(true);
    *tries2 = 0;
    qDebug() << "TESSSSSSSSssAdmin\n";
}

void hospital::loginDokter(int *tries)
{
//    ui->statusLoginnn->setPlainText("Login Sukses");

    // Mulai
    // Panggil inputListDokter sekaligus menghitung jumlah dokter
    int jumlahDokter = inputListDokter();
    QString tempID;

    // Masukkan id dari GUI
    tempID = ui->id->text();

    if(!Exist(tempID, jumlahDokter))
    {
        ui->statusLoginnn->setPlainText("ID tidak ditemukan");
    }
    else{
        // Copy ID to global var
        tempIDLogin = tempID;

        // Check password
        // Maukkan pass dari GUI
        QString tempPASS = ui->pass->text();
        if(checkPass(tempID, tempPASS, jumlahDokter))
        {
            ui->statusLoginnn->setPlainText("Login berhasil");
            hide();
            DokterPage *dokterPage = new DokterPage();
            dokterPage->show();
            dokterPage->activateWindow();
        }
        else if((*tries) == 3)
        {
            ui->statusLoginnn->setPlainText("Sudah 3 kali login");
            ui->loginButton->setEnabled(false);
            QTimer::singleShot(30*1000, this, [this, tries](){reset(tries);});

        }
        else{
            ui->statusLoginnn->setPlainText("Password salah silahkan coba lagi");
            (*tries)++;
        }
    }
}

void hospital::loginAdmin(int *tries2)
{
    // Mulai
    // Panggil inputListAdmin sekaligus menghitung jumlah admin
    int jumlahAdmin = inputListAdmin();
    QString tempID;

    // Masukkan id dari GUI
    tempID = ui->idA->text();

    if(!Exist2(tempID, jumlahAdmin))
    {
        ui->statusLoginnnA->setPlainText("ID tidak ditemukan");
    }
    else{
        // Copy ID to global var
        tempIDLoginA = tempID;

        // Check password
        // Maukkan pass dari GUI
        QString tempPASS = ui->passA->text();
        if(checkPass2(tempID, tempPASS, jumlahAdmin))
        {
            ui->statusLoginnnA->setPlainText("Login berhasil");
            hide();
            AdminPage *adminPage = new AdminPage();
            adminPage->show();
            adminPage->activateWindow();
        }
        else if((*tries2) == 3)
        {
            ui->statusLoginnnA->setPlainText("Sudah 3 kali login");
            ui->loginButtonA->setEnabled(false);
            QTimer::singleShot(3*1000, this, [this, tries2](){reset2(tries2);});

        }
        else{
            ui->statusLoginnnA->setPlainText("Password salah silahkan coba lagi");
            (*tries2)++;
        }
    }
}

int tries = 0;
void hospital::on_loginButton_clicked(){
    loginDokter(&tries);
}

int tries2 = 0;
void hospital::on_loginButtonA_clicked()
{
    loginAdmin(&tries2);
}

