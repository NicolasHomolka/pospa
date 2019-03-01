/*
authors: Homolka, Prinz
desc: Airline Pathfinding Example
class: 5BHIF
 */


#include "drawservice.h"
#include <QString>
#include <iostream>

using namespace std;

void DrawService::Init() {
    this->pixmap = new QPixmap(":/images/Earthmap.jpg");
    this->painter = new QPainter(this->pixmap);

    this->pen.setColor(Qt::red);
    this->pen.setWidth(2);

    this->unit_width = this->pixmap->width() / 360;
    this->unit_heigth = this->pixmap->height() / 180;

    this->middle.setX(180 * this->unit_width);
    this->middle.setY(90 * this->unit_heigth);

    cout << "x: " << this->middle.x() << ", y: " << this->middle.y() << endl;
    cout << "unit width: " << this->unit_width << ", unit_heigth: " << this->unit_heigth << endl;

    this->label->setPixmap(*this->pixmap);
}

DrawService::DrawService(QLabel* label)
: label(label) {
    Init();
}

void DrawService::DrawRoute(float latitude1, float longitude1, float latitude2, float longitude2, QString name1, QString name2) {
    this->painter->setPen(this->pen);
    this->pen.setColor(Qt::red);
    cout << "Test" << endl;
    //longitude: z.B.: 16.5697 = width
    //latitude: z.B.: 48.1103 = heigth
    cout << this->middle.x() + longitude1 * this->unit_width << endl;
    cout << this->middle.y() - latitude1 * this->unit_heigth << endl;
    cout << this->middle.x() + longitude2 * this->unit_width << endl;
    cout << this->middle.y() - latitude2 * this->unit_heigth << endl;
    this->painter->drawLine(this->middle.x() + longitude1 * this->unit_width, this->middle.y() - latitude1 * this->unit_heigth,
            this->middle.x() + longitude2 * this->unit_width, this->middle.y() - latitude2 * this->unit_heigth);

    QPixmap pixmap2(":/images/baseline.svg");
    this->painter->drawPixmap(this->middle.x() + longitude1 * this->unit_width - pixmap2.width() / 2, this->middle.y() - latitude1 * this->unit_heigth - pixmap2.height() + 5, 20, 20, pixmap2);
    this->painter->drawPixmap(this->middle.x() + longitude2 * this->unit_width - pixmap2.width() / 2, this->middle.y() - latitude2 * this->unit_heigth - pixmap2.height() + 5, 20, 20, pixmap2);

    this->pen.setColor(Qt::red);
    this->painter->drawText(this->middle.x() + longitude1 * this->unit_width - pixmap2.width() / 2, this->middle.y() - latitude1 * this->unit_heigth - pixmap2.height() + 5, name1);
    this->painter->drawText(this->middle.x() + longitude2 * this->unit_width - pixmap2.width() / 2, this->middle.y() - latitude2 * this->unit_heigth - pixmap2.height() + 5, name2);


    this->label->setPixmap(*this->pixmap);
}

void DrawService::DrawRoute(QList<QList<QPair<Airport*, Airline*>>> airports) {
    for (int i = 0; i < airports.count(); i++) {
        cout << &airports[i] << endl;
        for (int j = 1; j < airports[i].count(); j++) {
            //cout << before.second << "." << endl;
            //cout << before.first->GetLatitude() << " " << before.first->GetLongitude() << " mit " << before.second->GetName().toUtf8().constData() << endl;
            DrawRoute(airports[i][j - 1].first->GetLatitude(), airports[i][j - 1].first->GetLongitude(), airports[i][j].first->GetLatitude(), airports[i][j].first->GetLongitude(), airports[i][j - 1].first->GetIData(), airports[i][j].first->GetIData());
            //before = airports[i][j];
        }
    }

}

void DrawService::ClearRoutes() {
    Init();
}
