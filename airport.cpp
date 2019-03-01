/*
authors: Homolka, Prinz
desc: Airline Pathfinding Example
class: 5BHIF
 */



#include "airport.h"

Airport::Airport() {

}

Airport::Airport(int id, float latitude, float longitude, QString name, QString idata)
: id(id), latitude(latitude), longitude(longitude), name(name), idata(idata) {

}

QString Airport::GetName() {
    return this->name;
}

int Airport::GetId() {
    return this->id;
}

float Airport::GetLatitude() {
    return this->latitude;
}

float Airport::GetLongitude() {
    return this->longitude;
}

QString Airport::GetIData() {
    return this->idata;
}
