#ifndef MAINVIEW_H
#define MAINVIEW_H

#include "noteview.h"
#include "panel.h"

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
class QModelIndex;

class MainView : public Panel 
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
    void setupUI();
    
private:
    QVBoxLayout *verticalLayout;
    QSplitter *vsplitter;
    QSplitter *hsplitter;
    Panel *terminal;
    Panel *navigator;
    Panel *listPanel;
    KAction *previewAction;
    
    KTextEditor::View *editor;
    NoteView *noteView;
    int column;

public slots:
    void newNote();
    
private slots:
    void oneColView();
    void twoColView();
    void threeColView();
    void toggleTerminal();
    
protected:
    virtual bool urlChanged();
};

#endif // MAINVIEW_H