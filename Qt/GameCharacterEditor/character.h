#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>

#define MAX_POINTS 20

#define HEALTH_RATE 9
#define DAMAGE_RATE 6
#define MANA_RATE 11
#define WEIGHT_RATE 5.5

#define DEF_STRENGTH 1
#define DEF_AGILITY 1
#define DEF_INTELLIG 0
#define DEF_ENDURANCE 1

namespace Gender{
    enum Gender{
        None, Male, Female
    };
}

enum Operation{
    Increment, Decrement
};

enum CharacterStat{
    Strength, Agility, Intelligence, Endurance
};


class Character{
public:
    Character(){
        strength = DEF_STRENGTH, agility = DEF_AGILITY, intelligence = DEF_INTELLIG, endurance = DEF_ENDURANCE;
        calculateSecondaryCharacterValues();
    }

    std::string name;
    Gender::Gender gender = Gender::None;
    int strength = 0, agility = 0, intelligence = 0, endurance = 0;
    float health = 0, damage = 0, mana = 0, weight = 0;
    int maxAvailablePoints = MAX_POINTS;

    void calculateSecondaryCharacterValues();
    int changeStat(CharacterStat cs, Operation op);
};

#endif // CHARACTER_H
