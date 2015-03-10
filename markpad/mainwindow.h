#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <kparts/mainwindow.h>
class KMarkPad;

class MainWindow : public KParts::MainWindow
{
    Q_OBJECT
    
public:
    MainWindow();
    virtual ~MainWindow();
    
private:
    void setupAction();
    void setupConnect();
    
private slots:
    void slotNew();
    void slotOpen();
    void slotClose();
    void updateCaption();
    void updateCaptionModified();
    
private:
    KMarkPad *m_markpad;
};

#endif