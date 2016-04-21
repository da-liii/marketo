#ifndef KMARKVIEW_H
#define KMARKVIEW_H

#include "htmlgenerator.h"
#include "document.h"

#include <QWidget>
#include <QThread>
#include <QTimer>
class QWebEngineView;

class QHBoxLayout;
class QSplitter;
class QUrl;
class WebPage;
namespace KTextEditor {
    class View;
    class Document;
    class Cursor;
    class Editor;
};

class Markpado : public QWidget
{
    Q_OBJECT
    
public:
    Markpado(QWidget *parent = 0);
    virtual ~Markpado();
    void unpreview();
    KTextEditor::View* view();
    KTextEditor::Document *m_note;
    KTextEditor::View *m_editor;
    void setPreview(bool checked);
    void setSplit(bool checked);
 
signals:
    void stop();
    
public slots:
    void preview(bool livePreview);
    void preview();
    
private:
    QSplitter *hs;
    QHBoxLayout *hl;
    QWebEngineView *m_previewer;
    WebPage *m_page;
    bool m_livePreview;
    KTextEditor::Editor *m_new_editor;
    HTMLGenerator *m_generator;
    Document m_content;
    
private slots:
    void updatePreviewer();
    void updatePreviewerByCursor(KTextEditor::View *a_editor, const KTextEditor::Cursor& a_cursor);
    void onSavedOrUploaded(KTextEditor::Document *document, bool saveAs);
    void generateHtml();
};

#endif
