#ifndef NAVPANEL_H
#define NAVPANEL_H

#include "panel.h"

class QFileSystemModel;
class QTreeView;
class QVBoxLayout;
class QModelIndex;
class QItemSelection;
class QItemSelectionModel;
class QContextMenuEvent;

class Navigator : public Panel
{
    Q_OBJECT
    
public:
    Navigator(Panel *parent=0);
    virtual ~Navigator();
    
private:
    Panel *m_parent;
    QTreeView *treeView;
    QFileSystemModel *tmodel;
    QVBoxLayout *vl;
    QItemSelection *m_selection;
    QItemSelectionModel *m_selectionModel;
    QPoint m_pos;
    
private slots:
    void setUrlFromIndex(const QModelIndex& index);
    void showContextMenu(const QPoint& pos);
    void slotNewDir();
    void slotDeleteDir();
    
protected:
    virtual bool urlChanged();
};
#endif