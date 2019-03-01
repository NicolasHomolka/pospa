/*
authors: Homolka, Prinz
desc: Airline Pathfinding Example
class: 5BHIF
 */

#include "databaseservice.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QPainter>
#include <dijkstrasearch.h>
#include <QMessageBox>



Q_DECLARE_METATYPE(Airport*)
Q_DECLARE_METATYPE(Airline*)
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
QMainWindow(parent),
ui(new Ui::MainWindow) {
    ui->setupUi(this);

    this->dbService = new DatabaseService();
    this->drawService = new DrawService(this->ui->label_4);

    cout << dbService->CreateConnection() << endl;

    this->airlines = dbService->GetAirlineData();
    for (Airline* a : this->airlines) {
        this->ui->airlineComboBox->addItem(a->GetName(), QVariant::fromValue(a));
    }

    this->airports = dbService->GetAirportData();
    for (Airport* a : this->airports) {
        this->ui->startAirportComboBox->addItem(a->GetName(), QVariant::fromValue(a));
        this->ui->destAirportComboBox->addItem(a->GetName(), QVariant::fromValue(a));
    }
    //this->drawService->DrawRoute(47.877929f, 16.299184f, 49.484666f, -54.651002f);
}

MainWindow::~MainWindow() {
    delete ui;
    delete dbService;
    delete drawService;
}

void MainWindow::on_searchDestAirportButton_clicked() {
    this->ui->destAirportComboBox->clear();
    for (Airport* a : this->airports) {
        if (IsUpper(this->ui->destAirportLineEdit->text()) && a->GetIData() == this->ui->destAirportLineEdit->text()) {
            this->ui->destAirportComboBox->addItem(a->GetName(), QVariant::fromValue(a));
        } else if (a->GetName().startsWith(this->ui->destAirportLineEdit->text())) {
            this->ui->destAirportComboBox->addItem(a->GetName(), QVariant::fromValue(a));
        }

    }
}

void MainWindow::on_searchStartAirportButton_clicked() {
    this->ui->startAirportComboBox->clear();
    for (Airport* a : this->airports) {
        if (IsUpper(this->ui->startAirportLineEdit->text()) && a->GetIData() == this->ui->startAirportLineEdit->text()) {
            this->ui->startAirportComboBox->addItem(a->GetName(), QVariant::fromValue(a));
        } else if (a->GetName().startsWith(this->ui->startAirportLineEdit->text())) {
            this->ui->startAirportComboBox->addItem(a->GetName(), QVariant::fromValue(a));
        }

    }
}

void MainWindow::on_searchFlightButton_clicked() {
    ResetData();
    Airport* start = this->ui->startAirportComboBox->itemData(this->ui->startAirportComboBox->currentIndex()).value<Airport*>();
    Airport* dest = this->ui->destAirportComboBox->itemData(this->ui->destAirportComboBox->currentIndex()).value<Airport*>();
    cout << start->GetName().toUtf8().constData() << endl;
    DijkstraSearch search{start, dest, this->dbService};
    QList<QList<QPair < Airport*, Airline*>>> list = search.Search();

    Airline* selected = this->ui->airlineComboBox->itemData(this->ui->airlineComboBox->currentIndex()).value<Airline*>();

    for (QList<QPair < Airport*, Airline*>> itemI : list) {
        QString label{""};
        QListWidgetItem* item = new QListWidgetItem();
        item->setText(item->text() + itemI[itemI.count() - 1].first->GetName().trimmed());
        for (int i = itemI.count() - 2; i >= 0; i--) {
            if (itemI[i].second->GetId() == selected->GetId()) {
                item->setTextColor(Qt::red);
            } else if (itemI[i].second->GetAllianceId() == selected->GetAllianceId()) {
                item->setTextColor(Qt::blue);
            } else {
                item->setTextColor(Qt::gray);
            }
            item->setText(item->text() + " - (" + itemI[i].second->GetName() + ") -> " + itemI[i].first->GetName().trimmed());
        }
        this->ui->flightOverviewListWidget->addItem(item);
    }

    this->drawService->DrawRoute(list);

}

void MainWindow::ResetData() {
    this->ui->flightOverviewListWidget->clear();
    this->drawService->ClearRoutes();
}

bool MainWindow::IsUpper(QString s) {
    for (QChar c : s) {
        if (!c.isUpper()) {
            return false;
        }
    }
    return true;
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::information(this, "About", "Authors: Prinz, Homolka");

}
