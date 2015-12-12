#include "mainview.h"
// #include "terminalpanel.h"
#include "navpanel.h"
#include "listpanel.h"

#include <KTextEditor/Editor>
#include <KLineEdit>
#include <KMessageBox>
#include <KSharedConfig>
#include <KConfigGroup>
#include <KActionCollection>

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
    verticalLayout = new QVBoxLayout(this);
    vsplitter = new QSplitter(Qt::Vertical, this);
    hsplitter = new QSplitter(Qt::Horizontal, this);
    
    //terminal = new TerminalPanel(this);
    //terminal->hide();
    //connect(terminal, SIGNAL(changeUrl(QUrl)), this, SLOT(setUrl(QUrl)));
    
    navigator = new Navigator(this);
    navigator->setContentsMargins(0, -5, -15, 0);
    connect(navigator, SIGNAL(changeUrl(QUrl)), this, SLOT(setUrl(QUrl)));
    
    listPanel = new ListPanel(this);
    listPanel->setContentsMargins(0, -5, -15, 0);
    connect(listPanel, SIGNAL(changeUrl(QUrl)), this, SLOT(setUrl(QUrl)));
    
    noteView = new NoteView(this, actions);
    noteView->setContentsMargins(0, -5, 0, 0);
    note = noteView->note;
    markPad = noteView->markPad;

    vsplitter->addWidget(hsplitter);
    //vsplitter->addWidget(terminal);
    QList<int> sizeList;
    sizeList << 800 << 300;
    vsplitter->setSizes(sizeList);
    verticalLayout->addWidget(vsplitter);

    hsplitter->addWidget(navigator);
    hsplitter->addWidget(listPanel);
    hsplitter->addWidget(noteView);
    hsplitter->setHandleWidth(0);
}

bool MainView::urlChanged()
{
    //terminal->setUrl(url());
    listPanel->setUrl(url());
    navigator->setUrl(url());
    if (QFileInfo(url().toLocalFile()).isFile())
        noteView->openUrl(url());
    return true;
}

KTextEditor::View* MainView::getEditor()
{
    return markPad->m_editor;
}

bool MainView::preview()
{
    noteView->hideTitleLine();
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
        noteView->showTitleLine();
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
    noteView->hideTitleLine();
    
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
    noteView->hideTitleLine();
    
    column = 2;
    preview();
}

void MainView::threeColView()
{
    navigator->setHidden(false);
    listPanel->setHidden(false);
    noteView->showTitleLine();
    
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

    if (QFileInfo(tmpUrl.path()).isDir())
        tmpUrl = QUrl::fromLocalFile(tmpUrl.toLocalFile() + QString("/Untitled.cm"));
    else
        tmpUrl.setUrl(tmpUrl.url(QUrl::RemoveFilename).append("/Untitled.cm"));

    noteView->setTitle(tmpUrl.fileName());
    noteView->focusTitle();
    noteView->openUrl(tmpUrl);
    unpreview();
}

void MainView::goHome()
{
    KConfigGroup cfg(KSharedConfig::openConfig(), "General Options");
    QString noteDir(cfg.readEntry("NoteDir"));
    QUrl tmpUrl = QUrl::fromLocalFile(noteDir + QString("/Home.cm"));
    noteView->openUrl(tmpUrl);
    noteView->setTitle(tmpUrl.fileName());
    
    setUrl(QUrl::fromLocalFile(noteDir));
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
