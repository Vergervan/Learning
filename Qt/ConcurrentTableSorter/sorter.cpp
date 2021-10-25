#include "sorter.h"

Sorter::Sorter(QObject *parent) : QObject(parent)
{
    qRegisterMetaType<Sorter::SortType>("Sorter::SortType"); //Для работы enum с сигналами и слотами
    connect(this, SIGNAL(aborted()), this, SLOT(clearStack()));
}

void Sorter::clearStack(){
    emit sendLogMessage(QString("SafeStack called - Size: %1").arg(safeStack.size()));
    while(safeStack.size() > 0){
        if(*safeStack.top() != nullptr) delete[] *safeStack.top();
        safeStack.pop();
    }
    emit finishWork();
}

void Sorter::abort(){
    isAborted = true;
}

void Sorter::updateEvents(){
    QCoreApplication::processEvents();
}

void Sorter::sortArray(double* arr, int len, Sorter::SortType type){
    emit startWork();
    safeStack.push(&arr);
    auto start = std::chrono::high_resolution_clock::now(); //Время начала выполнения сортировки
    switch(type){
        case Bubble:
            bubbleSort(arr, len);
            break;
        case Quick:
            quickSort(arr, 0, len-1);
            break;
        case Comb:
            combSort(arr, len);
            break;
        case Gnome:
            gnomeSort(arr, len);
            break;
        case Bogo:
            bogoSort(arr, len);
            break;
    }
    if(isAborted){
        emit aborted();
        updateEvents();
        return;
    }
    safeStack.pop();
    auto stop = std::chrono::high_resolution_clock::now(); //Время завершения
    emit sendSortedArray(arr, std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count());
    emit finishWork();
}

void Sorter::bubbleSort(double* arr, int len){
    bool changed = true;
    while(changed && !isAborted){
        changed = false;
        for(int i = 0; i < len-1;++i){
            if(arr[i] > arr[i+1]){
                swap(arr[i], arr[i+1]);
                changed = true;
            }
        }
        updateEvents();
    }
}

void Sorter::combSort(double* arr, int len){
    double factor = 1.2473309; // Фактор уменьшения
    int step = len; // Шаг сортировки
    bool swapped = true;

    while((step != 1 || swapped) && !isAborted)
    {
        step = int(step/factor);
        if(step < 1) step = 1;
        swapped = false;
        for(int i = 0; i < len-step; i++)
        {
            if(arr[i] > arr[i + step])
            {
                swap(arr[i], arr[i+step]);
                swapped = true;
            }
        }
        updateEvents();
    }
}

void Sorter::gnomeSort(double* arr, int len){
    int i = 1, j = 2;
    while(i < len && !isAborted){
        if(arr[i - 1] < arr[i]) //Для разных направлений сортировки надо поменять знак на противоположный
            i = j++;
        else{
            swap(arr[i], arr[i-1]);
            --i;
            if(i == 0) i = j++;
        }
        updateEvents();
    }
}

void Sorter::quickSort(double* arr, int low, int high){
    updateEvents();
    if(low >= high || isAborted) return;
    int pi = partition(arr, low, high);

    //Рекурсивно сортируются элементы до раздления и после
    quickSort(arr, low, pi - 1);
    quickSort(arr, pi + 1, high);
}

int Sorter::partition(double* arr, int low, int high){
    int pivot = arr[high];
    int i = (low - 1);
    for(int j = low; j <= high - 1; j++)
    {
        if(arr[j] < pivot)
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

bool Sorter::correct(double* arr, int size) {
    if(size <= -1) return false;
    for(int i = 1; i < size; i++){
        if(arr[i] < arr[i-1]){
            return false;
        }
    }
    return true;
}

void Sorter::shuffle(double* arr, int len) {
    for(int i = 0; i < len; ++i)
        swap(arr[i], arr[rand() % len]);
}

void Sorter::bogoSort(double *arr, int len) {
    while(!correct(arr, len) && !isAborted){
        shuffle(arr, len);
        updateEvents();
    }
}

void Sorter::swap(double& el1, double& el2){
    double swp = el2;
    el2 = el1;
    el1 = swp;
}
