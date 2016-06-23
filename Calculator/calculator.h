#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "main.h"

class Calculator : public ICommandListener
{
public:
    Calculator(IDisplay* _display);
    virtual void OnTextEnter(QString s);
    virtual void OnClear();
    virtual void OnEquals();
    virtual void OnBack();

private:
    IDisplay* display;
    QString expression;

};

#endif // CALCULATOR_H
