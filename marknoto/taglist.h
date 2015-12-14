#ifndef TAGLIST_H
#define TAGLIST_H

#include <QListWidget>

class TagList : public QListWidget
{
    Q_OBJECT
public:
    TagList(QWidget *parent);
    ~TagList();
    QString tagText(int i) const;
    void stretchWidth();
    void addTags(const QString &);
};

#endif