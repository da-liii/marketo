#include "kmarkview.h"
#include "markdown.h"

#include <string>
#include <iostream>
#include <sstream>

#include <KDE/KLocale>
#include <KTextEditor/Editor>
#include <KTextEditor/EditorChooser>
#include <KMessageBox>
#include <QTimer>
#include <QList>

KMarkView::KMarkView(QWidget *parent)
    : QWidget(parent)
{
    hl = new QHBoxLayout(this);
    hs = new QSplitter(this);
    previewer = new KWebView(this);
    m_livePreview = false;
    
    // TODO: new_editor should be carefully handled, may memory leak
    KTextEditor::Editor* new_editor = KTextEditor::EditorChooser::editor();
    if (!new_editor) {
        KMessageBox::error(this,  i18n("A KDE text-editor component could not be found;\n"
                                       "please check your KDE installation."));
        note = 0;
    } else {
        note = new_editor->createDocument(0);
        editor = qobject_cast<KTextEditor::View*>(note->createView(this));
    }
    hs->addWidget(previewer);
    hs->addWidget(editor);
    hl->addWidget(hs);
    
    QList<int> sizeList;
    sizeList << 400 << 400;
    hs->setSizes(sizeList);
    
    connect(note, SIGNAL(textChanged(KTextEditor::Document *)), 
        this, SLOT(updatePreviewer())); 
}

KTextEditor::Document* KMarkView::getNote()
{
    return note;
}

KTextEditor::View* KMarkView::getEditor()
{
    return editor;
}

void KMarkView::preview(bool livePreview)
{
    std::stringstream html_ss;
    std::string html;
    markdown::Document processer;
    
    // Markdown rendering
    processer.read(std::string(note->text().toUtf8().constData()));
    processer.write(html_ss);
    html = html_ss.str();
    
    // Preview it
    m_livePreview = livePreview;
    previewer->setHtml(QString::fromUtf8(html.c_str()), QUrl());
    if (livePreview) {
        editor->setHidden(false);
        previewer->setHidden(false);
    } else {
        editor->setHidden(true);
        previewer->setHidden(false);
    }
}

void KMarkView::unpreview()
{
    editor->setHidden(false);
    previewer->setHidden(true);
}

void KMarkView::updatePreviewer()
{
    if (m_livePreview)
        QTimer::singleShot(1000, this, SLOT(preview()));
}

KMarkView::~KMarkView()
{

}
