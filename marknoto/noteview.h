#ifndef NOTEVIEW_H
#define NOTEVIEW_H

#include "markpado.h"

#include <QStack>

class QVBoxLayout;
class QLineEdit;
class KActionCollection;
class QListWidget;
class QLabel;
class TagList;

class QUrl;

class NoteView : public QWidget
{
    Q_OBJECT
public:
    Markpado *markPad;
    KTextEditor::Document *note;
    
    NoteView(QWidget *parent, KActionCollection *pActions);
    virtual ~NoteView();
    void hideMetaData();
    void showMetaData();
    void setTitle(const QString& titleOfNote);
    void focusTitle();
    void openUrl(const QUrl& url);
    void forward();
    void backward();
    bool canForward();
    bool canBackward();
    
signals:
    void tagsAdded(const QStringList &, const QUrl &);
    
public slots:
    void slotOpen(const QUrl& url);
    
private:
    KActionCollection *actions;
    QVBoxLayout *vl;
    QLineEdit *title;
    QStack<QUrl> *done;
    QStack<QUrl> *todo;
    
    void setupUI();
    void setupConnect();
    void pureOpenUrl(const QUrl& url);
    
private slots:
    void saveNote();
};

#endif
