#include "udp2.h"
#include "ui_udp2.h"

udp2::udp2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::udp2)
{
    ui->setupUi(this);

    ui->myport->setText("9999");

    ui->toport->setText("8888");

    ui->toip->setText("127.0.0.1");

    udp = new QUdpSocket(this);

    // 绑定自身端口号
    udp->bind(ui->myport->text().toInt());

    // 点击了发送按钮后,发送数据
    connect(ui->send, &QPushButton::clicked, [=](){
        //第一个参数是文本框中的内容,第二个参数是对方的IP地址, 第三个参数是对方的端口号

        udp->writeDatagram(ui->input->toPlainText().toUtf8(), QHostAddress(ui->toip->text()), ui->toport->text().toInt());

        ui->record->append("My say :" + ui->input->toPlainText());

        // 清空输入框
        ui->input->clear();
    });

    connect(udp, &QUdpSocket::readyRead, [=](){
        // 读取信息
        // 获取报文的长度
        qint64 mysize = udp->pendingDatagramSize();
        // 缓存区的大小
        QByteArray array = QByteArray(mysize, 0);
        udp->readDatagram(array.data(), mysize);

        // 将数据同步到聊天记录
        ui->record->append(array);
    });
}

udp2::~udp2()
{
    delete ui;
}
