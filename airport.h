/*
authors: Homolka, Prinz
desc: Airline Pathfinding Example
class: 5BHIF
 */


#ifndef AIRPORT_H
#define AIRPORT_H
#include <QString>

class Airport {
private:
    int id;
    float latitude;
    float longitude;
    QString name;
    QString idata;
public:
    Airport();
    Airport(int id, float latitude, float longitude, QString name, QString idata);
    QString GetName();
    int GetId();
    float GetLatitude();
    float GetLongitude();
    QString GetIData();
};

#endif // AIRPORT_H
