/*
authors: Homolka, Prinz
desc: Airline Pathfinding Example
class: 5BHIF
 */


#include "airportnode.h"

AirportNode::AirportNode(Airport *current, int distance, AirportNode *previous)
: current(current), distance(distance), previous(previous) {
    this->previouses = new QList<QPair<AirportNode*, QPair<int, Airline*>>>();
}

void AirportNode::SetDistance(int value) {
    this->distance = value;
}

AirportNode *AirportNode::GetPrevious() {
    return this->previous;
}

Airport *AirportNode::GetCurrent() {
    return this->current;
}

int AirportNode::GetDistance() {
    return this->distance;
}

bool AirportNode::IsVisited() {
    return this->visited;
}

Airline *AirportNode::GetAirline() {
    return this->airline;
}

void AirportNode::SetVisited(bool visited) {
    this->visited = visited;
}

void AirportNode::SetPrevious(AirportNode *node) {
    this->previous = node;
}

void AirportNode::SetAirline(Airline *airline) {
    this->airline = airline;
}

void AirportNode::SetPreviouses(QList<QPair<AirportNode*, QPair<int, Airline*>>>* value) {
    this->previouses = value;
}

QList<QPair<AirportNode*, QPair<int, Airline*>>>*AirportNode::GetPreviouses() {
    return this->previouses;
}
