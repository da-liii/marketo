#include "navpanel.h"

#include <QFileSystemModel>
#include <QItemSelection>
#include <QItemSelectionModel>
#include <QTreeView>
#include <QVBoxLayout>
#include <QModelIndex>

#include <KConfigGroup>
#include <KSharedConfig>
#include <KUrl>

Navigator::Navigator(Panel* parent)
    : Panel(parent)
{
    KConfigGroup cfg(KSharedConfig::openConfig(), "General Options");
    
    tmodel = new QFileSystemModel;
    tmodel->setRootPath(cfg.readEntry("NoteDir"));
    tmodel->setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
    
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
    
    connect(treeView, SIGNAL(clicked(QModelIndex)),
            this, SLOT(setUrlFromIndex(QModelIndex)));
    
    vl = new QVBoxLayout(this);
    vl->addWidget(treeView);
}


void Navigator::setUrlFromIndex(const QModelIndex& index)
{
    setUrl(KUrl(tmodel->filePath(index)));
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

Navigator::~Navigator()
{

}

#include "navpanel.moc"