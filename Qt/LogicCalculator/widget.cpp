#include "widget.h"
#include "ui_widget.h"
#include <QColor>

//Перечисление возможных операций в порядке, совпадающим с индексами знаков
enum Operation{
    AND, OR, XOR, NOT, EQUAL, NOTEQUAL
};

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    Calculate(); //Вызываем первичный расчёт
}

Widget::~Widget()
{
    delete ui;
}

void Widget::ChangeBackgroundColor(bool b){ //Смена фона в зависимости от результата вычисления операции
    QPalette pal; //Инициализация палитры
    pal.setColor(QPalette::Window, b ? "#73d200" : "#fd5c00"); //Устанавливаем цвет палитры в зависимости от переданного аргумента

    this->setPalette(pal); //Устанавливаем палитру на этот Widget
}

//Функция для расчёта логических операций для двух булевых операндов
bool getResult(bool op1, bool op2, int oper){
    bool result = false; //Переменная для хранения результата
    switch(oper){ //Нахождение случая используемого знака
    case AND: //И
        result = op1 & op2;
        break;
    case OR: //ИЛИ
        result = op1 | op2;
        break;
    case XOR: //ИСКЛЮЧАЮЩЕЕ ИЛИ
        result = op1 ^ op2;
        break;
    case NOT: //НЕ (ИНВЕРСИЯ)
        result = !op2;
        break;
    case EQUAL: //РАВНО
        result = op1 == op2;
        break;
    case NOTEQUAL: //НЕ РАВНО
        result = op1 != op2;
        break;
    }
    return result; //Возвращаем результат
}

void Widget::Calculate(){ //Вычисление операции
    bool left_index = ui->firstOperandCmb->currentText() == "True" ? true : false;  //Получение значение первого операнда путём проверки текста
    bool right_index = ui->secondOperandCmb->currentText() == "True" ? true : false; //Получение значения второго операнда
    int opIndex = ui->cmbOperation->currentIndex(); //Получаем индекс текушей операции
    if(ui->firstOperandCmb->isHidden()) ui->firstOperandCmb->show(); //Если первый операнд скрыт, то показываем его (для случая НЕ)
    bool result = getResult(left_index, right_index, opIndex); //Получаем результат расчёта через функцию getResult
    if(opIndex == NOT) ui->firstOperandCmb->hide(); //Если операция НЕ, то скрываем первый операнд

    ui->resultLabel->setText(result ? "True" : "False"); //Выводим текст результата в лейбл
    ChangeBackgroundColor(result); //Вызываем функцию смены цвета в зависимости от результата
}

void Widget::on_firstOperandCmb_currentIndexChanged(int){ //Изменение индекса первого операнда
    Calculate(); //Вызываем функцию расчёта
}

void Widget::on_cmbOperation_currentIndexChanged(int){ //Изменение индекса знака
    Calculate();
}

void Widget::on_secondOperandCmb_currentIndexChanged(int){ //Изменение индекса второго операнда
    Calculate();
}

