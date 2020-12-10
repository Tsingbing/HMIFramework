#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QVariant>
#include "Vehicle.h"
#include "CanLink.h"

namespace Ui
{
    class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void _carUpdated(QVariant value);

    void on_pushButton_menu_clicked();

    void on_pushButton_system_set_clicked();

    void on_pushButton_set2main_clicked();

    void on_pushButton_mainset_F10_clicked();

private:
    Ui::Dialog *ui;
    Vehicle * ve;
    CanLink * cl;
};

#endif // DIALOG_H
