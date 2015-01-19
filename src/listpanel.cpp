#include "listpanel.h"
#include "kmarknote_generalsettings.h"

#include <QVBoxLayout>
#include <QListView>
#include <QFileSystemModel>
#include <QModelIndex>

#include <KUrl>

ListPanel::ListPanel(QWidget* parent)
    : Panel(parent)
{
    lmodel = new QFileSystemModel; 
    lmodel->setRootPath(GeneralSettings::homeDir());
    lmodel->setFilter(QDir::Files);
    
    QStringList filters;
    filters << "*.md" << "*.markdown";
    lmodel->setNameFilters(filters);
    lmodel->setNameFilterDisables(false);
    
    listView = new QListView(this);
    listView->setModel(lmodel);
    listView->setRootIndex(lmodel->index(GeneralSettings::homeDir()));
    listView->setGridSize(QSize(listView->sizeHint().width(), 34));
    listView->setIconSize(QSize(listView->sizeHint().width(), 34));
    listView->setAlternatingRowColors(true);
    connect(listView, SIGNAL(clicked(QModelIndex)),
        this, SLOT(setUrlFromIndex(QModelIndex)));
    
    vl = new QVBoxLayout(this);
    vl->addWidget(listView);
}

void ListPanel::setUrlFromIndex(const QModelIndex& index)
{
    //lmodel->setRootPath(tmodel->filePath(index));
    //listView->setRootIndex(lmodel->index(tmodel->filePath(index)));
    setUrl(KUrl(lmodel->filePath(index)));
}

bool ListPanel::urlChanged()
{
    lmodel->setRootPath(url().directory(KUrl::ObeyTrailingSlash));
    listView->setRootIndex(lmodel->index(url().directory(KUrl::ObeyTrailingSlash)));
    emit changeUrl(url());
    return true;
}

ListPanel::~ListPanel()
{

}

#include "listpanel.moc"