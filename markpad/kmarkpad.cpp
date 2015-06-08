#include "kmarkpad.h"
#include "htmlgenerator.h"

#include <string>
#include <iostream>
#include <sstream>

#include <KTextEditor/Editor>
#include <KTextEditor/View>
#include <KTextEditor/Document>
#include <KTextEditor/Cursor>
#include <KMessageBox>
#include <KComponentData>
#include <KStandardDirs>
#include <KWebView>
#include <KGlobal>

#include <QSplitter>
#include <QHBoxLayout>
#include <QTimer>
#include <QList>
#include <QDir>
#include <QWebFrame>
#include <QWebPage>
#include <Qt>

using std::string;

KMarkPad::KMarkPad(QWidget *parent)
    : QWidget(parent)
    , m_generator(new HTMLGenerator)
{
    hl = new QHBoxLayout(this);
    hl->setMargin(0);
    
    hs = new QSplitter(this);
    
    m_previewer = new KWebView(this);
    m_livePreview = false;
    m_previewer->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);
    connect(m_previewer, SIGNAL(linkClicked(const QUrl&)),
            parent, SLOT(slotOpen(const QUrl&)));
    
    m_note = KTextEditor::Editor::instance()->createDocument(0);
    m_editor = qobject_cast<KTextEditor::View*>(m_note->createView(this));
    
    
    hs->addWidget(m_editor);
    hs->addWidget(m_previewer);
    hl->addWidget(hs);
    
    QList<int> sizeList;
    sizeList << 400 << 400;
    hs->setSizes(sizeList);

    setPreview(false);
    setSplit(false);
    
    connect(m_note, &KTextEditor::Document::textChanged, 
            this, &KMarkPad::updatePreviewer);
    connect(m_note, SIGNAL(urlChanged(KUrl)),
            this, SLOT(updatePreviewer()));
    connect(m_editor, &KTextEditor::View::cursorPositionChanged,
            this, &KMarkPad::updatePreviewerByCursor);
}

void KMarkPad::preview(bool livePreview)
{
    m_livePreview = livePreview;
    preview();
}

void KMarkPad::generateHtml()
{
    string html;
    KComponentData data(KGlobal::mainComponent());
    
    html = m_generator->generated(string(m_note->text().toUtf8().constData()));
    
    QString content = QString::fromUtf8(html.c_str());
    content = QString("<html>") + QString("<head>")
        + QString("<link href=\"file://") 
        + KGlobal::dirs()->locate("data", "kmarkpad/css/style.css") 
        + QString("\" rel=\"stylesheet\">")
        + QString("</head>") + QString("<body>")
        + content + QString("</body>")
        + QString("</html>");
    m_previewer->setHtml(content, QUrl());
}

void KMarkPad::preview()
{
    if (m_livePreview) {
        m_editor->setHidden(false);
        m_previewer->setHidden(false);
    } else {
        m_editor->setHidden(true);
        m_previewer->setHidden(false);
    }
    
    // scroll to the correct position
    updatePreviewerByCursor(0, m_editor->cursorPosition());
    
    setFocusProxy(m_previewer);
}

void KMarkPad::unpreview()
{
    m_editor->setHidden(false);
    m_previewer->setHidden(true);
    m_livePreview = false;
    
    setFocusProxy(m_editor);
}

void KMarkPad::updatePreviewer()
{
    QTimer::singleShot(100, this, SLOT(generateHtml()));
}

void KMarkPad::updatePreviewerByCursor(KTextEditor::View *editor, const KTextEditor::Cursor& cursor)
{
    Q_UNUSED(editor);
    
    int sourceTotal = m_note->lines();
    int sourceCur = cursor.line();
    int targetTotal = m_previewer->page()->mainFrame()->scrollBarMaximum(Qt::Vertical);
    int targetCur = sourceCur * targetTotal / sourceTotal;
    int offset = (sourceCur - sourceTotal/2) * 400 / sourceTotal;
    
    m_previewer->page()->mainFrame()->setScrollPosition(QPoint(0, targetCur + offset));
}

void KMarkPad::setPreview(bool checked)
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

void KMarkPad::setSplit(bool checked)
{
    m_livePreview = checked;
    m_previewer->setHidden(!checked);
    m_editor->setHidden(false);
}

KTextEditor::View* KMarkPad::view()
{
    return m_editor;
}

KMarkPad::~KMarkPad()
{

}

#include "kmarkpad.moc"
