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
#include <QTimer>
#include <QList>
#include <QDir>
#include <Qt>
#include <QStandardPaths>
#include <QtWebEngineWidgets/QWebEnginePage>
#include <QtWebEngineWidgets/QWebEngineView>

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
    //m_previewer->page()->setLinkDelegationPolicy(QWebEnginePage::DelegateAllLinks);
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
    
    // this will make the editor failing to receiving keystrokes, thus commented
    //connect(m_note, &KTextEditor::Document::textChanged, 
    //        this, &Markpado::updatePreviewer);
    connect(m_editor, &KTextEditor::View::cursorPositionChanged,
            this, &Markpado::updatePreviewerByCursor);
    connect(m_note, &KTextEditor::Document::documentSavedOrUploaded,
            this, &Markpado::setCommonMarkMode);

}

void Markpado::setCommonMarkMode(KTextEditor::Document *document, bool saveAs)
{
    Q_UNUSED(document);
    Q_UNUSED(saveAs);
    m_note->setHighlightingMode("CommonMark");
}

void Markpado::preview(bool livePreview)
{
    m_livePreview = livePreview;
    preview();
}

void Markpado::generateHtml()
{
    string html;
    
    html = m_generator->generated(string(m_note->text().toUtf8().constData()));

    QString content = QString::fromUtf8(html.c_str());
    content = QString("<html>") + QString("<head>")
        + QString("<link href=\"qrc:/css/style.css\" rel=\"stylesheet\">") 
	+ QString("<script type='text/x-mathjax-config'>MathJax.Hub.Config({tex2jax: {inlineMath: [['$','$']]}});</script>")
	// for arch
        + QString("<script type='text/javascript' async src='file:///usr/share/mathjax/MathJax.js'></script>")
        + QString("<script type='text/javascript' async src='file:///usr/share/mathjax/config/TeX-AMS-MML_HTMLorMML.js'></script>")
	// for debian
	+ QString("<script type=\"text/javascript\"> if(typeof jQval == 'undefined') {")
        + QString("document.write(unescape(\"%3Cscript src='file:///usr/share/javascript/mathjax/MathJax.js' type='text/javascript'%3E%3C/script%3E\"));")
    	+ QString("document.write(unescape(\"%3Cscript src='file:///usr/share/javascript/mathjax/config/TeX-AMS-MML_HTMLorMML.js' type='text/javascript'%3E%3C/script%3E\"));}</script>")
        + QString("</head>") + QString("<body>")
        + content + QString("</body>")
        + QString("</html>");
    m_previewer->setHtml(content, QUrl(m_note->url()));
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
    QTimer::singleShot(100, this, SLOT(generateHtml()));
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
