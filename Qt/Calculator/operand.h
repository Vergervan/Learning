#ifndef OPERAND_H
#define OPERAND_H

#include <QString>

class Operand{
private:
    QString numStr;
    bool _signed = false, _pointed = false, _zero = false;
public:
    inline void setIsSigned(bool s){
        _signed = s;
    }
    inline bool getIsSigned(){ return _signed; }
    inline void setIsPointed(bool p){
        _pointed = p;
    }
    inline bool getIsPointed(){ return _pointed; }
    inline void setIsZero(bool z){
        _zero = z;
    }
    inline bool getIsZero() { return _zero; }
    double toDouble(bool* b = nullptr);
    float toFloat(bool* b = nullptr);
    inline QString getString(){ return numStr; }
    bool findCharInOperand(char ch);
    void addChar(char);
    void setValue(const char* str);
    void setValue(QString str);
    void clear();
    int length();
    int trueLength();
    void removeLastCharacter();
    void checkSpecialCharacters();
    inline int startNumberPosition(){
        return _signed ? 1 : 0;
    }
};
#endif // OPERAND_H
