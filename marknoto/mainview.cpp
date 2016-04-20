#include "mainview.h"
// #include "terminalpanel.h"
#include "navpanel.h"
#include "listpanel.h"
#include "metadata.h"

#include <KTextEditor/Editor>
#include <KLineEdit>
#include <KMessageBox>
#include <KSharedConfig>
#include <KConfigGroup>
#include <KActionCollection>

#ifdef UNIX
#include <KFileMetaData/UserMetaData>
#endif

#include <QUrl>
#include <QAction>
#include <QDir>
#include <QtDebug>
#include <QVBoxLayout>
#include <QVariant>
#include <QAction>
#include <QApplication>
#include <QSplitter>
#include <QModelIndex>
#include <QTreeWidgetItem>
#include <QStringList>

MainView::MainView(QWidget *parent, KActionCollection *pActions)
    : Panel(parent),
    actions(pActions)
    
{
    setupUI();
    
    column = 3;
    switch (column) {
        case 1:
            oneColView();
            break;
        case 2:
            twoColView();
            break;
        case 3:
            threeColView();
            break;
        default:
            threeColView();
            break;
    }
}

void MainView::setupUI()
{
    resize(629, 470);
    horizonLayout = new QHBoxLayout(this);
    hsplitter = new QSplitter(Qt::Horizontal, this);
    
    //terminal = new TerminalPanel(this);
    //terminal->hide();
    //connect(terminal, SIGNAL(changeUrl(QUrl)), this, SLOT(setUrl(QUrl)));
    
    navigator = new Navigator(this);
    navigator->setContentsMargins(0, -5, -7, 0);
    connect(navigator, SIGNAL(changeUrl(QUrl)), this, SLOT(setUrl(QUrl)));
    connect(navigator->tagTree, SIGNAL(itemClicked(QTreeWidgetItem *, int )),
            this, SLOT(showTaggedFiles(QTreeWidgetItem *, int )));
    
    listPanel = new ListPanel(this);
    listPanel->setContentsMargins(0, -5, -15, 0);
    connect(listPanel, SIGNAL(changeUrl(QUrl)), this, SLOT(setUrl(QUrl)));
    connect(navigator->tabWidget, SIGNAL(tabBarClicked(int)),
            listPanel, SLOT(setDisplayMode(int)));
    connect(navigator->tabWidget, SIGNAL(tabBarClicked(int)),
            this, SLOT(setDisplayMode(int)));
    
    noteView = new NoteView(this, actions);
    noteView->setContentsMargins(0, -5, 0, 0);
    note = noteView->note;
    markPad = noteView->markPad;
    connect(noteView, SIGNAL(tagsAdded(const QStringList &, const QUrl &)),
            navigator, SLOT(addNewTags(const QStringList &, const QUrl &)));
    connect(note, &KTextEditor::Document::documentSavedOrUploaded, 
            this, &MainView::afterSave);

    hsplitter->addWidget(navigator);
    hsplitter->addWidget(listPanel);
    hsplitter->setHandleWidth(0);
    navigator->setMinimumWidth(180);
    hsplitter->setStretchFactor(0, 0);
    hsplitter->setStretchFactor(1, 1);
    
    horizonLayout->addWidget(hsplitter);
    horizonLayout->addWidget(noteView);
    horizonLayout->setSpacing(0);
    horizonLayout->setStretch(0, 0);
    horizonLayout->setStretch(1, 1);
}

bool MainView::urlChanged()
{
    //terminal->setUrl(url());
    listPanel->setUrl(url());
    navigator->setUrl(url());
    if (QFileInfo(url().toLocalFile()).isFile()) {
        if (noteView->note->isModified())
            noteView->note->documentSave();
        noteView->openUrl(url());
    }
    return true;
}

KTextEditor::View* MainView::getEditor()
{
    return markPad->m_editor;
}

bool MainView::preview()
{
    noteView->hideMetaData();
    markPad->preview(column == 2);
    markPad->setFocus();
    actions->action("file_preview")->setChecked(true);
    return true;
}

bool MainView::unpreview()
{
    if (column == 2)
        return true;
    else {
        if (column == 3)
            noteView->showMetaData();
        markPad->unpreview();
        markPad->setFocus();
        actions->action("file_preview")->setChecked(false);
        return false;
    }
}

void MainView::oneColView()
{
    navigator->setHidden(true);
    listPanel->setHidden(true);
    noteView->hideMetaData();
    
    column = 1;
    unpreview();
}

void MainView::twoColView()
{
    QList<int> sizeList;
    sizeList << 0 << 0 << 400;
    hsplitter->setSizes(sizeList);
    
    navigator->setHidden(true);
    listPanel->setHidden(true);
    noteView->hideMetaData();
    
    column = 2;
    preview();
}

void MainView::threeColView()
{
    navigator->setHidden(false);
    listPanel->setHidden(false);
    noteView->showMetaData();
    
    QList<int> sizeList;
    sizeList << 50 << 50<< 300;
    hsplitter->setSizes(sizeList);
    
    column = 3;
    unpreview();
}
/*
 * only called by Markpado, for separating pado and noto
 */
void MainView::slotOpen(const QUrl& url)
{
    setUrl(url);
}

void MainView::newNote()
{
    QUrl tmpUrl;
    
    tmpUrl = url();

    // avoid empty tmpUrl
    if (tmpUrl.isEmpty()) {
        KConfigGroup cfg(KSharedConfig::openConfig(), "General Options");
        tmpUrl = QUrl::fromLocalFile(cfg.readEntry("NoteDir"));
    }

    bool flag;
#ifdef UNIX
    flag = QFileInfo(tmpUrl.path()).isDir();
#else
    QString path = tmpUrl.path();
    flag = QFileInfo(path.right(path.length()-1)).isDir();
#endif
    if (flag)
        tmpUrl = QUrl::fromLocalFile(tmpUrl.toLocalFile() + QString("/Untitled.md"));
    else
        tmpUrl.setUrl(tmpUrl.url(QUrl::RemoveFilename).append("/Untitled.md"));

    noteView->setTitle(tmpUrl.fileName());
    noteView->focusTitle();
    noteView->openUrl(tmpUrl);
    unpreview();
}

void MainView::afterSave()
{
    MetaData metadata(note->url().toLocalFile());
    navigator->addNewTags(metadata.tags(), note->url());
#ifdef UNIX
    KFileMetaData::UserMetaData kmetadata(note->url().toLocalFile());
    kmetadata.setTags(metadata.tags());
#endif
}


void MainView::goHome()
{
    KConfigGroup cfg(KSharedConfig::openConfig(), "General Options");
    QString noteDir(cfg.readEntry("NoteDir"));
    
    QUrl tmpUrl = QUrl::fromLocalFile(noteDir + QString("/Home.md"));
    noteView->openUrl(tmpUrl);
    noteView->setTitle(tmpUrl.fileName());
    
    navigator->tabWidget->setCurrentIndex(0);
    
    setUrl(QUrl::fromLocalFile(noteDir));
    
    listPanel->goHome();
}

void MainView::showTaggedFiles(const QString& tag)
{
    QStringList halfPathList;
    QStringListIterator iter(navigator->getFilesByTag(tag));
    KConfigGroup cfg(KSharedConfig::openConfig(), "General Options");
    int len = cfg.readEntry("NoteDir").length();
    
    while(iter.hasNext())
        halfPathList.append(iter.next().midRef(len).toString());
    listPanel->setTaggedList(halfPathList);
}

void MainView::showTaggedFiles(QTreeWidgetItem *item, int row)
{
    QString tag(item->text(row));
    showTaggedFiles(tag);
}

void MainView::setDisplayMode(int mode) {
    if (mode == 0) {
        navigator->tabWidget->setCurrentIndex(0);
        listPanel->setUrlForLModel(note->url());
    } else {
        if (navigator->tagTree->currentItem())
            showTaggedFiles(navigator->tagTree->currentItem()->text(0));
        else showTaggedFiles(QString("@todo"));
    }
}

void MainView::toggleTerminal()
{
    /*
    if (terminal->isVisible())
        terminal->hide();
    else
        terminal->show();
    */
}

MainView::~MainView()
{
}

#include "mainview.moc"
