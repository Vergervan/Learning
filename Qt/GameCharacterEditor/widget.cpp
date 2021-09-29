#include "widget.h"
#include "ui_widget.h"
#include "character.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    msgBox.setWindowTitle("Ошибка");
    msgBox.setStandardButtons(QMessageBox::Ok);

    RefreshCharacterInfo();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::RefreshCharacterInfo(){
    ui->availablePointsCountLabel->setText(QString::number(character.maxAvailablePoints));
    ui->strengthCountLabel->setText(QString::number(character.strength));
    ui->agilityCountLabel->setText(QString::number(character.agility));
    ui->intelligenceCountLabel->setText(QString::number(character.intelligence));
    ui->enduranceCountLabel->setText(QString::number(character.endurance));
    ui->healthCountLabel->setText(QString::number(character.health));
    ui->damageCountLabel->setText(QString::number(character.damage));
    ui->manaCountLabel->setText(QString::number(character.mana));
    ui->weightCountLabel->setText(QString::number(character.weight));
}

void Widget::callMessageBox(QString str){
    msgBox.setText(str);
    msgBox.show();
}

void Widget::on_strengthPlusButton_clicked(){ character.incStrength(); RefreshCharacterInfo();}
void Widget::on_agilityPlusButton_clicked(){ character.incAgility(); RefreshCharacterInfo();}
void Widget::on_intelligencePlusButton_clicked(){ character.incIntelligence(); RefreshCharacterInfo();}
void Widget::on_endurancePlusButton_clicked(){ character.incEndurance(); RefreshCharacterInfo();}
void Widget::on_strengthMinusButton_clicked(){ character.decStrength(); RefreshCharacterInfo();}
void Widget::on_agilityMinusButton_clicked(){ character.decAgility(); RefreshCharacterInfo();}
void Widget::on_intelligenceMinusButton_clicked(){ character.decIntelligence(); RefreshCharacterInfo();}
void Widget::on_enduranceMinusButton_clicked(){ character.decEndurance(); RefreshCharacterInfo();}
void Widget::on_maleButton_clicked()
{
    character.gender = Male;
}


void Widget::on_femaleButton_clicked()
{
    character.gender = Female;
}


void Widget::on_nameEdit_textEdited(const QString &arg1)
{
    character.name = arg1.toStdString();
    //qDebug(character.name.c_str());
}

