#ifndef REGISTRY_H
#define REGISTRY_H

#include <QTreeWidget>
#include <QSettings>
#include <QIcon>
#include <QTableWidgetItem>
#include <QMap>
#include <windows.h>
#include <winreg.h>

class Registry
{
public:
    void ParseRegistryBranch(QTreeWidgetItem*, QSettings*, QIcon*);
    QString FindPathForGroup(QTreeWidgetItem*);
    QTreeWidgetItem* FindGroupByPath(QString, QTreeWidgetItem*);
    QMap<QString, QString> CreateGroupKeys(QTreeWidgetItem*, QList<QTableWidgetItem*>&);
    HKEY GetGroupHkeyByName(QString);

private:
    const QString PATH_SEPARATOR = "\\";
};

#endif // REGISTRY_H
