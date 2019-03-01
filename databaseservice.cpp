/*
authors: Homolka, Prinz
desc: Airline Pathfinding Example
class: 5BHIF
 */

#include "databaseservice.h"

#include <QSqlQuery>
#include <QVariant>
#include <iostream>
#include <QList>
#include <airline.h>
#include <QMap>

Airport *DatabaseService::GetAirportById(int id)
{
    for (Airport *a : this->airports)
    {
        if (a->GetId() == id)
        {
            return a;
        }
    }
    return nullptr;
}

Airline *DatabaseService::GetAirlineById(int id)
{
    for (Airline *a : this->airlines)
    {
        if (a->GetId() == id)
        {
            return a;
        }
    }
    return nullptr;
}

DatabaseService::DatabaseService()
{
}

bool DatabaseService::CreateConnection()
{
    this->db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("AirlineRoutes.db");
    return db.open();
}

QList<Airline *> DatabaseService::GetAirlineData()
{
    if (this->airlines.count() <= 0)
    {
        QSqlQuery query("select * from Airline order by name");
        query.exec();
        while (query.next())
        {
            int id = query.value(0).toInt();
            QString name = query.value(1).toString();
            int alliance_id = query.value(2).toInt();
            airlines.push_back(new Airline{name, id, alliance_id});
        }
    }

    return airlines;
}

QList<Airport *> DatabaseService::GetAirportData()
{
    std::cout << "Test" << std::endl;
    if (this->airports.count() <= 0)
    {
        QSqlQuery query("select * from Airport");
        query.exec();
        while (query.next())
        {
            int id = query.value(0).toInt();
            float latitude = query.value(1).toFloat();
            float longitude = query.value(2).toFloat();
            QString name = query.value(3).toString();
            QString idata = query.value(4).toString();
            airports.push_back(new Airport{id, latitude, longitude, name, idata});
        }
    }
    return airports;
}

QList<QPair<Airport *, Airline *>> DatabaseService::GetRouteInformationWithId(int id)
{
    QList<QPair<Airport *, Airline *>> pairs;
    QSqlQuery query("select distinct airline, airport2 from Route where airport1=" + QString::number(id));
    query.exec();
    while (query.next())
    {
        int airlineId = query.value(0).toInt();
        int airport2Id = query.value(1).toInt();
        pairs.push_back(QPair<Airport *, Airline *>(GetAirportById(airport2Id), GetAirlineById(airlineId)));
    }

    return pairs;
}
