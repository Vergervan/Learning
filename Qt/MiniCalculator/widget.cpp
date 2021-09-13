#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>
#include <math.h>  // isinf, isnan


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //Установка параметров MessageBox'а
    errorBox.setWindowTitle("Ошибка");
    errorBox.setStandardButtons(QMessageBox::Ok);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_calcButton_clicked()
{
    ui->resultEdit->clear(); //Предварительная очистка результата

    float num1 = 0, num2 = 0, result = 0; //Переменные результатов и
    bool num1Ok, num2Ok; //Булевы для проверки ошибок
    num1 = ui->firstNumberEdit->text().toFloat(&num1Ok); //Первый операнд
    num2 = ui->secondNumberEdit->text().toFloat(&num2Ok); //Второй операнд

    if(!num1Ok || !num2Ok || isinf(num1) || isinf(num2)) { //Проверка ошибок, в т.ч. не является ли число бесконечностью
        errorBox.setText("Введены некорректные числа");
        errorBox.show();
        return;
    }

    //Проверка кнопок на выбранный знак и выполнение соответствующей операции
    if(ui->plusButton->isChecked()) //Сложение
        result = num1 + num2;
    else if(ui->minusButton->isChecked()) //Вычитание
            result = num1 - num2;
    else if(ui->multiplyButton->isChecked()) //Умножение
            result = num1 * num2; //Деление
    else if(ui->divideButton->isChecked()) result = num1 / num2;
    else{
        errorBox.setText("Не выбран знак операции");
        errorBox.show();
        return;
    }

    if(isinf(result) || isnan(result)){ //Проверка результата на адекватность
        errorBox.setText("Результат не является вещественным числом");
        errorBox.show();
        return;
    }
    ui->resultEdit->setText(QString::number(result)); //Вывод результата на экран
}
