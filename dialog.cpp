#include "Dialog.h"
#include "ui_Dialog.h"

#include "XApplication.h"
#include "Toolbox.h"
#include "VehicleManager.h"
#include "FactGroup.h"
#include "Vehicle.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    Vehicle * ve = XApp()->toolbox()->vehicleManager()->activeVehicle();
    ui->label->setText(ve->speedFact()->rawValueString());
}

Dialog::~Dialog()
{
    delete ui;

}
