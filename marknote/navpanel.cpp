#include "navpanel.h"
// #include "kmarknote_generalsettings.h"

#include <QFileSystemModel>
#include <QItemSelection>
#include <QItemSelectionModel>
#include <QTreeView>
#include <QVBoxLayout>
#include <QModelIndex>

#include <QUrl>

Navigator::Navigator(Panel* parent)
    : Panel(parent)
{
    tmodel = new QFileSystemModel;
    tmodel->setRootPath(QString("/home/sadhen/Note"));
    //tmodel->setRootPath(GeneralSettings::noteDir());
    tmodel->setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
    
    m_selectionModel = new QItemSelectionModel(tmodel);
    
    treeView = new QTreeView(this);
    treeView->setModel(tmodel);
    treeView->setRootIndex(tmodel->index(QString("/home/sadhen/Note")));
    //treeView->setRootIndex(tmodel->index(GeneralSettings::noteDir()));
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
    setUrl(QUrl(tmodel->filePath(index)));
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