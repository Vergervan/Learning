#include "widget.h"
#include "ui_widget.h"
#include "character.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setStyle(QApplication::style());
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
    changeStatLabelColor(lbl, stat);
}

void Widget::changeStatLabelColor(QLabel* lbl, int x){
    if(x <= 3)
        lbl->setProperty("level", "normal");
    else if(x <= 7)
        lbl->setProperty("level", "good");
    else
        lbl->setProperty("level", "nice");
    lbl->style()->unpolish(lbl); //Действия для обновления стиля кнопки
    lbl->style()->polish(lbl);
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

//Сбрасывает выделение с кнопок пола
void Widget::resetGenderButtons(){
    ui->maleButton->setAutoExclusive(false);
    ui->maleButton->setChecked(false);
    ui->maleButton->setAutoExclusive(true);

    ui->femaleButton->setAutoExclusive(false);
    ui->femaleButton->setChecked(false);
    ui->femaleButton->setAutoExclusive(true);
}

void Widget::refreshCharactersList(){
    ui->charactersList->clear(); //Очишаем список персонажей перед новым заполнением
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
    characters.push_back(character); //Добавляем класс персонажа в вектор
    character = Character(); //Сбрасываем переменную персонажа
    ui->nameEdit->clear(); //Очищаем поле имени персонажа
    refreshCharacterInfo(); //Обновляем информацию о персонаже
    refreshCharactersList(); //Обновляем список всех персонажей
    resetGenderButtons(); //Сбрасываем кнопки выбора пола
    callMessageBox("Персонаж успешно создан");
}
