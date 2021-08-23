#ifndef GEOINFO_H
#define GEOINFO_H

#include <QtNetwork>
#include <QMessageBox>

class GeoInfo : public QObject
{
    Q_OBJECT

public:
    GeoInfo();
    void request();
    QString getIP();
    QString getPlz();
    QString getOrt();
    QJsonObject getResponse();
    QMap<QString, double> getCoords();
    bool isSslSupported() { return supportsSsl; };
    void sslError();

private:
    QJsonObject ipapi_json;
    QNetworkAccessManager *manager;
    bool supportsSsl;

private slots:
    void replyFinished(QNetworkReply *reply);
    void getRequest(QString str);
    void connector();
};

#endif // GEOINFO_H
