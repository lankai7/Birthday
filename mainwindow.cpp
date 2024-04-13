#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //图片设置
//    ui->menu->setIcon(QIcon(":/res/img/menu.png"));
//    ui->menu_2->setIcon(QIcon(":/res/img/menu_2.png"));

    ui->toolBar->setStyleSheet("QToolBar { background-color: rgba(247,199,191,0.6); }");


    //显示当前时间
    ui->NewTime->setDigitCount(10);
    ui->NewTime->display(time->getTime());

    //输出所有信息
    MainWindow::on_actionRefresh_triggered();
    //赞赏页面
    appreciateWindow = nullptr;
}

MainWindow::~MainWindow()
{
    delete ui;
}

//信息栏
void MainWindow::on_actionInfo_triggered()
{
    QMessageBox::information(this,"信息","生日记录系统\n\n"
                                       "版本：V1.3\n"
                                       "功能：记录查询生日信息\n"
                                       "作者：July_Lankai\n"
                                       "更新日期：2024年4月13日\n\n"
                                       "“学会自私一点，好好爱自己。不已物喜或已悲。坐看风起云涌，笑看云卷云舒。生日快乐！”");
}

//添加栏
void MainWindow::on_actionAdd_New_triggered()
{
    //收集数据
    QString getName;
    int getMonths;
    int getDays;

    //获取名字
    bool bOk = false;
    getName = QInputDialog::getText(this,
                                             "添加信息",
                                             "请输入姓名",
                                             QLineEdit::Normal,
                                             "姓名",
                                             &bOk
                                              );
    if(SQL->selectName(getName).month != 0){
        QMessageBox::information(this, "错误", "已存在数据:" + getName + " " + QString::number(SQL->selectName(getName).month) + "-" + QString::number(SQL->selectName(getName).day));
        return;
    }

    if (bOk && !getName.isEmpty()){
        //获取月
        getMonths = QInputDialog::getInt(this,
                                           "添加信息",
                                           "请输入生日月份",
                                            1,				//默认值
                                            1,				//最小值
                                            12,			//最大值
                                            1,				//步进
                                            &bOk);

        if (bOk && getMonths >= 0) {
            //获取日
            getDays = QInputDialog::getInt(this,
                                            "添加信息",
                                            "请输入生日日期",
                                            1,				//默认值
                                            1,				//最小值
                                            31,			//最大值
                                            1,				//步进
                                            &bOk);

            if (bOk && getDays >= 0) {
                SQL->insertData(getName ,getMonths ,getDays);

                //刷新
                MainWindow::on_actionRefresh_triggered();
            }
            else{
                QMessageBox::information(this, "错误", "添加信息错误");
            }

        }

    }

}

//查找槽
void MainWindow::on_actionSearch_triggered()
{
    //获取名字
    QString getName;
    bool bOk = false;
    getName = QInputDialog::getText(this,
                                             "查询信息",
                                             "请输入姓名",
                                             QLineEdit::Normal,
                                             "姓名",
                                             &bOk
                                              );
    Date birth = SQL->selectName(getName);
    if(bOk== true){
        if(birth.month == 0){
            QMessageBox::information(this, "查询", "没有找到:"+getName);
        }
        else{
            QMessageBox::information(this, "查询", getName + " " + QString::number(birth.month) + "-" + QString::number(birth.day));
        }
    }
}

//赞赏

void MainWindow::on_actionRefresh_triggered()
{
    reFreshAllData();
    reFreshRecnetlyData();
}

void MainWindow::reFreshRecnetlyData()
{
    //显示近期生日信息
    SQL->screenBirth(time->getMonth());
    ui->textBrowser->clear();
    ui->textBrowser->setFontPointSize(15);
    ui->textBrowser->insertPlainText("看看最近谁要过生日:\n\n");
    ui->textBrowser->setFontPointSize(12);

    QVector<Person*> tmp = SQL->getRecentlyBirthDay();
    for (int i = 0; i<tmp.size(); i++)
    {
        QString name = tmp[i]->name.trimmed();
        QString month = QString::number(tmp[i]->birth.month);
        QString day = QString::number(tmp[i]->birth.day);
        QString text = name+" "+month+"-"+day+"\n";
        ui->textBrowser->insertPlainText((text));
    }
}

void MainWindow::reFreshAllData()
{
    //输出所有信息
    SQL->popData();
    ui->textBrowser_2->clear();
    ui->textBrowser_2->setFontPointSize(12);
    QVector<Person*> useinfo = SQL->getAllBirthDay();
    for (int i = 0; i<useinfo.size(); i++)
    {
        QString name = useinfo[i]->name.trimmed();;
        QString month = QString::number(useinfo[i]->birth.month);
        QString day = QString::number(useinfo[i]->birth.day);
        QString text = name+" "+month+"-"+day+"\n";
        ui->textBrowser_2->insertPlainText(text);
        //qDebug()<<(text);
    }
}

void MainWindow::on_actionDelete_triggered()
{
    //获取名字
    QString getName;
    bool bOk = false;
    getName = QInputDialog::getText(this,
                                             "删除信息",
                                             "请输入姓名",
                                             QLineEdit::Normal,
                                             "姓名",
                                             &bOk
                                              );
    Date birth = SQL->selectName(getName);
    if(bOk== true){
        if(birth.month == 0){
            QMessageBox::information(this, "删除失败", "没有找到:"+getName);
        }
        else{
            QMessageBox::information(this, "删除成功", getName + " " + QString::number(birth.month) + "-" + QString::number(birth.day));
            SQL->deleteData(getName);
        }
    }
    MainWindow::on_actionRefresh_triggered();
}
//更改信息
void MainWindow::on_actionUpdate_triggered()
{
    //收集数据
    QString getName;
    int getMonths;
    int getDays;

    //获取名字
    bool bOk = false;
    getName = QInputDialog::getText(this,
                                             "修改信息",
                                             "请输入需要修改的姓名",
                                             QLineEdit::Normal,
                                             "姓名",
                                             &bOk
                                              );
    if(bOk && SQL->selectName(getName).month == 0){
        QMessageBox::information(this, "错误", "不存在数据:" + getName);
        return;
    }

    if (bOk && !getName.isEmpty()){
        //获取月
        getMonths = QInputDialog::getInt(this,
                                           "修改信息:" + getName + " " + QString::number(SQL->selectName(getName).month) + "-" + QString::number(SQL->selectName(getName).day),
                                           "请输入修改后生日月份",
                                            1,				//默认值
                                            1,				//最小值
                                            12,			//最大值
                                            1,				//步进
                                            &bOk);

        if (bOk && getMonths >= 0) {
            //获取日
            getDays = QInputDialog::getInt(this,
                                            "修改信息",
                                            "请输入修改后生日日期",
                                            1,				//默认值
                                            1,				//最小值
                                            31,			//最大值
                                            1,				//步进
                                            &bOk);

            if (bOk && getDays >= 0) {
                SQL->updateData(getName ,getMonths ,getDays);

                //刷新
                MainWindow::on_actionRefresh_triggered();
            }
            else{
                QMessageBox::information(this, "错误", "更改数据失败:" + getName);
            }

        }

    }
}

void MainWindow::on_actionAppreciate_toggled(bool arg1)
{
    if (arg1) {
            if (!appreciateWindow) { // 如果窗口还没有创建，则创建它
                appreciateWindow = new Appreciate(this);
                appreciateWindow->setWindowTitle("感谢您的支持！");
                appreciateWindow->setWindowIcon(QIcon(":/res/img/Thanks.png"));
                appreciateWindow->move(42, 230); // 设置窗口位置
            }
            appreciateWindow->show(); // 显示窗口
        } else {
            if (appreciateWindow) { // 如果窗口已经创建，则隐藏它
                appreciateWindow->hide(); // 隐藏窗口，而不是关闭它
            }
        }
}
