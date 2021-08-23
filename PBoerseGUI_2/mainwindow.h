#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtQuickWidgets/QQuickWidget>
#include <QDesktopServices>
#include "db.h"

#include <QDebug>
#include <QStandardItemModel>
#include <QMessageBox>
#include <QWidget>
#include <QObject>
#include <QtQuick>
#include <QtQuickWidgets/QQuickWidget>
#include <QPlainTextEdit>
#include <QVBoxLayout>
#include <QSqlQueryModel>
#include <QScrollBar>
#include <QRegExp>
#include <QRegExpValidator>

#include "formular.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void openHelp(QString err = "Tutorial");
     void showQry(QString qry, DB database);
     void showQry(QString qry, DB database,QList<int> ausblenden);
     QString curtable = "firma";


private slots:
    //-------------Startseite-------------------------------
        void on_pushStartseite_clicked();

        void on_pushRegistrieren_clicked();

        void on_pushAnmelden_clicked();

        void on_pushExit_clicked();

        void on_pushImportManuell_clicked();

        void on_pushImportWeb_clicked();

        void on_fachAuswahl_currentIndexChanged(const QString &arg1);

        void on_pushResetFilter_clicked();

        void on_skillAuswahl_currentIndexChanged(const QString &arg1);

        void on_spaltenFilter_currentIndexChanged(const QString &arg1);

        void on_checkBoxKartenEinAusToggle_clicked(bool checked);

        void on_suchFeld_editingFinished();


        void on_filterMinFeldEins_editingFinished();

        void on_filterMinFeldZwei_editingFinished();

        void on_filterMinFeldDrei_editingFinished();

        void on_filterMinFeldVier_editingFinished();

        void on_filterMinFeldFunf_editingFinished();


        void on_filterMaxFeldEins_editingFinished();

        void on_filterMaxFeldZwei_editingFinished();

        void on_filterMaxFeldDrei_editingFinished();

        void on_filterMaxFeldVier_editingFinished();

        void on_filterMaxFeldFunf_editingFinished();


        void on_tableViewTrefferTabelleAnzeige_clicked(const QModelIndex &index);


    //-------------Anmeldung-------------------------------
        void on_pushAnmeldenAn_clicked();

        void on_pushAbbrechenAn_clicked();


    //-------------Regestrierung-------------------------------
        void on_pushUserAnlegenReg_clicked();

        void on_pushAbbrechenReg_clicked();


    //-------------Info-------------------------------
        void on_actionVersion_triggered();

    //-------------Impressum-------------------------------
        void on_actionHauptsitz_triggered();

    //-------------Ansprechpartner-------------------------------
        void on_actionAnsprechpartner_triggered();

        void on_pushAnsprechpartnerAn_clicked();

        void on_pushAnsprechpartnerZur_clicked();

    //-------------Ausbildung,-Praktika-und-Jobangebote-------------------------------
        void on_angebotAnlegen_clicked();

        void on_angebotReset_clicked();

        void on_angebotBezeichnung_editingFinished();

        void on_angebotWebsite_editingFinished();

        void on_angebotForm_editingFinished();

        void on_angebotEinsatzortAbw_editingFinished();


    //-------------Firmen-und-Standorten-------------------------------
        void on_firmaStandortAnlegen_clicked();

        void on_firmaStandortReset_clicked();

        void on_firmaName_editingFinished();

        void on_firmaRechtsform_editingFinished();

        void on_firmaWebsite_editingFinished();

        void on_firmaBranche_editingFinished();

        void on_firmaPersonalvermitler_toggled(bool checked);

        void on_firmaInhouse_toggled(bool checked);


        void on_standortPlz_editingFinished();

        void on_standortStrasse_editingFinished();

        void on_standortOrt_editingFinished();

        void on_standortTelefon_editingFinished();

        void on_standortZentraleCheckBox_toggled(bool checked);

    //-------------Hilfe-------------------------------

        void on_quickWidget_sceneGraphError(const QQuickWindow::SceneGraphError &error, const QString &message);

        void on_actionTutorial_triggered();

        void on_actionFehlerbehandlung_triggered();
        void on_actionHandbuch_triggered();

        void on_tableViewTrefferTabelleAnzeige_activated(const QModelIndex &index);

        //-------------Web-Import--------------------------
                void on_pushButtonWebOpen_clicked();

                void on_pushButtonWebAbbrechen_clicked();

           //-------------CSV-Import--------------------------
                void on_pushImportCSV_clicked();

                void on_pushButtonCSVimport_clicked();

                void on_pushButtonCSVabbrechen_clicked();

                void on_pushButtonCSVdateiAuswahl_clicked();

        //-------------Karte-------------------------------

                void Standorte_aus_Tabelle_anzeigen();
                void on_updateMap_clicked();


                void on_firmaName_textEdited(const QString &arg1);

                void on_firmaRechtsform_textEdited(const QString &arg1);

                void on_firmaBranche_textEdited(const QString &arg1);



                void on_firmaWebsite_textEdited(const QString &arg1);

                void on_standortPlz_textEdited(const QString &arg1);

                void on_standortOrt_textEdited(const QString &arg1);

                void on_standortTelefon_textEdited(const QString &arg1);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
