#ifndef CHANGEKEYWINDOW_H
#define CHANGEKEYWINDOW_H

#include <QDialog>

namespace Ui {
class ChangeKeyWindow;
}

class ChangeKeyWindow : public QDialog
{
    Q_OBJECT

public:
    ChangeKeyWindow(QString, QWidget *parent = nullptr);
    ~ChangeKeyWindow();
    void ConfigureLineEdits();
    QString *GetStringValue() const;
    void SetStringValue(QString *newStringValue);
    uint *GetIntValue() const;
    void SetIntValue(uint *newIntValue);
    qulonglong *GetLongValue() const;
    void SetLongValue(qulonglong *newLongValue);
    QString GetKeyName() const;

private slots:
    void on_okButton_clicked();

private:
    void ConfigureWindow();

    QString* stringValue;
    uint* intValue;
    qulonglong* longValue;
    QString keyName;
    Ui::ChangeKeyWindow *ui;
};

#endif // CHANGEKEYWINDOW_H
