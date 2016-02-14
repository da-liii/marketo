#include "metadata.h"

#include <QFile>
#include <QTextStream>

MetaData::MetaData(const QString& filePath)
{
    this->filePath = filePath;
    parse();
}

void MetaData::parse()
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QTextStream in(&file);
    QString line = in.readLine();
    if (line!="<!--")
        return;
    while (!in.atEnd() && line!="-->") {
        line = in.readLine();
        QStringList lineSplited = line.split(":");
        if (lineSplited.size() > 1)
            data[lineSplited.at(0)] = lineSplited.at(1);
    }
    file.close();
}

QStringList MetaData::tags()
{
    if (data.contains("tags"))
        return data["tags"].split(",");
    else
        return QStringList();
}

MetaData::~MetaData()
{

}