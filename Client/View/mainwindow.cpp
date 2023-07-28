#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(800,600);
    ui->usernameInput->setPlaceholderText("请输入用户名");
    ui->passwordInput->setPlaceholderText("请输入密码");

    ui->welcomLabel->setObjectName("welcomLabel");
    ui->welcomLabel_2->setObjectName("welcomLabel_2");
    ui->welcomLabel_3->setObjectName("welcomLabel_3");
    ui->welcomLabel_4->setObjectName("welcomLabel_4");
    ui->usernameLabel->setObjectName("usernameLabel");
    ui->usernameInput->setObjectName("usernameInput");
    ui->passwordLabel->setObjectName("passwordLabel");
    ui->passwordInput->setObjectName("passwordInput");
    ui->logBtn->setObjectName("logBtn");
    ui->centralwidget->setObjectName("centralwidget");
    this->setObjectName("mainWindow");

    // ****************** 加载 qss 文件
    QFile file(":/qss/mainWindow.qss");
    /* 判断文件是否存在 */
    if (file.exists() ) {
        qDebug()<<"mainWindow.qss 加载成功 ______"<<endl;
        file.open(QFile::ReadOnly);
        QString styleSheet = QLatin1String(file.readAll());
        this->setStyleSheet(styleSheet);
        file.close();
    }else {
        qDebug()<<"mainWindow.qss 加载失败 ______"<<endl;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

MainPage *MainWindow::getMainPage()
{
    return mainPage;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QColor color(90, 185, 193);
    painter.setBrush(color);
    painter.drawRect(this->rect());

}

void MainWindow::on_logBtn_clicked()
{
    QString username = ui->usernameInput->text();
    QString password = ui->passwordInput->text();
    QString info=username+","+password;

    QString loginUrl = Config::url+"/login?username="+username+"&password="+password;
    QNetworkReply *reply =  Request::GET(loginUrl);
    //错误处理
    if (reply->error() == QNetworkReply::NoError){
         //请求返回的结果
         QByteArray responseByte = reply->readAll();
         QString valid= responseByte;
         if(valid=="error"){
             QMessageBox::information(this,
                                      "用户验证结果",
                                      "用户名或密码错误 !",
                                       "确定",
                                       "取消");
         }else{
             //初始化主界面
             MainPage *mainPage=new MainPage;

             QObject::connect(mainPage,&MainPage::updatePercentSignal,mainPage,&MainPage::updatePercentSlot);
             QObject::connect(mainPage,&MainPage::setErrorSignal,mainPage,&MainPage::setErrorSlot);

             mainPage->setWindowTitle("资源界面");
             mainPage->move(300,300);
             mainPage->setUserName(username);
             this->mainPage=mainPage;

             this->hide();
             this->mainPage->show();
         }
     }else{
         qDebug()<<"error !";
     }
}

