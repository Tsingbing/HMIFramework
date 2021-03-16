#ifndef NUMKEYBOARD_H
#define NUMKEYBOARD_H

#include <QDialog>
#include <QtDebug>
#include <QKeyEvent>
#include <QEvent>

namespace Ui {
class NumKeyboard;
}

class NumKeyboard : public QDialog
{
    Q_OBJECT
    
public:
    explicit NumKeyboard(QWidget *parent = 0);
    ~NumKeyboard();
    bool valid;

    void setText(QString str);
    QString getText();

protected:
    void changeEvent(QEvent *e);
//    void keyPressEvent(QKeyEvent *e);
    bool eventFilter(QObject *obj, QEvent *event);
        
private slots:
    void on_num1Button_clicked();
    void on_num2Button_clicked();
    void on_num3Button_clicked();
    void on_num4Button_clicked();
    void on_num5Button_clicked();
    void on_num6Button_clicked();
    void on_num7Button_clicked();
    void on_num8Button_clicked();
    void on_num9Button_clicked();
    void on_dotButton_clicked();
    void on_num0Button_clicked();
    void on_signButton_clicked();
    void on_backspaceButton_clicked();
    void on_cancelButton_clicked();
    void on_okButton_clicked();

private:
    Ui::NumKeyboard *ui;
    QString strContent;
};

#endif // NUMKEYBOARD_H
