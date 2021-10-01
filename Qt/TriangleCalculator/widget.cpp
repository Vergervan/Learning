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

void Widget::calculateAll(){
    ui->perimeterEdit->setText(QString::number(trngl.getPerimeter(), 'f', 2));
    ui->squareEdit->setText(QString::number(trngl.getSquare(), 'f', 2));
}

bool Widget::checkEditResult(QLineEdit* le){
    le->setStyleSheet(ok ? COLOR_SUCCESS : COLOR_ERROR);
    refreshResultsStyle();
    return ok;
}

void Widget::refreshResultsStyle(){
    if(ok){
        ui->perimeterEdit->setStyleSheet(COLOR_SUCCESS);
        ui->squareEdit->setStyleSheet(COLOR_SUCCESS);
    }else{
        ui->perimeterEdit->setText("Ошибка");
        ui->perimeterEdit->setStyleSheet(COLOR_ERROR);
        ui->squareEdit->setText("Ошибка");
        ui->squareEdit->setStyleSheet(COLOR_ERROR);
    }
}
void Widget::on_x1Edit_textChanged(const QString &arg1){
    trngl.point1.x = arg1.toInt(&ok);
    if(!checkEditResult(ui->x1Edit)) return;
    calculateAll();
}
void Widget::on_y1Edit_textChanged(const QString &arg1){
    trngl.point1.y = arg1.toInt(&ok);
    if(!checkEditResult(ui->y1Edit)) return;
    calculateAll();
}
void Widget::on_x2Edit_textChanged(const QString &arg1){
    trngl.point2.x = arg1.toInt(&ok);
    if(!checkEditResult(ui->x2Edit)) return;
    calculateAll();
}
void Widget::on_y2Edit_textChanged(const QString &arg1){
    trngl.point2.y = arg1.toInt(&ok);
    if(!checkEditResult(ui->y2Edit)) return;
    calculateAll();
}
void Widget::on_x3Edit_textChanged(const QString &arg1){
    trngl.point3.x = arg1.toInt(&ok);
    if(!checkEditResult(ui->x3Edit)) return;
    calculateAll();
}
void Widget::on_y3Edit_textChanged(const QString &arg1){
    trngl.point3.y = arg1.toInt(&ok);
    if(!checkEditResult(ui->y3Edit)) return;
    calculateAll();
}
