#include "navpanel.h"
#include "iconfilter.h"

#include <KConfigGroup>
#include <KSharedConfig>

#include <QFileSystemModel>
#include <QItemSelection>
#include <QItemSelectionModel>
#include <QTreeView>
#include <QVBoxLayout>
#include <QModelIndex>
#include <QUrl>
#include <QMenu>
#include <QAction>
#include <QContextMenuEvent>
#include <QMessageBox>
#include <QInputDialog>
#include <QDebug>

Navigator::Navigator(Panel* parent)
    : Panel(parent)
{
    KConfigGroup cfg(KSharedConfig::openConfig(), "General Options");
    m_pos = QPoint(0, 0);
    
    tmodel = new QFileSystemModel;
    tmodel->setRootPath(cfg.readEntry("NoteDir"));
    tmodel->setFilter(QDir::Dirs | QDir::NoDotAndDotDot);

    QFileIconProvider *iconProvider = new IconFilter();
    tmodel->setIconProvider(iconProvider);
    
    m_selectionModel = new QItemSelectionModel(tmodel);
    
    treeView = new QTreeView(this);
    treeView->setModel(tmodel);
    treeView->setRootIndex(tmodel->index(cfg.readEntry("NoteDir")));
    treeView->resizeColumnToContents(0);
    treeView->setColumnHidden(1, true);
    treeView->setColumnHidden(2, true);
    treeView->setColumnHidden(3, true);
    treeView->setUniformRowHeights(true);
    treeView->setIconSize(QSize(treeView->sizeHint().width(), 34));
    treeView->setHeaderHidden(true);
    treeView->setAnimated(true);
    treeView->setContextMenuPolicy(Qt::CustomContextMenu);
    
    connect(treeView, SIGNAL(clicked(QModelIndex)),
            this, SLOT(setUrlFromIndex(QModelIndex)));
    connect(treeView, SIGNAL(customContextMenuRequested(const QPoint&)),
            this, SLOT(showContextMenu(const QPoint&))); 

    vl = new QVBoxLayout(this);
    vl->addWidget(treeView);
}


void Navigator::setUrlFromIndex(const QModelIndex& index)
{
    setUrl(QUrl::fromLocalFile(tmodel->filePath(index)));
}

bool Navigator::urlChanged()
{
    emit changeUrl(url());

    if (QFileInfo(url().path()).isDir()) {
        treeView->scrollTo(tmodel->index(url().toLocalFile()));
        QItemSelection selection(
            tmodel->index(url().toLocalFile()),
            tmodel->index(url().toLocalFile())
        );
        m_selectionModel->select(selection, QItemSelectionModel::ClearAndSelect);
        treeView->setSelectionModel(m_selectionModel);
    }

    return true;
}

void Navigator::showContextMenu(const QPoint& pos)
{
    m_pos = pos;
    QMenu *contextMenu = new QMenu();
    QAction *newDirAction = contextMenu->addAction(QString("New Directory"));
    QAction *deleteDirAction = contextMenu->addAction(QString("Delete Directory"));
    connect(newDirAction, SIGNAL(triggered()), this, SLOT(slotNewDir()));
    connect(deleteDirAction, SIGNAL(triggered()), this, SLOT(slotDeleteDir()));
    
    if (contextMenu) {
        contextMenu->exec(QCursor::pos());
    }  
    delete contextMenu;
}

void Navigator::slotNewDir()
{
    QModelIndex index = treeView->indexAt(m_pos);
    QDir dir(tmodel->filePath(index));

    QString folderName = QInputDialog::getText(this,
                                                QString("Create Folder in ") + tmodel->filePath(index),
                                                QString("Folder Name"));
    dir.mkdir(folderName);
}

void Navigator::slotDeleteDir()
{
    QModelIndex index = treeView->indexAt(m_pos);
    QUrl url(tmodel->filePath(index));
    QDir dir(url.adjusted(QUrl::RemoveFilename).toLocalFile());
    
    if (!dir.rmdir(url.fileName())) {
        QMessageBox message;
        message.setWindowTitle("Delete folder");
        message.setText(QString("Cannot delete nonempty folder ") + url.fileName());
        message.exec();
    }
}


Navigator::~Navigator()
{

}

#include "navpanel.moc"
