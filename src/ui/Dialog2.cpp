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
    ve = XApp()->toolbox()->vehicleManager()->activeVehicle();
    cl = XApp()->toolbox()->linkManager()->canlink();

    _setupTimer();
    ///< fact 变化值和ui显示 连接
    connect(ve->supplyVoltageFact(),&Fact::valueChanged,[=](){ui->label_dianya->setText(ve->supplyVoltageFact()->valueString());});
    connect(ve->waterTemperatureFact(),&Fact::valueChanged,[=](){ui->label_shuiwen->setText(ve->waterTemperatureFact()->valueString());});
    connect(ve->rotatingSpeedFact(),&Fact::valueChanged,[=](){ui->label_zhuansu->setText(ve->rotatingSpeedFact()->valueString());});
    connect(ve->fuelLevelFact(),&Fact::valueChanged,[=](){ui->label_ranyouliang->setText(ve->fuelLevelFact()->valueString());});
    connect(ve->oilTemperatureFact(),&Fact::valueChanged,[=](){ui->label_youwen->setText(ve->oilTemperatureFact()->valueString());});
    connect(ve->frontPumpPressureFact(),&Fact::valueChanged,[=](){ui->label_qianbengyali->setText(ve->frontPumpPressureFact()->valueString());});
    connect(ve->backPumpPressureFact(),&Fact::valueChanged,[=](){ui->label_houbengyali->setText(ve->backPumpPressureFact()->valueString());});
    connect(ve->XDegreeFact(),&Fact::valueChanged,[=](){ui->label_qingjiaoX->setText(ve->XDegreeFact()->valueString());});
    connect(ve->YDegreeFact(),&Fact::valueChanged,[=](){ui->label_qingjiaoY->setText(ve->YDegreeFact()->valueString());});
}

Dialog2::~Dialog2()
{
    delete ui;
}

void Dialog2::_updateValues()
{
    static int count = 0;

    if(ve->warningList.size() == 0)
    {
        ui->label_warning->setText("");
        return;
    }

    if(count++ >= ve->warningList.size() -1 )
        count = 0;

    if(ve->warningList.size() == 0)
        ui->label_warning->setText("");
    else
        ui->label_warning->setText(ve->warningList.at(count));

}

void Dialog2::_setupTimer()
{
    connect(&_updateTimer, &QTimer::timeout, this, &Dialog2::_updateValues);
    _updateTimer.setSingleShot(false);
    _updateTimer.setInterval(1000); //1s
    _updateTimer.start();
}
