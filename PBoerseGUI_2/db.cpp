#include "db.h"
#include "helper.h"
#include <QDebug>
#include <QString>
#include <QSqlQuery>
#include <QSqlError>

DB::DB(string hostname ,string user ,string database)
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(QString::fromStdString(hostname));
    db.setDatabaseName(QString::fromStdString(database));
    db.setUserName(QString::fromStdString(user));
   // db.setPassword(QString::fromStdString(pw));
}

//----------------------------------------------------------------------------------------------//


bool DB::connect(string pw)
{
    bool ok = false;
    QString user = db.userName();

    // Prüft vor der Verbindung, ob der Datenbanktreiber vorhanden ist
    if (!(db.isDriverAvailable("QMYSQL")))
    {
        QString info = "Prüfen Sie, ob die DLL-Dateien des Treibers vorhanden sind und starten Sie die Anwendung neu";
        Helper::openMsgBox("Datenbankzugriff", "Datenbanktreiber nicht vorhanden!"+db.lastError().text(), info, 3);
        // Anwendung stoppen
    }
    // Prüft vor der Verbindung, ob der richtige Datenbanktreiber eingetragen worden ist
    else if (!(db.driverName() == "QMYSQL"))
    {
        QString info = "Prüfen Sie, ob der richtige Treiber angegeben worden ist und starten Sie die Anwendung neu";
        Helper::openMsgBox("Datenbankzugriff", "Datenbanktreiber nicht geladen!", info, 3);
        qDebug() << db.lastError().text();
    }
    else
    { if(db.open(user,QString::fromStdString(pw)))
        {qDebug()<<__FILE__<<":\n"<<__LINE__<<"db.open("<<user<<","<<QString::fromStdString(pw)<<")) ok";
            ok = true;
            query = QSqlQuery(db);   // notwendig, die Connection zuzweisen
        }
        else
        {QString info = db.lastError().text();
            Helper::openMsgBox("Datenbankzugriff", "Die Verbindung zur Datenbank ist fehlgeschlagen", info, 3);
        }
        // qDebug()<<__FILE__<<":\t"<<__LINE__<<"db is "<<(db.isOpen()?"open":"not open");
    }
    return ok;
}

//----------------------------------------------------------------------------------------------//


bool DB::execQuery(QString cmd)
{
    bool ok = false;
    qDebug()<<__FILE__<<" Zeile : "<<__LINE__<<"cmd = "<<cmd;

    qDebug()<<__FILE__<<":\t"<<__LINE__<<"db is "<<(db.isOpen()?"open":"not open");
    lastQueryCmd = cmd;
    qDebug()<<__FILE__<<" Zeile : "<<__LINE__<<"lastQueryCmd = "<<lastQueryCmd;

    if(query.exec(cmd))
    { qDebug()<<__FILE__<<":\t"<<__LINE__<<"query.exec("<<cmd<<") ok";
        lastQueryResultRows = query.size();
        ok=true;}
    else
    {
        qDebug()<<__FILE__<<":\n"<<__LINE__<<"query.exec("<<cmd<<") failed"<<
                  query.lastError().text();
        lastQueryResultRows = -1;
        QString info = query.lastError().text();
        Helper::openMsgBox("Datenbankabfrage", "Ausführung der Query fehlgeschlagen!", info, 3);
    }
    qDebug()<<__FILE__<<":\n"<<__LINE__<<"query.exec("<<cmd<<") has "<<lastQueryResultRows<<" rows";
    qDebug()<<__FILE__<<" Zeile : "<<__LINE__<<"lastQueryCmd = "<<lastQueryCmd;

    return ok;
}

//----------------------------------------------------------------------------------------------//
//
bool DB::execQuery(QMap<QString, QString> firmen_daten, bool exist)
{
    qDebug()<<__FILE__<<"\n"<<Q_FUNC_INFO<<"\tSTART";
    bool ok = false;

    if(exist)
        {
            query.exec("SELECT Firma_ID from 'fijp-demo'.'firma' WHERE Name = '" + firmen_daten["firmaName"] + "'");
            query.next();
            QString firma_id = query.value(0).toString();
            // Test
            qDebug()<<__LINE__<<query.lastQuery();
            qDebug()<<__LINE__<<query.value(0).toString();

            QString cmd = "INSERT INTO 'fijp-demo'.'standort'(Firma_ID, Zentrale,PLZ,Strasse, ORT, Mitarbeiter,TelefonStandort) VALUES("
                           + firma_id + ","
                           + firmen_daten["standortZentraleCheckBox"]+ ","
                           + firmen_daten["standortPlz"] + ","
                           + firmen_daten["standortStrasse"] + ","
                           + firmen_daten["standortOrt"] + ","
                           + firmen_daten["standortMitarbeiter"] + ","
                           + firmen_daten["standortTelefon"] + ")";
            DB::execQuery(cmd);
            // Test
            qDebug()<<__LINE__<<DB::get_query().value(0).toString();

        }
    else
        {
             QString cmd = "INSERT INTO 'fijp-demo'.'firma'(Name, Rechtsform, Branche, PLZ_Zentrale, ORT_Zentrale, Website, Inhouse_IT,Personalvermittler) VALUES("
                            + firmen_daten["firmaName"]+ ","
                            + firmen_daten["firmaRechtsform"] + ","
                            + firmen_daten["firmaBranche"] + ","
                            + firmen_daten["standortPlz"] + ","
                            + firmen_daten["standortOrt"] + ","
                            + firmen_daten["firmaWebsite"] + ","
                            + firmen_daten["firmaInhouse"] + ","
                            + firmen_daten["firmaPersonalvermitler"] + ")";
             DB::execQuery(cmd);
             // Test
             qDebug()<<__LINE__<<DB::get_query().value(0).toString();

             query.exec("SELECT last_instert_id() INTO @f_id");
             qDebug() << __LINE__ << query.lastError().text();
             qDebug() << query.lastInsertId();
             // Test
             qDebug()<<query.exec("SELECT @firma_id FROM firma WHERE Firma_ID = LAST_INSERT_ID()");


                     cmd = "INSERT INTO fijp-demo.standort(Firma_ID, Zentrale, PLZ, Strasse, ORT, Mitarbeiter,TelefonStandort) VALUES((SELECT @f_id),"
                            + firmen_daten["standortZentraleCheckBox"] + ","
                            + firmen_daten["standortPlz"] + ","
                            + firmen_daten["standortStrasse"] + ","
                            + firmen_daten["standortOrt"] + ","
                            + firmen_daten["standortMitarbeiter"] + ","
                            + firmen_daten["standortTelefon"]+ ")";

             DB::execQuery(cmd);
             // Test
             qDebug()<<__LINE__<<query.lastQuery();

          }

    qDebug()<<Q_FUNC_INFO<<"\tENDE\n"<<__FILE__;
    return ok;
}
//
//----------------------------------------------------------------------------------------------//

QString DB::get_curTable()
{    qDebug()<<__FILE__<<" Zeile : "<<__LINE__<<"lastQueryCmd = "<<lastQueryCmd;

    QString curTable;
    curTable = lastQueryCmd.mid(14,5); // ausschneiden des Tabellenname hinter SELECT * FROM _____
    qDebug()<<__FILE__<<" Zeile : "<<__LINE__<<"lastQueryCmd = "<<lastQueryCmd;
    qDebug()<<__FILE__<<" Zeile : "<<__LINE__<<"curTable ="<<curTable;
    return curTable;
}

//----------------------------------------------------------------------------------------------//

array<double, 2> DB::get_coordinate(int firma_id, QString plz)
{
    qDebug()<<__FILE__<<"\n"<<Q_FUNC_INFO<<"\tSTART";

    // Return-Variable
    array<double, 2> coordinate;

    // QString zu SQL-Abfrage aufbereiten
    QString cmd;
    QString cmd1 = "SELECT sLat, sLon FROM standort WHERE Firma_ID = ";
    QString cmd2 = " AND PLZ LIKE ";
    cmd.append(cmd1).append(QVariant::fromValue(firma_id).toString()).append(cmd2).append(plz);
    //---------------------------------------------//

    // SQL-Abfrage fuer die Koordinaten ausfuehren
    qDebug()<<__LINE__<<query.exec(cmd);
    qDebug()<<__LINE__<<"Return Zeilen-Anzehl: "<<query.numRowsAffected();
    //---------------------------------------------//

    // Ausgabe des Ergebnis der SQL-Abfrage im Debug
    while(query.next())
    {
        QString abfrage_erg;
        abfrage_erg.append(query.value(0).toString()+" / ").append(query.value(1).toString());
        qDebug()<<__LINE__<<"Abfrage-Ausgabe:\t"<<abfrage_erg;
    }
    //---------------------------------------------//

    // Befuellen des Arrays mit Koordinaten (double)
    if(query.exec() && query.numRowsAffected() == 1)
    {
        qDebug()<<__LINE__<<"Koordinaten in Array fuellen";
        while(query.next())
        {
            coordinate.at(0) = query.value(0).toDouble();
            coordinate.at(1) = query.value(1).toDouble();
        }

    }
    else
        qDebug()<<Q_FUNC_INFO<<__LINE__<<"Fehelr beim Befuellen des Array -> passen nur zwei Werte";
    //---------------------------------------------//

    // Ausgabe der Koordinaten aus dem Array im Debug
    QVariant coord_groesse;
    qDebug()<<__LINE__<<"Anzahl der Werte im Array: "<<coordinate.size();
    for(int i = 0; i < coord_groesse.fromValue(coordinate.size()).toInt(); i++)
    {
        qDebug()<<__LINE__<<"Nummer: "<<i+1;
        qDebug()<<__LINE__<<coordinate.at(i);
    }

    qDebug()<<Q_FUNC_INFO<<"\tENDE\n"<<__FILE__;
    return coordinate;
}

//----------------------------------------------------------------------------------------------//

QList<QString> DB::get_enumListe(QString enum_spalte)
{
    qDebug()<<__FILE__<<"\n"<<Q_FUNC_INFO<<"\tSTART";

    // Enum-Return-Liste
    QList<QString> enumListe;
    //---------------------------------------------//

    // vorbereiten des SQL-Statements
    QString cmd, tabelle, inListe;
    if(enum_spalte == "Art" || enum_spalte == "Fachrichtung")
    {
        tabelle = "angebote";
        inListe = " IN(1,2,3,4)";
    }
    if(enum_spalte == "Mitarbeiter")
    {
        tabelle = "standort";
        inListe = " IN(1,2,3,4,5,6,7,8,9,10) ORDER BY "+enum_spalte;
    }
    cmd.append("SELECT DISTINCT "+enum_spalte+" FROM "+tabelle+" WHERE "+enum_spalte+inListe);
    //---------------------------------------------//

    // Abfrage ausführen
    query.exec(cmd);
    qDebug()<<__LINE__<<"Ausgefuehrte Abfrage:\n"<<query.lastQuery();
    //---------------------------------------------//

    // befüllen von QList mit QString-Werten
    int i = 0;
    while(query.next())
    {
        enumListe.append(query.value(0).toString());
        i++;
    }
    //---------------------------------------------//

    // Test-Ausgabe der QList im Debug
    qDebug()<<__LINE__<<"Test-Ausgabe der QList:";
    for(int i = 0; i < QVariant::fromValue(enumListe.size()).toInt(); i++)
    {
        qDebug()<<__LINE__<<"Enum-Liste: "<<enum_spalte<<" = "<<enumListe.value(i);
    }
    //---------------------------------------------//

    qDebug()<<Q_FUNC_INFO<<"\tENDE\n"<<__FILE__;
    return enumListe;
}

//----------------------------------------------------------------------------------------------//

QList<QString> DB::get_pflichtfeld(QString tabelle)
{
    qDebug()<<__FILE__<<"\n"<<Q_FUNC_INFO<<"\tSTART";

    // QLsit mit den Pflichtfeldern
    QList<QString> pflichtfeld;
    //---------------------------------------------//

    // Abfrage, um die Pflichtfelder zu ermitteln
    query.exec("SELECT Spalte FROM feldlisteformulare WHERE Tabelle LIKE '"+tabelle+"' AND Pflicht != 0");
    qDebug()<<__LINE__<<"ausgefuehrte Abfrgae:\n"<<query.lastQuery();
    qDebug()<<__LINE__<<"Result-Rows: "<<query.numRowsAffected();
    //---------------------------------------------//

    // befüllen von QList mit QString-Werten
    if(query.numRowsAffected() > 0)
    {
        int i = 0;
        while(query.next())
        {
            pflichtfeld.append(query.value(0).toString());
            i++;
        }

        // Test-Ausgabe der QList im Debug
        qDebug()<<__LINE__<<"Größe von QList: "<<pflichtfeld.size();
        for(int i = 0; i < QVariant::fromValue(pflichtfeld.size()).toInt(); i++)
        {
            qDebug()<<__LINE__<<"Pflichtfeld: "<<pflichtfeld.value(i);
        }
    }
    else
    {
        qDebug()<<__LINE__<<"QList-Größe: "<<pflichtfeld.size();
        qDebug()<<__LINE__<<"Tabelle "+tabelle+" hat keine Pflichtfelder";
    }
    //---------------------------------------------//

    qDebug()<<Q_FUNC_INFO<<"\tENDE\n"<<__FILE__;
    return pflichtfeld;
}
