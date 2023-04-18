#include "../include/Registry.h"

#include <windows.h>
#include <winreg.h>

void Registry::ParseRegistryBranch(QTreeWidgetItem *registryBranch, QSettings* registryBranchSettings, QIcon* groupIcon)
{
    static int depth = 0;
    static const int MAX_DEPTH = 2;
    depth++;
    if (registryBranch->childCount() > 0)
    {
        for (int i = 0; i < registryBranch->childCount(); i++)
        {
            auto child = registryBranch->child(i);
            if (child->childCount() > 0)
            {
                break;
            }

            registryBranchSettings->beginGroup(child->text(0));
            ParseRegistryBranch(child, registryBranchSettings, groupIcon);
            registryBranchSettings->endGroup();
        }
    }
    else if (depth <= MAX_DEPTH)
    {
        foreach (const auto& childGroup, registryBranchSettings->childGroups())
        {
            auto* childItem = new QTreeWidgetItem(QStringList() << childGroup);
            childItem->setIcon(0, *groupIcon);
            registryBranch->addChild(childItem);
            registryBranchSettings->beginGroup(childGroup);
            ParseRegistryBranch(childItem, registryBranchSettings, groupIcon);
            registryBranchSettings->endGroup();
        }
    }

    depth--;
}

QString Registry::FindPathForGroup(QTreeWidgetItem *group)
{
    QStringList reversedPath;
    for (; group->text(0) != "Computer"; group = group->parent())
    {
        reversedPath.append(group->text(0));
    }

    std::reverse(reversedPath.begin(), reversedPath.end());
    return reversedPath.join(PATH_SEPARATOR);
}

QTreeWidgetItem *Registry::FindGroupByPath(QString pathForGroup, QTreeWidgetItem* registryTreeRoot)
{
    auto pathElements = pathForGroup.split(PATH_SEPARATOR);
    if (pathElements.last() == "")
    {
        pathElements.pop_back();
    }

    if (registryTreeRoot->text(0) != pathElements[0])
    {
        return nullptr;
    }

    pathElements.pop_front();
    foreach (auto pathElement, pathElements)
    {
        for (int i = 0; i < registryTreeRoot->childCount(); i++)
        {
            if (pathElement == registryTreeRoot->child(i)->text(0))
            {
                registryTreeRoot = registryTreeRoot->child(i);
                pathElements.pop_front();
                break;
            }
        }
    }

    if (pathElements.size() > 0)
    {
        return nullptr;
    }

    return registryTreeRoot;
}

QMap<QString, QString> Registry::CreateGroupKeys(QTreeWidgetItem *selectedGroup, QList<QTableWidgetItem*>& valuesTypes)
{
    QString pathToGroup = FindPathForGroup(selectedGroup);
    QSettings selectedGroupSettings(pathToGroup, QSettings::NativeFormat);
    auto childKeys = selectedGroupSettings.childKeys();
    QMap<QString, QString> keysAndValues;
    foreach (auto key, childKeys)
    {
        auto keyValue = selectedGroupSettings.value(key);
        auto typeName = QString::fromUtf8(keyValue.typeName()).toLower();
        if (typeName == "qstringlist")
        {
            keysAndValues[key] = keyValue.toStringList().join(" ");
            valuesTypes.append(new QTableWidgetItem("REG_MULTI_SZ"));
        }
        else if (typeName == "int")
        {
            keysAndValues[key] = QString::number(keyValue.toUInt());
            valuesTypes.append(new QTableWidgetItem("REG_DWORD"));
        }
        else if (typeName == "qlonglong")
        {
            keysAndValues[key] = QString::number(keyValue.toULongLong());
            valuesTypes.append(new QTableWidgetItem("REG_QWORD"));
        }
        else if (typeName == "qstring")
        {
            keysAndValues[key] = keyValue.toString();
            valuesTypes.append(new QTableWidgetItem("REG_SZ"));
        }
        else
        {
            keysAndValues[key] = "Can not display this key's value!";
            valuesTypes.append(new QTableWidgetItem("Unknown type of registry key!"));
        }
    }

    return keysAndValues;
}

HKEY Registry::GetGroupHkeyByName(QString baseGroupName)
{
    if (baseGroupName == "HKEY_CLASSES_ROOT")
    {
        return HKEY_CLASSES_ROOT;
    }
    else if (baseGroupName == "HKEY_CURRENT_USER")
    {
        return HKEY_CURRENT_USER;
    }
    else if (baseGroupName == "HKEY_LOCAL_MACHINE")
    {
        return HKEY_LOCAL_MACHINE;
    }
    else
    {
        return HKEY_USERS;
    }
}