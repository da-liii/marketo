#ifndef KMARKVIEW_H
#define KMARKVIEW_H

#include <KWebView>
#include <QSplitter>
#include <QHBoxLayout>

namespace KTextEditor {
    class View;
    class Document;
    class Cursor;
}
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
    void updatePreviewerByCursor(KTextEditor::View *a_editor, const KTextEditor::Cursor& a_cursor);
};

#endif
