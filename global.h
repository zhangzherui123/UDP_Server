#ifndef GLOBAL_H
#define GLOBAL_H

#include <QWidget>
#include <QToolButton>
#include <QUdpSocket>
#include <QDataStream>
#include <QMap>
#include <qdebug.h>
#include <QSet>
#include <QToolButton>
#include "widget.h"
#include <QMessageBox>



quint32 leastCommonMultiple(quint32 a, quint32 b);
quint32 maxCommonDivisor(quint32 a, quint32 b);

quint32 multiMod(quint32 input, quint32 rate, quint32 y);

quint32 CheckSum(QString str, quint32);
QString CodeMsg(QString str, quint8 key);
QString DeCodeMsg(QString str, quint8 key);
bool isPrime( quint32 num );
#endif // GLOBAL_H
