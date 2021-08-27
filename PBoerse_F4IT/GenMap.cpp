#include "GenMap.h"

#include "mainwindow.h"
#include "mainwindow.cpp"

#include <QDebug>

#include <qqmlengine.h>
#include <qqmlcontext.h>
#include <qqml.h>
#include <QtQuick/qquickitem.h>
#include <QtQuick/qquickview.h>

GenMap::GenMap()
{

}

//QObject* zeigt hier jeweils auf den Inhalt des Quickwidgets mit der Karte
void GenMap::Karte_zentrieren (QObject *cent, double latc, double lngc)
{

    cent->setProperty("centlat", latc);
    cent->setProperty("centlng", lngc);

}

void GenMap::Home_zeigen (QObject *home, double lath, double lngh)
{
    home->setProperty("homelat", lath);
    home->setProperty("homelng", lngh);
}

void GenMap::Firma_zeigen (QObject *firm, double latf, double lngf, QString firmname, int x)
{


    for (int i=1; i<=x; i++){
        QString c = QString::number(i);
        QString flat = "firmlat" + c;
        QString flng = "firmlng" + c;
        QString fname = "firmname" + c;
        //qDebug()<<flat<<"+"<<flng<<"+"<<fname;

        double lat = 52.300 + (0.015 * i);
        double lng = 9.700 + (0.02 * i);
        //qDebug()<<lat<<"+"<<lng;


        firm->setProperty(flat.toStdString().c_str(), lat);
        firm->setProperty(flng.toStdString().c_str(), lng);
        firm->setProperty(fname.toStdString().c_str(), fname);

    }

    for (int i=(x+1); i<=10; i++){
        QString c = QString::number(i);
        QString flat = "firmlat" + c;
        QString flng = "firmlng" + c;
        QString fname = "firmname" + c;
        //qDebug()<<flat<<"+"<<flng<<"+"<<fname;

        firm->setProperty(flat.toStdString().c_str(), NULL);
        firm->setProperty(flng.toStdString().c_str(), NULL);
        firm->setProperty(fname.toStdString().c_str(), NULL);

    }


    /*firm->setProperty("firmlat", latf);
    firm->setProperty("firmlng", lngf);
    firm->setProperty("firmname", firmname);*/


}
//Evtl. Darstellung mehrerer Firmen gleichzeitig.

void GenMap::Punkte_setzen (QObject *mapObject, QList<double> latList, QList<double> lngList, QList<QString> firmList)
{
    int max = 15;
    int x = latList.count();
    if (x > max)
        x = max;

    /*qDebug()<<x;
    qDebug()<<latList;
    qDebug()<<lngList;
    qDebug()<<firmList;*/

    for (int i=0; i<=x-1; i++){
        QString c = QString::number(i+1);
        QString flat = "firmlat" + c;
        QString flng = "firmlng" + c;
        QString fname = "firmname" + c;
        QString fvis = "firmvis" + c;
        //qDebug()<<flat<<"+"<<flng<<"+"<<fname;

        //qDebug()<<latList.at(i)<<"+"<<lngList.at(i)<<"+"<<firmList.at(i);

        mapObject->setProperty(flat.toStdString().c_str(), latList.value(i));
        mapObject->setProperty(flng.toStdString().c_str(), lngList.value(i));
        mapObject->setProperty(fname.toStdString().c_str(), firmList.value(i));
        mapObject->setProperty(fvis.toStdString().c_str(), true);

    }

    for (int j=x; j<=max-1; j++){
        QString c = QString::number(j+1);
        QString flat = "firmlat" + c;
        QString flng = "firmlng" + c;
        QString fname = "firmname" + c;
        QString fvis = "firmvis" + c;
        //qDebug()<<flat<<"+"<<flng<<"+"<<fname;

        mapObject->setProperty(flat.toStdString().c_str(), NULL);
        mapObject->setProperty(flng.toStdString().c_str(), NULL);
        mapObject->setProperty(fname.toStdString().c_str(), "");
        mapObject->setProperty(fvis.toStdString().c_str(), false);

    }

}
