#ifndef TERMINALVIEW_H
#define TERMINALVIEW_H

#include <QWidget>

class TerminalInterfaceV2;
class QVBoxLayout;
class QShowEvent;

namespace KParts {
    class ReadOnlyPart;
}

class TerminalView : public QWidget
{
    Q_OBJECT
    
public:
    TerminalView(QWidget *parent = 0);
    virtual ~TerminalView();

signals:
    void hideTerminalView();
    
public slots:
    void terminalExited();
    
protected:
    /** @see QWidget::showEvent() */
    virtual void showEvent(QShowEvent* event);
    
private:
    QVBoxLayout* m_layout;
    TerminalInterfaceV2* m_terminal;
    QWidget* m_terminalWidget;
    KParts::ReadOnlyPart* m_konsolePart;
};
#endif