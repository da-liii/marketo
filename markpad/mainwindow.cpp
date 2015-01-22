#include "mainwindow.h"
#include "kmarkpad.h"

#include <KDE/KXMLGUIFactory>
#include <KDE/KConfigGroup>
#include <KGlobal>
#include <KTextEditor/View>

MainWindow::MainWindow(QWidget* parent)
    : KXmlGuiWindow(parent)
{
    m_markpad = new KMarkPad(this);
    
    KConfigGroup cg(KGlobal::config(), "KMarkPad");
    setAutoSaveSettings(cg, true);
    setCentralWidget(m_markpad);
    guiFactory()->addClient(m_markpad->m_editor);
    restoreWindowSize(cg);
    
    m_markpad->preview(true);
}

MainWindow::~MainWindow()
{

}


#include "mainwindow.moc"