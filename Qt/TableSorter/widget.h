#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTableWidgetItem>
#include <QRandomGenerator>
#include <QMessageBox>
#include <chrono>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

enum SortType{
    Bubble, Quick, Comb, Gnome, Bogo, Bozo
};

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    //Функции заполнения
    void fillArrayRandom();
    void fillArrayZero();
    void fillTable(double*);

    //Алгоритмы сортировки
    void callBubbleSort();
    void callQuickSort(double*, int, int);

private slots:
    void on_createArrayButton_clicked();

    void on_arrayCountEdit_textChanged(const QString &arg1);

    void on_fillRandomButton_clicked();

    void on_dataTable_itemChanged(QTableWidgetItem *item);

    void on_checkErrorButton_clicked();

    void on_sortButton_clicked();
private:
    QMessageBox* waitBox;
    int arrLen = 0;
    void setWidgetProperty(QWidget*, const char*,const QVariant&);
    void setItemTextColor(QTableWidgetItem*, QColor);
    bool checkErrors();
    bool isCreated = false;
    void resizeEvent(QResizeEvent *event);
    void updateTableHeaderSize();
    void setupMessageBox();
    double* getTableArray();
    Ui::Widget *ui;
};
#endif // WIDGET_H