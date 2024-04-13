#ifndef SYSTEMTIME_H
#define SYSTEMTIME_H
#include<ctime>
#include <windows.h>
#include <QString>

class SystemTime
{
private:
    int years;
    int months;
    int days;
    QString Timer;
public:
    SystemTime();
    //获取现在时间
    QString getTime();
    //获取月份
    int getMonth();
};

#endif // SYSTEMTIME_H
