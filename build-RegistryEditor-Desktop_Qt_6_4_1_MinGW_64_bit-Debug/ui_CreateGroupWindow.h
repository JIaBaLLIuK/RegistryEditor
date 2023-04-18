/********************************************************************************
** Form generated from reading UI file 'CreateGroupWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATEGROUPWINDOW_H
#define UI_CREATEGROUPWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CreateGroupWindow
{
public:
    QLabel *inputNameRequest;
    QLineEdit *inputNameLineEdit;
    QPushButton *okButton;

    void setupUi(QWidget *CreateGroupWindow)
    {
        if (CreateGroupWindow->objectName().isEmpty())
            CreateGroupWindow->setObjectName("CreateGroupWindow");
        CreateGroupWindow->resize(300, 100);
        inputNameRequest = new QLabel(CreateGroupWindow);
        inputNameRequest->setObjectName("inputNameRequest");
        inputNameRequest->setGeometry(QRect(5, 5, 150, 25));
        QFont font;
        font.setPointSize(10);
        inputNameRequest->setFont(font);
        inputNameLineEdit = new QLineEdit(CreateGroupWindow);
        inputNameLineEdit->setObjectName("inputNameLineEdit");
        inputNameLineEdit->setGeometry(QRect(5, 30, 290, 22));
        okButton = new QPushButton(CreateGroupWindow);
        okButton->setObjectName("okButton");
        okButton->setGeometry(QRect(235, 60, 60, 25));

        retranslateUi(CreateGroupWindow);

        QMetaObject::connectSlotsByName(CreateGroupWindow);
    } // setupUi

    void retranslateUi(QWidget *CreateGroupWindow)
    {
        CreateGroupWindow->setWindowTitle(QCoreApplication::translate("CreateGroupWindow", "Form", nullptr));
        inputNameRequest->setText(QCoreApplication::translate("CreateGroupWindow", "Input group's name:", nullptr));
        okButton->setText(QCoreApplication::translate("CreateGroupWindow", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CreateGroupWindow: public Ui_CreateGroupWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATEGROUPWINDOW_H
