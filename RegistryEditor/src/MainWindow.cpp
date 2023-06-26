#include "../include/MainWindow.h"
#include "../include/Registry.h"
#include "../include/CreateGroupWindow.h"
#include "../include/CreateKeyWindow.h"
#include "../include/ChangeKeyWindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ConfigureMainWIndow();
    ConfigureRegistryTreeWidget();
    ConfigureGroupKeysWidget();
    ConfigureCurrentPathWidget();
    ConfigureCreateButtons();
    ConfigureRemoveKeyButton();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ConfigureMainWIndow()
{
    setWindowIcon(QIcon(":/img/window_icon.png"));
    setWindowTitle("Registry Editor");
}

void MainWindow::ConfigureRegistryTreeWidget()
{
    showMaximized();
    QTreeWidgetItem* root = new QTreeWidgetItem(QStringList() << "Computer");
    root->setIcon(0, QIcon(":/img/computer_icon.png"));
    ui->registryTree->addTopLevelItem(root);  // add top level item ("Computer") for the registry tree
    QStringList baseGroups =
    {
        "HKEY_CLASSES_ROOT",
        "HKEY_CURRENT_USER",
        "HKEY_LOCAL_MACHINE",
        "HKEY_USERS"
    };

    foreach (auto groupName, baseGroups)  // create subgroups for every base group
    {
        CreateRegistryBranch(groupName, ui->registryTree->topLevelItem(0));
    }
}

void MainWindow::ConfigureGroupKeysWidget()
{   // creation table for key name, type and value
    ui->groupKeys->setColumnCount(3);
    ui->groupKeys->setHorizontalHeaderLabels(QStringList() << "Key" << "Type" << "Value");
    ui->groupKeys->verticalHeader()->setVisible(false);
    ui->groupKeys->horizontalHeader()->setSectionsClickable(false);
    ui->groupKeys->horizontalHeader()->resizeSection(0, 250);
    ui->groupKeys->horizontalHeader()->resizeSection(1, 250);
    ui->groupKeys->horizontalHeader()->resizeSection(2, 350);
}

void MainWindow::ConfigureCurrentPathWidget(QString path)
{   // line edit which contains path for selected group
    ui->currentPath->setText("Computer\\" + path);
    ui->currentPath->setReadOnly(true);
}

void MainWindow::ConfigureCreateButtons(QString path)
{
    if (path.isEmpty())  // create buttons can be shown only when current path isn't empty
    {
        ui->createGroupAction->setEnabled(false);
        ui->createKeyAction->setEnabled(false);
    }
    else
    {
        ui->createGroupAction->setEnabled(true);
        ui->createKeyAction->setEnabled(true);
    }
}

void MainWindow::ConfigureRemoveKeyButton(QTableWidgetItem *currentItem)
{
    if (!currentItem)  // remove key button can be shown only if there is selected table item
    {
        ui->removeKeyAction->setEnabled(false);
    }
    else
    {
        ui->removeKeyAction->setEnabled(true);
    }
}

QTreeWidgetItem* MainWindow::CreateRegistryBranch(QString groupName, QTreeWidgetItem* parentItem)
{
    QTreeWidgetItem* item = new QTreeWidgetItem(QStringList() << groupName);
    QIcon icon(":/img/group_icon.ico");
    item->setIcon(0, icon);
    parentItem->addChild(item);
    QSettings settings(groupName, QSettings::NativeFormat);
    registry.ParseRegistryBranch(item, &settings, &icon);
    return item;
}

void MainWindow::on_registryTree_itemExpanded(QTreeWidgetItem *group)
{
    Q_UNUSED(group);
    ui->registryTree->resizeColumnToContents(0);
    QSettings settings(registry.FindPathForGroup(group), QSettings::NativeFormat);
    QIcon icon(":/img/group_icon.ico");
    registry.ParseRegistryBranch(group, &settings, &icon);
}

void MainWindow::on_registryTree_itemClicked(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(column);
    auto path = registry.FindPathForGroup(item);
    ConfigureCurrentPathWidget(path);  // set new path in the line edit
    ConfigureCreateButtons(path);  // enable create buttons enable
    ConfigureRemoveKeyButton();  // disable remove key button
    QList<QTableWidgetItem*> valuesTypes;
    auto keysAndValues = registry.CreateGroupKeys(item, valuesTypes);  // get map which contains key names and values; get list of table items with key types
    QMap<QString, QString>::const_iterator iterator = keysAndValues.constBegin();
    ui->groupKeys->setRowCount(keysAndValues.size());  // set row count for the table
    int rowIndex = 0;
    while (iterator != keysAndValues.constEnd())
    {
        // create table item for key name; make it immutable
        auto* keyItem = new QTableWidgetItem(iterator.key());
        keyItem->setFlags(keyItem->flags() & ~Qt::ItemIsEditable);
        ui->groupKeys->setItem(rowIndex, 0, keyItem);
        // create table item for key type; make it immutable
        valuesTypes[rowIndex]->setFlags(valuesTypes[rowIndex]->flags() & ~Qt::ItemIsEditable);
        ui->groupKeys->setItem(rowIndex, 1, valuesTypes[rowIndex]);
        // create table item for key value; make it immutable
        auto* valueItem = new QTableWidgetItem(iterator.value());
        valueItem->setFlags(valueItem->flags() & ~Qt::ItemIsEditable);
        ui->groupKeys->setItem(rowIndex, 2, valueItem);
        // increase row number and iterator
        iterator++;
        rowIndex++;
    }
}

void MainWindow::on_currentPath_returnPressed()
{
    auto group = registry.FindGroupByPath(ui->currentPath->text(), ui->registryTree->topLevelItem(0));  // get registry tree item with current path
    ui->registryTree->setCurrentItem(group);  // make it current item
    emit ui->registryTree->itemClicked(group, 0);  // open it
}

void MainWindow::on_createKeyAction_triggered()
{
    ConfigureRemoveKeyButton();  // disable remove key button
    CreateKeyWindow createKeyWindow(this);
    createKeyWindow.show();
    createKeyWindow.exec();
    auto currentItem = ui->registryTree->currentItem();
    auto path = registry.FindPathForGroup(currentItem);
    QSettings settings(path, QSettings::NativeFormat);
    settings.setValue(createKeyWindow.GetKeyName(), createKeyWindow.GetKeyValue());  // create new key
    on_registryTree_itemClicked(currentItem, 0);  // display new key
}

void MainWindow::on_groupKeys_itemClicked(QTableWidgetItem *item)
{
    ConfigureRemoveKeyButton(item);  // enable remove key button
}


void MainWindow::on_removeKeyAction_triggered()
{
    auto keyName = ui->groupKeys->selectedItems()[0]->text();  // get name of selected key
    auto currentGroup = ui->registryTree->currentItem();
    auto groupName = registry.FindPathForGroup(currentGroup);
    QSettings settings(groupName, QSettings::NativeFormat);
    settings.remove(keyName);  // remove selected key
    on_registryTree_itemClicked(currentGroup, 0);
}


void MainWindow::on_createGroupAction_triggered()
{
    CreateGroupWindow createGroupWindow(registry.FindPathForGroup(ui->registryTree->currentItem()), this);
    createGroupWindow.show();
    createGroupWindow.exec();
    auto createdGroupName = createGroupWindow.GetGroupName();  // get name for the new group
    if (createdGroupName.isEmpty())
    {
        return;
    }

    CreateRegistryBranch(createdGroupName, ui->registryTree->currentItem());  // create subbranch for the new item including it
    ConfigureCurrentPathWidget(registry.FindPathForGroup(ui->registryTree->currentItem()) + "\\" + createdGroupName);  // set new path
    on_currentPath_returnPressed();  // open new group
}


void MainWindow::on_removeGroupAction_triggered()
{
    auto currentPath = registry.FindPathForGroup(ui->registryTree->currentItem());
    auto currentPathElements = currentPath.split("\\");
    QString baseGroupName = currentPathElements[0];  // get base group name
    HKEY baseGroup = registry.GetGroupHkeyByName(baseGroupName);  // get base group descriptor
    currentPathElements.pop_front();  // remobe base group name
    currentPath = currentPathElements.join("\\");  // create path for the selected group
    if (RegDeleteKeyEx(baseGroup, (wchar_t*)currentPath.utf16(), KEY_WOW64_64KEY, 0) != ERROR_SUCCESS)  // if group wasn't removed
    {
        QMessageBox::warning(this, "Warning!", "Couldn't delete this group!");
        return;
    }

    int indexToRemove;
    auto* parentOfCurrentItem = ui->registryTree->currentItem()->parent();
    for (indexToRemove = 0; indexToRemove < parentOfCurrentItem->childCount(); indexToRemove++)
    {
        if (ui->registryTree->currentItem()->text(0) == parentOfCurrentItem->child(indexToRemove)->text(0))  // get index of the removed group
        {
            break;
        }
    }

    ui->registryTree->currentItem()->parent()->takeChild(indexToRemove);  // remove group from the tree
}

void MainWindow::on_groupKeys_cellDoubleClicked(int row, int column)
{
    Q_UNUSED(row);
    Q_UNUSED(column);
    auto currentKeyName = ui->groupKeys->selectedItems()[0]->text();  // get name of selected key
    ChangeKeyWindow window(currentKeyName, this);
    QString valueType = ui->groupKeys->selectedItems()[1]->text();  // get type of the selected type
    // get value of the key and set it in the window
    if (valueType == "REG_SZ")
    {
        auto keyValue = ui->groupKeys->selectedItems()[2]->text();
        window.SetStringValue(&keyValue);
    }
    else if (valueType == "REG_DWORD")
    {
        auto keyValue = ui->groupKeys->selectedItems()[2]->text().toUInt();
        window.SetIntValue(&keyValue);
    }
    else if (valueType == "REG_QWORD")
    {
        auto keyValue = ui->groupKeys->selectedItems()[2]->text().toULongLong();
        window.SetLongValue(&keyValue);
    }
    else
    {
        QMessageBox::warning(this, "Warning!", "Unable to change this key!");
        return;
    }

    window.ConfigureLineEdits();
    window.show();
    window.exec();
    // get key name and path for this key
    auto currentItem = ui->registryTree->currentItem();
    auto path = registry.FindPathForGroup(currentItem);
    QSettings settings(path, QSettings::NativeFormat);
    auto keyName = window.GetKeyName();
    if (currentKeyName != keyName)
    {
        on_removeKeyAction_triggered();
    }
    // set new value in registry
    if (valueType == "REG_SZ")
    {
        settings.setValue(keyName, *window.GetStringValue());
    }
    else if (valueType == "REG_DWORD")
    {
        settings.setValue(keyName, *window.GetIntValue());
    }
    else if (valueType == "REG_QWORD")
    {
        settings.setValue(keyName, *window.GetLongValue());
    }

    on_registryTree_itemClicked(currentItem, 0);
}

