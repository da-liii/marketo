#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <KDE/KXmlGuiWindow>
class KMarkPad;

class MainWindow : public KXmlGuiWindow
{
public:
    MainWindow(QWidget *parent=0);
    virtual ~MainWindow();
    
private:
    KMarkPad *m_markpad;
};

#endif