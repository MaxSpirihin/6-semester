#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtSql>
#include <QList>

#ifndef DATABASE_H
#define DATABASE_H

class DataBase
{
public:
    DataBase();
    QString GetCompanyInfo(int Id);
    void Search(QString str,QList<int> *ids, QList<QString> *names);
private:
    bool QueryToList(QSqlQuery *query, QList<int> *ids, QList<QString> *names);

};

#endif // DATABASE_H
