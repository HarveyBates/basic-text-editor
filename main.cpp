#include "mainwindow.h"

#include <QApplication> // Handles widgets and event handling

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
