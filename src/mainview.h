#ifndef MAINVIEW_H
#define MAINVIEW_H

#include "kmarkview.h"
#include "noteview.h"
#include "terminalview.h"

#include <QVariant>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QHeaderView>
#include <QListView>
#include <QSplitter>
#include <QTreeView>
#include <QVBoxLayout>
#include <QWidget>
#include <QFileSystemModel>

#include <KWebView>
#include <KTextEditor/View>
#include <KTextEditor/Document>
#include <KDE/KLineEdit>
#include <KUrl>
#include <KAction>

class MainView : public QWidget
{
    Q_OBJECT
    
public:
    KMarkView *markView;
    KTextEditor::Document *note;
    MainView(QWidget *parent = 0, KAction *pAction = 0);
    virtual ~MainView();    
    KTextEditor::View *getEditor();
    bool preview();
    bool unpreview();
    void openUrl(KUrl url);
    void newNote();
    void setupConnect();
    void setupUI();
    
private:
    QVBoxLayout *verticalLayout;
    QSplitter *vsplitter;
    QSplitter *hsplitter;
    TerminalView *terminal;
    QListView *listView;
    QTreeView *treeView;
    QFileSystemModel *lmodel;
    QFileSystemModel *tmodel;
    
    KTextEditor::View *editor;
    NoteView *noteView;
    KAction *previewAction;
    int column;

private slots:
    void gotoDir(const QModelIndex &index);
    void oneColView();
    void twoColView();
    void threeColView();
    void open(const QModelIndex &index);
    void showReadme(const QModelIndex &index);
    void toggleTerminal();
};

#endif // MAINVIEW_H