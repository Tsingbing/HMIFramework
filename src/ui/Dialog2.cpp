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

    ///< fact 变化值和ui显示 连接
    connect(ve->carSpeedFact(),&Fact::valueChanged,this,&Dialog2::_carUpdated);
}

Dialog2::~Dialog2()
{
    delete ui;
}

void Dialog2::_carUpdated(QVariant value)
{
    ui->label->setText(value.toString());
}
