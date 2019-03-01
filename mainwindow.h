/*
authors: Homolka, Prinz
desc: Airline Pathfinding Example
class: 5BHIF
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "databaseservice.h"

#include <QMainWindow>
#include <QList>
#include <airline.h>
#include <airport.h>
#include <drawservice.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_searchDestAirportButton_clicked();

    void on_searchStartAirportButton_clicked();

    void on_searchFlightButton_clicked();

    void on_actionAbout_triggered();

private:
    Ui::MainWindow *ui;
    QList<Airport*> airports;
    QList<Airline*> airlines;
    void DrawImage();
    DatabaseService* dbService;
    DrawService* drawService;
    void ResetData();
    bool IsUpper(QString s);
};

#endif // MAINWINDOW_H
