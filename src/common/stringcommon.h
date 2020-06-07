#ifndef __STRINGCOMMON__H
#define __STRINGCOMMON__H

#include <QFile>
#include <QString>
#include <QStringList>
#include <QTextStream>

QStringList getListFromFile(const QString &f_path)
{
    QFile t_innerSettings(f_path);
    t_innerSettings.open(QIODevice::ReadOnly);
    QStringList r_list;
    r_list << "all" << QTextStream(&t_innerSettings).readAll().split("\n");
    r_list.removeAll("");
    t_innerSettings.close();

    return r_list;
}

#endif // __STRINGCOMMON__H
