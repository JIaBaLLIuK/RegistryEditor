#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidget>

#include "Registry.h"

namespace Ui { class MainWindow; }

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_registryTree_itemExpanded(QTreeWidgetItem *item);
    void on_registryTree_itemClicked(QTreeWidgetItem *item, int column);
    void on_currentPath_returnPressed();
    void on_createKeyAction_triggered();
    void on_groupKeys_itemClicked(QTableWidgetItem *item);
    void on_removeKeyAction_triggered();
    void on_createGroupAction_triggered();
    void on_removeGroupAction_triggered();

private:
    void ConfigureMainWIndow();
    void ConfigureRegistryTreeWidget();
    void ConfigureGroupKeysWidget();
    void ConfigureCurrentPathWidget(QString path = "");
    void ConfigureCreateButtons(QString path = "");
    void ConfigureRemoveKeyButton(QTableWidgetItem* currentItem = nullptr);
    void CreateRegistryBranch(QString);

    Ui::MainWindow *ui;
    Registry registry;
};

#endif
