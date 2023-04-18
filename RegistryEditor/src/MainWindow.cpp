#include "../include/MainWindow.h"
#include "../include/Registry.h"
#include "../include/CreateGroupWindow.h"
#include "../include/CreateKeyWindow.h"
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
    ui->registryTree->addTopLevelItem(root);
    QStringList baseGroups = {
        "HKEY_CLASSES_ROOT",
        "HKEY_CURRENT_USER",
        "HKEY_LOCAL_MACHINE",
        "HKEY_USERS"
    };

    foreach (auto groupName, baseGroups)
    {
        CreateRegistryBranch(groupName);
    }
}

void MainWindow::ConfigureGroupKeysWidget()
{
    ui->groupKeys->setColumnCount(3);
    ui->groupKeys->setHorizontalHeaderLabels(QStringList() << "Key" << "Type" << "Value");
    ui->groupKeys->verticalHeader()->setVisible(false);
    ui->groupKeys->horizontalHeader()->setSectionsClickable(false);
    ui->groupKeys->horizontalHeader()->resizeSection(0, 250);
    ui->groupKeys->horizontalHeader()->resizeSection(1, 250);
    ui->groupKeys->horizontalHeader()->resizeSection(2, 350);
}

void MainWindow::ConfigureCurrentPathWidget(QString path)
{
    ui->currentPath->setText("Computer\\" + path);
}

void MainWindow::ConfigureCreateButtons(QString path)
{
    if (path.isEmpty())
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
    if (!currentItem)
    {
        ui->removeKeyAction->setEnabled(false);
    }
    else
    {
        ui->removeKeyAction->setEnabled(true);
    }
}

void MainWindow::CreateRegistryBranch(QString groupName)
{
    QTreeWidgetItem* item = new QTreeWidgetItem(QStringList() << groupName);
    QIcon icon(":/img/group_icon.ico");
    item->setIcon(0, icon);
    ui->registryTree->topLevelItem(0)->addChild(item);
    QSettings settings(groupName, QSettings::NativeFormat);
    registry.ParseRegistryBranch(item, &settings, &icon);
}

void MainWindow::on_registryTree_itemExpanded(QTreeWidgetItem *group)
{
    ui->registryTree->resizeColumnToContents(0);
    QSettings settings(registry.FindPathForGroup(group), QSettings::NativeFormat );
    QIcon icon(":/img/group_icon.ico");
    registry.ParseRegistryBranch(group, &settings, &icon);
    ConfigureRemoveKeyButton();
}

void MainWindow::on_registryTree_itemClicked(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(column);
    auto path = registry.FindPathForGroup(item);
    ConfigureCurrentPathWidget(path);
    ConfigureCreateButtons(path);
    ConfigureRemoveKeyButton();
    QList<QTableWidgetItem*> valuesTypes;
    auto keysAndValues = registry.CreateGroupKeys(item, valuesTypes);
    QMap<QString, QString>::const_iterator iterator = keysAndValues.constBegin();
    ui->groupKeys->setRowCount(keysAndValues.size());
    int rowIndex = 0;
    while (iterator != keysAndValues.constEnd())
    {
        auto* keyItem = new QTableWidgetItem(iterator.key());
        keyItem->setFlags(keyItem->flags() & ~Qt::ItemIsEditable);
        ui->groupKeys->setItem(rowIndex, 0, keyItem);
        valuesTypes[rowIndex]->setFlags(valuesTypes[rowIndex]->flags() & ~Qt::ItemIsEditable);
        ui->groupKeys->setItem(rowIndex, 1, valuesTypes[rowIndex]);
        auto* valueItem = new QTableWidgetItem(iterator.value());
        valueItem->setFlags(valueItem->flags() & ~Qt::ItemIsEditable);
        ui->groupKeys->setItem(rowIndex, 2, valueItem);
        iterator++;
        rowIndex++;
    }
}

void MainWindow::on_currentPath_returnPressed()
{
    auto group = registry.FindGroupByPath(ui->currentPath->text(), ui->registryTree->topLevelItem(0));
    if (!group)
    {
        QMessageBox::warning(this, "", "Couldn't find this group! Check if the path is correct!");
        return;
    }

    ui->registryTree->setCurrentItem(group);
    emit(ui->registryTree->itemClicked(group, 0));
}

void MainWindow::on_createKeyAction_triggered()
{
    ConfigureRemoveKeyButton();
    CreateKeyWindow createKeyWindow(this);
    createKeyWindow.show();
    createKeyWindow.exec();
    auto currentItem = ui->registryTree->currentItem();
    auto path = registry.FindPathForGroup(currentItem);
    QSettings settings(path, QSettings::NativeFormat);
    settings.setValue(createKeyWindow.GetKeyName(), createKeyWindow.GetKeyValue());
    on_registryTree_itemClicked(currentItem, 0);
}

void MainWindow::on_groupKeys_itemClicked(QTableWidgetItem *item)
{
    ConfigureRemoveKeyButton(item);
}


void MainWindow::on_removeKeyAction_triggered()
{
    auto keyName = ui->groupKeys->selectedItems()[0]->text();
    auto currentGroup = ui->registryTree->currentItem();
    auto groupName = registry.FindPathForGroup(currentGroup);
    QSettings settings(groupName, QSettings::NativeFormat);
    settings.remove(keyName);
    on_registryTree_itemClicked(currentGroup, 0);
}


void MainWindow::on_createGroupAction_triggered()
{
    CreateGroupWindow createGroupWindow(registry.FindPathForGroup(ui->registryTree->currentItem()), this);
    createGroupWindow.show();
    createGroupWindow.exec();
//    auto pathElements = ui->currentPath->text().split("\\");
//    CreateRegistryBranch(pathElements[1]);
//    auto currentPath = ui->currentPath->text() + "\\" + createGroupWindow.GetGroupName();
//    ui->currentPath->setText(currentPath);
//    auto* group = registry.FindGroupByPath(currentPath, ui->registryTree->topLevelItem(0));
//    ui->registryTree->setCurrentItem(group);
//    emit(ui->registryTree->itemClicked(group, 0));

    /*
    при создании раздела открывать его, менять путь в меню поиска
    */

    on_registryTree_itemExpanded(ui->registryTree->currentItem());
}


void MainWindow::on_removeGroupAction_triggered()
{
    auto currentPath = registry.FindPathForGroup(ui->registryTree->currentItem());
    auto currentPathElements = currentPath.split("\\");
    QString baseGroupName = currentPathElements[0];
    HKEY baseGroup = registry.GetGroupHkeyByName(baseGroupName);
    currentPathElements.pop_front();
    currentPath = currentPathElements.join("\\");
    if (RegDeleteKeyEx(baseGroup, (wchar_t*)currentPath.utf16(), KEY_WOW64_64KEY, 0) != ERROR_SUCCESS)
    {
        QMessageBox::warning(this, "Warning!", "Coludn't delete this group!");
        return;
    }

    currentPathElements.pop_back();
    currentPathElements.push_front(baseGroupName);
    currentPathElements.push_front("Computer");
    for (int i = 0; i < ui->registryTree->topLevelItem(0)->childCount(); i++)
    {
        auto baseGroup = ui->registryTree->topLevelItem(0)->child(i);
        if (baseGroup->text(0) == baseGroupName)
        {
            delete baseGroup;
            CreateRegistryBranch(baseGroupName);
            break;
        }
    }

    ui->currentPath->setText(currentPathElements.join("\\"));

    /*
    при удалении раздела открыть родительский раздел
    */
}

