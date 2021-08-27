#ifndef QUERY_H
#define QUERY_H

#include <QMap>

QMap<QString, QList<QString>> tablemap
{
    {"firma",
        {
            "SELECT * FROM standort WHERE Firma_ID = ", //0 Firma_ID
            "SELECT * FROM firma WHERE name = ",        //1 Name
            "",                                         //2 Rechtsreform
            "SELECT * FROM standort WHERE plz = ",      //3 PLZ_Zentrale
            "SELECT * FROM standort WHERE ort = ",      //4 ORT_Zentrale
            "",                                         //5 Website
            "",                                         //6 Inhouse_IT
            "",                                         //7 Branche
            "",                                         //8 Personalvermittler
            "",                                         //9 eingetragenAm
            ""                                          //10 eingetragenVon
        }
    },
    {"standort",
        {
            "SELECT * FROM angebote WHERE standort_id = ", //0 Standort_ID
            "SELECT * FROM firma WHERE Firma_ID = ",    //1 Firma_ID
            "",                                         //2 Ersteintrag
            "",                                         //3 Zentrale
            "SELECT * FROM standort WHERE PLZ = ",      //4 PLZ
            "",                                         //5 Strasse
            "",                                         //6 ORT
            "",                                         //7 TelefonStandort
            "",                                         //8 Mitarbeiter
            "",                                         //9 eingetragenAm
            "",                                         //10 eingetragenVon
            "",                                         //11 sLat
            ""                                          //12 sLon
        }
    },
    {"angebote",
        {
            "SELECT * FROM angebote WHERE Angebot_ID = ", //0 Angebot_ID
            "SELECT * FROM standort WHERE Standort_ID = ", //1 Standort_ID
            "",                                         //2 Ansprechpartner_ID
            "SELECT * FROM angebote WHERE bezeichnung = ", //3 bezeichnung
            "",                                         //4 abweichender_Einsatzort
            "SELECT * FROM angebote WHERE AnforderungenAllg = ", //5 AnforderungAllg
            "",                                         //6 AnforedrungDetails
            "SELECT * FROM angebote WHERE Art = ", //7 Art
            "SELECT * FROM angebote WHERE Fachrichtung = ", //8 Fachrichtung
            "",                                         //9 Web
            "",                                         //10 Bewerbungsform
            "SELECT * FROM angebote WHERE AusgeschriebenAm = ", //11 ausgeschriebenAm
            "",                                         //12 Start
            "",                                         //13 nichtMehrGueltig
            "",                                         //14 eingetragenAm
            "",                                         //15 eingetragenVon
            "",                                         //16 ansprechpartner_Ansprechpartner_ID
            "",                                         //17 ansprechpartner_standort_Standort_ID
        }
    }
};

QMap<QString, QList<int>> db_map
{
    {"firma", {6, 7, 8, 9, 10} },
    {"standort", {2,3,7,8, 9, 10, 11,12} },
    {"angebote", {2,4,10,11,12,13, 14, 15, 16, 17} }
};


#endif // QUERY_H
