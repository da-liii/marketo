#include "listpanel.h"
#include "iconfilter.h"
#include "listitemdelegate.h"

#include <KMessageBox>
#include <KConfigGroup>
#include <KSharedConfig>

#include <QVBoxLayout>
#include <QListView>
#include <QFileSystemModel>
#include <QModelIndex>
#include <QMenu>
#include <QAction>
#include <QContextMenuEvent>
#include <QApplication>
#include <QClipboard>
#include <QTextDocument>
#include <QDebug>
#include <QUrl>
#include <QStringListModel>
#include <QPainter>
#include <QDir>

ListPanel::ListPanel(QWidget* parent)
    : Panel(parent),
    m_parent(parent),
    displayByTag(false)
{
    KConfigGroup cfg(KSharedConfig::openConfig(), "General Options");
    
    m_pos = QPoint(0, 0);
    lmodel = new QFileSystemModel; 
    lmodel->setRootPath(cfg.readEntry("NoteDir"));
    lmodel->setFilter(QDir::Files);

    m_filters << "*.md" << "*.cm";
    lmodel->setNameFilters(m_filters);
    lmodel->setNameFilterDisables(false);

    smodel = new QStringListModel(QStringList(), this);
    
    listView = new QListView(this);
    listView->setModel(lmodel);
    m_delegate = new ListItemDelegate(this);
    listView->setItemDelegate(m_delegate);
    listView->setRootIndex(lmodel->index(cfg.readEntry("NoteDir")));
    listView->setGridSize(QSize(listView->sizeHint().width(), 26));
    listView->setAlternatingRowColors(true);
    listView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(listView, SIGNAL(clicked(QModelIndex)),
        this, SLOT(setUrlFromIndex(QModelIndex)));
    connect(listView, SIGNAL(customContextMenuRequested(const QPoint&)),
        this, SLOT(showContextMenu(const QPoint&)));
    
    vl = new QVBoxLayout(this);
    vl->addWidget(listView);
}

void ListPanel::setDisplayMode(int index)
{
   displayByTag = (index!=0);
}

void ListPanel::setTaggedList(const QStringList& list)
{
    smodel->setStringList(list);
    listView->setModel(smodel);
    displayByTag = true;
}

void ListPanel::goHome()
{
    displayByTag = false;
    listView->setModel(lmodel);
    lmodel->setRootPath(removeLeadingSlash(url().path()));
    lmodel->setNameFilters(m_filters);
    listView->setRootIndex(lmodel->index(removeLeadingSlash(url().path())));
}

void ListPanel::setUrlForLModel(const QUrl& url)
{
    displayByTag = false;
    setUrl(url.adjusted(QUrl::RemoveFilename));
    listView->scrollTo(lmodel->index(removeLeadingSlash(url.path())));
    listView->setCurrentIndex(lmodel->index(removeLeadingSlash(url.path())));
}

void ListPanel::setUrlFromIndex(const QModelIndex& index)
{
    if (displayByTag) {
        listView->setModel(smodel);    
        KConfigGroup cfg(KSharedConfig::openConfig(), "General Options");
        QString halfPath = smodel->data(index, Qt::DisplayRole).toString();
        halfPath = cfg.readEntry("NoteDir") + halfPath;
        setUrl(QUrl::fromLocalFile(halfPath));
    } else {
        listView->setModel(lmodel);
        setUrl(QUrl::fromLocalFile(lmodel->filePath(index)));
    }
}

QString ListPanel::getTitleByIndex(const QModelIndex& index)
{
    if (displayByTag) {
        QString halfPath = smodel->data(index, Qt::DisplayRole).toString();
        return QUrl::fromLocalFile(halfPath).fileName();
    } else {
        return lmodel->fileName(index);
    }
}

bool ListPanel::urlChanged()
{
    if (displayByTag)
        listView->setModel(smodel);    
    else
        listView->setModel(lmodel);
    if (QFileInfo(url().toLocalFile()).isDir() && !displayByTag) {
        lmodel->setRootPath(removeLeadingSlash(url().path()));
        lmodel->setNameFilters(m_filters);
        listView->setRootIndex(lmodel->index(removeLeadingSlash(url().path())));
    }
    emit changeUrl(url());
    return true;
}

void ListPanel::showContextMenu(const QPoint& pos)
{
    if (displayByTag)
        return;
    m_pos = pos;
    QMenu *contextMenu = new QMenu();
    QAction *newNoteAction = contextMenu->addAction(QString("New Note"));
    QAction *deleteNoteAction = contextMenu->addAction(QString("Delete Note"));
    QAction *copyNoteLinkAction = contextMenu->addAction(QString("Copy Note Link"));
    connect(newNoteAction, SIGNAL(triggered()), m_parent, SLOT(newNote()));
    connect(deleteNoteAction, SIGNAL(triggered()), this, SLOT(deleteNote()));
    connect(copyNoteLinkAction, SIGNAL(triggered()), this, SLOT(copyNoteLink()));
    
    if (contextMenu) {
        contextMenu->exec(QCursor::pos());
    }  
    delete contextMenu;
}

void ListPanel::deleteNote()
{
    QModelIndex index = listView->indexAt(m_pos);
    QString filePath(lmodel->filePath(index));
    
    if (filePath.isEmpty())
        return ;
    
    QFile file(filePath);
    QFileInfo fileInfo(filePath);
    KConfigGroup cfg(KSharedConfig::openConfig(), "General Options");
    QString trashFileName(cfg.readEntry("NoteDir")+"/Trash/"+ fileInfo.fileName());
    if (filePath == trashFileName)
        QFile::remove(filePath);
    else
        file.rename(trashFileName);
}

void ListPanel::copyNoteLink()
{
    QModelIndex index = listView->indexAt(m_pos);
    QString file(lmodel->filePath(index));
    QUrl url(file);
    
    KConfigGroup cfg(KSharedConfig::openConfig(), "General Options");
    QString rootPath(cfg.readEntry("NoteDir"));
    QClipboard *clipBoard = QApplication::clipboard();
    clipBoard->clear();
    clipBoard->setText("[" + url.fileName() + "](" 
                       + QString(url.toEncoded()).midRef(rootPath.length()).toString()
                       + ")");
}

ListPanel::~ListPanel()
{

}

QString ListPanel::removeLeadingSlash(QString path) {
#ifdef UNIX
    return path;
#endif
    return path.right(path.length() - 1);
}

#include "listpanel.moc"
