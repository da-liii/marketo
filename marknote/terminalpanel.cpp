#include "terminalpanel.h"
#include "kmarknote_generalsettings.h"

#include <signal.h>
#include <KDE/KPluginLoader>
#include <KDE/KPluginFactory>
#include <KDE/KService>
#include <kde_terminal_interface_v2.h>
#include <KParts/Part>
#include <KDE/KShell>

#include <QVBoxLayout>
#include <QShowEvent>

TerminalPanel::TerminalPanel(QWidget* parent) :
    Panel(parent),
    m_layout(0),
    m_terminal(0),
    m_terminalWidget(0),
    m_konsolePart(0)
{
    m_layout = new QVBoxLayout(this);
    m_layout->setMargin(0);
    m_konsolePartCurrentDirectory = GeneralSettings::noteDir();
}

void TerminalPanel::showEvent(QShowEvent* event)
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
        sendCdToTerminal(m_konsolePartCurrentDirectory);
    }
}

void TerminalPanel::sendCdToTerminal(const QString& dir)
{
    if (dir == m_konsolePartCurrentDirectory) {
        m_clearTerminal = false;
        return;
    }

    if (!m_clearTerminal) {
        // The TerminalV2 interface does not provide a way to delete the
        // current line before sending a new input. This is mandatory,
        // otherwise sending a 'cd x' to a existing 'rm -rf *' might
        // result in data loss. As workaround SIGINT is send.
        const int processId = m_terminal->terminalProcessId();
        if (processId > 0) {
            kill(processId, SIGINT);
        }
    }

    m_terminal->sendInput(" cd " + KShell::quoteArg(dir) + '\n');
    m_konsolePartCurrentDirectory = dir;

    if (m_clearTerminal) {
        m_terminal->sendInput(" clear\n");
        m_clearTerminal = false;
    }
}

bool TerminalPanel::urlChanged()
{
    if (!url().isValid()) {
        return false;
    }

    const bool sendInput = m_terminal && (m_terminal->foregroundProcessId() == -1) && isVisible();
    if (sendInput) {
        sendCdToTerminal(url().toLocalFile());
    }

    return true;
}

void TerminalPanel::terminalExited()
{
    m_terminal = 0;
    hide();
}

TerminalPanel::~TerminalPanel()
{

}
#include "terminalpanel.moc"