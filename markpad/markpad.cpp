#include "markpad.h"
#include "htmlgenerator.h"

#include <string>
#include <iostream>
#include <sstream>

#include <KDE/KLocale>
#include <KTextEditor/Editor>
#include <KTextEditor/EditorChooser>
#include <KTextEditor/View>
#include <KTextEditor/Document>
#include <KTextEditor/Cursor>
#include <KMessageBox>
#include <KComponentData>
#include <KStandardDirs>
#include <KWebView>

#include <QtGlobal>
#include <QSplitter>
#include <QHBoxLayout>
#include <QTimer>
#include <QList>
#include <QDir>
#include <QWebFrame>
#include <QWebPage>
#include <Qt>

using std::string;

MarkPad::MarkPad(QWidget *parent)
    : QWidget(parent)
    , m_generator(new HTMLGenerator)
{
    hl = new QHBoxLayout(this);
    hl->setMargin(0);
    
    hs = new QSplitter(this);
    
    m_previewer = new KWebView(this);
    m_livePreview = false;
    m_previewer->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);
    connect(m_previewer, SIGNAL(linkClicked(const QUrl&)), parent, SLOT(slotOpen(const QUrl&)));
    
    m_new_editor = KTextEditor::EditorChooser::editor();
    if (!m_new_editor) {
        KMessageBox::error(this, i18n("A KDE text-editor component could not be found;\n"
                                      "please check your KDE installation."));
        m_note = 0;
    } else {
        m_note = m_new_editor->createDocument(0);
        m_editor = qobject_cast<KTextEditor::View*>(m_note->createView(this));
    }
    hs->addWidget(m_editor);
    hs->addWidget(m_previewer);
    hl->addWidget(hs);
    
    QList<int> sizeList;
    sizeList << 400 << 400;
    hs->setSizes(sizeList);
    
    setPreview(false);
    setSplit(false);
    
    connect(m_note, SIGNAL(textChanged(KTextEditor::Document *)), 
            this, SLOT(updatePreviewer()));
    connect(m_note, SIGNAL(urlChanged(KUrl)),
        this, SLOT(updatePreviewer()));
    connect(m_editor, SIGNAL(cursorPositionChanged(KTextEditor::View *,const KTextEditor::Cursor&)),
            this, SLOT(updatePreviewerByCursor(KTextEditor::View *, const KTextEditor::Cursor&)));
}

void MarkPad::preview(bool livePreview)
{
    m_livePreview = livePreview;
    preview();
}

void MarkPad::generateHtml()
{
    string html;
    KComponentData data(KGlobal::mainComponent());
    
    html = m_generator->generated(string(m_note->text().toUtf8().constData()));
    
    QString content = QString::fromUtf8(html.c_str());
    content = QString("<html>") + QString("<head>")
        + QString("<link href=\"file://") 
        + data.dirs()->locate("data", "markpad/css/style.css") 
        + QString("\" rel=\"stylesheet\">")
        + QString("</head>") + QString("<body>")
        + content + QString("</body>")
        + QString("</html>");
    m_previewer->setHtml(content, QUrl());
}

void MarkPad::preview()
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

void MarkPad::unpreview()
{
    m_editor->setHidden(false);
    m_previewer->setHidden(true);
    m_livePreview = false;
    
    setFocusProxy(m_editor);
}

void MarkPad::updatePreviewer()
{
    QTimer::singleShot(100, this, SLOT(generateHtml()));
}

void MarkPad::updatePreviewerByCursor(KTextEditor::View *editor, const KTextEditor::Cursor& cursor)
{
    Q_UNUSED(editor);
    int sourceTotal = m_note->lines();
    int sourceCur = cursor.line();
    int targetTotal = m_previewer->page()->mainFrame()->scrollBarMaximum(Qt::Vertical);
    int targetCur = sourceCur * targetTotal / sourceTotal;
    int offset = (sourceCur - sourceTotal/2) * 400 / sourceTotal;
    
    m_previewer->page()->mainFrame()->setScrollPosition(QPoint(0, targetCur + offset));
}

void MarkPad::setPreview(bool checked)
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

void MarkPad::setSplit(bool checked)
{
    m_livePreview = checked;
    m_previewer->setHidden(!checked);
    m_editor->setHidden(false);
}

KTextEditor::View* MarkPad::view()
{
    return m_editor;
}

MarkPad::~MarkPad()
{

}

#include "markpad.moc"
