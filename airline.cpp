/*
authors: Homolka, Prinz
desc: Airline Pathfinding Example
class: 5BHIF
 */


#include "airline.h"

Airline::Airline() {

}

Airline::Airline(QString name, int id, int alliance)
: name(name), id(id), alliance_id(alliance) {

}

QString Airline::GetName() {
    return this->name;
}

int Airline::GetId() {
    return this->id;
}

int Airline::GetAllianceId() {
    return this->alliance_id;
}
