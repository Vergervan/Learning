#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTableWidgetItem>
#include <QRandomGenerator>
#include <QMessageBox>
#include <QDialog>
#include <QKeyEvent>
#include <QThread>

#include <chrono>
#include <time.h>
#include "sorter.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

enum State{
    None, Create, Randomize, Sort, ItemChange, ErrorCheck, Remove
};

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    QTimer* eventTimer;


    //Функции заполнения
    void fillArrayRandom();
    void fillArrayZero();
    void fillTable(double*);

    void callErrorBox(QString);
    int callWarningBox(QString);

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
    void on_removeDublicatesButton_clicked();
    void on_arrayCountEdit_returnPressed();
    void on_useCurrentSizeCheckBox_stateChanged(int arg1);
    void on_removeDublicatesCheckBox_stateChanged(int arg1);

    void getSortedArray(double*, long);
    void getNewArraySize(int);
    void waitBoxReject();
public slots:
    void fillWithoutDublicates(double*);
    void startEventTimer();
    void stopEventTimer();
    void updateEvents();
    void writeLogMessage(QString);
    void changeWaitBoxText(QString);
    void dublicateWaitBox();
signals:
    void sendToSort(double*, int, Sorter::SortType, bool = false);
    void sendToRemoveDublicates(double**, int);
private:
    QDialog* waitBox;
    QMessageBox errorBox, warningBox;
    State cur_state = None;
    bool isCreated = false;
    bool resize = false;
    bool fastRemove = false; //Моментальное удаление дубликатов
    int arrLen = 0;
    std::vector<int> s_indexes;
    std::vector<int>::iterator cur_index;
    void setWidgetProperty(QWidget*, const char*,const QVariant&);
    void setItemTextColor(QTableWidgetItem*, QColor);
    void setEnabledSearchButtons(bool);
    bool checkErrors();
    bool makeTable();
    void createTable(int);
    void createItemsInTable(int, int);
    bool getArrayCount(QString, int* = nullptr);
    //void updateTableHeaderSize(); Deprecated

    void callSortArray(Sorter::SortType);

    void setupWaitBox();
    void setupErrorBox();
    void setupWarningBox();

    double getMinValue(double*, bool = false);
    double getMaxValue(double*, bool = false);
    void refreshMaxAndMinValues(double* = nullptr, bool = false);
    void refreshArrayLengthLabelValue();
    void callMaxAndMin(State, double* = nullptr);

    void callSearchValue(double* = nullptr);
    void searchValue(double, double* = nullptr);
    void binarySearch(std::vector<int>*, double*,double);
    void linearSearch(std::vector<int>*, double*,double);

    void removeDublicates(double**);

    void chooseItem(int index);
    std::vector<int>::iterator incIndex();
    std::vector<int>::iterator decIndex();

    double* getTableArray();
    Ui::Widget *ui;
};
#endif // WIDGET_H
