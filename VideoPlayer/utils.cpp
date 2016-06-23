#include "utils.h"

QStringList Utils::arguments(int argc, char *argv[])
{
    QStringList list;
    for (int a = 0; a < argc; ++a) {
        list << QString::fromLocal8Bit(argv[a]);
    }
    return list;
}

