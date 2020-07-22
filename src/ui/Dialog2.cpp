#include "Dialog2.h"
#include "ui_Dialog2.h"

#include "XApplication.h"
#include "Toolbox.h"
#include "VehicleManager.h"
#include "FactGroup.h"
#include "Vehicle.h"
#include <QDebug>

Dialog2::Dialog2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog2)
{
    ui->setupUi(this);
    Vehicle * ve = XApp()->toolbox()->vehicleManager()->activeVehicle();
    ui->label->setText(ve->speedFact()->rawValueString());

    qDebug() << ve->speedFact()->rawValueString();
    qDebug() << ve->rotatingSpeedFact()->rawValueString();
    qDebug() << ve->rotatingSpeedFact()->shortDescription();
//    qDebug() << ve->rotatingSpeedFact()->rawMax();
//    qDebug() << ve->rotatingSpeedFact()->rawMin();
}

Dialog2::~Dialog2()
{
    delete ui;
}
