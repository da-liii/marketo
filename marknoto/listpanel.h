#ifndef LISTPANEL_H
#define LISTPANEL_H

#include "panel.h"

class QListView;
class QFileSystemModel;
class QVBoxLayout;
class QModelIndex;
class QContextMenuEvent;
class QPoint;

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
    QPoint m_pos;
    QStringList m_filters;
    QWidget *m_parent;
    
private slots:
    void setUrlFromIndex(const QModelIndex& index);
    void showContextMenu(const QPoint& pos);
    void deleteNote();
    void copyNoteLink();
    
protected:
    virtual bool urlChanged();
};

#endif