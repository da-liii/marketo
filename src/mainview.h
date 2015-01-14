#ifndef MAINVIEW_H
#define MAINVIEW_H

#include "noteview.h"
#include "terminalview.h"

#include <KTextEditor/View>
#include <KTextEditor/Document>
#include <QWidget>

class KUrl;
class KAction;
class KWebView;

class QVariant;
class QApplication;
class QListView;
class QSplitter;
class QFileSystemModel;
class QTreeView;
class QModelIndex;

class MainView : public QWidget
{
    Q_OBJECT
    
public:
    KMarkPad *markPad;
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