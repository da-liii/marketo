#include "mainwindow.h"
#include "markpado.h"

#include <KParts/MainWindow>
#include <KXMLGUIFactory>
#include <KConfig>
#include <KStandardAction>
#include <KActionCollection>
#include <KIOFileWidgets/KEncodingFileDialog>
#include <KTextEditor/View>
#include <KTextEditor/Document>
#include <KRecentFilesAction>
#include <KLocalizedString>

#include <QUrl>

MainWindow::MainWindow()
    : m_markpad(0)
    , m_recentFiles(0)
    , m_firstTextChange(false)
{
    m_markpad = new Markpado(this);

    setupAction();
    setupConnect();

    setCentralWidget(m_markpad);
    setupGUI(QSize(500,600), Default, "markpado.rc");
    guiFactory()->addClient(m_markpad->m_editor);
    setStandardToolBarMenuEnabled(true);
    
    setAutoSaveSettings();
    readConfig();

    show();
}

MainWindow::MainWindow(const QUrl& url)
    : m_markpad(0)
    , m_recentFiles(0)
    , m_firstTextChange(false)
{
    m_markpad = new Markpado(this);
    
    setupAction();
    setupConnect();
    
    
    setCentralWidget(m_markpad);
    setupGUI(QSize(500,600), Default, "markpado.rc");
    guiFactory()->addClient(m_markpad->m_editor);
    setStandardToolBarMenuEnabled(true);
    
    // FIXME: make sure the config dir exists, any idea how to do it more cleanly?
    QDir(QStandardPaths::writableLocation(QStandardPaths::DataLocation)).mkpath(QStringLiteral("."));    
    
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

    QAction *previewAction = actionCollection()->addAction("file_preview", this, SLOT(slotPreview()));
    previewAction->setIcon(QIcon::fromTheme(QLatin1String("document-preview")));
    previewAction->setText(i18n("Preview"));
    previewAction->setCheckable(true);
    actionCollection()->setDefaultShortcut(previewAction, QKeySequence("F8"));
    
    QAction *splitAction = actionCollection()->addAction("window_split", this, SLOT(slotSplit()));
    splitAction->setIcon(QIcon::fromTheme(QLatin1String("view-split-left-right")));
    splitAction->setText(i18n("Split"));
    splitAction->setCheckable(true);

    m_recentFiles = KStandardAction::openRecent(this, SLOT(slotOpen(QUrl)), this);
    actionCollection()->addAction(m_recentFiles->objectName(), m_recentFiles);
    m_recentFiles->setWhatsThis(i18n("This lists files which you have opened recently, and allows you to easily open them again."));
}

void MainWindow::setupConnect()
{
    connect(m_markpad->m_note, &KTextEditor::Document::modifiedChanged,
        this, &MainWindow::updateCaption);
    connect(m_markpad->m_note, &KTextEditor::Document::documentUrlChanged,
        this, &MainWindow::updateCaption);
    connect(m_markpad->m_note, &KTextEditor::Document::textChanged,
        this, &MainWindow::updateCaptionModified);
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
    Q_UNUSED(config);
    readConfig();
}

void MainWindow::saveProperties(KConfigGroup &config)
{
    Q_UNUSED(config);
    writeConfig();
}

void MainWindow::updateCaptionModified()
{
    // The first textChanged signal is caused by document loading
    // Thus, we should ignore it
    if (m_firstTextChange) {
        m_firstTextChange = false;
        return ;
    }
    setCaption(m_markpad->m_note->url().fileName() + " [modified]- markpado");
}

void MainWindow::updateCaption()
{
    setCaption(m_markpad->m_note->url().fileName() + " - markpado");
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
    QUrl url = KEncodingFileDialog::getOpenUrlAndEncoding().URLs.first();
    
    slotOpen(url);
}

void MainWindow::slotOpen(const QUrl &url)
{
    // NOTICE: the order of assigning m_firstTextChange and markpad matters
    m_firstTextChange = true;
    m_markpad->m_note->openUrl(url);
    m_recentFiles->addUrl(url);
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
