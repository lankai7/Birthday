#include "SQLconnect.h"

/*------------------数据库记录用户账户密码--------------------*/
SQLconnect::SQLconnect(){
    // 设置ODBC数据源名称
    db.setDatabaseName("birthday");
    // 设置连接用户名和密码
    db.setUserName("lankai");
    db.setPassword("aini1314");
    //设置表格名
    dbo = "birthday_data";
    // 打开数据库连接
    if (db.open()) {
        qDebug() << "Connected to SQL Server!";
    }
}

SQLconnect::~SQLconnect(){
    QSqlDatabase::removeDatabase("birthday");
    qDebug() << "Disconnected from database";
}

//记录姓名和生日信息保存到表中
bool SQLconnect::insertData(const QString &Name, const int &Month, const int &Day) {
    QSqlQuery query;
    query.prepare("INSERT INTO "+ dbo + " (姓名, 生日月份, 生日日期) VALUES (?, ?, ?)");
    query.bindValue(0, Name);
    query.bindValue(1, Month);
    query.bindValue(2, Day);

    if (query.exec()) {
        qDebug() << "Data inserted successfully";
        return true;
    } else {
        qDebug() << "Error: " << query.lastError().text();
        return false;
    }
}
//所有数据从表中取出
void SQLconnect::popData()
{
    QSqlQuery query;
    query.prepare("SELECT * FROM "+ dbo);
    if (!query.exec()) {
            // 如果查询执行失败，输出错误信息并关闭文件
            qDebug() << "SQL查询错误: " << query.lastError().text();
            return;
        }

    // 遍历查询结果
    info.clear();
    while (query.next()) {
            Person* p = new Person;
            p->name = query.value("姓名").toString();
            p->birth.month = query.value("生日月份").toInt();
            p->birth.day = query.value("生日日期").toInt();
            info.push_back(p);
    }

    std::sort(info.begin(), info.end(),
              [](Person* &a, Person *&b){
                  if (a->birth.month != b->birth.month)
                  return a->birth.month < b->birth.month;
                  return a->birth.day < b->birth.day;
              });

    useinfo = info;
}
//查询生日
Date SQLconnect::selectName(const QString &Name) {
    QSqlQuery query;
    query.prepare("SELECT * FROM "+ dbo + " WHERE 姓名 = :qName");
    query.bindValue(":qName", Name);

    if (query.exec() && query.next()) {
        Date birth;
        birth.month = query.value("生日月份").toInt();
        birth.day = query.value("生日日期").toInt();
        return birth;
    } else {
        qDebug() << "没有找到:" << Name <<endl;
        return Date{0,0}; // 没找到
    }

}
//近期生日数据
void SQLconnect::screenBirth(const int month)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM "+ dbo + " WHERE 生日月份 = :qMonth OR 生日月份 = :qMonthNext");
    query.bindValue(":qMonth", month);
    query.bindValue(":qMonthNext", ((month+1)%12));

    tmp.clear();    //清空原数据
    if (query.exec()) {
        qDebug() << "screen successfully";
    }
    while (query.next()) {
        Person* p = new Person;
        p->name = query.value("姓名").toString();
        p->birth.month = query.value("生日月份").toInt();
        p->birth.day = query.value("生日日期").toInt();
        tmp.push_back(p);
    }
    std::sort(tmp.begin(), tmp.end(),
              [](Person* &a, Person *&b){
                  if (a->birth.month != b->birth.month)
                  return a->birth.month < b->birth.month;
                  return a->birth.day < b->birth.day;
              });
}

//更改数据
bool SQLconnect::updateData(const QString &Name ,const int Month ,const int Day) {
    QSqlQuery query;
    query.prepare("UPDATE " + dbo + " SET 生日月份 = ?, 生日日期 = ? WHERE 姓名 = ?");
    query.bindValue(0, Month);
    query.bindValue(1, Day);
    query.bindValue(2, Name);

    if (query.exec()) {
        qDebug() << "Data updated successfully";
        return true;
    } else {
        qDebug() << "Error: " << query.lastError().text();
        return false;
    }
}
//删除数据
bool SQLconnect::deleteData(const QString &Name)
{
    QSqlQuery query;
    query.prepare("DELETE FROM " + dbo + " WHERE 姓名 = :qName ");
    query.bindValue(":qName", Name);

    if (query.exec()) {
        qDebug() << "Data delete successfully:"<<query.numRowsAffected()<<endl;
        return true;
    } else {
        qDebug() << "Error: " << query.lastError().text()<<endl;
        return false;
    }
}

QVector<Person *> SQLconnect::getAllBirthDay()
{
    return useinfo;
}

QVector<Person *> SQLconnect::getRecentlyBirthDay()
{
    return tmp;
}

void SQLconnect::closeSQL(){
    QSqlDatabase::removeDatabase("birthday");
    qDebug() << "Disconnected from database";
}
