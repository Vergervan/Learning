#ifndef SORTER_H
#define SORTER_H

#include <QObject>
#include <QString>
#include <QCoreApplication>
#include <QTimer>

#include <chrono>
#include <stack>

class Sorter : public QObject
{
    Q_OBJECT
public:
    explicit Sorter(QObject *parent = nullptr);
    enum SortType{
        Bubble, Quick, Comb, Gnome, Bogo
    };

    bool isAborted = false;

    void bubbleSort(double*, int);
    void quickSort(double*, int, int);
    void combSort(double*, int);
    void gnomeSort(double*, int);
    void bogoSort(double*, int);

    static void swap(double&, double&);
    static bool correct(double*, int);

private:
    std::stack<double**>safeStack;

    int partition (double*, int, int);
    void shuffle(double*, int);

public slots:
    void sortArray(double* arr, int len, Sorter::SortType type, bool noDublicates = false);
    void removeDublicates(double** arr, int len);
    void clearStack();

signals:
    void startWork();
    void finishWork();
    void startRemoveDublicates();
    void endRemoveDublicates();
    void sendNewArraySize(int newLen);
    void sendLogMessage(QString);
    void sendSortedArray(double* arr, long duration);
    void arrayWithoutDublicates(double* arr);
    void aborted();
};

#endif // SORTER_H
