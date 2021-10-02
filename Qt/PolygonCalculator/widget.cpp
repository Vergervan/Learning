#include "widget.h"
#include "ui_widget.h"

#define COLOR_SUCCESS "color:green;"
#define COLOR_ERROR "color:red;"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    calculateAll();
}

Widget::~Widget()
{
    delete ui;
}

//Добавить новую точку
void Widget::addPoint(){
    QListWidgetItem* item = new QListWidgetItem;
    Point* point = new Point;
    item->setText(POINT_NAME + QString::number(ui->pointList->count()+1));
    points.insert({item, point});
    ui->pointList->addItem(item);
}

//Расчёт модуля для вещественного числа
double Widget::dabs(double x){
    if(x >= 0) return x;
    return -1 * x;
}

void Widget::calculateAll(){
    calculatePolygonSides();
    double s = calculatePolygonSquare();
    double p = calculatePerimeter();
    ui->squareEdit->setText(QString::number(s, 'f', 2));
    ui->perimeterEdit->setText(QString::number(p, 'f', 2));
}

//Расчёт периметра многоульника
double Widget::calculatePerimeter(){
    double p = 0;
    for(auto it = points.begin(); it != points.end(); ++it){
        p += it->second->side;
    }
    return p;
}

//Рассчитывает стороны всех сторон многоугольника
void Widget::calculatePolygonSides(){
    if(points.size() <= 1) return;
    auto it = points.begin();
    auto end = --points.end();
    end->second->side = sqrt(pow(it->second->x-end->second->x, 2) + pow(it->second->y-end->second->y, 2));
    while(it != end){
        auto p1 = it->second;
        auto p2 = (++it)->second;
        p1->side = sqrt(pow(p2->x-p1->x, 2) + pow(p2->y-p1->y, 2));
    }
}

//Расчёт площади многоульника
double Widget::calculatePolygonSquare(){
    if(points.size() <= 1) return 0;
    double part1 = 0, part2 = 0;
    auto it = points.begin();
    auto end = --points.end();
    part1 += end->second->x * it->second->y;
    part2 += end->second->y * it->second->x;
    while(it != end){
        int x1 = it->second->x, y1 = it->second->y;
        ++it;
        part1+=x1*it->second->y;
        part2+=y1*it->second->x;
    }
    return dabs((part1-part2)/2);
}


void Widget::on_addPointButton_clicked()
{
    addPoint();
}


void Widget::on_removePointButton_clicked()
{
    if(ui->pointList->count() < 1) return;
    //if(ui->pointList->selectedItems().count() < 1)
    delete ui->pointList->item(ui->pointList->count()-1);
    //else if(ui->pointList->selectedItems().count() == 1) delete ui->pointList->selectedItems()[0];
}


void Widget::on_pointList_itemClicked(QListWidgetItem *item)
{
    ui->xEdit->setText(QString::number(points.at(item)->x));
    ui->yEdit->setText(QString::number(points.at(item)->y));
    ui->sideEdit->setText(QString::number(points.at(item)->side, 'f', 2));
}


void Widget::on_xEdit_textChanged(const QString &arg1)
{
    bool ok = true;
    int x = arg1.toInt(&ok);
    points.at(ui->pointList->selectedItems()[0])->x = ok ? x : 0;
    calculateAll();
}


void Widget::on_yEdit_textChanged(const QString &arg1)
{
    bool ok = true;
    int x = arg1.toInt(&ok);
    points.at(ui->pointList->selectedItems()[0])->y = ok ? x : 0;
    calculateAll();
}

