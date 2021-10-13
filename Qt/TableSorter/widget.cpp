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

    //waitBox = new QDialog;
    //setupWaitBox();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::resizeEvent(QResizeEvent*){
    updateTableHeaderSize();
}

/*void Widget::setupWaitBox(){
    QLabel* lbl = new QLabel(waitBox);
    lbl->setText("Sorting is in the process\nPlease wait...");
    lbl->setAlignment(Qt::AlignCenter);
    lbl->setWordWrap(true);
    lbl->setGeometry(0, 0, 200, 80);
    waitBox->setFixedSize(200, 80);
    waitBox->setWindowTitle("Message");
}*/

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

void Widget::swap(double* el1, double* el2){
    double swp = *el2;
    *el2 = *el1;
    *el1 = swp;
}

void Widget::on_checkErrorButton_clicked()
{
    checkErrors();
}

void Widget::on_sortButton_clicked()
{
    if(arrLen < 1) return;
    if(checkErrors()) return;
    auto start = std::chrono::high_resolution_clock::now();
    switch(ui->sortCmb->currentIndex()){
    case Bubble:
        callBubbleSort();
        break;
    case Quick:
        callQuickSort();
        break;
    case Comb:

        break;
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop-start);
    ui->sortTimeLabel->setText(QString("Time: ") + QString::number(duration.count()) + " ms");
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
    bool changed = true;
    while(changed){
        changed = false;
        for(int i = 0; i < arrLen-1;++i){
            if(nums[i] > nums[i+1]){
                swap(&nums[i], &nums[i+1]);
                changed = true;
            }
        }
    }
    fillTable(nums);
    delete[] nums;
}

void Widget::callQuickSort(){
    double* nums = getTableArray();
    quickSort(nums, 0, arrLen-1);
    fillTable(nums);
    delete[] nums;
}

void Widget::quickSort(double* arr, int low, int high){
    if (low >= high) return;
    /* pi is partitioning index, arr[p] is now
        at right place */
    int pi = partition(arr, low, high);

    // Separately sort elements before
    // partition and after partition
    quickSort(arr, low, pi - 1);
    quickSort(arr, pi + 1, high);
}

int Widget::partition (double* arr, int low, int high)
{
    int pivot = arr[high]; // pivot
    int i = (low - 1); // Index of smaller element and indicates the right position of pivot found so far
    for (int j = low; j <= high - 1; j++)
    {
        // If current element is smaller than the pivot
        if (arr[j] < pivot)
        {
            i++; // increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}


