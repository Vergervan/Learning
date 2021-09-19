#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:

    void ChangeBackGroundColor(bool);
    void Calculate();

    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_firstOperandCmb_currentIndexChanged(int index);

    void on_cmbOperation_currentIndexChanged(int index);

    void on_secondOperandCmb_currentIndexChanged(int index);

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
