#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QListView>
#include <QtGui/QSplitter>
#include <QtGui/QTreeView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <KWebView>
#include <QFileSystemModel>

namespace KTextEditor {
    class Document;
    class View;
}

class MainView : public QWidget
{
    Q_OBJECT
public:
    QVBoxLayout *verticalLayout;
    QSplitter *splitter;
    QListView *listView;
    QTreeView *treeView;
    KWebView *previewer;
    QFileSystemModel *lmodel;
    QFileSystemModel *tmodel;
    KTextEditor::View *editor;

    MainView(QWidget *parent = 0);
    virtual ~MainView();
private slots:
    void gotoDir(const QModelIndex &index);
};

#endif // MAINVIEW_H