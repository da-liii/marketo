#include "mainwindow.h"
#include "kmarkpad.h"

#include <KParts/MainWindow>
#include <KXMLGUIFactory>
#include <KGlobal>
#include <KConfigGroup>
#include <KStandardAction>
#include <KActionCollection>
#include <KIOFileWidgets/KEncodingFileDialog>
#include <KTextEditor/View>
#include <KTextEditor/Document>
#include <QUrl>

MainWindow::MainWindow()
{
    m_markpad = new KMarkPad(this);
    m_markpad->preview(true);
    m_firstTime = false;

    setupAction();
    setupConnect();

    // FIXME:should not use KGlobal
    KConfigGroup cg(KGlobal::config(), "KMarkPad");
    setAutoSaveSettings(cg, true);
    
    setCentralWidget(m_markpad);
    setupGUI(QSize(500,600), Default, "kmarkpad.rc");
    guiFactory()->addClient(m_markpad->m_editor);
    setStandardToolBarMenuEnabled(true);
    
    restoreWindowSize(cg);

    show();
}

MainWindow::MainWindow(const QUrl& url)
{
    m_markpad = new KMarkPad(this);
    m_markpad->preview(true);
    
    setupAction();
    setupConnect();
    
    KConfigGroup cg(KGlobal::config(), "KMarkPad");
    setAutoSaveSettings(cg, true);
    
    setCentralWidget(m_markpad);
    setupGUI(QSize(500,600), Default, "kmarkpad.rc");
    guiFactory()->addClient(m_markpad->m_editor);
    setStandardToolBarMenuEnabled(true);
    
    restoreWindowSize(cg);
    
    openUrl(url);
    show();
}

void MainWindow::setupAction()
{
    actionCollection()->addAction( KStandardAction::Close, "file_close", this, SLOT(slotClose()) );
    actionCollection()->addAction( KStandardAction::New, "file_new", this, SLOT(slotNew()) );
    actionCollection()->addAction( KStandardAction::Open, "file_open", this, SLOT(slotOpen()) );
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
    m_markpad->m_note->openUrl(url);
}

void MainWindow::openUrl(const QUrl &url)
{
    m_markpad->m_note->openUrl(url);
}

MainWindow::~MainWindow()
{
}


#include "mainwindow.moc"
