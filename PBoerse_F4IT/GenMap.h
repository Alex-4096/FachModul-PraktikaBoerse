#ifndef MAP_H
#define MAP_H

#include <QMainWindow>
#include <QObject>
#include <QQuickItem>
#include <QWidget>

class GenMap
{
public:
    GenMap();
    static void Karte_zentrieren (QObject *cent, double latc, double lngc);
    static void Home_zeigen (QObject *home, double lath, double lngh);
    static void Firma_zeigen (QObject *firm, double latf, double lngf, QString firmname, int x);
    static void Punkte_setzen(QObject *mapObject, QList<double> latList, QList<double> lngList, QList<QString> firmList);
};


#endif // MAP_H
