#include "widget.h"
#include "ui_widget.h"

#include <QScrollBar>
#include <QFile>
#include <QTimer>

#define MIN_ARRAY_SIZE 1
#define MAX_ARRAY_SIZE 100000

//TODO
//#define RAND_NUM_BOUND 1000000 // Максимальная граница случайного числа

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setStyle(QApplication::style());
    //waitBox = new QDialog;
    //setupWaitBox();
    setupDublicateBox();

    refreshMaxAndMinValues();
    setEnabledSearchButtons(false);
    cur_index = s_indexes.end();
}

Widget::~Widget()
{
    delete ui;
}
void Widget::setupDublicateBox(){
    dublicateBox.setWindowTitle("Message");
    dublicateBox.setText("Отсортируйте список перед удалением дубликатов");
    dublicateBox.setStandardButtons(QMessageBox::Ok);
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
    waitBox->setStyleSheet("width: 150px;");7
    waitBox->setStandardButtons((QMessageBox::StandardButton)0);
    waitBox->setText("<p align='center'>Sorting is in process<br>Please wait...</p>");
}*/

/*void Widget::updateTableHeaderSize(){
    double columnRatio = (double)(ui->dataTable->width()/30)-6.1; //Коэффициент изменения экрана
    ui->dataTable->setColumnWidth(0, ui->dataTable->width() - 30 + columnRatio); //Гибкая смена ширины заголовка таблицы в зависимости от размеров экрана
}*/

double Widget::getMinValue(double* arr, bool sorted){
    if(arrLen < 1) return 0;
    if(sorted) return arr[0];
    double min = arr[0];
    for(int i = 1; i < arrLen; i++)
        if(arr[i] < min) min = arr[i];
    return min;
}

double Widget::getMaxValue(double* arr, bool sorted){
    if(arrLen < 1) return 0;
    if(sorted) return arr[arrLen-1];
    double max = arr[0];
    for(int i = 1; i < arrLen; i++)
        if(arr[i] > max) max = arr[i];
    return max;
}

void Widget::refreshMaxAndMinValues(double* arr, bool sorted){
    ui->minValueLabel->setText("Min: " + (arr == nullptr ? "0" : QString::number(getMinValue(arr, sorted))));
    ui->maxValueLabel->setText("Max: " + (arr == nullptr ? "0" : QString::number(getMaxValue(arr, sorted))));
}

void Widget::on_createArrayButton_clicked()
{
    this->cur_state = Create;
    int len = 0;
    if(!getArrayCount(ui->arrayCountEdit->text(), &len)) return;
    arrLen = len;
    if(arrLen == 0) return;
    createTable(arrLen);
    fillArrayZero();
    ui->searchEdit->clear();
    ui->searchCountLabel->clear();
    this->cur_state = None;
}

void Widget::createTable(int size){
    isCreated = false;
    ui->dataTable->clear();
    ui->dataTable->setColumnCount(1);
    ui->dataTable->setRowCount(size);
    ui->dataTable->setHorizontalHeaderLabels({"Значение"});
    for(int i = 0; i < size; i++) ui->dataTable->setItem(i, 0, new QTableWidgetItem);
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
    setWidgetProperty(ui->arrayCountEdit, "state", getArrayCount(QString(arg1.toStdString().c_str())) ? "" : "error");
}

///Returns false, if convertation to number failed
bool Widget::getArrayCount(QString numstr, int* num){
    bool ok = true;
    int x = numstr.toInt(&ok);
    if(x < MIN_ARRAY_SIZE || x > MAX_ARRAY_SIZE) ok = false;
    if(num != nullptr) *num = x;
    return ok;
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
        ui->dataTable->item(i, 0)->setText("0");
}

void Widget::on_fillRandomButton_clicked()
{
    this->cur_state = Randomize;
    int len = 0;
    if(!getArrayCount(ui->arrayCountEdit->text(), &len)) return;
    if(ui->dataTable->rowCount() != len) createTable(len);
    arrLen = len;
    fillArrayRandom();

    double* nums = getTableArray();
    callMaxAndMin(Randomize, nums);
    ui->searchEdit->clear();
    ui->searchCountLabel->clear();

    delete[] nums;
    this->cur_state = None;
}

void Widget::on_dataTable_itemChanged(QTableWidgetItem *item)
{
    if(!isCreated || this->cur_state != None) return;
    this->cur_state = ItemChange;
    bool ok = true;
    item->text().toDouble(&ok);
    setItemTextColor(item, ok ? Qt::black : Qt::red);
    if(!ok){
        ui->dataTable->scrollToItem(item);
        item->setSelected(true);
    }
    callMaxAndMin(ItemChange);
    this->cur_state = None;
    qDebug("Item changed");
}

void Widget::callMaxAndMin(State st, double* arr){
    if(this->cur_state != st) return;
    double* nums = (arr == nullptr ? getTableArray() : arr);
    refreshMaxAndMinValues(nums, st == Sort ? true : false);
    if(arr == nullptr) delete[] nums;
}

bool Widget::checkErrors(){
    this->cur_state = ErrorCheck;
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
        this->cur_state = None;
        return true;
    }
    return false;
    this->cur_state = None;
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
    this->cur_state = Sort;
    ui->sortTimeLabel->setText("Sorting...");
    double* nums = getTableArray();
    auto start = std::chrono::high_resolution_clock::now(); //Время начала выполнения сортировки
    switch(ui->sortCmb->currentIndex()){
        case Bubble:
            bubbleSort(nums);
            break;
        case Quick:
            quickSort(nums, 0, arrLen-1);
            break;
        case Comb:
            combSort(nums);
            break;
        case Gnome:
            gnomeSort(nums);
            break;
        case Bogo:
            bogoSort(nums);
            break;
    }
    correct(nums, arrLen);
    auto stop = std::chrono::high_resolution_clock::now(); //Время завершения
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop-start); //Расчёт временнго промежутка
    ui->sortTimeLabel->setText(QString("Time: ") + QString::number(duration.count()) + " ms"); //Вывод затраченного времени на экран

    callMaxAndMin(Sort, nums);
    callSearchValue(nums);

    fillTable(nums);
    delete[] nums;
    this->cur_state = None;
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

void Widget::bubbleSort(double* arr){
    bool changed = true;
    while(changed){
        changed = false;
        for(int i = 0; i < arrLen-1;++i){
            if(arr[i] > arr[i+1]){
                swap(&arr[i], &arr[i+1]);
                changed = true;
            }
        }
    }
}

void Widget::combSort(double* arr){
    double factor = 1.2473309; // фактор уменьшения
    int step = arrLen - 1; // шаг сортировки
    //Последняя итерация цикла, когда step==1 эквивалентна одному проходу сортировки пузырьком
    while (step >= 1)
    {
        for (int i = 0; i + step < arrLen; i++)
        {
            if (arr[i] > arr[i + step])
            {
                swap(&arr[i], &arr[i+step]);
            }
        }
        step /= factor;
    }
}

void Widget::gnomeSort(double* arr){
    int i = 1, j = 2;
    while(i < arrLen){
        if(arr[i - 1] < arr[i]) //Для разных направлений сортировки надо поменять знак на противоположный
            i = j++;
        else{
            swap(&arr[i], &arr[i-1]);
            --i;
            if(i == 0) i = j++;
        }
    }
}

void Widget::quickSort(double* arr, int low, int high){
    if (low >= high) return;
    /* pi is partitioning index, arr[p] is now
        at right place */
    int pi = partition(arr, low, high);

    //Отдельно сортируются элементы до раздления и после
    quickSort(arr, low, pi - 1);
    quickSort(arr, pi + 1, high);
}

int Widget::partition(double* arr, int low, int high){
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

bool Widget::correct(double* arr, int size) {
    while (size-- > 0){
        if (arr[size - 1] > arr[size]){
            qDebug(QString("Not sorted, false at: " + QString::number(size)).toStdString().c_str());
            return false;
        }
    }
    return true;
}

void Widget::shuffle(double* arr) {
    for (int i = 0; i < arrLen; ++i)
        swap(&arr[i], &arr[rand() % arrLen]);
}

void Widget::bogoSort(double *arr) {
    while (!correct(arr, arrLen))
        shuffle(arr);
}

void Widget::setEnabledSearchButtons(bool b){
    ui->searchBackButton->setEnabled(b);
    ui->searchForwardButton->setEnabled(b);
}

void Widget::searchValue(double key, double* arr){
    double* nums = (arr == nullptr ? getTableArray() : arr);
    s_indexes.clear();
    cur_index = s_indexes.end();
    if(correct(nums, arrLen)){
        binarySearch(&s_indexes, nums, key);
        qDebug("Binary search");
    }
    else{
        linearSearch(&s_indexes, nums, key);
        qDebug("Linear search");
    }
    setEnabledSearchButtons(s_indexes.size() < 1 ? false : true);
    ui->searchCountLabel->setText("Найдено: " + QString::number(s_indexes.size()));
    if(s_indexes.size() > 0) {
        cur_index = s_indexes.begin();
        chooseItem(*cur_index);
    }

    if(arr == nullptr) delete[] nums;
}

void Widget::chooseItem(int index){
    ui->dataTable->clearSelection();
    auto item = ui->dataTable->item(index, 0);
    item->setSelected(true);
    ui->dataTable->scrollToItem(item);
}

void Widget::binarySearch(std::vector<int>* indexes, double* arr,double key){
    int left = 0;
    int right = arrLen;
    int mid = 0;
    while(true){
        mid = (left+right)/2;
        if(arr[mid] == key) return indexes->push_back(mid);
        else if(arr[mid] > key) right = mid-1;
        else if(arr[mid] < key) left = mid+1;
        if(mid == 0) return;
    }
}

void Widget::linearSearch(std::vector<int>* indexes, double* arr,double key){
    for(int i = 0; i < arrLen; i++)
        if(arr[i] == key) indexes->push_back(i);
}

std::vector<int>::iterator Widget::incIndex(){
    ++cur_index;
    if(cur_index == s_indexes.end()) cur_index = s_indexes.begin();
    return cur_index;
}
std::vector<int>::iterator Widget::decIndex(){
    if(cur_index == s_indexes.begin()) {
        cur_index = --s_indexes.end();
        return cur_index;
    }
    --cur_index;
    return cur_index;
}


void Widget::on_searchBackButton_clicked()
{
    if(s_indexes.size() == 1) return chooseItem(*cur_index);
    chooseItem(*decIndex());
}

void Widget::on_searchForwardButton_clicked()
{
    if(s_indexes.size() == 1) return chooseItem(*cur_index);
    chooseItem(*incIndex());
}

void Widget::on_searchEdit_returnPressed()
{
    callSearchValue();
}

void Widget::callSearchValue(double* arr){
    ui->searchCountLabel->clear();
    if(ui->searchEdit->text().isEmpty()) return;
    bool ok = true;
    double key = ui->searchEdit->text().toDouble(&ok);
    if(!ok) return;
    searchValue(key, arr);
}

void Widget::on_searchEdit_textChanged(const QString &arg1)
{
    if(arg1.isEmpty()){
        ui->searchCountLabel->clear();
        return setEnabledSearchButtons(false);
    }
    bool ok = true;
    ui->searchEdit->text().toDouble(&ok);
    setWidgetProperty(ui->searchEdit, "state", ok ? "" : "error");
}

void Widget::on_removeDublicatesButton_clicked()
{
    this->cur_state = Remove;
    if(arrLen <= 0) return;
    double* nums = getTableArray();
    if(!correct(nums, arrLen)) {
        dublicateBox.show();
        return;
    }
    removeDublicates(&nums);
    ui->dataTable->setRowCount(arrLen);
    callSearchValue(nums);
    fillTable(nums);
    delete[] nums;
    this->cur_state = None;
}

void Widget::removeDublicates(double** p_arr){
    std::vector<double> numVec;
    double num = (*p_arr)[0];
    for(int i = 1; i <= arrLen; i++){
        if((*p_arr)[i] != num) {
            numVec.push_back(num);
            num = (*p_arr)[i];
        }
    }
    qDebug(QString::number(numVec.size()).toStdString().c_str());
    double* newArr = new double[numVec.size()];
    for(unsigned int i = 0; i < numVec.size(); i++)
        newArr[i] = numVec.at(i);
    delete[] *p_arr;
    *p_arr = newArr;
    arrLen = numVec.size();
}
