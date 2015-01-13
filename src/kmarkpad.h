#ifndef KMARKVIEW_H
#define KMARKVIEW_H

#include <KTextEditor/View>
#include <KTextEditor/Document>
#include <KWebView>
#include <QSplitter>
#include <QHBoxLayout>

class KMarkPad : public QWidget
{
    Q_OBJECT
    
public:
    KMarkPad(QWidget *parent = 0);
    virtual ~KMarkPad();
    KWebView *getPreviewer();
    void unpreview();
    
    KTextEditor::Document *note;
    KTextEditor::View *editor;
 
public slots:
    void preview(bool livePreview = true);
    
private:
    QSplitter *hs;
    QHBoxLayout *hl;
    KWebView *previewer;
    bool m_livePreview;
    
private slots:
    void updatePreviewer();
};

#endif
