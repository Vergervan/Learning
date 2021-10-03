#include "operand.h"

float Operand::toFloat(bool* ok){
    return numStr.toFloat(ok);
}

double Operand::toDouble(bool* ok){
    return numStr.toDouble(ok);
}

bool Operand::findCharInOperand(char ch){
    for(int i = 0; i < numStr.length(); i++) if(numStr[i] == ch) return true;
    return false;
}

void Operand::setValue(QString str){
    clear();
    numStr = str;
    checkUniqueChars();
}

void Operand::setValue(const char *str){
    clear();
    numStr = str;
    checkUniqueChars();
}

void Operand::checkUniqueChars(){
    setIsSigned(findCharInOperand('-'));
    setIsPointed(findCharInOperand('.'));
    setIsZero(getIsSigned() ? (numStr[1] == '0' ? true : false) : (numStr[0] == '0' ? true : false));
}

void Operand::addChar(char ch){ numStr.append(ch); }

void Operand::clear(){
    numStr.clear();
    setIsSigned(false);
    setIsPointed(false);
    setIsZero(false);
}

void Operand::removeLastCharacter(){
    numStr = numStr.left(numStr.length()-1);
    if(numStr.length() < 1) clear();
}

int Operand::length() { return _signed ? numStr.length()-1 : numStr.length(); }
int Operand::trueLength() {return numStr.length();}
