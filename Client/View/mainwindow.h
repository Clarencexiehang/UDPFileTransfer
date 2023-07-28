#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QDebug>
#include<QMessageBox>

#include<QtCore>
#include<QtNetwork/QNetworkAccessManager>
#include<QtNetwork/QNetworkReply>


//文件头
#include"View/mainpage.h"
//

//#include"clientservice.h"
//#include"BreakPoint.h"

//配置文件
#include"Request.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    //请求 IP url
    QString url = "http://192.168.1.104:8888";

    //显示主界面
    MainPage * getMainPage();
    void paintEvent(QPaintEvent *);

private slots:
    void on_logBtn_clicked();

private:
    Ui::MainWindow *ui;
    //主界面
    MainPage *mainPage;
};
#endif // MAINWINDOW_H
