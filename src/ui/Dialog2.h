#ifndef DIALOG2_H
#define DIALOG2_H

#include <QDialog>
#include <QVariant>
#include "LinkManager.h"
#include "Vehicle.h"
#include "CanLink.h"

namespace Ui
{
    class Dialog2;
}

class Dialog2 : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog2(QWidget *parent = nullptr);
    ~Dialog2();

private slots:
    void on_pushButton_menu_F4_2_clicked();
    void on_pushButton_menu_F5_2_clicked();
    void on_pushButton_menu_F4_clicked();
    void on_pushButton_menu_F5_clicked();
    void on_pushButton_frontLight_clicked();
    void on_pushButton_backLight_clicked();
    void on_pushButton_alarmLight_clicked();
    void on_pushButton_pochaiduan_clicked();
    void on_pushButton_wajueduan_clicked();
    void on_pushButton_pochaiduanquick_clicked();

private:
    Ui::Dialog2 *ui;
    Vehicle * ve;
    CanLink * cl;
};

#endif // DIALOG2_H
