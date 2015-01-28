#ifndef LISTPANEL_H
#define LISTPANEL_H

#include "panel.h"

class QListView;
class QFileSystemModel;
class QVBoxLayout;
class QModelIndex;

class ListPanel : public Panel
{
    Q_OBJECT
    
public:
    ListPanel(QWidget *parent = 0);
    virtual ~ListPanel();
    
private:
    QListView *listView;
    QFileSystemModel *lmodel;
    QVBoxLayout *vl;
    QStringList m_filters;
    
private slots:
    void setUrlFromIndex(const QModelIndex& index);
    
protected:
    virtual bool urlChanged();
};

#endif