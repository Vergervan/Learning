#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QListWidgetItem>
#include <map>
#include "point.h"

#define POINT_NAME "Точка "

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    std::map<QListWidgetItem*, Point*> points;
    void addPoint();
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_addPointButton_clicked();

    void on_removePointButton_clicked();

    void on_pointList_itemClicked(QListWidgetItem *item);

    void on_xEdit_textChanged(const QString &arg1);

    void on_yEdit_textChanged(const QString &arg1);

private:
    void calculateSides();
    Ui::Widget *ui;
};
#endif // WIDGET_H
