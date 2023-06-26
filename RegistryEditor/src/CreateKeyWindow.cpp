#include "../include/CreateKeyWindow.h"
#include "ui_CreateKeyWindow.h"

#include <QMessageBox>
#include <QSettings>

CreateKeyWindow::CreateKeyWindow(QWidget *parent): QDialog(parent), ui(new Ui::CreateKeyWindow)
{
    ui->setupUi(this);
    ConfigureWindow();
}

CreateKeyWindow::~CreateKeyWindow()
{
    delete ui;
}

QString CreateKeyWindow::GetKeyName() const
{
    return keyName;
}

QVariant CreateKeyWindow::GetKeyValue() const
{
    return keyValue;
}

void CreateKeyWindow::ConfigureWindow()
{
    setWindowModality(Qt::ApplicationModal);
    setFixedSize(400, 230);
    setWindowTitle("Create key");
}

void CreateKeyWindow::on_okButton_clicked()
{
    keyName = ui->inputNameLineEdit->text();  // name for the new key
    keyValue = ui->inputValueLineEdit->text();  // value for the new key
    if (!ui->stringKey->isChecked() && !ui->intKey->isChecked() && !ui->longKey->isChecked())  // if type for the new key wasn't selected
    {
        QMessageBox::critical(this, "Error!", "You should choose key type!");
        return;
    }
    else if (keyName.isEmpty() || keyValue.toString().isEmpty())  // if name of value wasn't entered
    {
        QMessageBox::critical(this, "Error!", "Error! Name or value can't be empty!");
        return;
    }

    bool isNumber;
    if (ui->intKey->isChecked())
    {
        uint number = keyValue.toUInt(&isNumber);
        if (!isNumber)  // if string was entered for the dword key
        {
            QMessageBox::warning(this, "Warning!", "DWORD key can't has a string value!");
            return;
        }

        keyValue = QVariant(number);
    }
    else if (ui->longKey->isChecked())
    {
        qulonglong number = keyValue.toULongLong(&isNumber);
        if (!isNumber)  // if string was entered for the qword key
        {
            QMessageBox::warning(this, "Warning!", "QWORD key can't be a string!");
            return;
        }

        keyValue = QVariant(number);
    }

    close();
}

