#include "widget.h"
#include <QApplication>

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>



//#include "udp2.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();


//        QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

//        db.setHostName("localhost");  //远程数据库的主机IP
//        db.setDatabaseName("nengxin");
//        db.setUserName("root");  //用户名
//        db.setPassword("123456");
//        if(!db.open())
//        {
//            qDebug()<<db.lastError();
//            return 0;
//        }
//        else
//        {
//            qDebug()<<"open success!";
//        }

//        QSqlQuery query(db);
////        if(!query.exec("create table student(Ciphertext varchar primary key,"
////                           "userName varchar(20))"))
//        if(!query.exec("create table student(Ciphertext int primary key,"
//                       "userName varchar(20))"))
//        {
//            qDebug()<<"creat success!";
//        }
//        if(!query.exec("insert into nengxin.student values(1,'first')"))//在数据库中，可能会出错，但是在Qt中却没有出错
//        {
//            qDebug() << "error1" ;
//        }

//        query.exec("create table student(id int primary key,"
//                                            "name varchar(20))");
//query.exec("CREATE TABLE student(Ciphertext varchar primary key, " "userName varchar," "CheckSum integer," "Key integer))");

//        if(!query.exec("insert into nengxin.student values(1,'first')"))//在数据库中，可能会出错，但是在Qt中却没有出错
//        {
//            qDebug() << "error1" ;
//        }
//        if(!query.exec("insert into nengxin.student values(2,'second')"))
//        {
//               qDebug() << "error2" ;
//        }


//        //插入内容语句：创建好表格后，插入一行语句
//             //在数据库中，需要把单引号变为双引号，即：'first'变为"first"
//         query.exec("insert into nengxin.student(id,name) values(40,'ABC')");//这条语句绝对可用，经过我亲自测试十几次

//           //修改一行内容语句(更新语句)
//          query.exec("update nengxin.student set name='zhang' where id=1");

//          //删除一行内容语句
//          query.exec("delete from nengxin.student where id>=2");

//          //必须创建好表后，才能对列进行操作
//          //插入一列内容语句
//          query.exec("alter table nengxin.student add address char(60)");//在表列的后面增加一列，列明为address
//          query.exec("alter table nengxin.student add address123 char(60)");
//          query.exec("alter table nengxin.student add age tinyint unsigned after name");//在列名称为name的后面增加一列，列名称为age

//        //删除一列内容语句
//          query.exec("alter table nengxin.student drop address123");//在表的后面删除一列

//          //修改列的类型或者名称
//          query.exec("alter table nengxin.student change name name varchar(30)");//将列名称name改为name varchar(30)类型

//          //修改表名称drop table nengxin.mqtt
//          query.exec("alter table nengxin.student rename nengxin.student1");//将表nengxin.student名称修改为nengxin.student1
//          query.exec("alter table nengxin.student1 rename nengxin.student");//将表nengxin.student1名称修改为nengxin.student

//          //遍历数据库（查询数据库表nengxin.student每一行的内容，并且输出）
//          query.exec("SELECT * FROM nengxin.student where id>=0");//代表选择id=3的一行内容
//          while(query.next())//遍历数据表nengxin.student每一行，从第0行到最后一行
//          {
//            quint32 id = query.value(0).toInt();//value(0)，0代表第几列的值。在该例中，代表id=3的行，第0列
//              QString name = query.value(1).toString();
//              QString age = query.value(2).toString();
//              QString address = query.value(3).toString();
//              qDebug()<<id<<name<<age<<address;//输出MySql数据库表mqtt.a10001中id=3的MAC和state
//          }




//        db.close();//关闭数据库






//        QStringList tables = db.tables();
//        if(!tables.contains("users"))
//        {
//            if(!query.exec("CREATE TABLE users(id integer primary key, name varchar, age integer);"))
//            {
//                qDebug()<<"create users error";
//                qDebug()<<query.lastError();
//                db.close();
//                return 0;
//            }
//        }
//        if(!query.exec("insert into users values(1, 'name1', 21), (2, 'name2', 23);"))
//        {
//            qDebug()<<"insert data into users error";
//            qDebug()<<query.lastError();
//        }
//        if(!query.exec("select * from users;"))
//        {
//            qDebug()<<"query from users error";
//            qDebug()<<query.lastError();
//        }
//        for(; query.next();)
//        {
//            qDebug()<<query.value("id").toInt();
//            qDebug()<<query.value("name").toString();
//            qDebug()<<query.value("age").toUInt();
//        }
//        db.close();

    return a.exec();
}
