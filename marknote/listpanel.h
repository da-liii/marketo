#ifndef LISTPANEL_H
#define LISTPANEL_H

#include "panel.h"

class QListView;
class QFileSystemModel;
class QVBoxLayout;
class QModelIndex;
class QContextMenuEvent;

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
    QWidget *m_parent;
    
private slots:
    void setUrlFromIndex(const QModelIndex& index);
    
protected:
    virtual bool urlChanged();
    virtual void contextMenuEvent(QContextMenuEvent *event);
};

#endif