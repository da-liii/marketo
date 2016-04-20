#include "markpado.h"
#include "htmlgenerator.h"

#include <string>
#include <iostream>
#include <sstream>

#include <KTextEditor/Editor>
#include <KTextEditor/View>
#include <KTextEditor/Document>
#include <KTextEditor/Cursor>
#include <KMessageBox>

#include <QSplitter>
#include <QHBoxLayout>
#include <QList>
#include <QDir>
#include <Qt>
#include <QStandardPaths>
#include <QtWebEngineWidgets/QWebEnginePage>
#include <QtWebEngineWidgets/QWebEngineView>
#include <QtWebChannel/QWebChannel>

using std::string;

Markpado::Markpado(QWidget *parent)
    : QWidget(parent)
    , m_generator(new HTMLGenerator)
{
    hl = new QHBoxLayout(this);
    hl->setMargin(0);
    
    hs = new QSplitter(this);
    
    m_previewer = new QWebEngineView(this);
    m_livePreview = false;
    
    QWebChannel *channel = new QWebChannel(this);
    channel->registerObject(QStringLiteral("content"), &m_content);
    m_previewer->page()->setWebChannel(channel);
    m_previewer->setUrl(QUrl("qrc:/index.html"));
    connect(m_previewer, SIGNAL(linkClicked(const QUrl&)),
            parent, SLOT(slotOpen(const QUrl&)));
    
    m_note = KTextEditor::Editor::instance()->createDocument(0);
    m_editor = qobject_cast<KTextEditor::View*>(m_note->createView(this));
    m_editor->setStatusBarEnabled(false);
    m_editor->setFocus(Qt::OtherFocusReason);
    
    hs->addWidget(m_editor);
    hs->addWidget(m_previewer);
    hl->addWidget(hs);
    
    hs->setStretchFactor(0, 16);
    hs->setStretchFactor(1, 10);

    setPreview(false);
    setSplit(false);
    
    connect(m_note, &KTextEditor::Document::textChanged, 
            this, &Markpado::updatePreviewer);
    connect(m_editor, &KTextEditor::View::cursorPositionChanged,
            this, &Markpado::updatePreviewerByCursor);
    connect(m_note, &KTextEditor::Document::documentSavedOrUploaded,
            this, &Markpado::onSavedOrUploaded);
}

void Markpado::onSavedOrUploaded(KTextEditor::Document *document, bool saveAs)
{
    Q_UNUSED(document);
    Q_UNUSED(saveAs);
    m_note->setHighlightingMode("CommonMark");
    generateHtml();
}

void Markpado::preview(bool livePreview)
{
    m_livePreview = livePreview;
    preview();
}


void Markpado::preview()
{
    if (m_livePreview) {
        m_editor->setHidden(false);
        m_previewer->setHidden(false);
    } else {
        m_editor->setHidden(true);
        m_previewer->setHidden(false);
    }
    
    generateHtml();
    // scroll to the correct position
    updatePreviewerByCursor(0, m_editor->cursorPosition());
    
    setFocusProxy(m_previewer);
}

void Markpado::unpreview()
{
    m_editor->setHidden(false);
    m_previewer->setHidden(true);
    m_livePreview = false;
    
    setFocusProxy(m_editor);
}

void Markpado::updatePreviewer()
{
    generateHtml();
}

void Markpado::generateHtml() {
    string html = m_generator->generated(string(m_note->text().toUtf8().constData()));
    m_content.setText(QString::fromUtf8(html.c_str()));
}

void Markpado::updatePreviewerByCursor(KTextEditor::View *editor, const KTextEditor::Cursor& cursor)
{
    Q_UNUSED(editor);
    
    int sourceTotal = m_note->lines();
    int sourceCur = cursor.line();
    int targetCur = sourceCur / sourceTotal;
    int offset = (sourceCur - sourceTotal/2) * 400 / sourceTotal;
    
    const QString ScrollJavaScript("window.scrollTo(0, document.body.scrollHeight * %1 / %2 + %3);");
    m_previewer->page()->runJavaScript(ScrollJavaScript.arg(sourceCur).arg(sourceTotal).arg(offset));
}

void Markpado::setPreview(bool checked)
{
    if (checked) {
        m_editor->setHidden(true);
        m_previewer->setHidden(false);
        preview();
    } else {
        m_editor->setHidden(false);
        m_previewer->setHidden(!m_livePreview);
    }
}

void Markpado::setSplit(bool checked)
{
    m_livePreview = checked;
    m_previewer->setHidden(!checked);
    m_editor->setHidden(false);
}

KTextEditor::View* Markpado::view()
{
    return m_editor;
}

Markpado::~Markpado()
{
}

#include "markpado.moc"
