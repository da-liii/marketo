#include "terminalview.h"

#include <signal.h>
#include <KDE/KPluginLoader>
#include <KDE/KPluginFactory>
#include <KDE/KService>
#include <kde_terminal_interface_v2.h>
#include <KParts/Part>
#include <KDE/KShell>

#include <QVBoxLayout>
#include <QShowEvent>

TerminalView::TerminalView(QWidget* parent) :
    QWidget(parent),
    m_layout(0),
    m_terminal(0),
    m_terminalWidget(0),
    m_konsolePart(0)
{
    m_layout = new QVBoxLayout(this);
    m_layout->setMargin(0);
}

void TerminalView::showEvent(QShowEvent* event)
{
    if(!m_terminal) {
        KPluginFactory* factory = 0;
        KService::Ptr service = KService::serviceByDesktopName("konsolepart");
        if (service)
            factory = KPluginLoader(service->library()).factory();
        m_konsolePart = factory ? (factory->create<KParts::ReadOnlyPart>(this)) : 0;
        if (m_konsolePart) {
            connect(m_konsolePart, SIGNAL(destroyed(QObject*)), this, SLOT(terminalExited()));
            m_terminalWidget = m_konsolePart->widget();
            m_layout->addWidget(m_terminalWidget);
            m_terminal = qobject_cast<TerminalInterfaceV2 *>(m_konsolePart);
        }
    }
    if (m_terminal) {
        m_terminalWidget->setFocus();
    }
}

void TerminalView::terminalExited()
{
    m_terminal = 0;
    hide();
}

TerminalView::~TerminalView()
{

}
#include "terminalview.moc"