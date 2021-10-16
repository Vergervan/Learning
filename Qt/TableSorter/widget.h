#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTableWidgetItem>
#include <QRandomGenerator>
#include <QMessageBox>
#include <QDialog>
#include <chrono>
#include <time.h>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

enum SortType{
    Bubble, Quick, Comb, Gnome, Bogo
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

    void swap(double*, double*);
    int partition (double*, int, int);
    bool correct(double*, int);
    void shuffle(double*);
private slots:
    void on_createArrayButton_clicked();

    void on_arrayCountEdit_textChanged(const QString &arg1);

    void on_fillRandomButton_clicked();

    void on_dataTable_itemChanged(QTableWidgetItem *item);

    void on_checkErrorButton_clicked();

    void on_sortButton_clicked();

    void on_searchBackButton_clicked();

    void on_searchForwardButton_clicked();

    void on_searchEdit_returnPressed();

    void on_searchEdit_textChanged(const QString &arg1);

private:
    //QDialog* waitBox;
    int arrLen = 0;
    double key = 0;
    std::vector<int> s_indexes;
    std::vector<int>::iterator cur_index;
    void setWidgetProperty(QWidget*, const char*,const QVariant&);
    void setItemTextColor(QTableWidgetItem*, QColor);
    void setEnabledSearchButtons(bool);
    bool checkErrors();
    bool isCreated = false;
    void createTable(int);
    bool getArrayCount(QString, int* = nullptr);
    void updateTableHeaderSize();
    //void setupMessageBox();
    //void setupWaitBox();

    //Алгоритмы сортировки
    void bubbleSort(double*);
    void quickSort(double*, int, int);
    void combSort(double*);
    void gnomeSort(double*);
    void bogoSort(double*);

    double getMinValue(double*, bool = false);
    double getMaxValue(double*, bool = false);
    void refreshMaxAndMinValues(double* = nullptr, bool = false);

    void searchValue(double);
    void binarySearch(std::vector<int>*, double*,double);
    void linearSearch(std::vector<int>*, double*,double);

    void chooseItem(int index);
    std::vector<int>::iterator incIndex();
    std::vector<int>::iterator decIndex();

    double* getTableArray();
    Ui::Widget *ui;
};
#endif // WIDGET_H
