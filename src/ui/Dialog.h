#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QVariant>
namespace Ui {
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

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
