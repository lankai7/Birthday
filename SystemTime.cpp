#include "SystemTime.h"

SystemTime::SystemTime()
{
    SYSTEMTIME sys;
    GetLocalTime(&sys);
    years = sys.wYear; months = sys.wMonth; days = sys.wDay;
    Timer=QString::number(years,10)+"-"+
    QString::number(months,10)+"-"+
            QString::number(days,10)+"";
}

int SystemTime::getMonth()
{
    return months;
}

QString SystemTime::getTime(){
    return Timer;
}
