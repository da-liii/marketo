#ifndef KMARKVIEW_H
#define KMARKVIEW_H

#include "htmlgenerator.h"

#include <QWidget>
class KWebView;

class QHBoxLayout;
class QSplitter;
class QUrl;
namespace KTextEditor {
    class View;
    class Document;
    class Cursor;
    class Editor;
};

class KMarkPad : public QWidget
{
    Q_OBJECT
    
public:
    KMarkPad(QWidget *parent = 0);
    virtual ~KMarkPad();
    KWebView *getPreviewer();
    void unpreview();
    KTextEditor::View* view();
    KTextEditor::Document *m_note;
    KTextEditor::View *m_editor;
    void setPreview(bool checked);
    void setSplit(bool checked);
 
public slots:
    void preview(bool livePreview);
    void preview();
    void generateHtml();
    
private:
    QSplitter *hs;
    QHBoxLayout *hl;
    KWebView *m_previewer;
    bool m_livePreview;
    KTextEditor::Editor *m_new_editor;
    HTMLGenerator *m_generator;
    
private slots:
    void updatePreviewer();
    void updatePreviewerByCursor(KTextEditor::View *a_editor, const KTextEditor::Cursor& a_cursor);
};

#endif
