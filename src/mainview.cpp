#include "mainview.h"

#include <QDir>
#include <QtDebug>
#include <QVBoxLayout>
#include <QVariant>
#include <QAction>
#include <QApplication>
#include <QListView>
#include <QSplitter>
#include <QFileSystemModel>
#include <QTreeView>
#include <QModelIndex>

#include <KDE/KWebView>
#include <KDE/KUrl>
#include <KDE/KAction>
#include <KDE/KLocale>
#include <KTextEditor/Editor>
#include <KTextEditor/EditorChooser>
#include <KDE/KLineEdit>
#include <KDE/KMessageBox>


MainView::MainView(QWidget *parent, KAction *pAction)
    : QWidget(parent)
{
    setupUI();
    setupConnect();
    
    previewAction = pAction;
    column = 3;
    threeColView();
}

void MainView::setupUI()
{
    resize(629, 470);
    verticalLayout = new QVBoxLayout(this);
    vsplitter = new QSplitter(Qt::Vertical, this);
    hsplitter = new QSplitter(Qt::Horizontal, this);
    terminal = new TerminalView(this);
    terminal->hide();
    treeView = new QTreeView(hsplitter);
    listView = new QListView(hsplitter);
    noteView = new NoteView(hsplitter);
    note = noteView->note;
    markPad = noteView->markPad;

    vsplitter->addWidget(hsplitter);
    vsplitter->addWidget(terminal);
    QList<int> sizeList;
    sizeList << 800 << 300;
    vsplitter->setSizes(sizeList);
    verticalLayout->addWidget(vsplitter);
    
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
    
    hsplitter->addWidget(treeView);
    hsplitter->addWidget(listView);
    hsplitter->addWidget(noteView);
}

void MainView::setupConnect()
{
    connect(treeView, SIGNAL(clicked(QModelIndex)),
            this, SLOT(gotoDir(QModelIndex)));
    connect(listView, SIGNAL(clicked(QModelIndex)),
            this, SLOT(open(QModelIndex)));
    connect(treeView, SIGNAL(clicked(QModelIndex)),
            this, SLOT(showReadme(QModelIndex)));    
}

void MainView::open(const QModelIndex &index)
{
    KUrl url = KUrl(lmodel->filePath(index));
    note->openUrl(url);
    noteView->setTitle(url.fileName());
}

void MainView::gotoDir(const QModelIndex& index)
{
    lmodel->setRootPath(tmodel->filePath(index));
    listView->setRootIndex(lmodel->index(tmodel->filePath(index)));
}

KTextEditor::View* MainView::getEditor()
{
    return markPad->editor;
}

bool MainView::preview()
{
    markPad->preview(column == 2);
    return true;
}

bool MainView::unpreview()
{
    if (column == 2)
        return true;
    else {
        markPad->unpreview();
        return false;
    }
}

void MainView::oneColView()
{
    treeView->setHidden(true);
    listView->setHidden(true);
    noteView->hideTitleLine();
    
    column = 1;
    unpreview();
    previewAction->setChecked(false);
}

void MainView::twoColView()
{
    QList<int> sizeList;
    sizeList << 0 << 0 << 400;
    hsplitter->setSizes(sizeList);
    
    treeView->setHidden(true);
    listView->setHidden(true);
    noteView->hideTitleLine();
    
    column = 2;
    preview();
    previewAction->setChecked(true);
}

void MainView::threeColView()
{
    treeView->setHidden(false);
    listView->setHidden(false);
    noteView->showTitleLine();
    
    QList<int> sizeList;
    sizeList << 50 << 50<< 300;
    hsplitter->setSizes(sizeList);
    
    column = 3;
    unpreview();
    previewAction->setChecked(false);
}

void MainView::showReadme(const QModelIndex &index)
{
    QString readmePath = tmodel->filePath(index).append("/README.md");
    note->openUrl(KUrl(readmePath));
    noteView->setTitle("README.md");
    unpreview();
}

void MainView::openUrl(KUrl url)
{
    // TODO:if the url is not in the watching dir and is in three column view
    // switch to one column view
    note->openUrl(url);
}

void MainView::newNote()
{
    KUrl url;
    
    url = note->url();
    url = url.directory().append("/Untitle.md");
    noteView->setTitle(url.fileName());
    note->openUrl(url);
}

void MainView::toggleTerminal()
{
    if (terminal->isVisible())
        terminal->hide();
    else
        terminal->show();
}

MainView::~MainView()
{
}

#include "mainview.moc"