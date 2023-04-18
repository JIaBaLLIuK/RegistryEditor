/********************************************************************************
** Form generated from reading UI file 'CreateKeyWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATEKEYWINDOW_H
#define UI_CREATEKEYWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CreateKeyWindow
{
public:
    QRadioButton *stringKey;
    QRadioButton *intKey;
    QRadioButton *longKey;
    QLabel *chooseKeyLabel;
    QFrame *line;
    QLabel *inputDataRequestLabel;
    QLabel *inputNameLabel;
    QLabel *inputValueLabel;
    QLineEdit *inputNameLineEdit;
    QLineEdit *inputValueLineEdit;
    QPushButton *okButton;

    void setupUi(QWidget *CreateKeyWindow)
    {
        if (CreateKeyWindow->objectName().isEmpty())
            CreateKeyWindow->setObjectName("CreateKeyWindow");
        CreateKeyWindow->resize(400, 230);
        stringKey = new QRadioButton(CreateKeyWindow);
        stringKey->setObjectName("stringKey");
        stringKey->setGeometry(QRect(5, 30, 400, 25));
        QFont font;
        font.setPointSize(10);
        stringKey->setFont(font);
        intKey = new QRadioButton(CreateKeyWindow);
        intKey->setObjectName("intKey");
        intKey->setGeometry(QRect(5, 55, 400, 25));
        intKey->setFont(font);
        longKey = new QRadioButton(CreateKeyWindow);
        longKey->setObjectName("longKey");
        longKey->setGeometry(QRect(5, 80, 400, 25));
        longKey->setFont(font);
        chooseKeyLabel = new QLabel(CreateKeyWindow);
        chooseKeyLabel->setObjectName("chooseKeyLabel");
        chooseKeyLabel->setGeometry(QRect(5, 5, 400, 25));
        chooseKeyLabel->setFont(font);
        line = new QFrame(CreateKeyWindow);
        line->setObjectName("line");
        line->setGeometry(QRect(0, 107, 400, 3));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        inputDataRequestLabel = new QLabel(CreateKeyWindow);
        inputDataRequestLabel->setObjectName("inputDataRequestLabel");
        inputDataRequestLabel->setGeometry(QRect(5, 110, 400, 25));
        inputDataRequestLabel->setFont(font);
        inputNameLabel = new QLabel(CreateKeyWindow);
        inputNameLabel->setObjectName("inputNameLabel");
        inputNameLabel->setGeometry(QRect(5, 135, 45, 25));
        inputNameLabel->setFont(font);
        inputValueLabel = new QLabel(CreateKeyWindow);
        inputValueLabel->setObjectName("inputValueLabel");
        inputValueLabel->setGeometry(QRect(5, 160, 45, 25));
        inputValueLabel->setFont(font);
        inputNameLineEdit = new QLineEdit(CreateKeyWindow);
        inputNameLineEdit->setObjectName("inputNameLineEdit");
        inputNameLineEdit->setGeometry(QRect(50, 135, 340, 22));
        inputValueLineEdit = new QLineEdit(CreateKeyWindow);
        inputValueLineEdit->setObjectName("inputValueLineEdit");
        inputValueLineEdit->setGeometry(QRect(50, 160, 340, 22));
        okButton = new QPushButton(CreateKeyWindow);
        okButton->setObjectName("okButton");
        okButton->setGeometry(QRect(330, 190, 60, 25));

        retranslateUi(CreateKeyWindow);

        QMetaObject::connectSlotsByName(CreateKeyWindow);
    } // setupUi

    void retranslateUi(QWidget *CreateKeyWindow)
    {
        CreateKeyWindow->setWindowTitle(QCoreApplication::translate("CreateKeyWindow", "Form", nullptr));
        stringKey->setText(QCoreApplication::translate("CreateKeyWindow", "REG_SZ key", nullptr));
        intKey->setText(QCoreApplication::translate("CreateKeyWindow", "DWORD key (32 bits)", nullptr));
        longKey->setText(QCoreApplication::translate("CreateKeyWindow", "QWORD key (64 bits)", nullptr));
        chooseKeyLabel->setText(QCoreApplication::translate("CreateKeyWindow", "Choose key type:", nullptr));
        inputDataRequestLabel->setText(QCoreApplication::translate("CreateKeyWindow", "Input key's name and value:", nullptr));
        inputNameLabel->setText(QCoreApplication::translate("CreateKeyWindow", "Name:", nullptr));
        inputValueLabel->setText(QCoreApplication::translate("CreateKeyWindow", "Value:", nullptr));
        okButton->setText(QCoreApplication::translate("CreateKeyWindow", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CreateKeyWindow: public Ui_CreateKeyWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATEKEYWINDOW_H
