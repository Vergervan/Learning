#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>

#define MAX_POINTS 20 //Максимальное количество очков прокачки

#define HEALTH_RATE 9 //Здоровья за единицу силы
#define DAMAGE_RATE 6 //Урона за единицу ловкости
#define MANA_RATE 11 //Маны за единицу интеллекта
#define WEIGHT_RATE 5.5 //Веса за единицу выносливости

#define DEF_STRENGTH 1 //Стартовое значение силы
#define DEF_AGILITY 1 //Стартовое значение ловкости
#define DEF_INTELLIG 0 //Стартовое значение интеллекта
#define DEF_ENDURANCE 1 //Стартовое значение выносливости

#define CLASS_UNION_RATIO 1.5 //Коэффициент, при котором характеристики персонажа будут объединятся в новый класс

//Пол персонажа
namespace Gender{
    enum Gender{
        None, Male, Female
    };
}

//Типа операции с характеристикой персонажа
enum Operation{
    Increment, Decrement
};

//Первинчные характеристики персонажа
enum CharacterStat{
    Strength, Agility, Intelligence, Endurance
};

//Возможные классы персонажей
enum CharacterClass{
    None, Tank, Warrior, Mage, Knight, Paladin, Bard
};


//Сущность персонажа
class Character{
private:
    CharacterClass ch_class = None; //Переменная класса персонажа
    void calculateClass(); //Фукнция для определения класса персонажа на основе характеристик
    void setCharacterClass(CharacterClass); //Установка класса персонажа
public:
    Character(){
        strength = DEF_STRENGTH, agility = DEF_AGILITY, intelligence = DEF_INTELLIG, endurance = DEF_ENDURANCE; //Установка стартовых характеристик персонажу
        calculateSecondaryCharacterValues(); //Стартовый расчёт вторичных характеристик
    }

    std::string name; //Имя персонажа
    Gender::Gender gender = Gender::None; //Пол персонажа
    int strength = 0, agility = 0, intelligence = 0, endurance = 0; //Первичные характеристики
    float health = 0, damage = 0, mana = 0, weight = 0; //Вторичные характеристики
    int maxAvailablePoints = MAX_POINTS; //Количество свободных очков прокачки

    void calculateSecondaryCharacterValues(); //Функция расчёта вторичных характеристик
    int changeStat(CharacterStat cs, Operation op); //Функция изменения первичных характеристик
    inline CharacterClass getClass(){return ch_class;} //Геттер класса персонажа
};

#endif // CHARACTER_H
