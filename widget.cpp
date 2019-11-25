#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget), db(QSqlDatabase::addDatabase("QMYSQL"))
{
    ui->setupUi(this);
//    mythread = new thread(this);
//    mythread->start();
    /**
          建立初始数据库
    */

    db.setHostName("localhost");  //远程数据库的主机IP
    db.setDatabaseName("nengxin");
    db.setUserName("root");  //用户名
    db.setPassword("123456");

    if(!db.open())
    {
        qDebug()<<db.lastError();
        return ;
    }
    else
        qDebug()<<"open success!";
    query = new QSqlQuery(db);


# if 0
    if(!query->exec("create table student(CheckSum int primary key,"
                   "userName varchar(20))"))
    {
        qDebug()<<"create student error";
        qDebug()<<query->lastError();
        db.close();
        return ;
    }
    if(!query->exec("alter table nengxin.student add Ciphertext TEXT(1024)"))//在表列的后面增加一列，列明为address
    {
        qDebug()<<"add student error1";
        qDebug()<<query->lastError();
    }

    if(!query->exec("alter table nengxin.student add Secret char(160)"))//在列名称为name的后面增加一列，列名称为age)//在表列的后面增加一列，列明为address
    {
        qDebug()<<"add student error2";
        qDebug()<<query->lastError();
    }

#endif
    myset.insert(server_Key);
    QList<QString> nameList;
    nameList.append("Aggie");
    nameList.append("mike");
    nameList.append("Blossom");
    nameList.append("Cherry");
    nameList.append("Cady");
    nameList.append("girl");
    nameList.append("Dabria");
    nameList.append("Ebony");
    nameList.append("Faith");


    for(int i = 0; i < nameList.size(); i++)
    {
        mymap.insert(nameList[i], (100*(i+1) + 10*(i+1) + i + 1));
    }

    ui->myport->setText("6000");

    ui->toport->setText("9999");

    ui->ServerIP->setText("192.168.81.1");

    server = new QUdpSocket(this);

    // 绑定自身端口号
    server->bind(ui->myport->text().toInt(), QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);

    // 点击了发送按钮后,发送数据
    connect(ui->save, &QPushButton::clicked, [=](){
        //第一个参数是文本框中的内容,第二个参数是对方的IP地址, 第三个参数是对方的端口号

//        server->writeDatagram(ui->input->toPlainText().toUtf8(), QHostAddress(ui->toip->text()), ui->toport->text().toInt());

//        ui->record->append("My say :" + ui->input->toPlainText());

//        // 清空输入框
//        ui->input->clear();
    });

    connect(server, &QUdpSocket::readyRead, this, &Widget::ReceiveMessage);

}

Widget::~Widget()
{
    server->close();
    server->destroyed();
    delete ui;
}


void Widget::ReceiveMessage()
{
    // 读取信息
    // 获取报文的长度


    qint64  mysize = server->pendingDatagramSize();

    QByteArray array = QByteArray(mysize, 0);
    QHostAddress recIP;
    quint16 recPort;
    server->readDatagram(array.data(), mysize,&recIP, &recPort);

    int msgType;
    QDataStream stream(&array, QIODevice::ReadOnly);
    stream >> msgType;
    switch (msgType) {
    case Secret_Request:
    {
        QString usrname;
        stream >> usrname;
//        qDebug() << "Receive msg " << D;
        ui->input->append(QStringLiteral("Client request for key"));
        quint32 client_key;
        stream >> client_key;
        for(quint32 i = 200; i < 9999; i++)
        {
            if(myset.find(i) == myset.end() && isPrime(i))
            {
                myset.insert(i);

                client_key = i;
                break;

            }
        }
        quint32 E;  // 分发给用户的加密公钥(需要返回给用户)
        E = Creat_Key(server_Key, client_key);
//        qDebug() << "D = " << D;
        Match_Key.insert(E, D);
        QByteArray array;
        QDataStream stream(&array, QIODevice::WriteOnly);
//        stream << Secret_Response << recPort << E << N;
        stream << Secret_Response  << E << N;
        server->writeDatagram(array, recIP, recPort);
        ui->input->append(QStringLiteral("Key created successfully"));
        break;
    }
    case LoginReqeust:
    {
//        QString usrname;
//        stream >> usrname;

        QString usrname;
        quint32 password;
        stream >> usrname >> password;
        if(mymap.find(usrname) == mymap.end())
        {
            // 构建数据包通知客户端没有注册
            ui->input->append("User : " + usrname + QStringLiteral(" does not exist"));
            QByteArray array;
            QDataStream stream(&array, QIODevice::WriteOnly);
//            stream << UnLogin << recPort <<usrname;
            stream << UnLogin <<usrname;
            server->writeDatagram(array, recIP, recPort);
            return;
        }
    //    qDebug("密码解密前:%d\n", password);
        if(loginset.find(usrname) != loginset.end())
        {
            QByteArray array;
            QDataStream stream(&array, QIODevice::WriteOnly);
//            stream << loginReapt << recPort <<usrname;
            stream << loginReapt  <<usrname;
            server->writeDatagram(array, recIP, recPort);



            ui->input->append("The logged in user repeatedly logs in, Please refuse");
            return;
        }

        password = multiMod(password, D, N);
    //    qDebug("密码解密后: %d\n", password);
        if(mymap[usrname] ==  password)
        {
            loginset.insert(usrname);
            quint32 E;
            stream >> E;
            ui->input->append("user :  " + usrname + QStringLiteral("  login in success  "));
            QByteArray array;
            QDataStream stream(&array, QIODevice::WriteOnly);
//            stream << LoginSuccess << recPort << usrname;
            stream << LoginSuccess  << usrname;
            server->writeDatagram(array, recIP, recPort);

            ui->record->append("user :  " + usrname + " D = " + QString::number(Match_Key[E]) + " E = " + QString::number(E) + "  N = " + QString::number(N));
            return;
        }
        else
        {
            qDebug() << "name = " << usrname << "passwd = " << password;
            ui->input->append("user :" + usrname + QStringLiteral("Passwd is Error"));
            QByteArray array;
            QDataStream stream(&array, QIODevice::WriteOnly);
//            stream << PasswdError << recPort << usrname;
            stream << PasswdError << usrname;
            server->writeDatagram(array, recIP, recPort);
            return;
        }
        break;

    }

    case Widget_Exit:
    {
//        QString usrname;
//        stream >> usrname;


        QString usrname;

        stream >> usrname;

        ui->input->append("user " + usrname + " exit !");
        loginset.erase(loginset.find(usrname));
        break;
    }

    case Msg:
    {

        quint32 key;
        quint32 CheckSum;
        QString usrname;
        QString msg;
        stream >> usrname >> key >> msg >> CheckSum;

//        stream >> usrname;


        QString tmp = "dafafag";
        qDebug() << tmp;
        usrname = QString("'") + usrname + QString("'");
//        msg = QString("'") + msg + QString("'");
//        msg = "123";
        QByteArray bytes = msg.toUtf8();
        QByteArray mybytes;
        for(int i = 0; i < msg.size(); i++)
        {
            if(bytes[i] >= '0' && bytes[i] <= '9' || bytes[i] >= 'a' && bytes[i] <= 'z' || bytes[i] >= 'A' && bytes[i] <= 'Z')
            {
                mybytes.append(bytes[i]);
            }
        }
        msg = mybytes;
        QString secret_Strng = QString::number(key);
        secret_Strng = QString("'") + secret_Strng + QString("'");
        QString mystr = QString("insert into nengxin.student(CheckSum,userName, Ciphertext, Secret) values(%3, %2, '%4', %1);").arg(secret_Strng).arg(usrname).arg(CheckSum).arg(msg);

        qDebug() << "mystr  = " << mystr;
        if(!query->exec(mystr))
        {
            qDebug()<<"insert data into users error";
            qDebug()<<query->lastError();
        }

        ui->communicate->append("The key for user " + usrname + " is " + QString::number(key));
        ui->communicate->append("The CheckSum for user " + usrname + " is " + QString::number(CheckSum));
        ui->communicate->append("Message to key for user " + usrname + " : ");
        ui->communicate->append(msg);
        ui->communicate->append(" ");

        break;
    }

    case UsrEnter:
    {
        break;
    }

    case UsrLeft:
    {
        break;
    }
    default:
    {

        break;
    }

    }
}

quint32 Widget::Creat_Key(quint32 p, quint32 q)
{

    quint32 L;
    quint32 E;
    N = p * q;
    //最小公倍数
    L = leastCommonMultiple(p - 1, q - 1);
    for (quint32 i = 2; i < L; ++i)
    {
        //找到一个不为1且跟L最大公约数为1
        if (maxCommonDivisor(L, i) == 1)
        {
            E = i;
            break;
        }
    }
    quint32 X = 1;
    while((X * L + 1) % E) {
        X ++;
    }

    D = (X * L + 1) / E;
    return E;
}

void Widget::on_save_clicked()
{
//    server->bind(ui->myport->text().toInt());


    if(ui->communicate->document()->isEmpty())
    {
        QMessageBox::warning(this, "警告", "Chat record box cannot be empty");
        return;
    }
    QString str1 = QStringLiteral("CompleteRecord");
    QString str2 = QStringLiteral("ChatRecord");
    QString path = QFileDialog::getSaveFileName(this, str1, str2, "(*.txt)");
//     如果聊天框是空的, 这里的documnet是另外一种获取文本的方式
    if(path.isEmpty())
    {
        QMessageBox::warning(this, "警告", "Path cannot be empty");

        return;
    }

    QFile file(path);
    // 打开模式加换行操作
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream stream(&file);
    stream << ui->communicate->toPlainText();
    file.close();


//    if(ui->communicate->document()->isEmpty())
//    {
//        QMessageBox::warning(this, "警告", "Chat record box cannot be empty");
//        return;
//    }
//    QString mystr = QString("insert into users values(1, 'name1', 21), (2, 'name2', 23);")


//   query.exec("insert into users values(1, 'name1', 21), (2, 'name2', 23);")
}
