#include "guihash.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GuiHash w;
    w.show();

    return a.exec();
}
