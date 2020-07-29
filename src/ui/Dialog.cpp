#include "Dialog.h"
#include "ui_Dialog.h"

#include "XApplication.h"
#include "Toolbox.h"
#include "VehicleManager.h"
#include "FactGroup.h"
#include "Vehicle.h"
#include <QDebug>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    Vehicle * ve = XApp()->toolbox()->vehicleManager()->activeVehicle();
    connect(ve->carSpeedFact(),&Fact::valueChanged,this,&Dialog::_carUpdated);

    //qDebug() << ve->getFact("carSpeed")->type();
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::_carUpdated(QVariant value)
{
    ui->label->setText(value.toString());
}
