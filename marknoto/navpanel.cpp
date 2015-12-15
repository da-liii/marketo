#include "navpanel.h"
#include "iconfilter.h"

#include <KConfigGroup>
#include <KSharedConfig>
#include <KFileMetaData/UserMetaData>

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
#include <QFile>
#include <QFileInfo>
#include <QDebug>
#include <QTreeWidget>
#include <QDirIterator>

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
    treeView->setIconSize(QSize(16, 16));
    treeView->setHeaderHidden(true);
    treeView->setAnimated(true);
    treeView->setContentsMargins(-5, -5, 0, 0);
    treeView->setContextMenuPolicy(Qt::CustomContextMenu);
    
    connect(treeView, SIGNAL(clicked(QModelIndex)),
            this, SLOT(setUrlFromIndex(QModelIndex)));
    connect(treeView, SIGNAL(customContextMenuRequested(const QPoint&)),
            this, SLOT(showContextMenu(const QPoint&))); 
 
    buildTagStaffs();
    
    tabWidget = new QTabWidget(this);
    tabWidget->addTab(treeView, QString("Folder"));
    tabWidget->addTab(tagTree, QString("Tag"));
    tabWidget->setContentsMargins(0, 0, 0, 0);
    vl = new QVBoxLayout(this);
    vl->addWidget(tabWidget);
}

void Navigator::buildTagStaffs()
{
    KConfigGroup cfg(KSharedConfig::openConfig(), "General Options");
    QString noteDir(cfg.readEntry("NoteDir"));
    
    tagPaths = new QStringList();
    tagRoots = new QStringList();
    
    QDirIterator it(noteDir, QStringList() << "*.cm" << "*.md", QDir::Files, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        QString file(it.next());
        KFileMetaData::UserMetaData metaData(file);
        QStringList tags = metaData.tags();
        if (!tags.isEmpty()) {
            tagPaths->append(file);
            *tagRoots += tags;
        }
    }
    tagRoots->removeDuplicates();
    tagRoots->sort();
    
    tagTree = new QTreeWidget(this);
    QStringListIterator iter(*tagRoots);
    while (iter.hasNext()) {
        QTreeWidgetItem *item = new QTreeWidgetItem;
        item->setText(0, iter.next());
        tagTree->addTopLevelItem(item);
    }
}

QStringList Navigator::getFilesByTag(const QString& tag)
{
    QStringList list;
    QStringListIterator iter(*tagPaths);
    while (iter.hasNext()) {
        QString curPath(iter.next());
        KFileMetaData::UserMetaData metaData(curPath);
        if (metaData.tags().contains(tag))
            list.append(curPath);
    }
    return list;
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
    QString indexDir(tmodel->filePath(index));
    QDir dir(indexDir);
    
    KConfigGroup cfg(KSharedConfig::openConfig(), "General Options");
    if (indexDir.isEmpty())
        dir.setPath(cfg.readEntry("NoteDir"));
    
    QString folderName = QInputDialog::getText(this,
                                                QString("Create Folder in ") + tmodel->filePath(index),
                                                QString("Folder Name"));
    dir.mkdir(folderName);
}

/*
 * move the Notes to Trash, than delete the Directory
 */
void Navigator::slotDeleteDir()
{
    KConfigGroup cfg(KSharedConfig::openConfig(), "General Options");
    
    QModelIndex index = treeView->indexAt(m_pos);
    qDebug() << tmodel->filePath(index);
    QDir dir(tmodel->filePath(index));
    QDirIterator it(tmodel->filePath(index), QDirIterator::Subdirectories);
    while (it.hasNext()) {
        QFileInfo fileInfo(it.next());
        if (fileInfo.isFile()) {
            QFile file(fileInfo.filePath());
            // TODO: what if the target file already exists, currently overwrite
            file.rename(cfg.readEntry("NoteDir")+"/Trash/"+fileInfo.fileName());
        }
    }
    dir.removeRecursively();
}

Navigator::~Navigator()
{

}

#include "navpanel.moc"
