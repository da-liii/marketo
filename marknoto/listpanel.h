#ifndef LISTPANEL_H
#define LISTPANEL_H

#include "panel.h"

class QListView;
class QFileSystemModel;
class QVBoxLayout;
class QModelIndex;
class QContextMenuEvent;
class QPoint;
class QStringListModel;
class ListItemDelegate;

class ListPanel : public Panel
{
    Q_OBJECT
    
public:
    ListPanel(QWidget *parent = 0);
    virtual ~ListPanel();
    void setTaggedList(const QStringList& list);
    QString getTitleByIndex(const QModelIndex& index);
    void setUrlForLModel(const QUrl& url);
    void goHome();
    
private:
    QListView *listView;
    QFileSystemModel *lmodel;
    QStringListModel *smodel;
    QVBoxLayout *vl;
    QPoint m_pos;
    QStringList m_filters;
    QWidget *m_parent;
    ListItemDelegate *m_delegate;
    bool displayByTag;
    
public slots:
    void setDisplayMode(int);
    
private slots:
    void setUrlFromIndex(const QModelIndex& index);
    void showContextMenu(const QPoint& pos);
    void deleteNote();
    void copyNoteLink();
    
protected:
    virtual bool urlChanged();
};

#endif