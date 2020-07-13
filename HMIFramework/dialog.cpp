#include "dialog.h"
#include "ui_dialog.h"
#include <QVariant>
#include <QDebug>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    vehicle = new Vehicle(this);
    Fact * factSpeed = vehicle->speedFact();
    float f = (factSpeed->rawValue()).value<float>();
    ui->label_TestValue->setText(QString("float is %1").arg(f));
}

Dialog::~Dialog()
{
    delete ui;
}

