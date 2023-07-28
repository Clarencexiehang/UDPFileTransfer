#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QWidget>
#include<QFileDialog>
#include<QStyledItemDelegate>
#include<QPainter>
#include<QProgressBar>
#include<QLabel>
#include<QPushButton>
#include<QModelIndex>
#include<QStandardItemModel>
#include<QHBoxLayout>
#include<QMenu>
#include<QAction>
#include<QList>

#include<QtCore>
#include<QtNetwork/QNetworkAccessManager>
#include<QtNetwork/QNetworkReply>


#include"config.h"
#include"Request.h"
#include"DownLoad.h"


//
#include"../Entity/BreakPoint.h"
#include"../Service/clientservice.h"
#include"DownFileInfo.h"

namespace Ui {
class MainPage;
}

class MainPage : public QWidget
{
    Q_OBJECT

public:
    explicit MainPage(QWidget *parent = nullptr);
    ~MainPage();
    void startDown();
    void stopDown();
    void instantDown();
    void pauseDown();
    //绘制窗口颜色
    void paintEvent(QPaintEvent *);

    //用户信息
    void downUser();
    void setUserName(QString username);
    QString getUserName();

    //
    void setBreakPoint(BreakPoint *b);
    BreakPoint* getBreakPoint();

signals:
    void updatePercentSignal(int id, int percent);
    void setErrorSignal(int id);

public slots:
    void on_selectPathBtn_clicked();
    void on_startDownBtn_clicked();
    void on_fileListWidget_customContextMenuRequested(const QPoint &pos);

    void on_backToLogBtn_clicked();
    //更改界面进度
    void updatePercent(int id,int percent);
    void updatePercentSlot(int id,int percent);
    //设置出错标志
    void setError(int id);
    void setErrorSlot(int id);
    //下载完成后隐藏进度
    void hideCompleteProgress(int id,QTimer*t);
    void clearTimer(QTimer *timer);

private:
    Ui::MainPage *ui;
    QString username;
    QMenu *menu;
    QList<int> selectedIndexList;

    //
    BreakPoint *breakPoint;

    //断点文件信息
    QList<DownFileInfo> breakDownFileInfo;
};
#endif // MAINPAGE_H
