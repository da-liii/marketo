#ifndef NOTEVIEW_H
#define NOTEVIEW_H

#include "kmarkpad.h"

#include <QVBoxLayout>
#include <KLineEdit>
#include <KTextEditor/Document>

class NoteView : public QWidget
{
    Q_OBJECT
public:
    KMarkPad *markPad;
    KTextEditor::Document *note;
    
    NoteView(QWidget *parent);
    virtual ~NoteView();
    void hideTitleLine();
    void showTitleLine();
    void setTitle(const QString& titleOfNote);
    
private:
    QVBoxLayout *vl;
    QHBoxLayout *hl;
    
    KLineEdit *title;
    
    void setupUI();
    void setupConnect();
    
private slots:
    void saveNote(QString name);
};

#endif