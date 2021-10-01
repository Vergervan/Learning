#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLineEdit>

#include <math.h>
#include "triangle.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    Triangle trngl;
    void calculateAll();
    ~Widget();
private slots:
    void on_x1Edit_textChanged(const QString &arg1);
    void on_y1Edit_textChanged(const QString &arg1);
    void on_x2Edit_textChanged(const QString &arg1);
    void on_y2Edit_textChanged(const QString &arg1);
    void on_x3Edit_textChanged(const QString &arg1);
    void on_y3Edit_textChanged(const QString &arg1);

private:
    bool checkEditResult(QLineEdit*, bool);
    void refreshResultsStyle();
    void readPoints();
    bool hasError = false;

    Ui::Widget *ui;
};
#endif // WIDGET_H
