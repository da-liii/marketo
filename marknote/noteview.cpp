#include "noteview.h"
#include <QDir>
#include <KUrl>
#include <KTextEditor/Document>
#include <KTextEditor/View>
#include <QVBoxLayout>
#include <KLineEdit>

NoteView::NoteView(QWidget* parent)
    : QWidget(parent)
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
    KUrl url;
    
    note->documentSave();
    url = note->url().directory().append("/").append(name);
    
    QDir dir(url.directory());
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

void NoteView::openUrl(KUrl url)
{
    // TODO:if the url is not in the watching dir and is in three column view
    // switch to one column view
    title->setText(url.fileName());
    note->openUrl(url);
}

void NoteView::focusTitle()
{
    title->setFocus();
}

NoteView::~NoteView()
{

}

#include "noteview.moc"