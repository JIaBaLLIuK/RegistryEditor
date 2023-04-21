/********************************************************************************
** Form generated from reading UI file 'ChangeKeyWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHANGEKEYWINDOW_H
#define UI_CHANGEKEYWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_ChangeKeyWindow
{
public:
    QLabel *nameLabel;
    QLineEdit *nameLineEdit;
    QLabel *valueLabel;
    QLineEdit *valueLineEdit;
    QPushButton *okButton;

    void setupUi(QDialog *ChangeKeyWindow)
    {
        if (ChangeKeyWindow->objectName().isEmpty())
            ChangeKeyWindow->setObjectName("ChangeKeyWindow");
        ChangeKeyWindow->resize(400, 150);
        nameLabel = new QLabel(ChangeKeyWindow);
        nameLabel->setObjectName("nameLabel");
        nameLabel->setGeometry(QRect(5, 5, 75, 25));
        QFont font;
        font.setPointSize(10);
        nameLabel->setFont(font);
        nameLineEdit = new QLineEdit(ChangeKeyWindow);
        nameLineEdit->setObjectName("nameLineEdit");
        nameLineEdit->setGeometry(QRect(5, 30, 390, 22));
        nameLineEdit->setFont(font);
        valueLabel = new QLabel(ChangeKeyWindow);
        valueLabel->setObjectName("valueLabel");
        valueLabel->setGeometry(QRect(5, 55, 75, 25));
        valueLabel->setFont(font);
        valueLineEdit = new QLineEdit(ChangeKeyWindow);
        valueLineEdit->setObjectName("valueLineEdit");
        valueLineEdit->setGeometry(QRect(5, 80, 390, 22));
        valueLineEdit->setFont(font);
        okButton = new QPushButton(ChangeKeyWindow);
        okButton->setObjectName("okButton");
        okButton->setGeometry(QRect(335, 110, 60, 25));

        retranslateUi(ChangeKeyWindow);

        QMetaObject::connectSlotsByName(ChangeKeyWindow);
    } // setupUi

    void retranslateUi(QDialog *ChangeKeyWindow)
    {
        ChangeKeyWindow->setWindowTitle(QCoreApplication::translate("ChangeKeyWindow", "Dialog", nullptr));
        nameLabel->setText(QCoreApplication::translate("ChangeKeyWindow", "Name:", nullptr));
        valueLabel->setText(QCoreApplication::translate("ChangeKeyWindow", "Value:", nullptr));
        okButton->setText(QCoreApplication::translate("ChangeKeyWindow", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChangeKeyWindow: public Ui_ChangeKeyWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHANGEKEYWINDOW_H
