#ifndef SORTER_H
#define SORTER_H

#include <QObject>
#include <QString>

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
    std::stack<double**>safeStack;

    void bubbleSort(double*, int);
    void quickSort(double*, int, int);
    void combSort(double*, int);
    void gnomeSort(double*, int);
    void bogoSort(double*, int);

    static void swap(double&, double&);
    static bool correct(double*, int);

private:
    int partition (double*, int, int);
    void shuffle(double*, int);

public slots:
    void sortArray(double* arr, int len, Sorter::SortType type);
    void clearStack();
    void abort();

signals:
    void startWork();
    void finishWork();
    void sendLogMessage(QString);
    void sendSortedArray(double* arr, long duration);
    void aborted();
};

#endif // SORTER_H
