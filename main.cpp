#include "hospital.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    hospital w;
    w.show();
    return a.exec();
}
