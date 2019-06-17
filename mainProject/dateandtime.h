#ifndef DATEANDTIME_H
#define DATEANDTIME_H

#include<QString>
#include <QTime>
#include<QDateTime>

class DateAndTime
{
public:
    DateAndTime() = default;
    DateAndTime(QDateTime &dt, int sec)
    {
        seconds = sec%60; //no errors
        dateTime = dt;
    }

    QDateTime dateTime;
    int seconds;
};

#endif // DATEANDTIME_H
