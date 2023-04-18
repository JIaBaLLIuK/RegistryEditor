#ifndef CREATEGROUPWINDOW_H
#define CREATEGROUPWINDOW_H

#include <QDialog>

namespace Ui {
class CreateGroupWindow;
}

class CreateGroupWindow : public QDialog
{
    Q_OBJECT

public:
    CreateGroupWindow(QString, QWidget *parent = nullptr);
    ~CreateGroupWindow();
    QString GetGroupName() const;

private slots:
    void on_okButton_clicked();

private:
    void ConfigureWindow();

    QString currentPath;
    QString groupName;
    Ui::CreateGroupWindow *ui;
};

#endif
