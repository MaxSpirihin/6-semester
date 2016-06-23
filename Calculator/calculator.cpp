#include "calculator.h"

Calculator::Calculator(IDisplay *_display)
{
   display = _display;
}


void Calculator::OnTextEnter(QString s)
{
    expression += s;
    display->ShowText(expression);
}

void Calculator::OnClear()
{
    expression = QString("");
    display->ShowText("0");
}

void Calculator::OnEquals()
{
    QScriptEngine engine;
    double Result = engine.evaluate(expression).toNumber();
    expression = QString(QString::number(Result));
    display->ShowText(QString::number(Result));
}

void Calculator::OnBack()
{
    if (!expression.isEmpty())
    {
    expression = expression.mid(0,expression.length()-1);
    }
    if (!expression.isEmpty())
        display->ShowText(expression);
    else
         display->ShowText("0");
}
