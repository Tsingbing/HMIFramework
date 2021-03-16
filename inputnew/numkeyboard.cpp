#include "numkeyboard.h"
#include "ui_numkeyboard.h"

NumKeyboard::NumKeyboard(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::NumKeyboard)
{
    ui->setupUi(this);

    strContent = "";
    ui->lineEdit->setText(strContent);
    ui->lineEdit->setFocus();

    ui->lineEdit->installEventFilter(this);
}

NumKeyboard::~NumKeyboard()
{
    delete ui;
}

void NumKeyboard::changeEvent(QEvent* e)
{
    QDialog::changeEvent(e);
    switch (e->type())
    {
        case QEvent::LanguageChange:
            ui->retranslateUi(this);
            break;
        default:
            break;
    }
}

bool NumKeyboard::eventFilter(QObject* obj, QEvent* event)
{
    if (event->type() == QEvent::KeyPress)
    {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
        if (obj == ui->lineEdit)
        {
            if (keyEvent->key() >= 0x20 && keyEvent->key() <= 0x0ff) //屏蔽所有按键输入
                return true;
            else
                return false;
        }
        else
        {
            return false;
        }
    }
    else
    {
        // standard event processing
        return QObject::eventFilter(obj, event);
    }
}

//***********************按键*****************************//
void NumKeyboard::on_num1Button_clicked() //1
{
    int idx = ui->lineEdit->cursorPosition();
    if (strContent.left(idx) == "0")
    {
        ui->lineEdit->setCursorPosition(idx);
        ui->lineEdit->setFocus();
        return;
    }
    strContent.insert(idx, '1');
    ui->lineEdit->setText(strContent);
    ui->lineEdit->setCursorPosition(idx + 1);
    ui->lineEdit->setFocus();
}

void NumKeyboard::on_num2Button_clicked() //2
{
    int idx = ui->lineEdit->cursorPosition();
    if (strContent.left(idx) == "0")
    {
        ui->lineEdit->setCursorPosition(idx);
        ui->lineEdit->setFocus();
        return;
    }
    strContent.insert(idx, '2');
    ui->lineEdit->setText(strContent);
    ui->lineEdit->setCursorPosition(idx + 1);
    ui->lineEdit->setFocus();
}

void NumKeyboard::on_num3Button_clicked() //3
{
    int idx = ui->lineEdit->cursorPosition();
    if (strContent.left(idx) == "0")
    {
        ui->lineEdit->setCursorPosition(idx);
        ui->lineEdit->setFocus();
        return;
    }
    strContent.insert(idx, '3');
    ui->lineEdit->setText(strContent);
    ui->lineEdit->setCursorPosition(idx + 1);
    ui->lineEdit->setFocus();
}

void NumKeyboard::on_num4Button_clicked() //4
{
    int idx = ui->lineEdit->cursorPosition();
    if (strContent.left(idx) == "0")
    {
        ui->lineEdit->setCursorPosition(idx);
        ui->lineEdit->setFocus();
        return;
    }
    strContent.insert(idx, '4');
    ui->lineEdit->setText(strContent);
    ui->lineEdit->setCursorPosition(idx + 1);
    ui->lineEdit->setFocus();
}

void NumKeyboard::on_num5Button_clicked() //5
{
    int idx = ui->lineEdit->cursorPosition();
    if (strContent.left(idx) == "0")
    {
        ui->lineEdit->setCursorPosition(idx);
        ui->lineEdit->setFocus();
        return;
    }
    strContent.insert(idx, '5');
    ui->lineEdit->setText(strContent);
    ui->lineEdit->setCursorPosition(idx + 1);
    ui->lineEdit->setFocus();
}

void NumKeyboard::on_num6Button_clicked() //6
{
    int idx = ui->lineEdit->cursorPosition();
    if (strContent.left(idx) == "0")
    {
        ui->lineEdit->setCursorPosition(idx);
        ui->lineEdit->setFocus();
        return;
    }
    strContent.insert(idx, '6');
    ui->lineEdit->setText(strContent);
    ui->lineEdit->setCursorPosition(idx + 1);
    ui->lineEdit->setFocus();
}

void NumKeyboard::on_num7Button_clicked() //7
{
    int idx = ui->lineEdit->cursorPosition();
    if (strContent.left(idx) == "0")
    {
        ui->lineEdit->setCursorPosition(idx);
        ui->lineEdit->setFocus();
        return;
    }
    strContent.insert(idx, '7');
    ui->lineEdit->setText(strContent);
    ui->lineEdit->setCursorPosition(idx + 1);
    ui->lineEdit->setFocus();
}

void NumKeyboard::on_num8Button_clicked() //8
{
    int idx = ui->lineEdit->cursorPosition();
    if (strContent.left(idx) == "0")
    {
        ui->lineEdit->setCursorPosition(idx);
        ui->lineEdit->setFocus();
        return;
    }
    strContent.insert(idx, '8');
    ui->lineEdit->setText(strContent);
    ui->lineEdit->setCursorPosition(idx + 1);
    ui->lineEdit->setFocus();
}

void NumKeyboard::on_num9Button_clicked() //9
{
    int idx = ui->lineEdit->cursorPosition();
    if (strContent.left(idx) == "0")
    {
        ui->lineEdit->setCursorPosition(idx);
        ui->lineEdit->setFocus();
        return;
    }
    strContent.insert(idx, '9');
    ui->lineEdit->setText(strContent);
    ui->lineEdit->setCursorPosition(idx + 1);
    ui->lineEdit->setFocus();
}

void NumKeyboard::on_dotButton_clicked() //.
{
    int idx = ui->lineEdit->cursorPosition();

    if (idx == 0 || strContent.contains('.'))
    {
        ui->lineEdit->setCursorPosition(idx);
        ui->lineEdit->setFocus();
        return;
    }

    strContent.insert(idx, '.');
    ui->lineEdit->setText(strContent);
    ui->lineEdit->setCursorPosition(idx + 1);
    ui->lineEdit->setFocus();
}

void NumKeyboard::on_num0Button_clicked() //0
{
    int idx = ui->lineEdit->cursorPosition();
    if (strContent.left(idx) == "0" || (idx == 0 && strContent != ""))
    {
        ui->lineEdit->setCursorPosition(idx);
        ui->lineEdit->setFocus();
        return;
    }
    strContent.insert(idx, '0');
    ui->lineEdit->setText(strContent);
    ui->lineEdit->setCursorPosition(idx + 1);
    ui->lineEdit->setFocus();
}

void NumKeyboard::on_signButton_clicked() //+/-
{
    int idx = ui->lineEdit->cursorPosition();
    if (strContent.left(1) == "-")
    {
        strContent.remove(0, 1);
        ui->lineEdit->setText(strContent);
        ui->lineEdit->setCursorPosition(idx - 1);
        ui->lineEdit->setFocus();
    }
    else
    {
        if (strContent == "0" || strContent == "")
        {
            ui->lineEdit->setCursorPosition(idx);
            ui->lineEdit->setFocus();
        }
        else
        {
            strContent.insert(0, '-');
            ui->lineEdit->setText(strContent);
            ui->lineEdit->setCursorPosition(idx + 1);
            ui->lineEdit->setFocus();
        }
    }
}

void NumKeyboard::on_backspaceButton_clicked() //backspace
{
    int idx = ui->lineEdit->cursorPosition();
    if (idx == 0)
    {
        ui->lineEdit->setCursorPosition(idx);
        ui->lineEdit->setFocus();
        return;
    }
    strContent.remove(idx - 1, 1);
    ui->lineEdit->setText(strContent);
    ui->lineEdit->setCursorPosition(idx - 1);
    ui->lineEdit->setFocus();
}

void NumKeyboard::on_cancelButton_clicked() //cancel
{
    this->close();
    valid = false;
}

void NumKeyboard::on_okButton_clicked() //ok
{
    this->close();
    valid = true;
}

void NumKeyboard::setText(QString str) //设置文本内容
{
    strContent = str;
    ui->lineEdit->setText(strContent);
    ui->lineEdit->setFocus();
}

QString NumKeyboard::getText() //获取内容
{
    return strContent;
}
