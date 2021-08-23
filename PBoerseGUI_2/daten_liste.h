#ifndef DATEN_LISTE_H
#define DATEN_LISTE_H

#include <QMap>

QMap <QString, QList<QString>> daten_liste
{
    {"firma",
        {
            "firmaName",
            "firmaRechtsform",
            "firmaBranche",
            "firmaWebsite",
            "firmaPersonalvemitler",
            "firmaInhouse"
        }
    },
    {"standort",
        {
            "standortOrt",
            "standortPlz",
            "standortStrasse",
            "standortTelefon",
            "standortZentraleCheckBox",
            "standortMitarbeiter"
        }
    }
};


#endif // DATEN_LISTE_H
