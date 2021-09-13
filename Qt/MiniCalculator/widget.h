#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    QMessageBox errorBox; //MessageBox для вывода ошибок

    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:

    void on_calcButton_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
