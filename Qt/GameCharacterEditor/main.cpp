#include "widget.h"

#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile styleFile(":/style.css");
    styleFile.open(QFile::ReadOnly);
    a.setStyleSheet(styleFile.readAll());

    Widget w;
    w.show();
    return a.exec();
}
