#include "tilitoli.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TiliToli w;
    w.show();

    return a.exec();
}
