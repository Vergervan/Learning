#include "widget.h"
#include "ui_widget.h"
#include "character.h"

//Набор цветов для характеристик
#define ORANGE "#fe9600"
#define YELLOW "#fed200"
#define GREEN "#66c500"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    msgBox.setStandardButtons(QMessageBox::Ok); //Заготовка для MessageBox с кнопкой Ok
    refreshCharacterInfo(); //Стартовое обновление информации
}

Widget::~Widget()
{
    delete ui;
}

//Функция для обновления информации в UI
void Widget::refreshCharacterInfo(){
    ui->availablePointsLabel->setText("Доступно очков прокачки: " + QString::number(character.maxAvailablePoints));
    ui->classNameLabel->setText(classMap.at(character.getClass()).c_str());
    ui->nameEdit->setText(QString(character.name.c_str()));

    setStatText(ui->strengthCountLabel, character.strength);
    setStatText(ui->agilityCountLabel, character.agility);
    setStatText(ui->intelligenceCountLabel, character.intelligence);
    setStatText(ui->enduranceCountLabel, character.endurance);

    ui->healthCountLabel->setText(QString::number(character.health));
    ui->damageCountLabel->setText(QString::number(character.damage));
    ui->manaCountLabel->setText(QString::number(character.mana));
    ui->weightCountLabel->setText(QString::number(character.weight));
}

//Функция для вызова окна с Ошибкой
void Widget::callErrorBox(QString str){
    msgBox.setWindowTitle("Ошибка");
    msgBox.setText(str);
    msgBox.show();
}

//Функция для вызова сообщения
void Widget::callMessageBox(QString str){
    msgBox.setWindowTitle("Сообщение");
    msgBox.setText(str);
    msgBox.show();
}

//Функция для изменения показателей и их цвета
void Widget::setStatText(QLabel* lbl, int stat){
    lbl->setText(QString::number(stat));
    lbl->setStyleSheet(getStatColor(stat));
}

//Функция для получения цвета, соответствующего уровню характеристики персонажа
const char* Widget::getStatColor(int x){
    std::string str = "color:";
    str += (x <= 3 ? ORANGE : (x <= 7 ? YELLOW : GREEN));
    str += ";";
    return str.c_str();
}

//Функция для изменения характеристик персонажа
void Widget::changeCharacterStats(CharacterStat cs, Operation op){
    int err = character.changeStat(cs, op);
    if(err == -1) callErrorBox("Превышен лимит характеристики персонажа");
    refreshCharacterInfo();
}

void Widget::on_strengthPlusButton_clicked(){ changeCharacterStats(Strength, Increment); }
void Widget::on_agilityPlusButton_clicked(){ changeCharacterStats(Agility, Increment); }
void Widget::on_intelligencePlusButton_clicked(){ changeCharacterStats(Intelligence, Increment); }
void Widget::on_endurancePlusButton_clicked(){ changeCharacterStats(Endurance, Increment); }
void Widget::on_strengthMinusButton_clicked(){ changeCharacterStats(Strength, Decrement); }
void Widget::on_agilityMinusButton_clicked(){ changeCharacterStats(Agility, Decrement); }
void Widget::on_intelligenceMinusButton_clicked(){ changeCharacterStats(Intelligence, Decrement); }
void Widget::on_enduranceMinusButton_clicked(){ changeCharacterStats(Endurance, Decrement); }

void Widget::on_maleButton_clicked()
{
    character.gender = Gender::Male;
}

void Widget::on_femaleButton_clicked()
{
    character.gender = Gender::Female;
}

void Widget::on_nameEdit_textEdited(const QString &arg1)
{
    character.name = arg1.toStdString();
    //qDebug(character.name.c_str());
}

void Widget::refreshCharactersList(){
    ui->charactersList->clear();
    for(auto it = characters.begin(); it != characters.end(); ++it){
        std::string pattern = "Имя: ";
        pattern += it->name;
        pattern += "\nКласс: ";
        pattern += classMap.at(it->getClass());
        ui->charactersList->addItem(QString(pattern.c_str()));
    }
}

//Клик по кнопке создания персонажа
void Widget::on_createButton_clicked()
{
    //Проверка на различные ошибки
    if(character.name == "") {
        callErrorBox("Не указано имя персонажа");
        return;
    }else if(character.gender == Gender::None) {
        callErrorBox("Не указан пол персонажа");
        return;
    }else if(character.maxAvailablePoints > 0){
        callErrorBox("Не распределены все очки прокачки");
        return;
    }
    characters.push_back(character);
    character = Character();
    refreshCharacterInfo();
    refreshCharactersList();
    ui->maleButton->setChecked(false);
    ui->femaleButton->setChecked(false);
    callMessageBox("Персонаж успешно создан");
}
