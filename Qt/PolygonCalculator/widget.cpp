#include "widget.h"
#include "ui_widget.h"

#define COLOR_SUCCESS "color:green;"
#define COLOR_ERROR "color:red;"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::addPoint(){
    QListWidgetItem* item = new QListWidgetItem;
    Point* point = new Point;
    item->setText(POINT_NAME + QString::number(ui->pointList->count()+1));
    points.emplace(item, point);
    ui->pointList->addItem(item);
}

void Widget::calculateSides(){
    for(auto it = points.begin(); it != points.end();){
        auto p1 = it;
        ++it;
        auto p2 = it->second;
        p1->side = sqrt(pow(p2->x-p1->x, 2) + pow(p2->y-p1->y, 2));
    }
}

void Widget::on_addPointButton_clicked()
{
    addPoint();
    qDebug(QString::number(points.size()).toStdString().c_str());
    qDebug(QString::number(ui->pointList->count()).toStdString().c_str());
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
    points.at(ui->pointList->selectedItems()[0])->x = arg1.toInt();
    calculateSides();
}


void Widget::on_yEdit_textChanged(const QString &arg1)
{
    points.at(ui->pointList->selectedItems()[0])->y = arg1.toInt();
    calculateSides();
}

