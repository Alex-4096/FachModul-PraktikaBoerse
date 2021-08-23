#include "geo.h"
/*
 * TLS Libs:
 * https://github.com/thecodemonkey86/qt_mysql_driver
 *
 * Nach instanziierung mit der request() Methode den request nach den
 * nötigen Daten (Lat/Lon, Stadt, etc.) starten und fertigstellen.
 * Daraufhin mit getIP/Ort/Plz/Coords die Daten abholen.
 *
 * getCoords() ist ein Container und beinhaltet Lat. und Lon.
 *
 * Bsp:
 * GeoInfo geo;
 * geo.request();
 * geo.getCoords()["latitude"];
 *
 * für einen beliebigen key  geo.getResponse()["key"];
 */

//1)-----SSL-im-server-Verfügbar?--------------------------------------------------------------------
//SSL = (Secure Sockets Layer,Verschlüsselungsprotokoll, sichere Datenübertragung)
GeoInfo::GeoInfo() {

    supportsSsl = QSslSocket::supportsSsl(); // true/false
    // qDebug() << supportsSsl;
    // qDebug() << QSslSocket::sslLibraryBuildVersionString();
}

void GeoInfo::replyFinished(QNetworkReply *reply) {
    QJsonObject jsonObject = QJsonDocument::fromJson(reply->readAll()).object();
    // Ganzes JSON in qDebug:
    // qDebug() << "replyFinished:" << jsonObject;
    this->ipapi_json = jsonObject;
}

void GeoInfo::getRequest(QString str) {
    // qDebug() << "getRequest:" << str;
    QUrl url(str);
    QNetworkRequest request(url);
    request.setRawHeader("User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:90.0) Gecko/20100101 Firefox/90.0");
    manager->get(request);
    connector();
}

void GeoInfo::request() {
    // Stellt Verbindung nur her, falls TLS auf dem System funktioniert.
    if (supportsSsl) {
        manager = new QNetworkAccessManager(this);
        getRequest("https://ipapi.co/json");
    } else {
        sslError();
    }
}

void GeoInfo::connector() {
    QEventLoop loop;
    // connect(manager, &QNetworkAccessManager::finished, this, &GeoInfo::replyFinished);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*))); // asynchronous
    connect(manager, SIGNAL(finished(QNetworkReply*)), &loop, SLOT(quit())); // quit loop
    loop.exec();
    // erst hier hat this->ipapi_json einen Wert
}
//2)-------GET----IP--PLZ--ORT----------------------------------------------------------------
QString GeoInfo::getIP() {
    return this->ipapi_json["ip"].toString();
}
QString GeoInfo::getPlz() {
    return this->ipapi_json["postal"].toString();
}
QString GeoInfo::getOrt() {
    return this->ipapi_json["city"].toString();
}
QJsonObject GeoInfo::getResponse() {
    return this->ipapi_json;
    /*
     * Keys:
     * ip, version, city, region, region_code, country, country_name, country_code,
     * country_code_iso3, country_capital, country_tld, continent_code, in_eu, postal,
     * latitude, longitude, timezone, utc_offset, country_calling_code, currency,
     * currency_name, languages, country_area, country_population, asn, org
     */
}
//3)------------LATI-LONG-Abfrage----------------------------------------------------------
QMap<QString, double> GeoInfo::getCoords() {
    QMap<QString, double> coords;
    coords["latitude"] = this->ipapi_json["latitude"].toDouble();
    coords["longitude"] = this->ipapi_json["longitude"].toDouble();
    // qDebug() << coords;
    return coords;
}
//4)---------Fehlermeldung-DLL-Datei-Fehlt-------------------------------------------------------
void GeoInfo::sslError() {
    QString sslVer = QSslSocket::sslLibraryBuildVersionString();
    // Critical error
    QMessageBox msgBox;
       msgBox.setTextFormat(Qt::RichText); // Erlaubt HTML
       msgBox.setIcon(QMessageBox::Critical); // Critical error
       msgBox.setWindowTitle("SSL Fehler!");
       msgBox.setText(sslVer +" für "+QT_VERSION_STR+ " wurde nicht gefunden.<br>"
       "<a href='https://github.com/thecodemonkey86/qt_mysql_driver/releases'>Zum Download</a>"
       "<br><br>"
       "Die Dateien libcrypto-1_1 und libssl-1_1 in das Programmverzeichnis kopieren.");
       msgBox.exec();
}
