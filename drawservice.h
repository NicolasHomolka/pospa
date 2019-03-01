/*
authors: Homolka, Prinz
desc: Airline Pathfinding Example
class: 5BHIF
 */

#ifndef DRAWSERVICE_H
#define DRAWSERVICE_H

#include <QLabel>
#include <QPixmap>
#include <QPainter>
#include <QPen>
#include <airport.h>
#include <QList>
#include <QPair>
#include <airline.h>

class DrawService
{
  private:
    QLabel *label;
    QPixmap *pixmap;
    QPainter *painter;
    QPen pen;
    int unit_width;
    int unit_heigth;
    QPoint middle;
    void Init();

  public:
    DrawService(QLabel *label);
    void DrawRoute(float latitude1, float longitude1, float latitude2, float longitude2, QString name1, QString name2);
    void DrawRoute(QList<QList<QPair<Airport *, Airline *>>> airports);
    void ClearRoutes();
};

#endif // DRAWSERVICE_H
