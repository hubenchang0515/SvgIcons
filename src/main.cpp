#include <QApplication>
#include "mainwindow.h"

using namespace SvgIcon;

int main(int argc, char* argv[])
{
    QApplication app{argc, argv};
    MainWindow window;
    window.show();
    return app.exec();
}