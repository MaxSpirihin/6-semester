#include "database.h"
#include <QRegExp>

DataBase::DataBase()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("DRIVER={SQL Server};Server=.;Database=Companies;Trusted_Connection=yes;");
    db.open();
}

QString DataBase::GetCompanyInfo(int Id)
{
    QSqlQuery query;
    query.exec(QString("SELECT ShortName,Name,LawAddress,Email,Site,Phone,INN,KPP,OGRN,ActivityKind,Extra ") +
                       QString("FROM Companies WHERE Id=%1").arg(Id));
    query.next();

    QString result;
    result += query.value(0).toString() + "\n\n\n";
    result += QString::fromUtf8("Полное наименование: %1 \n").arg(query.value(1).toString());
    result += QString::fromUtf8("Юр. адрес: %1 \n").arg(query.value(2).toString());
    result += QString::fromUtf8("Email: %1 \n").arg(query.value(3).toString());
    result += QString::fromUtf8("Сайт: %1 \n").arg(query.value(4).toString());
    result += QString::fromUtf8("Телефон: %1 \n").arg(query.value(5).toString());
    result += QString::fromUtf8("ИНН: %1 \n").arg(query.value(6).toString());
    result += QString::fromUtf8("КПП: %1 \n").arg(query.value(7).toString());
    result += QString::fromUtf8("ОГРН: %1 \n").arg(query.value(8).toString());
    result += QString::fromUtf8("Тип деятельности: %1 \n\n").arg(query.value(9).toString());

    if (query.value(10).toString().indexOf(QString::fromUtf8("правляющая")) !=-1)
        result += QString::fromUtf8("%1 \n").arg(query.value(10).toString());

    //ищем сотрудников
    query.exec(QString("SELECT Name,Position FROM People WHERE CompanyId=%1").arg(Id));

    int num = 1;
    while (query.next()) {

        if (num == 1)
            result += QString::fromUtf8("\nСотрудники:\n");

        result += QString::fromUtf8("%1)%2 (%3)\n").arg(
                    QString::number(num),query.value(0).toString(),query.value(1).toString());
        num++;
       }

    return result;
}


void DataBase::Search(QString str, QList<int> *ids, QList<QString> *names)
{
    ids->clear();
    names->clear();

    QSqlQuery query;
    str = str.trimmed();

    //проверка, что поиск по ИНН
    if (QRegExp("[0-9]{10}").exactMatch(str))
    {
        query.exec(QString("SELECT Id,ShortName FROM Companies WHERE INN LIKE '%%%1%%'").arg(str.trimmed()));
    }
    //поиск по ОГРН
    else if (QRegExp("[0-9]{13}").exactMatch(str))
    {
        query.exec(QString("SELECT Id,ShortName FROM Companies WHERE OGRN LIKE '%%%1%%'").arg(str.trimmed()));
    }
    //поиск по КПП
    else if (QRegExp("[0-9]{9}").exactMatch(str))
    {
        query.exec(QString("SELECT Id,ShortName FROM Companies WHERE KPP LIKE '%%%1%%'").arg(str.trimmed()));
    }
    else //поиск по имени адресу
        query.exec(QString("SELECT Id,ShortName FROM Companies WHERE Name LIKE '%%[ \"]%1%%' OR LawAddress LIKE '%%[ \"]%1%%' OR Extra LIKE '%%[ \"]%1%%'").arg(str.trimmed()));

    QueryToList(&query,ids,names);
    {
        //поиск людей
        query.clear();
        query.exec(QString("SELECT DISTINCT Companies.Id,Companies.ShortName FROM Companies,People WHERE People.Name LIKE '%% %1%%' AND People.CompanyId=Companies.Id").arg(str.trimmed()));
        QueryToList(&query,ids,names);
    }
}

bool DataBase::QueryToList(QSqlQuery *query, QList<int> *ids, QList<QString> *names)
{
    bool found = false;
    while (query->next()) {
        ids->append(query->value(0).toInt());
        QString name = query->value(1).toString();
        name = name.length() > 25 ? name.mid(0,25)+"..." : name;
        names->append(name);
        found = true;
    }
    return found;
}
