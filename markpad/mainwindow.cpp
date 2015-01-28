#include "mainwindow.h"
#include "kmarkpad.h"

#include <KDE/KXMLGUIFactory>
#include <KDE/KConfigGroup>
#include <KDE/KGlobal>
#include <KDE/KStandardAction>
#include <KDE/KActionCollection>
#include <KDE/KEncodingFileDialog>
#include <KDE/KLocale>
#include <KTextEditor/View>
#include <KTextEditor/Document>

MainWindow::MainWindow()
{
    setupActions();
    
    m_markpad = new KMarkPad(this);
    m_markpad->preview(true);
    
    KConfigGroup cg(KGlobal::config(), "KMarkPad");
    setAutoSaveSettings(cg, true);
    setCentralWidget(m_markpad);
    setupGUI(QSize(500,600), Default, "kmarkpad.rc");
    guiFactory()->addClient(m_markpad->m_editor);
    setStandardToolBarMenuEnabled(true);
    restoreWindowSize(cg);
    show();
}

void MainWindow::setupActions()
{
    actionCollection()->addAction( KStandardAction::Close, "file_close", this, SLOT(slotClose()) );
    actionCollection()->addAction( KStandardAction::New, "file_new", this, SLOT(slotNew()) );
    actionCollection()->addAction( KStandardAction::Open, "file_open", this, SLOT(slotOpen()) );
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
    m_markpad->m_note->openUrl(url);
}

MainWindow::~MainWindow()
{
}


#include "mainwindow.moc"