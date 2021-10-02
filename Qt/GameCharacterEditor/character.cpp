#include "character.h"

void Character::calculateSecondaryCharacterValues(){
    health = strength * HEALTH_RATE;
    damage = agility * DAMAGE_RATE;
    mana = intelligence * MANA_RATE;
    weight = endurance * WEIGHT_RATE;
}

void Character::calculateClass(){
    if(strength >= agility && strength >= intelligence){
        if(agility == intelligence)
            (float)strength/agility < CLASS_UNION_RATIO ? setCharacterClass(Master) : setCharacterClass(Tank);
        else if(agility > intelligence)
            (float)strength/agility < CLASS_UNION_RATIO ? setCharacterClass(Knight) : setCharacterClass(Tank);
        else
            (float)strength/intelligence < CLASS_UNION_RATIO ? setCharacterClass(Paladin) : setCharacterClass(Tank);

    }else if(agility >= strength && agility >= intelligence){
        if(strength == intelligence)
            (float)agility/strength < CLASS_UNION_RATIO ? setCharacterClass(Master) : setCharacterClass(Warrior);
        else if(strength > intelligence)
            (float)agility/strength < CLASS_UNION_RATIO ? setCharacterClass(Knight) : setCharacterClass(Warrior);
        else
            (float)agility/intelligence < CLASS_UNION_RATIO ? setCharacterClass(Bard) : setCharacterClass(Warrior);

    }else if(intelligence >= agility && intelligence >= strength){
        if(strength == agility)
            (float)agility/strength < CLASS_UNION_RATIO ? setCharacterClass(Master) : setCharacterClass(Mage);
        else if(strength > agility)
            (float)intelligence/agility < CLASS_UNION_RATIO ? setCharacterClass(Bard) : setCharacterClass(Mage);
        else
            (float)intelligence/strength < CLASS_UNION_RATIO ? setCharacterClass(Paladin) : setCharacterClass(Mage);
    }
}

//Установка класса персонажа
void Character::setCharacterClass(CharacterClass cc){
    ch_class = cc;
}

int Character::changeStat(CharacterStat cs, Operation op){
    int* statValue = nullptr; //
    int minLimit = 0;
    switch (cs){
        case Strength:
            statValue = &strength;
            minLimit = DEF_STRENGTH;
        break;
        case Agility:
            statValue = &agility;
            minLimit = DEF_AGILITY;
        break;
        case Intelligence:
            statValue = &intelligence;
            minLimit = DEF_INTELLIG;
        break;
        case Endurance:
            statValue = &endurance;
            minLimit = DEF_ENDURANCE;
        break;
    }
    switch(op){
        case Increment:
            if(*statValue == MAX_STAT_LIMIT) return -1;
            if(maxAvailablePoints > 0) {
                (*statValue)++;
                maxAvailablePoints--;
            }
        break;
        case Decrement:
            if(*statValue > minLimit) {
                (*statValue)--;
                maxAvailablePoints++;
            }
        break;
    }
    calculateSecondaryCharacterValues();
    calculateClass();
    return *statValue;
}
