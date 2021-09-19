#include "widget.h"
#include "ui_widget.h"
#include <QColor>

enum Operation{
    AND, OR, XOR, NOT, EQUAL, NOTEQUAL
};

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    Calculate();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::ChangeBackGroundColor(bool b){
    QPalette pal;
    pal.setColor(QPalette::Window, b ? "#73d200" : "#fd5c00");

    this->setPalette(pal);
}


void Widget::Calculate(){
    bool left_index = ui->firstOperandCmb->currentIndex();
    bool right_index = ui->secondOperandCmb->currentIndex();

    ui->secondOperandCmb->show();

    bool result = false;
    switch(ui->cmbOperation->currentIndex()){
        case AND:
            result = left_index & right_index;
            break;
        case OR:
            result = left_index | right_index;
            break;
        case XOR:
            result = left_index ^ right_index;
            break;
        case NOT:
            result = !left_index;
            ui->secondOperandCmb->hide();
            break;
        case EQUAL:
            result = left_index == right_index;
            break;
        case NOTEQUAL:
            result = left_index != right_index;
            break;
    }

    ui->resultLabel->setText(result ? "True" : "False");
    ChangeBackGroundColor(result);
}

void Widget::on_firstOperandCmb_currentIndexChanged(int index){
    Calculate();
}

void Widget::on_cmbOperation_currentIndexChanged(int index){
    Calculate();
}

void Widget::on_secondOperandCmb_currentIndexChanged(int index){
    Calculate();
}

