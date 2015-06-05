#ifndef NOTEVIEW_H
#define NOTEVIEW_H

#include "kmarkpad.h"
class QVBoxLayout;
class KLineEdit;
class KUrl;
class KAction;
class QUrl;

class NoteView : public QWidget
{
    Q_OBJECT
public:
    KMarkPad *markPad;
    KTextEditor::Document *note;
    
    NoteView(QWidget *parent, KAction *pAction);
    virtual ~NoteView();
    void hideTitleLine();
    void showTitleLine();
    void setTitle(const QString& titleOfNote);
    void openUrl(const KUrl& url);
    void focusTitle();
    
public slots:
    void openUrl(const QUrl& url);
    void slotOpen(const QUrl& url);
    
private:
    QVBoxLayout *vl;
    QHBoxLayout *hl;
    KAction *previewAction;
    KLineEdit *title;
    
    void setupUI();
    void setupConnect();
    
private slots:
    void saveNote(QString name);
};

#endif