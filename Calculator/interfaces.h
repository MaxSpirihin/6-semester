#ifndef ICOMMANDLISTENER_H
#define ICOMMANDLISTENER_H
#include "main.h"

class ICommandListener
{
 public:
 virtual void OnTextEnter(QString s) = 0;
 virtual void OnClear() = 0;
 virtual void OnEquals() = 0;
 virtual void OnBack() = 0;
};


class IDisplay
{
    public:
    virtual void ShowText(QString s) = 0;
    virtual QString GetText() = 0;
    virtual void Clear() = 0;
};


#endif
