#include "navpanel.h"
#include "kmarknote_generalsettings.h"

#include <QFileSystemModel>
#include <QTreeView>
#include <QVBoxLayout>
#include <QModelIndex>

#include <KUrl>

Navigator::Navigator(Panel* parent)
    : Panel(parent)
{
    tmodel = new QFileSystemModel;
    tmodel->setRootPath(GeneralSettings::homeDir());
    tmodel->setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
    
    treeView = new QTreeView(this);
    treeView->setModel(tmodel);
    treeView->setRootIndex(tmodel->index(GeneralSettings::homeDir()));
    treeView->resizeColumnToContents(0);
    treeView->setColumnHidden(1, true);
    treeView->setColumnHidden(2, true);
    treeView->setColumnHidden(3, true);
    treeView->setUniformRowHeights(true);
    treeView->setIconSize(QSize(treeView->sizeHint().width(), 34));
    treeView->setHeaderHidden(true);
    
    connect(treeView, SIGNAL(clicked(QModelIndex)),
            this, SLOT(setUrlFromIndex(QModelIndex)));
    
    vl = new QVBoxLayout(this);
    vl->addWidget(treeView);
}


void Navigator::setUrlFromIndex(const QModelIndex& index)
{
    setUrl(KUrl(tmodel->filePath(index).append("/")));
}

bool Navigator::urlChanged()
{
    emit changeUrl(url());
    return true;
}

Navigator::~Navigator()
{

}

#include "navpanel.moc"