#include "Dialog.h"
#include "ui_Dialog.h"

#include "XApplication.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    XApp()->toolbox();
}

Dialog::~Dialog()
{
    delete ui;

}
