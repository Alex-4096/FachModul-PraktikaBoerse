#ifndef CUSTOMDATABASE_H
#define CUSTOMDATABASE_H
#include <string>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <array>
#include <QMap>

using namespace std;

class DB : public QSqlDatabase
{
    QSqlDatabase db; //
    string hostname;
    string user;
    string password;
    string database;

    QSqlQuery query;
    int lastQueryResultRows;
    QString lastQueryCmd;

    QMap<QString, QString> firmen_daten;

public:
    DB(string hostname ,string user ,string database);

    bool connect(string);  // deklaration: returntype signatur
    bool execQuery(QString);
    bool execQuery(QMap<QString, QString> list, bool exist);
    QSqlDatabase get_db() { return db;}
    QSqlQuery get_query() { return query;}
    int get_lastQueryResultRows() { return lastQueryResultRows;}
    QString get_lastQueryCmd() { return lastQueryCmd;}
    string get_user() {return user;}
    QString get_curTable();

    array<double, 2> get_coordinate(int, QString);

    QList<QString> get_enumListe(QString);
    QList<QString> get_pflichtfeld(QString);
};

#endif // CUSTOMDATABASE_H
