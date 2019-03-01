/*
authors: Homolka, Prinz
desc: Airline Pathfinding Example
class: 5BHIF
 */

#ifndef AIRPORTNODE_H
#define AIRPORTNODE_H

#include <airport.h>
#include <airline.h>
#include <QPair>
#include <QList>

class AirportNode {
private:
    Airport* current;
    int distance;
    AirportNode* previous;
    bool visited;
    Airline* airline;
    QList<QPair<AirportNode*, QPair<int, Airline*>>>* previouses;
public:
    AirportNode(Airport* current, int distance, AirportNode* previous);
    void SetDistance(int value);
    AirportNode* GetPrevious();
    Airport* GetCurrent();
    int GetDistance();
    bool IsVisited();
    Airline* GetAirline();
    void SetVisited(bool visited);
    void SetPrevious(AirportNode* node);
    void SetAirline(Airline* airline);
    void SetPreviouses(QList<QPair<AirportNode*, QPair<int, Airline*>>>* value);
    QList<QPair<AirportNode*, QPair<int, Airline*>>>* GetPreviouses();
};

#endif // AIRPORTNODE_H
