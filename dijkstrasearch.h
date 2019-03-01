/*
authors: Homolka, Prinz
desc: Airline Pathfinding Example
class: 5BHIF
 */

#ifndef DIJKSTRASEARCH_H
#define DIJKSTRASEARCH_H

#include <QList>
#include <airport.h>
#include <airline.h>
#include <airportnode.h>
#include <databaseservice.h>

class DijkstraSearch {
private:
    QList<AirportNode*> airportNodes;
    Airport* start;
    Airport* dest;
    AirportNode* startNode;
    AirportNode* destNode;
    DatabaseService* dbService;
    void InitData();
public:
    DijkstraSearch(Airport* start, Airport* dest, DatabaseService* dbService);
    QList<QList<QPair<Airport*, Airline*>>> Search();
};

#endif // DIJKSTRASEARCH_H
