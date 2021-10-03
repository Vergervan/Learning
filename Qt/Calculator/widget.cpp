#include "widget.h"
#include "ui_widget.h"
#include <QKeyEvent>
#include <algorithm>
#include <QDebug>
#include "operand.h"
#include <QRegularExpression>

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
    if(this->op == None){
        CheckOperand(oa, ch);
    }else{
        CheckOperand(ob, ch);
    }

    RefreshText();
}

void Widget::CheckOperand(Operand& op, char ch){
    switch(ch){
        case '-':
            if(op.trueLength() > 0 || op.getIsSigned()) return;
            op.setIsSigned(true);
            break;
        case '.':
            if(op.findCharInOperand(ch) || op.length() < 1) return;
            op.setIsPointed(true);
            break;
        case '0':
            if(op.length() > 0 && op.getIsZero() && !op.getIsPointed()) return;
            op.setIsZero(true);
            break;
    }

    op.addChar(ch);
}

void Widget::SetOperation(Operation op){
    CheckEmptyPoint(oa);
    CheckEmptyPoint(ob);
    if(!oa.getIsSigned() && op == Subtract){
        AddNum('-');
        return;
    }
    if(oa.length() < 1) return;
    if(op == Subtract && !ob.getIsSigned() && this->op == Subtract){
        AddNum('-');
        return;
    }
    this->op = op;
    RefreshText();
}

//Обновить текст на экране
void Widget::RefreshText(){
    ui->resultText->setText(oa.getString());
    if(op == None) return;
    ui->resultText->append(QString(signMap.at(op)));
    ui->resultText->append(ob.getString());
}

void Widget::ClearAll(){
    oa.clear();
    ob.clear();
    op = None;
    ui->resultText->clear();
}

void Widget::Calculate(){
    if(op == None || ob.length() < 1) return;
    double numA = 0, numB = 0, numC = 0;
    numA = oa.toDouble();
    numB = ob.toDouble();
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
    oa.setValue(QString::number(numC)); //Преобразуем результат в строку
    RefreshText();
}
//Удаление последней цифры или знака
void Widget::Stepback(){
    if(ob.trueLength() > 0) ob.removeLastCharacter();
    else if(op != None) op = None;
    else oa.removeLastCharacter();
    RefreshText();
}

void Widget::CheckEmptyPoint(Operand& op){
    for(int i = 0; i < op.trueLength(); i++){
        if(op.getString()[i] == '.' && i == op.trueLength()-1) {
            op.removeLastCharacter();
            return;
        }
    }
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
