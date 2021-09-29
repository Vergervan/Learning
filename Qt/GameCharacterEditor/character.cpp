#include "character.h"

#define HEALTH_RATE 3.5
#define DAMAGE_RATE 6
#define MANA_RATE 11
#define WEIGHT_RATE 5.5

void Character::calculateSecondaryCharacterValues(){
    health = strength * HEALTH_RATE;
    damage = agility * DAMAGE_RATE;
    mana = intelligence * MANA_RATE;
    weight = endurance * WEIGHT_RATE;
}
