#ifndef DATEANDTIME_H
#define DATEANDTIME_H

#include<QString>
#include <QTime>

class DateAndTime
{
public:
    DateAndTime() = default;
    DateAndTime(QDateTime &dt, int sec)
    {
        seconds = sec%60; //no errors
        dateTime = dt;
    }

    QString DateAndTimeToString();

    QDateTime dateTime;
    int seconds;
};

#endif // DATEANDTIME_H
