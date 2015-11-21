#include "iconfilter.h"

#include <QIcon>
#include <QFileInfo>
#include <QDebug>

QIcon IconFilter::icon(IconType type) const
{
    switch (type) {
    case QFileIconProvider::Folder:
        return QIcon::fromTheme(QLatin1String("folder-blue"));
    case QFileIconProvider::File:
        return QIcon::fromTheme(QLatin1String("text-markdown"));
    default:
        return QIcon::fromTheme(QLatin1String("text-markdown"));
    }
}

QIcon IconFilter::icon(const QFileInfo &info) const
{
    return QIcon::fromTheme(type(info).toLatin1());
}

QString IconFilter::type(const QFileInfo &info) const
{
    if (info.isDir())
        return QString("folder-blue");
    if (info.suffix().isEmpty())
        return QString("text-plain");
    // TODO: using a global mime dict
    return QString("text-markdown");
}

IconFilter::~IconFilter()
{
}
