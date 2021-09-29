#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>

enum Gender{
    None, Male, Female
};

class Character{
public:
    float health = 0, damage = 0, mana = 0, weight = 0;
    std::string name;
    Gender gender = None;
    int strength = 0, agility = 0, intelligence = 0, endurance = 0;
    int maxAvailablePoints = 10;
    inline void incStrength(){
        if(maxAvailablePoints > 0) {
            strength++;
            maxAvailablePoints--;
            calculateSecondaryCharacterValues();
        }
    }
    inline void decStrength(){
        if(strength > 0){
            strength--;
            maxAvailablePoints++;
            calculateSecondaryCharacterValues();
        }
    }
    inline void incAgility(){
        if(maxAvailablePoints > 0) {
            agility++;
            maxAvailablePoints--;
            calculateSecondaryCharacterValues();
        }
    }
    inline void decAgility(){
        if(agility > 0){
            agility--;
            maxAvailablePoints++;
            calculateSecondaryCharacterValues();
        }
    }
    inline void incIntelligence(){
        if(maxAvailablePoints > 0) {
            intelligence++;
            maxAvailablePoints--;
            calculateSecondaryCharacterValues();
        }
    }
    inline void decIntelligence(){
        if(intelligence > 0){
            intelligence--;
            maxAvailablePoints++;
            calculateSecondaryCharacterValues();
        }
    }
    inline void incEndurance(){
        if(maxAvailablePoints > 0) {
            endurance++;
            maxAvailablePoints--;
            calculateSecondaryCharacterValues();
        }
    }
    inline void decEndurance(){
        if(endurance > 0){
            endurance--;
            maxAvailablePoints++;
            calculateSecondaryCharacterValues();
        }
    }
    void calculateSecondaryCharacterValues();
};

#endif // CHARACTER_H
