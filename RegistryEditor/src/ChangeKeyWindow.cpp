#include "../include/ChangeKeyWindow.h"
#include "ui_ChangeKeyWindow.h"

#include <QMessageBox>

ChangeKeyWindow::ChangeKeyWindow(QString keyName, QWidget *parent): QDialog(parent), stringValue(nullptr), intValue(nullptr), longValue(nullptr), keyName(keyName),
    ui(new Ui::ChangeKeyWindow)
{
    ui->setupUi(this);
    ConfigureWindow();
}

ChangeKeyWindow::~ChangeKeyWindow()
{
    delete ui;
}

void ChangeKeyWindow::ConfigureWindow()
{
    setFixedSize(400, 150);
    setWindowModality(Qt::WindowModal);
}

QString ChangeKeyWindow::GetKeyName() const
{
    return keyName;
}

void ChangeKeyWindow::ConfigureLineEdits()
{
    ui->nameLineEdit->setText(keyName);  // set selected key name
    if (stringValue)  // set selected key value according to it type
    {
        ui->valueLineEdit->setText(*stringValue);
    }
    else if (intValue)
    {
        ui->valueLineEdit->setText(QString::number(*intValue));
    }
    else
    {
        ui->valueLineEdit->setText(QString::number(*longValue));
    }
}

qulonglong *ChangeKeyWindow::GetLongValue() const
{
    return longValue;
}

void ChangeKeyWindow::SetLongValue(qulonglong *newLongValue)
{
    longValue = newLongValue;
}

uint *ChangeKeyWindow::GetIntValue() const
{
    return intValue;
}

void ChangeKeyWindow::SetIntValue(uint *newIntValue)
{
    intValue = newIntValue;
}

QString *ChangeKeyWindow::GetStringValue() const
{
    return stringValue;
}

void ChangeKeyWindow::SetStringValue(QString *newStringValue)
{
    stringValue = newStringValue;
}

void ChangeKeyWindow::on_okButton_clicked()
{
    auto newValue = ui->valueLineEdit->text();  // new value for selected key
    auto newName = ui->nameLineEdit->text();  // new name for selected key
    if (newValue.isEmpty() || newName.isEmpty())
    {
        QMessageBox::critical(this, "Error!", "Error! New name or value can't be empty!");
        return;
    }

    keyName = newName;  // set new name
    // set new value for the key according to it type
    if (stringValue)
    {
        *stringValue = newValue;
    }
    else if (intValue)
    {
        bool isOk;
        *intValue = newValue.toUInt(&isOk);
        if (!isOk)
        {
            QMessageBox::warning(this, "Warning!", "DWORD key can't has a string value!");  // if string was entered for dword key
            return;
        }
    }
    else
    {
        bool isOk;
        *longValue = newValue.toULongLong(&isOk);
        if (!isOk)
        {
            QMessageBox::warning(this, "Warning!", "QWORD key can't has a string value!");   // if string was entered for qword key
            return;
        }
    }

    close();
}

