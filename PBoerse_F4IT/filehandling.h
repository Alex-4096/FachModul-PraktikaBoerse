#ifndef FILEHANDLING_H
#define FILEHANDLING_H

#include <QFile>
#include <QString>
#include <QTableView>
#include <QSqlQuery>

class FileHandling : public QFile
{
public:
    FileHandling();
    FileHandling(QString filename);

    bool writeCSV(QTableView *table);    // Table als csv Datei ausgeben
    bool readCSVInto(QTableView *table); // csv Date in Table anzeigen
};

#endif // FILEHANDLING_H
