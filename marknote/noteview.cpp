#include "noteview.h"
#include <KTextEditor/Document>
#include <KTextEditor/View>
#include <KLineEdit>

#include <QAction>
#include <QDir>
#include <QVBoxLayout>
#include <QUrl>

NoteView::NoteView(QWidget* parent, QAction *pAction)
    : QWidget(parent),
    previewAction(pAction)
{
    setupUI();
    setupConnect();
}

void NoteView::setupConnect()
{
    connect(title, SIGNAL(returnPressed(QString)),
        this, SLOT(saveNote(QString)));
}

void NoteView::setupUI()
{
    vl = new QVBoxLayout(this);
    markPad = new KMarkPad(this);
    title = new KLineEdit(this);
    note = markPad->m_note;
    
    vl->addWidget(title);
    vl->addWidget(markPad);
}

void NoteView::saveNote(QString name)
{
    QUrl url;
    
    note->documentSave();
    url = note->url().toString().append("/").append(name);
    
    qDebug() << url;
    
    QDir dir(url.toString());
    dir.rename(note->url().fileName(), url.fileName());
    note->openUrl(url);
    markPad->view()->setFocus();
}

void NoteView::hideTitleLine()
{
    title->setHidden(true);
}

void NoteView::showTitleLine()
{
    title->setHidden(false);
}

void NoteView::setTitle(const QString& titleOfNote)
{
    title->setText(titleOfNote);
}

void NoteView::openUrl(const QUrl& url)
{
    // TODO:if the url is not in the watching dir and is in three column view
    // switch to one column view
    qDebug() << "NoteView::openUrl " << url;
    title->setText(url.fileName());
    note->openUrl(url);
    if (previewAction->isChecked())
        markPad->preview();
    else
        markPad->unpreview();
}

void NoteView::slotOpen(const QUrl& url)
{
    openUrl(url);
}

void NoteView::focusTitle()
{
    title->setFocus();
}

NoteView::~NoteView()
{

}

#include "noteview.moc"