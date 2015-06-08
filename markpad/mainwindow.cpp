#include "mainwindow.h"
#include "kmarkpad.h"

#include <KXMLGUIFactory>
#include <KConfig>
#include <KStandardAction>
#include <KActionCollection>
#include <KEncodingFileDialog>
#include <KLocale>
#include <KRecentFilesAction>
#include <KTextEditor/View>
#include <KTextEditor/Document>

#include <QThread>
#include <QtGlobal>

MainWindow::MainWindow()
    : m_markpad(0)
    , m_recentFiles(0)
{
    m_markpad = new KMarkPad(this);
    
    setupAction();
    setupConnect();
    
    setCentralWidget(m_markpad);
    setupGUI(QSize(500,600), Default, "kmarkpad.rc");
    guiFactory()->addClient(m_markpad->m_editor);
    setStandardToolBarMenuEnabled(true);
    
    setAutoSaveSettings();
    readConfig();

    show();
}

MainWindow::MainWindow(const KUrl& url)
    : m_markpad(0)
    , m_recentFiles(0)
{
    m_markpad = new KMarkPad(this);
    
    setupAction();
    setupConnect();
    
    setCentralWidget(m_markpad);
    setupGUI(QSize(500,600), Default, "kmarkpad.rc");
    guiFactory()->addClient(m_markpad->m_editor);
    setStandardToolBarMenuEnabled(true);
    
    setAutoSaveSettings();
    readConfig();
    
    slotOpen(url);
    show();
}

void MainWindow::setupAction()
{
    actionCollection()->addAction( KStandardAction::Close, "file_close", this, SLOT(slotClose()) );
    actionCollection()->addAction( KStandardAction::New, "file_new", this, SLOT(slotNew()) );
    actionCollection()->addAction( KStandardAction::Open, "file_open", this, SLOT(slotOpen()) );
    
    KAction *previewAction = actionCollection()->addAction("file_preview", this, SLOT(slotPreview()));
    previewAction->setIcon(KIcon("document-preview"));
    previewAction->setText(i18n("Preview"));
    previewAction->setCheckable(true);
    previewAction->setShortcut(QKeySequence("F8"));
    
    KAction *splitAction = actionCollection()->addAction("window_split", this, SLOT(slotSplit()));
    splitAction->setIcon(KIcon("view-split-left-right"));
    splitAction->setText(i18n("Split"));
    splitAction->setCheckable(true);
    
    m_recentFiles = KStandardAction::openRecent(this, SLOT(slotOpen(KUrl)), this);
    actionCollection()->addAction(m_recentFiles->objectName(), m_recentFiles);
    m_recentFiles->setWhatsThis(i18n("This lists files which you have opened recently, and allows you to easily open them again."));
}

void MainWindow::setupConnect()
{
    connect(m_markpad->m_note, SIGNAL(modifiedChanged(KTextEditor::Document*)),
        this, SLOT(updateCaption()));
    connect(m_markpad->m_note, SIGNAL(documentUrlChanged(KTextEditor::Document*)),
        this, SLOT(updateCaption()));
    connect(m_markpad->m_note, SIGNAL(textChanged(KTextEditor::Document*)),
        this, SLOT(updateCaptionModified()));
}

//common config
void MainWindow::readConfig(KSharedConfigPtr config)
{
    KConfigGroup cfg(config, "General Options");

    m_recentFiles->loadEntries(config->group("Recent Files"));
}

void MainWindow::writeConfig(KSharedConfigPtr config)
{
    KConfigGroup generalOptions(config, "General Options");

    m_recentFiles->saveEntries(KConfigGroup(config, "Recent Files"));

    config->sync();
}

//config file
void MainWindow::readConfig()
{
    readConfig(KSharedConfig::openConfig());
}

void MainWindow::writeConfig()
{
    writeConfig(KSharedConfig::openConfig());
}

void MainWindow::readProperties(const KConfigGroup &config)
{
    readConfig();
    Q_UNUSED(config);
}

void MainWindow::saveProperties(KConfigGroup &cg)
{
    writeConfig();
    Q_UNUSED(cg);
}

void MainWindow::updateCaptionModified()
{
    setCaption(m_markpad->m_note->url().fileName() + " [modified]- KMarkPad");
}

void MainWindow::updateCaption()
{
    setCaption(m_markpad->m_note->url().fileName() + " - KMarkPad");
}

void MainWindow::slotNew()
{
    new MainWindow();
}

void MainWindow::slotClose()
{
    m_markpad->m_note->closeUrl();
}

void MainWindow::slotOpen()
{
    KUrl url = KEncodingFileDialog::getOpenUrl();
    slotOpen(url);
}

void MainWindow::slotOpen(const KUrl &url)
{
    m_markpad->m_note->openUrl(url);
    m_recentFiles->addUrl(url);
}

void MainWindow::slotOpen(const QUrl &url)
{
    slotOpen(KUrl(url.toString()));
}

void MainWindow::slotPreview()
{
    bool isPreview = actionCollection()->action("file_preview")->isChecked();
    m_markpad->setPreview(isPreview);
    if (!isPreview) {
        m_markpad->setSplit(false);
        actionCollection()->action("window_split")->setChecked(false);
    }
}

void MainWindow::slotSplit()
{
    bool isSplit = actionCollection()->action("window_split")->isChecked();
    m_markpad->setSplit(isSplit);
    actionCollection()->action("file_preview")->setChecked(isSplit);
}

MainWindow::~MainWindow()
{
    writeConfig();
}


#include "mainwindow.moc"