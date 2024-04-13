#ifndef SQLCONNECT_H
#define SQLCONNECT_H
#pragma once

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>
#include <string>
#include <algorithm>

/*数据库操作*/

struct Date
{
    int month;
    int day;
};

struct Person
{
    QString name;
    Date birth;
};

class SQLconnect{
private:
    //表名
    QString dbo;
    //用于近期数据传输
    QVector<Person*> tmp;
    //用于全部
    QVector<Person*> useinfo;
    //保存姓名、生日信息
    QVector<Person*> info;
    //排序方法

public:
    // 添加SQL Server数据库驱动程序
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    SQLconnect();
    ~SQLconnect();

    // 插入数据
    bool insertData(const QString &Name, const int &Month, const int &Day);

    //输出数据
    void popData();

    // 查询数据
    Date selectName(const QString& Name);

    //本月以及下月的生日成员记录
    void screenBirth(const int month);

    // 更新数据
    bool updateData(const QString &Name, const int Month, const int Day);

    //删除数据
    bool deleteData(const QString &Name);

    //获取所有生日数据
    QVector<Person*> getAllBirthDay();
    //获取近期的生日数据
    QVector<Person*> getRecentlyBirthDay();

    //关闭数据库
    void closeSQL();

};

#endif // SQLCONNECT_H
