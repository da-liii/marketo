#include "mainwindow.h"
#include "kmarkpad.h"

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
    : m_recentFiles(0)
{
    m_markpad = new KMarkPad(this);
    m_markpad->preview(true);
    m_firstTime = false;

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

MainWindow::MainWindow(const QUrl& url)
{
    m_markpad = new KMarkPad(this);
    m_markpad->preview(true);
    
    setupAction();
    setupConnect();
    
    
    setCentralWidget(m_markpad);
    setupGUI(QSize(500,600), Default, "kmarkpad.rc");
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
    m_recentFiles = KStandardAction::openRecent(this, SLOT(slotOpen(QUrl)), this);
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
}

void MainWindow::saveProperties(KConfigGroup &cg)
{
    writeConfig();
}

void MainWindow::updateCaptionModified()
{
    if (m_firstTime) {
        m_firstTime = false;
        return ;
    }
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
    QUrl url = KEncodingFileDialog::getOpenUrlAndEncoding().URLs.first();
    
    // NOTICE: the order of assigning firstTime and markpad matters
    m_firstTime = true;
    slotOpen(url);
}

void MainWindow::slotOpen(const QUrl &url)
{
    m_markpad->m_note->openUrl(url);
    m_recentFiles->addUrl(url);
}

MainWindow::~MainWindow()
{
    writeConfig();
}


#include "mainwindow.moc"
