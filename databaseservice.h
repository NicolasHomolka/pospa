/*
authors: Homolka, Prinz
desc: Airline Pathfinding Example
class: 5BHIF
 */

#ifndef DATABASESERVICE_H
#define DATABASESERVICE_H

#include <QStringList>
#include <QSqlDatabase>
#include <QList>
#include <airline.h>
#include <airport.h>

class DatabaseService {
private:
    QSqlDatabase db;
    QList<Airline*> airlines;
    QList<Airport*> airports;
    Airport *GetAirportById(int id);
    Airline *GetAirlineById(int id);
public:
    DatabaseService();
    bool CreateConnection();
    QList<Airline*> GetAirlineData();
    QList<Airport*> GetAirportData();
    QList<QPair<Airport*, Airline*>> GetRouteInformationWithId(int id);
};

#endif // DATABASESERVICE_H
