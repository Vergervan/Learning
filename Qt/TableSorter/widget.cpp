#include "widget.h"
#include "ui_widget.h"

#include <QScrollBar>
#include <QFile>
#include <QTimer>

#define MIN_ARRAY_SIZE 1
#define MAX_ARRAY_SIZE 100000

#define RAND_NUM_BOUND 1000000 //Максимальная граница случайного числа

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setStyle(QApplication::style());

    waitBox = new QDialog;
    setupWaitBox();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::resizeEvent(QResizeEvent*){
    updateTableHeaderSize();
}

void Widget::setupWaitBox(){
    QLabel* lbl = new QLabel(waitBox);
    lbl->setText("Sorting is in the process\nPlease wait...");
    lbl->setAlignment(Qt::AlignCenter);
    lbl->setWordWrap(true);
    lbl->setGeometry(0, 0, 200, 80);
    waitBox->setFixedSize(200, 80);
    waitBox->setWindowTitle("Message");
}

/*void Widget::setupMessageBox(){
    waitBox = new QMessageBox(this);
    waitBox->setWindowTitle("Message");
    waitBox->setStyleSheet("width: 150px;");
    waitBox->setStandardButtons((QMessageBox::StandardButton)0);
    waitBox->setText("<p align='center'>Sorting is in process<br>Please wait...</p>");
}*/

void Widget::updateTableHeaderSize(){
    double columnRatio = (double)(ui->dataTable->width()/30)-6.1; //Коэффициент изменения экрана
    ui->dataTable->setColumnWidth(0, ui->dataTable->width() - 30 + columnRatio); //Гибкая смена ширины заголовка таблицы в зависимости от размеров экрана
}

void Widget::on_createArrayButton_clicked()
{
    isCreated = false;
    if(arrLen == 0) return;
    ui->dataTable->clear();
    ui->dataTable->setColumnCount(1);
    ui->dataTable->setRowCount(arrLen);
    ui->dataTable->setHorizontalHeaderLabels({"Значение"});
    fillArrayZero();
    updateTableHeaderSize();
    isCreated = true;
}

void Widget::setItemTextColor(QTableWidgetItem* item, QColor color){
    item->setForeground(QBrush(color));
}

void Widget::setWidgetProperty(QWidget* obj, const char* name,const QVariant& value){
        obj->setProperty(name, value);
        obj->style()->unpolish(obj);
        obj->style()->polish(obj);
}

void Widget::on_arrayCountEdit_textChanged(const QString &arg1)
{
    bool ok = true;
    arrLen = arg1.toInt(&ok);
    if(arrLen < MIN_ARRAY_SIZE || arrLen > MAX_ARRAY_SIZE){
        ok = false;
        arrLen = 0;
    }
    setWidgetProperty(ui->arrayCountEdit, "state", ok ? "" : "error");
}

void Widget::fillArrayRandom(){
    ui->dataTable->clearSelection();
    srand(time(NULL));
    int x = 0;
    for(int i = 0; i < arrLen; i++){
        x = rand();
        ui->dataTable->item(i, 0)->setText(QString::number(x));
    }
}

void Widget::fillArrayZero(){
    for(int i = 0; i < arrLen; i++)
        ui->dataTable->setItem(i, 0, new QTableWidgetItem("0"));
}

void Widget::on_fillRandomButton_clicked()
{
    fillArrayRandom();
}

void Widget::on_dataTable_itemChanged(QTableWidgetItem *item)
{
    if(!isCreated) return;
    bool ok = true;
    item->text().toDouble(&ok);
    setItemTextColor(item, ok ? Qt::black : Qt::red);
    if(!ok){
        ui->dataTable->scrollToItem(item);
        item->setSelected(true);
    }
}

bool Widget::checkErrors(){
    QTableWidgetItem* firstErr = nullptr;
    bool ok = true;
    for(int i = 0; i < arrLen; i++){
        ui->dataTable->item(i, 0)->text().toDouble(&ok);
        if(!ok) {
            if(firstErr == nullptr) firstErr = ui->dataTable->item(i, 0);
        }
        setItemTextColor(ui->dataTable->item(i, 0), ok ? Qt::black : Qt::red);
    }
    if(firstErr != nullptr) {
        ui->dataTable->clearSelection();
        ui->dataTable->clearFocus();
        ui->dataTable->scrollToItem(firstErr);
        firstErr->setSelected(true);
        ui->dataTable->setFocus();
        return true;
    }
    return false;
}



void Widget::on_checkErrorButton_clicked()
{
    checkErrors();
}

void Widget::on_sortButton_clicked()
{
    if(arrLen < 1) return;
    if(checkErrors()) return;
    waitBox->show();
    auto start = std::chrono::high_resolution_clock::now();
    switch(ui->sortCmb->currentIndex()){
    case Bubble:
        callBubbleSort();
        break;
    case Comb:

        break;
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop-start);
    ui->sortTimeLabel->setText(QString("Time: ") + QString::number(duration.count()) + " micro sec");
    waitBox->hide();
}

void Widget::fillTable(double* arr){
    for(int i = 0; i < arrLen; i++){
        ui->dataTable->item(i, 0)->setText(QString::number(arr[i]));
    }
}

double* Widget::getTableArray(){
    double* numbers = new double[arrLen];
    for(int i = 0; i < arrLen; i++) numbers[i] = ui->dataTable->item(i, 0)->text().toDouble();
    return numbers;
}

void Widget::callBubbleSort(){
    double* nums = getTableArray();
    double swp = 0;
    bool changed = true;
    while(changed){
        changed = false;
        for(int i = 0; i < arrLen-1;++i){
            if(nums[i] > nums[i+1]){
                swp = nums[i+1];
                nums[i+1] = nums[i];
                nums[i] = swp;
                changed = true;
            }
        }
    }
    fillTable(nums);
    delete[] nums;
}

void Widget::callQuickSort(double* arr,int first,int last){
    int pivot,i,j,temp;

     if(first < last){
         pivot = first;
         i = first;
         j = last;

         while(i < j){
             while(arr[i] <= arr[pivot] && i < last)
                 i++;
             while(arr[j] > arr[pivot])
                 j--;
             if(i <j){
                  temp = arr[i];
                  arr[i] = arr[j];
                  arr[j] = temp;
             }
         }

         temp = arr[pivot];
         arr[pivot] = arr[j];
         arr[j] = temp;
         callQuickSort(arr,first,j-1);
         callQuickSort(arr,j+1,last);
         fillTable(arr);
    }
}

void Widget::quickSort(double* arr, int left, int right){
    srand(time(NULL));
    if(left >= right) return;
    int pivot = (right + left)/2;
    int i = left , j = right;
    while(i < j){
        while(arr[i] <= arr[pivot]) ++i;
        while(arr[j] > arr[pivot]) --j;
        if(i < j){
            //swap(arr+i, arr+j);
        }
    }
    quickSort(arr, left, j-1);
    quickSort(arr, i, right);
}


