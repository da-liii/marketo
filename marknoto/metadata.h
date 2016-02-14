#ifndef METADATA_H
#define METADATA_H

#include <QMap>
#include <QStringList>

class MetaData {
public:
    MetaData(const QString& filePath);
    virtual ~MetaData();
    
    QStringList tags();
    void parse();
    
private:
    QString filePath;
    QMap<QString, QString> data;
};

#endif