#ifndef OPERAND_H
#define OPERAND_H

#include <QString>

class Operand{
private:
    QString numStr;
    void checkUniqueChars();
    bool _signed, _pointed, _zero;
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
};
#endif // OPERAND_H
