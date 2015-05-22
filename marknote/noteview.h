#ifndef NOTEVIEW_H
#define NOTEVIEW_H

#include "kmarkpad.h"
class QVBoxLayout;
class KLineEdit;

class QAction;
class QUrl;

class NoteView : public QWidget
{
    Q_OBJECT
public:
    KMarkPad *markPad;
    KTextEditor::Document *note;
    
    NoteView(QWidget *parent, QAction *pAction);
    virtual ~NoteView();
    void hideTitleLine();
    void showTitleLine();
    void setTitle(const QString& titleOfNote);
    void focusTitle();
    void openUrl(const QUrl& url);
    
public slots:
    void slotOpen(const QUrl& url);
    
private:
    QVBoxLayout *vl;
    QHBoxLayout *hl;
    QAction *previewAction;
    KLineEdit *title;
    
    void setupUI();
    void setupConnect();
    
private slots:
    void saveNote(QString name);
};

#endif