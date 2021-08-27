#include "formular.h"

formular::formular()
{

}


bool firmaB=false, rechtB=false, plzB=false, strB=false, vorhplzB=true, vorhstraB=true;

//ja, hier passiert etwas
QCompleter* formular::einfache_Liste(DB db, QString arg1, QString arg2)
{
    QStringList liste;
    QString abfrage = "SELECT " + arg1 + " FROM " + arg2;
    qDebug()<< abfrage;
    db.execQuery(abfrage);
    while (db.get_query().next()){
        liste.append(db.get_query().value(0).toString());
        qDebug()<< db.get_query().value(0).toString();
    }

    QCompleter *complist;
    complist = new QCompleter(liste);
    complist->setCaseSensitivity(Qt::CaseInsensitive);
    complist->setFilterMode(Qt::MatchContains);

    return complist;

}


QCompleter* formular::einfache_Liste(DB db, QString arg1, QString arg2, Qt::MatchFlag flag)
{
    QStringList liste;
    QString abfrage = "SELECT " + arg1 + " FROM " + arg2;
    qDebug()<< abfrage;
    db.execQuery(abfrage);
    while (db.get_query().next()){
        liste.append(db.get_query().value(0).toString());
        qDebug()<< db.get_query().value(0).toString();
    }

    QCompleter *complist;
    complist = new QCompleter(liste);
    complist->setCaseSensitivity(Qt::CaseInsensitive);
    complist->setFilterMode(flag);

    return complist;

}


QString formular::einzelne_Daten(DB db, QString arg1, QString arg2, QString arg3)
{
    QString abfrage = "SELECT " + arg1 + " FROM " + arg2 + " WHERE " + arg3;
    //qDebug()<< "Query einzelne Daten: "<<abfrage;

    db.execQuery(abfrage);
    db.get_query().first();
    //qDebug()<< db.get_query().value(0).toString();
    //qDebug()<< wert;

    return db.get_query().value(0).toString();


}


void formular::eingabe_Test(QString eingabe, QRegExp regx, QString feldname)
{
        if (!regx.exactMatch(eingabe))
            Helper::openMsgBox("Unpassende Eingabe", "Die Eingabe im Feld:" + feldname, "entspricht nicht den Standards.", 1);
}


bool formular::pflicht_gefuellt(bool pflB, QString strng, QWidget *w)
{
    bool pflicht = false;
    QString cmd = "border: 1px solid ";
    if(strng!="vorhplz" && strng != "vorhstra")
       {w->setStyleSheet(cmd+(pflB?"black":"red"));}


    if (strng == "firma") firmaB = pflB;
    qDebug()<< "firma: "<<firmaB;
    if (strng == "recht") rechtB = pflB;
    qDebug()<< "recht: "<<rechtB;
    if (strng == "stplz") plzB = pflB;
    qDebug()<< "PLZ: "<<plzB;
    if (strng == "ststr") strB = pflB;
    qDebug()<< "Str.: "<<strB;
    if (strng =="vorhplz") vorhplzB = pflB;
    qDebug()<< "PLZ vorh: "<<vorhplzB;
    if (strng =="vorhstra") vorhstraB = pflB;
    qDebug()<< "Str. vorh: "<<vorhstraB;


    if (firmaB && rechtB && plzB && strB)
        if (vorhplzB == false || vorhstraB == false)
                pflicht = true;

    qDebug() << "Pflichtstatus: "<< pflicht;

    return pflicht;

}
