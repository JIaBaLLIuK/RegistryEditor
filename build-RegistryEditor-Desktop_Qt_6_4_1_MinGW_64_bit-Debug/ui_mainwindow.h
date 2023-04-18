/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *removeKeyAction;
    QAction *removeGroupAction;
    QAction *createKeyAction;
    QAction *createGroupAction;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QLineEdit *currentPath;
    QHBoxLayout *horizontalLayout;
    QTreeWidget *registryTree;
    QTableWidget *groupKeys;
    QMenuBar *menubar;
    QMenu *menuEdit;
    QMenu *menuCreate;
    QMenu *menuRemove;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        removeKeyAction = new QAction(MainWindow);
        removeKeyAction->setObjectName("removeKeyAction");
        removeGroupAction = new QAction(MainWindow);
        removeGroupAction->setObjectName("removeGroupAction");
        createKeyAction = new QAction(MainWindow);
        createKeyAction->setObjectName("createKeyAction");
        createGroupAction = new QAction(MainWindow);
        createGroupAction->setObjectName("createGroupAction");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        currentPath = new QLineEdit(centralwidget);
        currentPath->setObjectName("currentPath");

        gridLayout->addWidget(currentPath, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        registryTree = new QTreeWidget(centralwidget);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        registryTree->setHeaderItem(__qtreewidgetitem);
        registryTree->setObjectName("registryTree");
        registryTree->setMinimumSize(QSize(350, 0));
        registryTree->setMaximumSize(QSize(350, 16777215));
        registryTree->setHeaderHidden(true);

        horizontalLayout->addWidget(registryTree);

        groupKeys = new QTableWidget(centralwidget);
        groupKeys->setObjectName("groupKeys");
        groupKeys->setSelectionBehavior(QAbstractItemView::SelectRows);

        horizontalLayout->addWidget(groupKeys);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
        menuEdit = new QMenu(menubar);
        menuEdit->setObjectName("menuEdit");
        menuCreate = new QMenu(menuEdit);
        menuCreate->setObjectName("menuCreate");
        menuRemove = new QMenu(menuEdit);
        menuRemove->setObjectName("menuRemove");
        MainWindow->setMenuBar(menubar);

        menubar->addAction(menuEdit->menuAction());
        menuEdit->addAction(menuCreate->menuAction());
        menuEdit->addAction(menuRemove->menuAction());
        menuCreate->addAction(createKeyAction);
        menuCreate->addAction(createGroupAction);
        menuRemove->addAction(removeKeyAction);
        menuRemove->addAction(removeGroupAction);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        removeKeyAction->setText(QCoreApplication::translate("MainWindow", "Key", nullptr));
        removeGroupAction->setText(QCoreApplication::translate("MainWindow", "Group", nullptr));
        createKeyAction->setText(QCoreApplication::translate("MainWindow", "Key", nullptr));
        createGroupAction->setText(QCoreApplication::translate("MainWindow", "Group", nullptr));
        menuEdit->setTitle(QCoreApplication::translate("MainWindow", "Edit", nullptr));
        menuCreate->setTitle(QCoreApplication::translate("MainWindow", "Create", nullptr));
        menuRemove->setTitle(QCoreApplication::translate("MainWindow", "Remove", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
