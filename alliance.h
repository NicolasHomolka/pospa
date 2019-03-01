/*
authors: Homolka, Prinz
desc: Airline Pathfinding Example
class: 5BHIF
 */

#ifndef ALLIANCE_H
#define ALLIANCE_H

#include <QString>

class Alliance
{
  private:
    int id;
    QString name;

  public:
    Alliance();
    QString GetName();
    int GetId();
};

#endif // ALLIANCE_H
