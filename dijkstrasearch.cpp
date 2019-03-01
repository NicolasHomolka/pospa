/*
authors: Homolka, Prinz
desc: Airline Pathfinding Example
class: 5BHIF
 */

#include "dijkstrasearch.h"
#include <iostream>
#include <limits.h>
#include <functional>

using namespace std;

//select * from route where airport1=(select id from airport where name like '%Rostock%' limit 1);

void DijkstraSearch::InitData()
{
    for (Airport *a : this->dbService->GetAirportData())
    {

        AirportNode *node = new AirportNode(a, INT_MAX, nullptr);
        if (a == start)
        {
            node->SetDistance(0);
            startNode = node;
        }
        else if (a == dest)
        {
            destNode = node;
        }
        this->airportNodes.push_back(node);
    }
}

DijkstraSearch::DijkstraSearch(Airport *start, Airport *dest, DatabaseService *dbService)
    : start(start), dest(dest), dbService(dbService)
{
}

QList<QList<QPair<Airport *, Airline *>>> DijkstraSearch::Search()
{
    InitData();
    AirportNode *current{this->startNode};
    QList<QPair<AirportNode *, QPair<int, Airline *>>> tmp{};
    tmp.push_back(QPair<AirportNode *, QPair<int, Airline *>>(current, QPair<int, Airline *>(0, nullptr)));

    while (current != this->destNode)
    {
        current->SetVisited(true);
        for (QPair<AirportNode *, QPair<int, Airline *>> pair : tmp)
        {
            if (pair.first == current)
            {
                tmp.removeOne(pair);
            }
        }
        QList<QPair<Airport *, Airline *>> routes = this->dbService->GetRouteInformationWithId(current->GetCurrent()->GetId());
        for (QPair<Airport *, Airline *> pair : routes)
        {
            //Get AirportNode to Airport
            AirportNode *airportNode = nullptr;
            for (AirportNode *node : this->airportNodes)
            {
                if (node->GetCurrent()->GetId() == pair.first->GetId())
                {
                    airportNode = node;
                    //cout << airportNode->GetCurrent()->GetName().toUtf8().constData() << "-" << airportNode << endl;
                    break;
                }
            }

            if (!airportNode->IsVisited())
            {
                //Add to Work List
                tmp.push_back(QPair<AirportNode *, QPair<int, Airline *>>(airportNode, QPair<int, Airline *>(current->GetDistance() + 1, pair.second)));
                //Route{current->GetDistance() + 1, current, pair.second};
                airportNode->GetPreviouses()->push_back(QPair<AirportNode *, QPair<int, Airline *>>(current, QPair<int, Airline *>(current->GetDistance() + 1, pair.second)));
                //cout << airportNode->GetCurrent()->GetName().toUtf8().constData() << "-" << airportNode->GetPreviouses()->count() << endl;
                //Check Distance
                if (airportNode->GetDistance() > current->GetDistance() + 1)
                {
                    airportNode->SetDistance(current->GetDistance() + 1);
                    airportNode->SetPrevious(current);
                    airportNode->SetAirline(pair.second);
                }
            }
        }
        //Get Minimum of tmp => new current
        int min{INT_MAX};
        for (QPair<AirportNode *, QPair<int, Airline *>> pair : tmp)
        {
            if (pair.first->GetDistance() < min)
            {
                min = pair.first->GetDistance();
                if (current == this->destNode)
                {
                    break;
                }
                current = pair.first;
            }
        }
    }

    QList<QList<QPair<Airport *, Airline *>>> routes;
    for (QPair<AirportNode *, QPair<int, Airline *>> node : tmp)
    {
        if (node.first->GetCurrent()->GetId() == this->destNode->GetCurrent()->GetId() && current->GetDistance() == node.second.first)
        {
            AirportNode *tmpNode = node.first;
            QList<QPair<Airport *, Airline *>> route{};
            while (tmpNode != this->startNode)
            {
                route.push_back(QPair<Airport *, Airline *>(tmpNode->GetCurrent(), tmpNode->GetAirline()));
                cout << tmpNode->GetCurrent()->GetName().replace(" ", "").toUtf8().constData() << "(" << tmpNode->GetDistance() << ")"
                     << "<-" << flush;
                tmpNode = tmpNode->GetPrevious();
            }
            cout << tmpNode->GetCurrent()->GetName().replace(" ", "").toUtf8().constData() << "(" << tmpNode->GetDistance() << ")" << endl;
            route.push_back(QPair<Airport *, Airline *>(tmpNode->GetCurrent(), node.second.second));
            routes.push_back(route);
            cout << node.first->GetCurrent()->GetName().toUtf8().constData() << ": " << node.second.second->GetName().toUtf8().constData() << endl;
        }
    }

    return routes;
}
