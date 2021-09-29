#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMessageBox>
#include "character.h"
#include <string>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Character character;
    void refreshCharacterInfo();
    void setStatText(QLabel*, int);
    const char* getStatColor(int);
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_strengthPlusButton_clicked();
    void on_agilityPlusButton_clicked();
    void on_intelligencePlusButton_clicked();
    void on_endurancePlusButton_clicked();
    void on_strengthMinusButton_clicked();
    void on_agilityMinusButton_clicked();
    void on_intelligenceMinusButton_clicked();
    void on_enduranceMinusButton_clicked();
    void on_maleButton_clicked();
    void on_femaleButton_clicked();
    void on_nameEdit_textEdited(const QString &arg1);
    void on_createButton_clicked();

private:
    QMessageBox msgBox;
    void callMessageBox(QString);
    void callErrorBox(QString);
    void changeCharacterStats(CharacterStat cs, Operation op);
    Ui::Widget *ui;
};
#endif // WIDGET_H
