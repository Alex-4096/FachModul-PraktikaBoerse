#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "geo.h"
#include "GenMap.h"
#include "helper.h"
#include "query.h"

#include <QDesktopServices>
#include <QUrl>
#include <QFileDialog>
#include <QMessageBox>

#include <QCompleter>

GeoInfo home;
QObject *genMapObj;


DB test("fimando.info",  "cc21dm", "fijp-demo");

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);

    ui->quickWidget->setSource(QUrl("qrc:/GenMap.qml"));
    ui->quickWidget->setFixedSize(580,480);
    formular::formplz = 1;
    formular::formstr = 1;

    //ui->firmaStandortAnlegen->setEnabled(false);
    genMapObj = ui->quickWidget->rootObject();

    if (home.isSslSupported()) { // true/false
           home.request();
           qDebug()<<home.getCoords();
           MainWindow::setWindowTitle("Standort: "+home.getOrt()+
               +" lat:"+QString::number(home.getCoords()["latitude"])
               +" lon:"+QString::number(home.getCoords()["longitude"])    );

           GenMap::Karte_zentrieren (genMapObj, home.getCoords()["latitude"], home.getCoords()["longitude"]);
           GenMap::Home_zeigen(genMapObj, home.getCoords()["latitude"], home.getCoords()["longitude"]);

    ui->tableViewTrefferTabelleAnzeige->setMouseTracking(true);

    } else {
           home.sslError();
           openHelp("error0001");
       }

 // 1)-------------------DB-QDEBUG----------------------------------
    qDebug()<<test.connect("fLo9o8_8");
    QString aufrufPLZ = home.getPlz().left(2);
    QList<int> ausblenden {5,6,7,8,9,10};
    showQry("SELECT * FROM firma WHERE PLZ_Zentrale LIKE \""+aufrufPLZ+"%\"", test/*,ausblenden*/);

    //-------------DB-Verbindung-Anzeige-------------------------------------------
            if(test.connect("fLo9o8_8"))
            {
                if(test.connect("fLo9o8_8"))
                  {
                   ui->radioButtonON->setChecked(true);
                  }
                  else
                  {
                  ui->radioButtonStoerung->setChecked(true);
                  }
           }
           else
            {
            ui->radioButtonOFF->setChecked(true);
            ui->tableViewTrefferTabelleAnzeige->hide();
                        ui->quickWidget->hide();
                        ui->checkBoxKartenEinAusToggle->hide();
            }
    //-----------------------------------------------------------------------------

    MainWindow::Standorte_aus_Tabelle_anzeigen();


    //qDebug()<<"enumcount"<<test.get_enumListe("Mitarbeiter").count();
    for(int i =0; i <test.get_enumListe("Mitarbeiter").count(); i++)
        //qDebug()<<"enum"<<test.get_enumListe("Mitarbeiter").at(i);
        ui->standortMitarbeiter->addItem(test.get_enumListe("Mitarbeiter").at(i));

    ui->fachAuswahl->addItem("Fach auswählen.");
    ui->fachAuswahl->addItem("Fach 1");
    ui->fachAuswahl->addItem("Fach 2");
    ui->fachAuswahl->addItem("Fach 3");

    ui->skillAuswahl->addItem("Skills auswählen.");
    ui->skillAuswahl->addItem("Skill 1");
    ui->skillAuswahl->addItem("Skill 2");
    ui->skillAuswahl->addItem("Skill 3");

    ui->ortAuswahl->addItem("Ort auswählen.");
    ui->ortAuswahl->addItem("Ort 1");
    ui->ortAuswahl->addItem("Ort 2");
    ui->ortAuswahl->addItem("Ort 3");

    ui->ansprechpartnerAnrede->addItem("");
    ui->ansprechpartnerAnrede->addItem("Diverse");
    ui->ansprechpartnerAnrede->addItem("Frau");
    ui->ansprechpartnerAnrede->addItem("Herr");

    ui->anmeldungPass->setPlaceholderText("*********");
    ui->registrierungPass->setPlaceholderText("*********");
    ui->registrierungPassWied->setPlaceholderText("*********");
    ui->ansprechpartnerTelefon->setPlaceholderText("+12(123)123456-789");
    ui->ansprechpartnerEmail->setPlaceholderText("musterman@google.com");
    ui->angebotWebsite->setPlaceholderText("www.google.com");
    ui->firmaWebsite->setPlaceholderText("www.unicon.com");
    ui->standortPlz->setPlaceholderText("01234 oder 12345");
    ui->standortTelefon->setPlaceholderText("+12(123)123456-789");

    ui->lineEditWeb->setPlaceholderText("Webseite eingeben.");

       ui->quickWidget->hide();
       ui->updateMap->hide();
       ui->stackedWidget_2->hide();



 //2)-----------------------------------------------------------------------------
 ui->tableViewTrefferTabelleAnzeige->verticalHeader()->setVisible(false);

 QScrollBar *sb = ui->tableViewTrefferTabelleAnzeige->verticalScrollBar();
 qDebug()<<__FILE__<<" "<<__LINE__<<sb->value();

}
MainWindow::~MainWindow()
{ delete ui; }



//3)-------------Startseite--------------------
void MainWindow::on_pushStartseite_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    curtable = "firma";
    ui->labelMax->show();
    ui->labelMin->show();
    showQry("SELECT * FROM firma WHERE PLZ_Zentrale LIKE \""+home.getPlz().left(2)+"%\"", test);
}

void MainWindow::on_pushRegistrieren_clicked()
{
     ui->stackedWidget->setCurrentIndex(2);
     ui->labelMin->hide();
     ui->labelMax->hide();
}

void MainWindow::on_pushAnmelden_clicked()
{
     ui->stackedWidget->setCurrentIndex(3);
     ui->labelMin->hide();
     ui->labelMax->hide();
}

void MainWindow::on_pushExit_clicked()
{
     QApplication::quit();
}


void MainWindow::on_pushImportManuell_clicked()
{
      ui->stackedWidget->setCurrentIndex(1);
      ui->labelMin->hide();
      ui->labelMax->hide();


}

void MainWindow::on_pushImportWeb_clicked()
{
    ui->stackedWidget_2->show();
       ui->pageWebImport->show();
       ui->page2CSVimport->hide();
        QMessageBox::information(this, Q_FUNC_INFO,"Ab Zeile " + QString::number(__LINE__));
}

void MainWindow::on_pushResetFilter_clicked()
{
    QMessageBox::information(this, Q_FUNC_INFO,"Ab Zeile " + QString::number(__LINE__));
    showQry("SELECT 'reset' ",test);
}

void MainWindow::on_fachAuswahl_currentIndexChanged(const QString &arg1)
{
QMessageBox::information(this, Q_FUNC_INFO,"Ab Zeile " + QString::number(__LINE__));
}

void MainWindow::on_skillAuswahl_currentIndexChanged(const QString &arg1)
{
QMessageBox::information(this, Q_FUNC_INFO,"Ab Zeile " + QString::number(__LINE__));
}

void MainWindow::on_spaltenFilter_currentIndexChanged(const QString &arg1)
{
QMessageBox::information(this, Q_FUNC_INFO,"Ab Zeile " + QString::number(__LINE__));
}

void MainWindow::on_checkBoxKartenEinAusToggle_clicked(bool checked)
{
    if(ui->checkBoxKartenEinAusToggle->isChecked()) {
              ui->quickWidget->show();
              ui->updateMap->show();
          }else{
              ui->quickWidget->hide();
              ui->updateMap->hide();
              ui->tableViewTrefferTabelleAnzeige->resize(1177, 478);
          }
          QMessageBox::information(this, Q_FUNC_INFO,"Ab Zeile " + QString::number(__LINE__));
}

void MainWindow::on_suchFeld_editingFinished()
{
    QMessageBox::information(this, Q_FUNC_INFO,"Ab Zeile " + QString::number(__LINE__));
}


void MainWindow::on_filterMinFeldEins_editingFinished()
{
    QMessageBox::information(this, Q_FUNC_INFO,"Ab Zeile " + QString::number(__LINE__));
}

void MainWindow::on_filterMinFeldZwei_editingFinished()
{
    QMessageBox::information(this, Q_FUNC_INFO,"Ab Zeile " + QString::number(__LINE__));
}

void MainWindow::on_filterMinFeldDrei_editingFinished()
{
    QMessageBox::information(this, Q_FUNC_INFO,"Ab Zeile " + QString::number(__LINE__));
}

void MainWindow::on_filterMinFeldVier_editingFinished()
{
    QMessageBox::information(this, Q_FUNC_INFO,"Ab Zeile " + QString::number(__LINE__));
}

void MainWindow::on_filterMinFeldFunf_editingFinished()
{
    QMessageBox::information(this, Q_FUNC_INFO,"Ab Zeile " + QString::number(__LINE__));
}


void MainWindow::on_filterMaxFeldEins_editingFinished()
{
    QMessageBox::information(this, Q_FUNC_INFO,"Ab Zeile " + QString::number(__LINE__));
}

void MainWindow::on_filterMaxFeldZwei_editingFinished()
{
    QMessageBox::information(this, Q_FUNC_INFO,"Ab Zeile " + QString::number(__LINE__));
}

void MainWindow::on_filterMaxFeldDrei_editingFinished()
{
    QMessageBox::information(this, Q_FUNC_INFO,"Ab Zeile " + QString::number(__LINE__));
}

void MainWindow::on_filterMaxFeldVier_editingFinished()
{
    QMessageBox::information(this, Q_FUNC_INFO,"Ab Zeile " + QString::number(__LINE__));
}

void MainWindow::on_filterMaxFeldFunf_editingFinished()
{
    QMessageBox::information(this, Q_FUNC_INFO,"Ab Zeile " + QString::number(__LINE__));
}

void MainWindow::on_updateMap_clicked()
{
    QMessageBox::information(this, Q_FUNC_INFO,"Ab Zeile " + QString::number(__LINE__));
    Standorte_aus_Tabelle_anzeigen();
}

//4)-------------Anmeldung--------------------
void MainWindow::on_pushAnmeldenAn_clicked()
{
    QString anmUserName = ui->anmeldungUserName->text();
        QString anmUserPass = ui->anmeldungPass->text();

        if(anmUserName == "test" && anmUserPass == "test"){
            ui->labelAnmeldungErf->setText("Anmeldung erfolgreich");
         QMessageBox::information(this, Q_FUNC_INFO,"Ab Zeile " + QString::number(__LINE__));
        }else{
            ui->labelAnmeldungErf->setText("Anmeldung fehlgeschlagen");
        }
}

void MainWindow::on_pushAbbrechenAn_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
        ui->labelMax->show();
        ui->labelMin->show();
        ui->anmeldungUserName->setText("");
        ui->anmeldungPass->setText("");
        QMessageBox::information(this, Q_FUNC_INFO,"Ab Zeile " + QString::number(__LINE__));
}

//5)-------------Registrierung--------------------
void MainWindow::on_pushUserAnlegenReg_clicked()
{
    QString regUserName = ui->registrierungUsername->text();
    QString regUserPass = ui->registrierungPass->text();
    QString regUserPassWie = ui->registrierungPassWied->text();
    QString regUserEmail = ui->registrierungEmail->text();

    if(regUserPassWie == regUserPass){
        ui->labelRegPassWie->setText("Passwort Identisch");
        ui->labelRegBestetigung->setText("Registrierung Erfolgreich");
      QMessageBox::information(this, Q_FUNC_INFO,"Ab Zeile " + QString::number(__LINE__));
    }else{
        ui->labelRegPassWie->setText("Passwort Wiederholen");
    }
}

void MainWindow::on_pushAbbrechenReg_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
        ui->labelMax->show();
        ui->labelMin->show();
        ui->registrierungUsername->setText("");
        ui->registrierungPass->setText("");
        ui->registrierungPassWied->setText("");
        ui->registrierungEmail->setText("");
        QMessageBox::information(this, Q_FUNC_INFO,"Ab Zeile " + QString::number(__LINE__));
}

//6)----------------------Info----------------------------------------------
void MainWindow::on_actionVersion_triggered()
{
    QString filePath(QString(PROJECT_PATH));
    filePath += "Version.txt";
    if (QFileInfo::exists(filePath)) {
        QUrl helpUrl = QUrl::fromLocalFile(filePath);
        QDesktopServices::openUrl(helpUrl);
    } else {
        QMessageBox::warning(this, "Pfadname Fehler!", filePath + " wurde nicht gefunden.");
    }
}

//7)------------------------------Kontakt----------------------------------------
void MainWindow::on_actionAnsprechpartner_triggered()
{
    QMessageBox::information(this, "Ansprechpartner", "DetlefKremer \nTel. 02244/9185845 \nEmail. business@detlef-kremer.de");
}

//8)-------------Impressum--------------------
void MainWindow::on_actionHauptsitz_triggered()
{
    QMessageBox::information(this, "Hauptsitz", "dmnbc \nWeilerweg 6A \n53639 Königswinter \n\nTelefon: 02244/9185845 \n\nAnsprechpartner: Detlef Kremer");
}

//9)-------------Hilfe----------------------------------------------------------
void MainWindow::on_actionHandbuch_triggered()
{
    QString filePath(QString(PROJECT_PATH));
    filePath += "Tutorial.html";
    if (QFileInfo::exists(filePath)) {
        QUrl helpUrl = QUrl::fromLocalFile(filePath);
        QDesktopServices::openUrl(helpUrl);
    } else {
        QMessageBox::warning(this, "Pfadname Fehler!", filePath + " wurde nicht gefunden.");
    }
}

//10-------------Ansprechpartner--------------------
void MainWindow::on_pushAnsprechpartnerAn_clicked()
{
    QMessageBox::information(this, Q_FUNC_INFO,"Ab Zeile " + QString::number(__LINE__));
    ui->ansprechpartnerName->setText("");
    ui->ansprechpartnerVorname->setText("");
    ui->ansprechpartnerTelefon->setText("");
    ui->ansprechpartnerEmail->setText("");
    ui->ansprechpartnerFunktion->setText("");
}

void MainWindow::on_pushAnsprechpartnerZur_clicked()
{
    QMessageBox::information(this, Q_FUNC_INFO,"Ab Zeile " + QString::number(__LINE__));
    ui->ansprechpartnerName->setText("");
    ui->ansprechpartnerVorname->setText("");
    ui->ansprechpartnerTelefon->setText("");
    ui->ansprechpartnerEmail->setText("");
    ui->ansprechpartnerFunktion->setText("");
}


//11)-------------Ausbildung,-Praktika-und-Jobangebote--------------------
void MainWindow::on_angebotAnlegen_clicked()
{
    QMessageBox::information(this, Q_FUNC_INFO,"Ab Zeile " + QString::number(__LINE__));
}

void MainWindow::on_angebotReset_clicked()
{
    QMessageBox::information(this, Q_FUNC_INFO,"Ab Zeile " + QString::number(__LINE__));
}

void MainWindow::on_angebotBezeichnung_editingFinished()
{
    QMessageBox::information(this, Q_FUNC_INFO,"Ab Zeile " + QString::number(__LINE__));
}

void MainWindow::on_angebotWebsite_editingFinished()
{
    QMessageBox::information(this, Q_FUNC_INFO,"Ab Zeile " + QString::number(__LINE__));
}

void MainWindow::on_angebotForm_editingFinished()
{
    QMessageBox::information(this, Q_FUNC_INFO,"Ab Zeile " + QString::number(__LINE__));
}

void MainWindow::on_angebotEinsatzortAbw_editingFinished()
{
    QMessageBox::information(this, Q_FUNC_INFO,"Ab Zeile " + QString::number(__LINE__));
}

//12)-----------------------Firma-Standort--------------------------------
void MainWindow::on_firmaStandortAnlegen_clicked()
{
    //QMessageBox::information(this, Q_FUNC_INFO,"Ab Zeile " + QString::number(__LINE__));

    if (formular::formplz == 0 && formular::formstr ==0)
        qDebug()<< "Datensatz bereits vorhanden";
    else
        qDebug()<< "Auslesen und übergeben kann erfolgen";
    formular::formplz = 1;
    formular::formstr = 1;


    QMap<QString, QString> firmaMap;
    firmaMap.insert("firmaName", ui->firmaName->text());
    firmaMap.insert("firmaRechtsform", ui->firmaRechtsform->text());
    firmaMap.insert("firmaWebsite", ui->firmaWebsite->text());
    firmaMap.insert("firmaBranche", ui->firmaBranche->text());
    if (ui->firmaInhouse->isChecked())
        firmaMap.insert("firmaInhouse", "1");
    else
        firmaMap.insert("firmaInhouse", "0");
    if (ui->firmaPersonalvermitler->isChecked())
        firmaMap.insert("firmaPersonalvermitler", "1");
    else
        firmaMap.insert("firmaPersonalvermitler", "0");
    firmaMap.insert("standortPlz", ui->standortPlz->text());
    firmaMap.insert("standortOrt", ui->standortOrt->text());
    firmaMap.insert("standortStrasse", ui->standortStrasse->text());
    firmaMap.insert("standortTelefon", ui->standortTelefon->text());
    if (ui->standortZentraleCheckBox->isChecked())
        firmaMap.insert("standortZentraleCheckBox", "1");
    else
        firmaMap.insert("standortZentraleCheckBox", "0");
    firmaMap.insert("standortMitarbeiter", ui->standortMitarbeiter->currentText());

    qDebug()<< "firmaMap:";

        qDebug()<< firmaMap.values();


}

void MainWindow::on_firmaStandortReset_clicked()
{
    //QMessageBox::information(this, Q_FUNC_INFO,"Ab Zeile " + QString::number(__LINE__));

    ui->firmaName->setText("");
    ui->firmaRechtsform->setText("");
    ui->firmaBranche->setText("");
    ui->firmaWebsite->setText("");
    ui->firmaPersonalvermitler->setChecked(false);
    ui->firmaInhouse->setChecked(false);
    ui->standortOrt->setText("");
    ui->standortPlz->setText("");
    ui->standortStrasse->setText("");
    ui->standortTelefon->setText("");
    ui->standortZentraleCheckBox->setChecked(false);
    //ui->standortMitarbeiter->setText("");


}

void MainWindow::on_firmaName_editingFinished()
{
    //QMessageBox::information(this, Q_FUNC_INFO,"Ab Zeile " + QString::number(__LINE__));
    test.execQuery("SELECT Firma_id, name, rechtsform, website, branche, Personalvermittler, inhouse_IT FROM firma WHERE name = '"+ ui->firmaName->text()+"'");
    //qDebug()<< test.execQuery("SELECT name, rechtsform, website, branche, Personalvermittler, inhouse_IT FROM firma WHERE name = '"+ ui->firmaName->text()+"'");
    test.get_query().first();
    if (ui->firmaName->text() ==test.get_query().value(1).toString())
    {
        ui->firmaRechtsform->setText(test.get_query().value(2).toString());
        ui->firmaWebsite->setText(test.get_query().value(3).toString());
        ui->firmaBranche->setText(test.get_query().value(4).toString());
        ui->firmaPersonalvermitler->setChecked(test.get_query().value(5).toBool());
        ui->firmaInhouse->setChecked(test.get_query().value(6).toBool());
        showQry("SELECT * FROM standort WHERE Firma_ID = '"+ test.get_query().value(0).toString() +"'", test/*, {2,3,7,8, 9, 10, 11,12}*/);
        ui->firmaStandortAnlegen->setEnabled(formular::pflicht_gefuellt(true, "firma",1,1));
        ui->firmaStandortAnlegen->setEnabled(formular::pflicht_gefuellt(true, "recht",1,1));
    }

}

void MainWindow::on_firmaRechtsform_editingFinished()
{
    //QMessageBox::information(this, Q_FUNC_INFO,"Ab Zeile " + QString::number(__LINE__));
}

void MainWindow::on_firmaWebsite_editingFinished()
{
    //QMessageBox::information(this, Q_FUNC_INFO,"Ab Zeile " + QString::number(__LINE__));
    QRegExp regx("www.([-a-zA-Z0-9_&]{1,256}).([a-z]{2,4})$");

    formular::eingabe_Test(ui->firmaWebsite->text(), regx, "Website");

}

void MainWindow::on_firmaBranche_editingFinished()
{
    //QMessageBox::information(this, Q_FUNC_INFO,"Ab Zeile " + QString::number(__LINE__));
}

void MainWindow::on_firmaPersonalvermitler_toggled(bool checked)
{
    QMessageBox::information(this, Q_FUNC_INFO,"Ab Zeile " + QString::number(__LINE__));
}

void MainWindow::on_firmaInhouse_toggled(bool checked)
{
    //QMessageBox::information(this, Q_FUNC_INFO,"Ab Zeile " + QString::number(__LINE__));
}

void MainWindow::on_standortPlz_editingFinished()
{
    //QMessageBox::information(this, Q_FUNC_INFO,"Ab Zeile " + QString::number(__LINE__));
    //ui->standortOrt->setCompleter(formular::einfache_Liste(test, "Ort", "postleitzahlen WHERE PLZ = '"+ ui->standortPlz->text()+"'"));
    ui->standortOrt->setText(formular::einzelne_Daten(test, "Ort" , "postleitzahlen", "PLZ = '"+ ui->standortPlz->text()+"'"));

    int rc = ui->tableViewTrefferTabelleAnzeige->model()->rowCount();
    //qDebug()<< rc << "+" << ui->standortPlz->text();
    for (int i = 0; i<rc ;i++)
    {
    if (ui->standortPlz->text() == ui->tableViewTrefferTabelleAnzeige->model()->index(i,4).data().toString())
        ui->firmaStandortAnlegen->setEnabled(formular::pflicht_gefuellt(false, "stplz",0,1));
    else
        ui->firmaStandortAnlegen->setEnabled(formular::pflicht_gefuellt(true, "stplz",1,1));
        //qDebug()<< "formplz: " <<formular::formplz;
    }

}

void MainWindow::on_standortStrasse_editingFinished()
{
    //QMessageBox::information(this, Q_FUNC_INFO,"Ab Zeile " + QString::number(__LINE__));
    int rc = ui->tableViewTrefferTabelleAnzeige->model()->rowCount();
    //qDebug()<< rc << "+" << ui->standortStrasse->text();
    for (int i = 0; i<rc ;i++)
    {
    //qDebug ()<< ui->tableViewTrefferTabelleAnzeige->model()->index(i,5).data().toString();
    if (ui->standortStrasse->text() == ui->tableViewTrefferTabelleAnzeige->model()->index(i,5).data().toString())
        ui->firmaStandortAnlegen->setEnabled(formular::pflicht_gefuellt(false, "ststr",1,0));
    else
        ui->firmaStandortAnlegen->setEnabled(formular::pflicht_gefuellt(true, "ststr",1,0));

        //qDebug()<< "formstr: " <<formular::formstr;
    }

}

void MainWindow::on_standortOrt_editingFinished()
{
    //QMessageBox::information(this, Q_FUNC_INFO,"Ab Zeile " + QString::number(__LINE__));
    //ui->standortPlz->setFocus();
    //ui->standortPlz->setCompleter(formular::einfache_Liste(test, "PLZ", "postleitzahlen WHERE Ort = '"+ ui->standortOrt->text()+"'"));
    ui->standortPlz->setText(formular::einzelne_Daten(test, "PLZ" , "postleitzahlen", "Ort = '"+ ui->standortOrt->text()+"'"));

}

void MainWindow::on_standortTelefon_editingFinished()
{
    //QMessageBox::information(this, Q_FUNC_INFO,"Ab Zeile " + QString::number(__LINE__));
    QRegExp regx("([+](\\d{1,3})\\s?)?((\\\\(\\d{3,5}\\\\)|\\d{3,5})(\\s)?)\\d{3,8}$");
    formular::eingabe_Test(ui->standortTelefon->text(), regx, "Telefon");

}

void MainWindow::on_standortZentraleCheckBox_toggled(bool checked)
{
    QMessageBox::information(this, Q_FUNC_INFO,"Ab Zeile " + QString::number(__LINE__));
}

//13)-----------------Treffertabelleanzeige------------------------------------------------------------------
void MainWindow::on_tableViewTrefferTabelleAnzeige_clicked(const QModelIndex &index)
{
    QString spaltenname = ui->tableViewTrefferTabelleAnzeige->model()->headerData(index.column(),Qt::Orientation::Horizontal).toString(); //     ->horizontalHeader();
        ui->spaltenName->setText(spaltenname);
        ui->inhalt->setText(index.data().toString());

    foreach (int i, db_map[curtable]) {
            ui->tableViewTrefferTabelleAnzeige->setColumnHidden(i, false);
        }

        QString curqry = tablemap[curtable].value(index.column());
        qDebug() << curqry;
        if (curqry != "") {
            curqry +='"'+index.data().toString()+'"';
            showQry(curqry, test, db_map[curqry.split(" ")[3]]);

            qDebug()<<__FILE__<<" "<<__LINE__<<db_map[curqry.split(" ")[3]];

            curtable = curqry.split(" ")[3];
        } else {
            Helper::openMsgBox("Keine Abfrage vonhanden", "Zu diesem Feld gubt es keine weiteren Informationen.");
        }
    }

//14)----------quickwidget---action_tutorial---fehlerbehandlung---openbhelp------------------------------------------------
void MainWindow::on_quickWidget_sceneGraphError(const QQuickWindow::SceneGraphError &error, const QString &message)
{
    QMessageBox::information(this, Q_FUNC_INFO,"Ab Zeile " + QString::number(__LINE__));
}
void MainWindow::on_actionTutorial_triggered()
{
    QMessageBox::information(this, Q_FUNC_INFO,"Ab Zeile " + QString::number(__LINE__));
    openHelp("Tutorial");
}
void MainWindow::on_actionFehlerbehandlung_triggered()
{
    QMessageBox::information(this, Q_FUNC_INFO,"Ab Zeile " + QString::number(__LINE__));
}
void MainWindow::openHelp(QString err) {
        QString filePath(QString(PROJECT_PATH));
//14)-----If-Else-Tutorial------------------------------------------------------------
if (err == "Tutorial") {
            filePath += "Tutorial.html";
} else {
            filePath += "errorfiles/" + err + ".html";
        }
 if (QFileInfo::exists(filePath)) {
            QUrl helpUrl = QUrl::fromLocalFile(filePath);
            QDesktopServices::openUrl(helpUrl);
} else {
            QMessageBox::warning(this, "Pfadname Fehler!", filePath + " wurde nicht gefunden.");
}
}

void MainWindow::showQry(QString qry, DB database) {
    database.execQuery(qry);
    QSqlQueryModel *model = new QSqlQueryModel; // instanziert ein model für das MVC
    model->clear();

    if(database.get_lastQueryResultRows()!=0)   // hat Datensätze gefunden
    {
    model->setQuery(database.get_query());
    // Sortieren, sortingEnabled vom QTableView muss in der .ui angekreuzt werden
    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel; // (model)
    proxyModel->setSourceModel(model);
    // Use the setModel() method to bind the data model to QTableView
    ui->tableViewTrefferTabelleAnzeige->setModel(proxyModel);
    }
    else // keine Datensätze vorhanden
    {
        showQry("SELECT 'keine weitere Informationen' AS 'Ergebnis der Datenabfrage' ",test);
    }

}

void MainWindow::showQry(QString qry, DB database,QList<int> aus)
{
    showQry(qry,database);
    for(auto col : aus)
   { ui->tableViewTrefferTabelleAnzeige->setColumnHidden(col, true);}
}

//16)-----------Web-Import------------------------------------------------------
void MainWindow::on_pushButtonWebOpen_clicked()
{
    QString lineWeb = ui->lineEditWeb->text();
    QDesktopServices::openUrl(QUrl(lineWeb));
}

void MainWindow::on_pushButtonWebAbbrechen_clicked()
{
    ui->stackedWidget_2->hide();
}

//17)-----------CSV-Import------------------------------------------------------
void MainWindow::on_pushImportCSV_clicked()
{
    ui->stackedWidget_2->show();
    ui->page2CSVimport->show();
    ui->pageWebImport->hide();
}

void MainWindow::on_pushButtonCSVimport_clicked()
{
    QMessageBox::information(this, Q_FUNC_INFO,"Ab Zeile " + QString::number(__LINE__));
}

void MainWindow::on_pushButtonCSVabbrechen_clicked()
{
    ui->page2CSVimport->hide();
}

void MainWindow::on_pushButtonCSVdateiAuswahl_clicked()
{
    QString file_name = QFileDialog::getOpenFileName(this, "open a file", "C://");
    QMessageBox::information(this, "..", file_name);
    ui->lineEditCSVimport->setText(file_name);
}

void MainWindow::on_tableViewTrefferTabelleAnzeige_activated(const QModelIndex &index)
{
    QString locationSQL =
            "SELECT sLat, sLon FROM standort WHERE Firma_ID = "+index.data().toString();
    test.execQuery(locationSQL);
    test.get_query().first();
    QString lon  = test.get_query().value(0).toString();
    QString lat  = test.get_query().value(1).toString();
    QMessageBox::information(this, "in Karte zeigen ",lon + " "+lat);
}

void MainWindow::Standorte_aus_Tabelle_anzeigen()
{
    QList<double> latList;
    QList<double> lngList;
    QList<QString> firmList;
    int y = ui->tableViewTrefferTabelleAnzeige->model()->rowCount();
    int i = ui->tableViewTrefferTabelleAnzeige->rowAt(0);
    int x = i+15;
    qDebug()<<"y "<<y;
    for (i; i<(y<x?y:x);i++){
        //Methode db 2 double
        int id = ui->tableViewTrefferTabelleAnzeige->model()->index(i,0).data().toInt();
        QString plz = ui->tableViewTrefferTabelleAnzeige->model()->index(i,3).data().toString();
        std::array<double,2> coordinates;
        coordinates= test.get_coordinate(id, plz);

        latList.append(coordinates.at(0));  // sLat
        lngList.append(coordinates.at(1));  // sLon
        firmList.append(ui->tableViewTrefferTabelleAnzeige->model()->index(i,1).data().toString()+" ("+QString::number(id)+")");
    }
    qDebug()<<"Übergabe Daten "<<__FILE__<<__LINE__;
    qDebug()<<latList;
    qDebug()<<lngList;
    qDebug()<<firmList;
    GenMap::Punkte_setzen(genMapObj, latList, lngList, firmList);

}



void MainWindow::on_firmaName_textEdited(const QString &arg1)
{
    if (ui->firmaName->text().length()==1)
    {
        ui->firmaName->setCompleter(formular::einfache_Liste(test, "name", "firma WHERE name LIKE '%"+ ui->firmaName->text()+"%'"));
        ui->firmaStandortAnlegen->setEnabled(formular::pflicht_gefuellt(true, "firma",1,1));
    }
    if (ui->firmaName->text().length()==0)
        ui->firmaStandortAnlegen->setEnabled(formular::pflicht_gefuellt(false, "firma",1,1));
}


void MainWindow::on_firmaRechtsform_textEdited(const QString &arg1)
{
    if (ui->firmaRechtsform->text().length()==1)
    {
        ui->firmaRechtsform->setCompleter(formular::einfache_Liste(test, "DISTINCT rechtsform", "firma WHERE rechtsform LIKE '%"+ ui->firmaRechtsform->text()+"%' ORDER BY rechtsform"));
        ui->firmaStandortAnlegen->setEnabled(formular::pflicht_gefuellt(true, "recht",1,1));
    }
    if (ui->firmaRechtsform->text().length()==0)
        ui->firmaStandortAnlegen->setEnabled(formular::pflicht_gefuellt(false, "recht",1,1));
}


void MainWindow::on_firmaBranche_textEdited(const QString &arg1)
{
    if (ui->firmaBranche->text().length()==1)
        ui->firmaBranche->setCompleter(formular::einfache_Liste(test, "name", "branchen WHERE name LIKE '%"+ ui->firmaBranche->text()+"%'"));

}





void MainWindow::on_firmaWebsite_textEdited(const QString &arg1)
{

}


void MainWindow::on_standortPlz_textEdited(const QString &arg1)
{
    if (ui->standortPlz->text().length()==1)
    {
        ui->standortPlz->setCompleter(formular::einfache_Liste(test, "plz", "postleitzahlen WHERE plz LIKE '"+ ui->standortPlz->text()+"%'", Qt::MatchStartsWith));
        ui->firmaStandortAnlegen->setEnabled(formular::pflicht_gefuellt(true, "stplz",1,1));
    }
    if (ui->standortPlz->text().length()==0)
        ui->firmaStandortAnlegen->setEnabled(formular::pflicht_gefuellt(false, "stplz",1,1));
}


void MainWindow::on_standortOrt_textEdited(const QString &arg1)
{
    if (ui->standortOrt->text().length()==1)
    {
        ui->standortOrt->setCompleter(formular::einfache_Liste(test, "DISTINCT ort", "postleitzahlen WHERE ort LIKE '"+ ui->standortOrt->text()+"%' ORDER BY ort", Qt::MatchStartsWith));
        ui->firmaStandortAnlegen->setEnabled(formular::pflicht_gefuellt(true, "stort",1,1));
    }
    if (ui->standortOrt->text().length()==0)
        ui->firmaStandortAnlegen->setEnabled(formular::pflicht_gefuellt(false, "stort",1,1));
}


void MainWindow::on_standortTelefon_textEdited(const QString &arg1)
{

}
