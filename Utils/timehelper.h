#ifndef TIMEHELPER_H
#define TIMEHELPER_H

#include <QString>

class TimeHelper
{
public:
    static QString print_elapsed_time(qint64 elapsed_time){

        double msecs = elapsed_time/1000000.0;

        if(msecs >= 1000)
            return QString::number(msecs/1000,'g',2) + " segundos";
        else
            return QString::number(msecs) + " milisegundos";
    }
};

#endif // TIMEHELPER_H
