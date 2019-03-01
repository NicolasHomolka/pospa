/*
authors: Homolka, Prinz
desc: Airline Pathfinding Example
class: 5BHIF
 */

#ifndef AIRLINE_H
#define AIRLINE_H
#include <QString>
#include "alliance.h"

class Airline
{
private:
  QString name;
  int id;
  int alliance_id;

public:
  Airline();
  Airline(QString name, int id, int alliance_id);
  QString GetName();
  int GetId();
  int GetAllianceId();
};

#endif // AIRLINE_H
