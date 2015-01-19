#ifndef TERMINALVIEW_H
#define TERMINALVIEW_H

#include "panel.h"

#include <QWidget>

class TerminalInterfaceV2;
class QVBoxLayout;
class QShowEvent;

namespace KParts {
    class ReadOnlyPart;
}

class TerminalPanel : public Panel
{
    Q_OBJECT
    
public:
    TerminalPanel(QWidget *parent = 0);
    virtual ~TerminalPanel();
    void sendCdToTerminal(const QString& dir);

signals:
    void hideTerminalPanel();

public slots:
    void terminalExited();
    
protected:
    /** @see QWidget::showEvent() */
    virtual void showEvent(QShowEvent* event);
    /** @see Panel::urlChanged() */
    virtual bool urlChanged();
    
private:
    QVBoxLayout* m_layout;
    TerminalInterfaceV2* m_terminal;
    QWidget* m_terminalWidget;
    KParts::ReadOnlyPart* m_konsolePart;
    QString m_konsolePartCurrentDirectory;
    bool m_clearTerminal;
};
#endif