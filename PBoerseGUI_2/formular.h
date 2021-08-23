#ifndef FORMULAR_H
#define FORMULAR_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QSqlQuery>
#include <QList>
#include <QStringList>
#include <QRegularExpression>
#include <QIntValidator>
#include <QValidator>
#include <QRegularExpressionValidator>
#include <QCompleter>
#include <QRegExp>
#include <QRegExpValidator>
#include "db.h"
#include "mainwindow.h"
#include "helper.h"


class formular
{
public:
    formular();
    static int formplz;
    static int formstr;
    static int formkomp;
    static QStringList formbool;
    static QCompleter* einfache_Liste(DB db, QString arg1, QString arg2);
    static QCompleter* einfache_Liste(DB db, QString arg1, QString arg2, Qt::MatchFlag flag);
    static QString einzelne_Daten(DB db, QString arg1, QString arg2, QString arg3);
    static void eingabe_Test(QString eingabe, QRegExp regx, QString feldname);
    static bool pflicht_gefuellt(bool pflB, QString strng, int plz, int str);
};

#endif // FORMULAR_H
