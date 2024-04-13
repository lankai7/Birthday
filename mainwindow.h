#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QMessageBox>
#include <QDebug>
#include <QInputDialog>
#include <string.h>
#include <QtWidgets>
#include <QSystemSemaphore>
#include <QSharedMemory>
#include <QMessageBox>

#include "ui_mainwindow.h"
#include "appreciate.h"
#include "SQLconnect.h"
#include "SystemTime.h"
#include "SQLconnect.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



private slots:
    void on_actionInfo_triggered();

    void on_actionAdd_New_triggered();

    void on_actionSearch_triggered();

    void on_actionRefresh_triggered();

    void on_actionDelete_triggered();

    void on_actionUpdate_triggered();

    void on_actionAppreciate_toggled(bool arg1);

private:
    Ui::MainWindow *ui;
    //系统时
    SystemTime* time = new SystemTime;
    //数据库
    SQLconnect* SQL = new SQLconnect;
    //赞赏页面
    Appreciate *appreciateWindow;

    void reFreshAllData();
    void reFreshRecnetlyData();
};
#endif // MAINWINDOW_H
