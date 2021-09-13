#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <vector>
#include <map>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    enum Operation{ //Перечисление возможных операций
        None, Add, Subtract, Multiply, Divide
    };
    //Словарь символов-знаков в зависимости от операции
    std::map<Operation, char> signMap {{Add, '+'}, {Subtract, '-'}, {Multiply, '*'}, {Divide, '/'}};

    //Массив доступных для ввода чисел
    std::vector<char> validChars {'0','1','2','3','4','5','6','7','8','9','.'};

    Q_OBJECT

public:
    QString r_a, r_b; //Строки для чисел a,b
    Operation op = None; //Переменная для хранения выбранной операции

    void AddNum(char);
    void SetOperation(Operation);
    void Calculate();
    void RefreshText();
    void ClearAll();
    void Stepback();
    Widget(QWidget *parent = nullptr);
    ~Widget();
protected:
    void keyPressEvent(QKeyEvent *event) override;
private slots:
    void on_buttonNum0_clicked();

    void on_buttonNum1_clicked();

    void on_buttonNum2_clicked();

    void on_buttonNum3_clicked();

    void on_buttonNum4_clicked();

    void on_buttonNum5_clicked();

    void on_buttonNum6_clicked();

    void on_buttonNum7_clicked();

    void on_buttonNum8_clicked();

    void on_buttonNum9_clicked();

    void on_buttonClear_clicked();

    void on_buttonBack_clicked();

    void on_buttonPlus_clicked();

    void on_buttonMinus_clicked();

    void on_buttonMultiply_clicked();

    void on_buttonDivide_clicked();

    void on_buttonResult_clicked();

    void on_buttonPoint_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
