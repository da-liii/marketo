#ifndef KMARKVIEW_H
#define KMARKVIEW_H

#include <KTextEditor/View>
#include <KTextEditor/Document>
#include <KWebView>
#include <QSplitter>
#include <QHBoxLayout>

class KMarkView : public QWidget
{
    Q_OBJECT
    
public:
    KMarkView(QWidget *parent = 0);
    virtual ~KMarkView();
    
    KTextEditor::View *getEditor();
    KTextEditor::Document *getNote();
    KWebView *getPreviewer();
    void unpreview();

public slots:
    void preview(bool livePreview = true);
    
private:
    QSplitter *hs;
    QHBoxLayout *hl;
    KWebView *previewer;
    KTextEditor::View *editor;
    KTextEditor::Document *note;
    bool m_livePreview;
    
private slots:
    void updatePreviewer();
};

#endif
