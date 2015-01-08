#include "mainview.h"

#include <QDir>
#include <QtDebug>

#include <KDE/KLocale>
#include <KTextEditor/Editor>
#include <KTextEditor/EditorChooser>
#include <KDE/KMessageBox>

MainView::MainView(QWidget *parent)
    : QWidget(parent)
{
    resize(629, 470);
    verticalLayout = new QVBoxLayout(this);
    splitter = new QSplitter(this);
    treeView = new QTreeView(splitter);
    listView = new QListView(splitter);
    previewer = new KWebView(splitter);
    fulleditor = new QWidget(this);
    vl2 = new QVBoxLayout(fulleditor);
    title = new KLineEdit(fulleditor);
   
    verticalLayout->addWidget(splitter);
    
    tmodel = new QFileSystemModel;
    tmodel->setRootPath(QDir::homePath());
    tmodel->setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
    treeView->setModel(tmodel);
    treeView->setRootIndex(tmodel->index(QDir::homePath().append("/notes")));
    treeView->resizeColumnToContents(0);
    treeView->setColumnHidden(1, true);
    treeView->setColumnHidden(2, true);
    treeView->setColumnHidden(3, true);
    treeView->setUniformRowHeights(true);
    treeView->setIconSize(QSize(treeView->sizeHint().width(), 34));
    treeView->setHeaderHidden(true);

    lmodel = new QFileSystemModel; 
    lmodel->setRootPath(QDir::homePath());
    lmodel->setFilter(QDir::Files);
    
    QStringList filters;
    filters << "*.md" << "*.markdown";
    lmodel->setNameFilters(filters);
    lmodel->setNameFilterDisables(false);
    
    listView->setModel(lmodel);
    listView->setRootIndex(lmodel->index(QDir::homePath().append("/notes")));
    listView->setGridSize(QSize(listView->sizeHint().width(), 34));
    listView->setIconSize(QSize(listView->sizeHint().width(), 34));
    listView->setAlternatingRowColors(true);
    
    // TODO: new_editor should be carefully handled, may memory leak
    KTextEditor::Editor* new_editor = KTextEditor::EditorChooser::editor();
    if (!new_editor) {
        KMessageBox::error(this,  i18n("A KDE text-editor component could not be found;\n"
                                       "please check your KDE installation."));
        note = 0;
    } else {
        note = new_editor->createDocument(0);
        editor = qobject_cast<KTextEditor::View*>(note->createView(this));
    }
    
    vl2->addWidget(title);
    vl2->addWidget(editor);
    splitter->setOrientation(Qt::Horizontal);
    splitter->addWidget(treeView);
    splitter->addWidget(listView);
    splitter->addWidget(previewer);
    splitter->addWidget(fulleditor);
    connect(treeView, SIGNAL(clicked(QModelIndex)),
            this, SLOT(gotoDir(QModelIndex)));
}

void MainView::gotoDir(const QModelIndex& index)
{
    lmodel->setRootPath(tmodel->filePath(index));
    listView->setRootIndex(lmodel->index(tmodel->filePath(index)));
}

MainView::~MainView()
{
}

#include "mainview.moc"