#include "noteview.h"
#include <QDir>
#include <KUrl>

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
    markView = new KMarkView(this);
    title = new KLineEdit(this);
    note = markView->getNote();
    
    vl->addWidget(title);
    vl->addWidget(markView);
}

void NoteView::saveNote(QString name)
{
    KUrl url;
    
    note->documentSave();
    url = note->url().directory().append("/").append(name);
    
    QDir dir(url.directory());
    dir.rename(note->url().fileName(), url.fileName());
    note->openUrl(url);
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

NoteView::~NoteView()
{

}


#include "noteview.moc"