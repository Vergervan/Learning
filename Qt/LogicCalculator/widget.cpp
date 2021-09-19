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


void Widget::Calculate(){ //Вычисление операции
    bool left_index = ui->firstOperandCmb->currentIndex(); //Получение значение первого операнда
    bool right_index = ui->secondOperandCmb->currentIndex(); //Получение значения второго операнда

    if(ui->secondOperandCmb->isHidden()) ui->secondOperandCmb->show(); //Если второй операнд скрыт, то показываем его (для случая НЕ)

    bool result = false; //Первчиная инициализация переменной для хранения результата
    switch(ui->cmbOperation->currentIndex()){ //Нахождение случая используемого знака
        case AND: //И
            result = left_index & right_index;
            break;
        case OR: //ИЛИ
            result = left_index | right_index;
            break;
        case XOR: //ИСКЛЮЧАЮЩЕЕ ИЛИ
            result = left_index ^ right_index;
            break;
        case NOT: //НЕ (ИНВЕРСИЯ)
            result = !left_index;
            ui->secondOperandCmb->hide(); //Скрываем второй операнд, т.к. для данной операции требуется лишь один операнд
            break;
        case EQUAL: //РАВНО
            result = left_index == right_index;
            break;
        case NOTEQUAL: //НЕ РАВНО
            result = left_index != right_index;
            break;
    }

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

