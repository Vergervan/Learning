#include "character.h"

void Character::calculateSecondaryCharacterValues(){
    health = strength * HEALTH_RATE;
    damage = agility * DAMAGE_RATE;
    mana = intelligence * MANA_RATE;
    weight = endurance * WEIGHT_RATE;
}

int Character::changeStat(CharacterStat cs, Operation op){
    int* statValue = nullptr;
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
            if(*statValue == 10) return -1;
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
    return *statValue;
}
