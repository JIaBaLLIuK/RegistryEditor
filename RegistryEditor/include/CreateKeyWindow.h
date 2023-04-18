#ifndef CREATEKEYWINDOW_H
#define CREATEKEYWINDOW_H

#include <QDialog>
#include <QVariant>

namespace Ui {
class CreateKeyWindow;
}

class CreateKeyWindow : public QDialog
{
    Q_OBJECT

public:
    CreateKeyWindow(QWidget *parent = nullptr);
    ~CreateKeyWindow();

    QString GetKeyName() const;
    QVariant GetKeyValue() const;

private slots:
    void on_okButton_clicked();

private:
    void ConfigureWindow();

    QString keyName;
    QVariant keyValue;
    Ui::CreateKeyWindow *ui;
};

#endif
