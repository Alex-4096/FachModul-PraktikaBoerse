// 2021-08-24-1200 export der Tabellenansicht in csv Datei
#include "filehandling.h"
#include <QDebug>
#include <QSqlRecord>
#include <QStandardItemModel>

FileHandling::FileHandling()
{

}

FileHandling::FileHandling(QString filename)
{
   this->setFileName(filename);

}


bool FileHandling::writeCSV(QTableView *table)
{
    int rows = table->model()->rowCount();
    int cols = table->model()->columnCount();
    QString line2write;
    qDebug()<<__FILE__<<" "<<__LINE__<<"CSV Schreiben aus Table mit "<<cols<<"Spalten"
            <<rows<<"Zeilen";
    for(int index = 0; index < cols; index++)
   { QString colHeader  = table->model()->headerData(index,Qt::Orientation::Horizontal).toString();
    line2write += colHeader +";";}


     line2write += "\n";

    // in 2 Schleifen durch das Model : zeilenweise , Spalten durch ; trennen
    for(int row = 0; row < rows; row++)
    {
        for(int col = 0; col < cols; col++)
        {
            line2write += table->model()->data(table->model()->index(row,col)).toString();
            line2write += ";";
        }
        line2write += "\n";

    }
    if(this->open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
    {
        QTextStream out(this);
        out << line2write;
        this->close();
        return true;
    }



     qDebug()<<__FILE__<<" "<<__LINE__<<"\n"<<line2write;
    return false;
}

bool FileHandling::readCSVInto(QTableView *table)
{
    QStandardItemModel *model = new QStandardItemModel;

    if(this->open(QIODevice::ReadOnly))
    {   qDebug()<<__FILE__<<" "<<__LINE__<<this->fileName()<<" opened";
        int lineindex = 0;                        // file line counter
            QTextStream in(this);                 // read to text stream
            while (!in.atEnd()) {

                    // read one line from textstream(separated by "\n")
                    QString fileLine = in.readLine();

                    // parse the read line into separate pieces(tokens) with "," as the delimiter
                    QStringList lineToken = fileLine.split(",", QString::SkipEmptyParts);

                    // load parsed data to model accordingly
                    for (int j = 0; j < lineToken.size(); j++) {
                        QString value = lineToken.at(j);
                        QStandardItem *item = new QStandardItem(value);
                        model->setItem(lineindex, j, item);
                    }

                    lineindex++;
                }

                this->close();

    table->setModel(model);

    }
    return true;
}
