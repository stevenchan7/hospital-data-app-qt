#ifndef HOSPITAL_H
#define HOSPITAL_H

#include <QWidget>
#include "dokterpage.h"
#include "adminpage.h"

QT_BEGIN_NAMESPACE
namespace Ui { class hospital; }
QT_END_NAMESPACE

class hospital : public QWidget
{
    Q_OBJECT

public:
    hospital(QWidget *parent = nullptr);
    ~hospital();
    bool Exist(QString tempID, int jumlahDokter);
    int inputListDokter();

public slots:
    void reset(int *tries);
    void reset2(int *tries2);

private slots:
    void on_loginButton_clicked();
    void on_loginButtonA_clicked();

private:
    Ui::hospital *ui;
    void loadTextFile();
    void loginDokter(int *tries);
    void loginAdmin(int *tries2);
    int inputListAdmin();
    bool Exist2(QString tempID, int jumlahAdmin);
    int jumlahDokter();
    bool checkPass(QString tempID, QString tempPass, int jumlahDokter);
    bool checkPass2(QString tempID, QString tempPass, int jumlahAdmin);
};

extern QString tempIDLogin;
extern QString tempIDLoginA;
#endif // HOSPITAL_H
