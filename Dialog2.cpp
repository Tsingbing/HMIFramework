#include "Dialog2.h"
#include "ui_Dialog2.h"

#include "XApplication.h"
#include "Toolbox.h"
#include "VehicleManager.h"
#include "FactGroup.h"
#include "Vehicle.h"

Dialog2::Dialog2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog2)
{
    ui->setupUi(this);
    Vehicle * ve = XApp()->toolbox()->vehicleManager()->activeVehicle();
    ui->label->setText(ve->speedFact()->rawValueString());
}

Dialog2::~Dialog2()
{
    delete ui;
}
