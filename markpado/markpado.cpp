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
#include <QtWebKitWidgets/QWebView>
#include <QtWebKitWidgets/QWebFrame>

using std::string;

Markpado::Markpado(QWidget *parent)
    : QWidget(parent)
    , m_generator(new HTMLGenerator)
{
    hl = new QHBoxLayout(this);
    hl->setMargin(0);
    
    hs = new QSplitter(this);
    
    m_previewer = new QWebView(this);
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
            this, &Markpado::updatePreviewer);
    connect(m_note, SIGNAL(urlChanged(KUrl)),
            this, SLOT(updatePreviewer()));
    connect(m_editor, &KTextEditor::View::cursorPositionChanged,
            this, &Markpado::updatePreviewerByCursor);
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
        + QString("<link href=\"file://") 
        + QStandardPaths::locate(QStandardPaths::GenericDataLocation, QLatin1String("markpado/css/style.css"))
        + QString("\" rel=\"stylesheet\">")
        + QString("</head>") + QString("<body>")
        + content + QString("</body>")
        + QString("</html>");
    m_previewer->setHtml(content, QUrl());
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
    int targetTotal = m_previewer->page()->mainFrame()->scrollBarMaximum(Qt::Vertical);
    int targetCur = sourceCur * targetTotal / sourceTotal;
    int offset = (sourceCur - sourceTotal/2) * 400 / sourceTotal;
    
    m_previewer->page()->mainFrame()->setScrollPosition(QPoint(0, targetCur + offset));
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
