#include "listpanel.h"
// #include "kmarknote_generalsettings.h"

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

#include <KMessageBox>

#include <QUrl>

ListPanel::ListPanel(QWidget* parent)
    : Panel(parent),
    m_parent(parent)
{
    m_pos = QPoint(0, 0);
    lmodel = new QFileSystemModel; 
    //lmodel->setRootPath(GeneralSettings::noteDir());
    lmodel->setRootPath(QString("/home/sadhen/Note"));
    lmodel->setFilter(QDir::Files);
    
    m_filters << "*.md" << "*.markdown";
    lmodel->setNameFilters(m_filters);
    lmodel->setNameFilterDisables(false);
    
    listView = new QListView(this);
    listView->setModel(lmodel);
    //listView->setRootIndex(lmodel->index(GeneralSettings::noteDir()));
    listView->setRootIndex(lmodel->index(QString("/home/sadhen/Note")));
    listView->setGridSize(QSize(listView->sizeHint().width(), 34));
    listView->setIconSize(QSize(listView->sizeHint().width(), 34));
    listView->setAlternatingRowColors(true);
    listView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(listView, SIGNAL(clicked(QModelIndex)),
        this, SLOT(setUrlFromIndex(QModelIndex)));
    connect(listView, SIGNAL(customContextMenuRequested(const QPoint&)),
        this, SLOT(showContextMenu(const QPoint&)));
    
   
    vl = new QVBoxLayout(this);
    vl->addWidget(listView);
}

void ListPanel::setUrlFromIndex(const QModelIndex& index)
{
    setUrl(QUrl::fromLocalFile(lmodel->filePath(index)));
}

bool ListPanel::urlChanged()
{
    if (QFileInfo(url().toLocalFile()).isDir()) {
        lmodel->setRootPath(url().path());
        lmodel->setNameFilters(m_filters);
        listView->setRootIndex(lmodel->index(url().path()));
    }
    emit changeUrl(url());
    return true;
}

void ListPanel::showContextMenu(const QPoint& pos)
{
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
    QString file(lmodel->filePath(index));
    
    if (!file.isEmpty() && !QFile::remove(lmodel->filePath(index))) {
        QMessageBox message;
        message.setText(QString("Fail to delete") + file);
        message.exec();
    }
}

void ListPanel::copyNoteLink()
{
    QModelIndex index = listView->indexAt(m_pos);
    QString file(lmodel->filePath(index));
    QUrl url(file);
    
    QClipboard *clipBoard = QApplication::clipboard();
    clipBoard->clear();
    clipBoard->setText("["+url.fileName()+"]("+file.replace(" ", "%20")+")");
}

ListPanel::~ListPanel()
{

}

#include "listpanel.moc"