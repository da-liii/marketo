#ifndef NOTEVIEW_H
#define NOTEVIEW_H

#include "markpado.h"

#include <QStack>
#include <Baloo/TagWidget>

class QVBoxLayout;
class QLineEdit;
class KActionCollection;
class QListWidget;
class QLabel;

class QUrl;

class NoteView : public QWidget
{
    Q_OBJECT
public:
    Markpado *markPad;
    KTextEditor::Document *note;
    
    NoteView(QWidget *parent, KActionCollection *pActions);
    virtual ~NoteView();
    void hideTitleLine();
    void showTitleLine();
    void setTitle(const QString& titleOfNote);
    void focusTitle();
    void openUrl(const QUrl& url);
    void forward();
    void backward();
    bool canForward();
    bool canBackward();
    
public slots:
    void slotOpen(const QUrl& url);
    
private:
    KActionCollection *actions;
    QVBoxLayout *vl;
    QHBoxLayout *hl;
    QLineEdit *title;
    QListWidget *tagList;
    QLineEdit *tagEdit;
    QLabel *label;
    QStack<QUrl> *done;
    QStack<QUrl> *todo;
    
    void setupUI();
    void setupConnect();
    void pureOpenUrl(const QUrl& url);
    
private slots:
    void saveNote();
    void addTags();
};

#endif
