#ifndef DIALOG2_H
#define DIALOG2_H

#include <QDialog>
#include <QVariant>

namespace Ui {
class Dialog2;
}

class Dialog2 : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog2(QWidget *parent = nullptr);
    ~Dialog2();

private slots:
    void _carUpdated(QVariant value);

private:
    Ui::Dialog2 *ui;
};

#endif // DIALOG2_H
