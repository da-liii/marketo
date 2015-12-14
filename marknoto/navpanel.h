#ifndef NAVPANEL_H
#define NAVPANEL_H

#include "panel.h"
#include <QList>

class QFileSystemModel;
class QTreeView;
class QVBoxLayout;
class QModelIndex;
class QItemSelection;
class QItemSelectionModel;
class QContextMenuEvent;
class QTabWidget;
class QTreeWidget;
class QUrl;
class QStringList;

class Navigator : public Panel
{
    Q_OBJECT
    
public:
    Navigator(Panel *parent=0);
    virtual ~Navigator();
    void buildTagStaffs();
    
private:
    Panel *m_parent;
    QTreeView *treeView;
    QTabWidget *tabWidget;
    QTreeWidget *tagTree;
    QFileSystemModel *tmodel;
    QStringList *tagRoots;
    QList<QUrl> *tagPaths;
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