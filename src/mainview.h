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
#include <QFileSystemModel>

#include <KWebView>
#include <KTextEditor/View>
#include <KTextEditor/Document>
#include <KDE/KLineEdit>

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
    KTextEditor::Document *note;
    QVBoxLayout *vl2;
    KLineEdit *title;
    QWidget *fulleditor;

    MainView(QWidget *parent = 0);
    virtual ~MainView();
private slots:
    void gotoDir(const QModelIndex &index);
};

#endif // MAINVIEW_H