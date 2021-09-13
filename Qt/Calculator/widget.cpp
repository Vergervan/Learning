#include "widget.h"
#include "ui_widget.h"
#include <QKeyEvent>
#include <algorithm>
#include <QDebug>

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

//Функция для ввода с клавиатуры
void Widget::keyPressEvent(QKeyEvent *event){
    //qDebug(QString::number(event->key(), 16).toStdString().c_str());
    if(event->key() == Qt::Key_Backspace)  Stepback();
    if(event->key() == Qt::Key_Return || event->key() == Qt::Key_Equal) Calculate();
    auto ch = std::find(validChars.begin(), validChars.end(), (char)event->key());
    if(ch != validChars.end()){
        AddNum(*ch);
    }
    for(auto it = signMap.begin(); it != signMap.end(); ++it){
        if(it != signMap.end()){
            if(it->second == (char)event->key()){
                SetOperation(it->first);
                break;
            }
        }
    }
}

void Widget::AddNum(char ch){
    if(r_a == "0" && ch != '.') ClearAll();
    if(op == None) r_a.append(ch); //Добавляем символ числа
    else{
        if(r_b == "0" && ch != '.') r_b.clear();
        r_b.append(ch);
    }
    RefreshText();
}

void Widget::SetOperation(Operation op){
    if(r_a.length() < 1 && op == Subtract){
        AddNum('-'); //Добавляем минус в начало первого числа
        return;
    }else if(this->op != None && r_b.length() < 1 && op == Subtract) {
        AddNum('-');
        return;
    }
    this->op = op;
    RefreshText();
}

//Обновить текст на экране
void Widget::RefreshText(){
    ui->resultText->setText(r_a);
    if(op == None) return;
    ui->resultText->append(QString(signMap.at(op)));
    ui->resultText->append(r_b);
}

void Widget::ClearAll(){
    r_a.clear();
    r_b.clear();
    op = None;
    ui->resultText->clear();
}

void Widget::Calculate(){
    if(op == None || r_b.length() < 1) return;
    float numA, numB, numC;
    numA = r_a.toFloat();
    numB = r_b.toFloat();
    switch(op){
        case Add:
            numC = numA+numB;
            break;
        case Subtract:
            numC = numA-numB;
            break;
        case Multiply:
            numC = numA*numB;
            break;
        case Divide:
            if(numB == 0) numC = 0;
            else numC = numA/numB;
            break;
    }
    ClearAll();
    r_a = QString::number(numC, 'g', 6); //Преобразуем результат в строку
    RefreshText();
}
//Удаление последней цифры или знака
void Widget::Stepback(){
    if(r_b.length() > 0) r_b.remove(r_b.length()-1, r_b.length());
    else if(op != None) op = None;
    else r_a.remove(r_a.length()-1, r_a.length());
    RefreshText();
}

void Widget::on_buttonNum0_clicked()
{
    AddNum('0');
}

void Widget::on_buttonNum1_clicked()
{
    AddNum('1');
}

void Widget::on_buttonNum2_clicked()
{
    AddNum('2');
}

void Widget::on_buttonNum3_clicked()
{
    AddNum('3');
}

void Widget::on_buttonNum4_clicked()
{
    AddNum('4');
}

void Widget::on_buttonNum5_clicked()
{
    AddNum('5');
}

void Widget::on_buttonNum6_clicked()
{
    AddNum('6');
}

void Widget::on_buttonNum7_clicked()
{
    AddNum('7');
}

void Widget::on_buttonNum8_clicked()
{
    AddNum('8');
}

void Widget::on_buttonNum9_clicked()
{
    AddNum('9');
}

void Widget::on_buttonResult_clicked()
{
    Calculate();
}

void Widget::on_buttonClear_clicked()
{
    ClearAll();
}

void Widget::on_buttonBack_clicked()
{
    Stepback();
}

void Widget::on_buttonPlus_clicked()
{
    SetOperation(Add);
}

void Widget::on_buttonMinus_clicked()
{
    SetOperation(Subtract);
}

void Widget::on_buttonMultiply_clicked()
{
    SetOperation(Multiply);
}

void Widget::on_buttonDivide_clicked()
{
    SetOperation(Divide);
}

void Widget::on_buttonPoint_clicked()
{
    AddNum('.');
}
