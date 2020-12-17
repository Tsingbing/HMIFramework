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
    void _updateValues();

private:
    void _setupTimer();
    QTimer _updateTimer;

private:
    Ui::Dialog2 *ui;

    QStringList _warningList;
    QStringList _warningAllList;
    Vehicle * ve;
    CanLink * cl;
};

#endif // DIALOG2_H
