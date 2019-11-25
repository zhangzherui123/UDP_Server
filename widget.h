#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QUdpSocket>
#include "global.h"
#include <QMessageBox>
#include <QThread>
#include <QSet>
#include <QFileDialog>
#include <QFile>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>



//class thread;
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    enum Server_MsgType {Msg,UsrEnter,UsrLeft, LoginSuccess,UnLogin,PasswdError,Secret_Request, Secret_Response, LoginReqeust, LoginReponse,
                        Widget_Exit, loginReapt,CAPMSG};
    quint32 server_Key = 127 ;
    quint32 D;
    quint32 N;
    // 账号 - 密码
    QMap<QString, quint32> mymap;
    // key:是客户端可以用的公钥, value是该公钥对应的私钥,需要服务器去解密使用
    QMap<quint32, quint32> Match_Key;
    QMap<QString, quint32> Map_Name_To_Key;
    QSet<QString> loginset;
//    thread* mythread;
private:
    Ui::Widget *ui;
    // 服务器的密钥池
    QSet<quint32> myset;

public:
    // 创建一个套接字
    QUdpSocket* server;
    void ReceiveMessage();   //接受UDP消息

    // 为用户创建KEY
    quint32 Creat_Key(quint32 server_Key, quint32 client_key);

    // sql 数据库相关
    QSqlDatabase db;
    QSqlQuery* query;
    QStringList tables;
private slots:
    void on_save_clicked();
};

#endif // WIDGET_H
