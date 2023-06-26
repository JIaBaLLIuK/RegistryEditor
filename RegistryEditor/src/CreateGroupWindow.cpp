#include "../include/CreateGroupWindow.h"
#include "ui_CreateGroupWindow.h"
#include "../include/Registry.h"

#include <QMessageBox>

CreateGroupWindow::CreateGroupWindow(QString currentPath, QWidget *parent): QDialog(parent), currentPath(currentPath), ui(new Ui::CreateGroupWindow)
{
    ui->setupUi(this);
    ConfigureWindow();
}

CreateGroupWindow::~CreateGroupWindow()
{
    delete ui;
}

void CreateGroupWindow::ConfigureWindow()
{
    setWindowModality(Qt::ApplicationModal);
    setWindowTitle("Create group");
    setFixedSize(300, 100);
}

QString CreateGroupWindow::GetGroupName() const
{
    return groupName;
}

void CreateGroupWindow::on_okButton_clicked()
{
    groupName = ui->inputNameLineEdit->text();
    if (groupName.isEmpty())
    {
        QMessageBox::critical(this, "Error!", "Group name can't be empty!");
        return;
    }

    auto pathElements = currentPath.split("\\");  // get all elements of the current path
    pathElements.push_back(groupName);  // add new group name for the current path
    HKEY baseGroup = Registry().GetGroupHkeyByName(pathElements[0]);  // curent group descriptor
    pathElements.pop_front();  // remove "Computer" from the current path
    HKEY hKey;
    auto pathToNewGroup = pathElements.join("\\");
    if (RegCreateKeyEx(baseGroup, (wchar_t*)pathToNewGroup.utf16(), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey, NULL) != ERROR_SUCCESS)  // attempt to create new group
    {
        QMessageBox::warning(this, "Warning!", "Couldn't create new group!");
        return;
    }

    close();
}

