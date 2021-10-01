#include "widget.h"
#include "ui_widget.h"

#define COLOR_SUCCESS "color:green;"
#define COLOR_ERROR "color:red;"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    readPoints();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::calculateAll(){
    ui->perimeterEdit->setText(QString::number(trngl.getPerimeter(), 'f', 2));
    ui->squareEdit->setText(QString::number(trngl.getSquare(), 'f', 2));
}

bool Widget::checkEditResult(QLineEdit* le, bool ok){

    le->setStyleSheet(ok ? COLOR_SUCCESS : COLOR_ERROR);
    refreshResultsStyle();
    return ok;
}

void Widget::readPoints(){
    hasError = false;
    bool ok = true;

    trngl.point1.x = ui->x1Edit->text().toInt(&ok);
    if(!checkEditResult(ui->x1Edit, ok)) hasError = true;
    trngl.point1.y = ui->y1Edit->text().toInt(&ok);
    if(!checkEditResult(ui->y1Edit, ok)) hasError = true;
    trngl.point2.x = ui->x2Edit->text().toInt(&ok);
    if(!checkEditResult(ui->x2Edit, ok)) hasError = true;
    trngl.point2.y = ui->y2Edit->text().toInt(&ok);
    if(!checkEditResult(ui->y2Edit, ok)) hasError = true;
    trngl.point3.x = ui->x3Edit->text().toInt(&ok);
    if(!checkEditResult(ui->x3Edit, ok)) hasError = true;
    trngl.point3.y = ui->y3Edit->text().toInt(&ok);
    if(!checkEditResult(ui->y3Edit, ok)) hasError = true;

    if(hasError) return refreshResultsStyle();

    calculateAll();
}

void Widget::refreshResultsStyle(){
    if(!hasError){
        ui->perimeterEdit->setStyleSheet(COLOR_SUCCESS);
        ui->squareEdit->setStyleSheet(COLOR_SUCCESS);
    }else{
        ui->perimeterEdit->setText("Ошибка расчёта");
        ui->perimeterEdit->setStyleSheet(COLOR_ERROR);
        ui->squareEdit->setText("Ошибка расчёта");
        ui->squareEdit->setStyleSheet(COLOR_ERROR);
    }
}
void Widget::on_x1Edit_textChanged(const QString&){
    readPoints();
}
void Widget::on_y1Edit_textChanged(const QString&){
    readPoints();
}
void Widget::on_x2Edit_textChanged(const QString&){
    readPoints();
}
void Widget::on_y2Edit_textChanged(const QString&){
    readPoints();
}
void Widget::on_x3Edit_textChanged(const QString&){
    readPoints();
}
void Widget::on_y3Edit_textChanged(const QString&){
    readPoints();
}
