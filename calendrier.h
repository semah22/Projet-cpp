#ifndef CALENDRIER_H
#define CALENDRIER_H
#include <QDate>
#include <QMainWindow>
#include <QMainWindow>
#include <QApplication>
#include <QMessageBox>
#include <QFileDialog>
#include <QtPrintSupport/QPrinter>
#include <QTextDocument>
#include <QtDebug>
#include <QMessageBox>
#include <QTableView>
#include <QAbstractItemView>
#include <QIntValidator>
#include <QVector>
#include <qjsondocument.h>
#include <QSortFilterProxyModel>

#include <QFile>
#include <QInputDialog>
#include <QJsonArray>
#include <QJsonObject>
#include <QLineEdit>
#include <QMainWindow>
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QNetworkCookie>
#include <QNetworkCookieJar>
#include <QNetworkReply>
#include <QNetworkSession>
QT_BEGIN_NAMESPACE

//! [0]


#include <QMainWindow>



QT_BEGIN_NAMESPACE
class QTextBrowser;
QT_END_NAMESPACE

class Calendrier : public QMainWindow
{
    Q_OBJECT

public:
     Calendrier();

public slots:
    void setFontSize(int size);
    void setMonth(int month);
    void setYear(QDate date);

private:
    void insertCalendar();

    int fontSize;
    QDate selectedDate;
    QTextBrowser *editor;


QNetworkAccessManager *manager;

    QByteArray token = "";
    QByteArray user = "";
    QByteArray name = "";

    QJsonObject json;
    QJsonArray selected_day_json;
    QString select_date;

    QByteArray post(QString url, QByteArray data, const char *type);
    QByteArray get(QString url);
    QJsonObject format(QByteArray data);
    void updatetoken(QNetworkReply *reply);
};


#endif // CALENDRIER_H
