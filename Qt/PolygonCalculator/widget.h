#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QListWidgetItem>
#include <map>
#include <math.h> //sqrt, pow
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
    double dabs(double x);
    double vectorMultiple(double x1, double y1, double x2, double y2);
    bool checkCross(Point p1, Point p2, Point p3, Point p4);
    std::map<QListWidgetItem*, Point*>::iterator getByIndex(std::map<QListWidgetItem*, Point*>::iterator start, int index);
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_addPointButton_clicked();

    void on_removePointButton_clicked();

    void on_pointList_itemClicked(QListWidgetItem *item);

    void on_xEdit_textChanged(const QString &arg1);

    void on_yEdit_textChanged(const QString &arg1);

private:
    double calculatePerimeter();
    void calculatePolygonSides();
    double calculatePolygonSquare();
    bool hasCross();
    void calculateAll();
    Ui::Widget *ui;
};
#endif // WIDGET_H
