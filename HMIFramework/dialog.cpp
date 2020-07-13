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

    ui->label_TestValue->setText(factSpeed->rawValueString());
}

Dialog::~Dialog()
{
    delete ui;
}

