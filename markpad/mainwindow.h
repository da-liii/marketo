#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <kparts/mainwindow.h>
class KMarkPad;
class KRecentFilesAction;

class MainWindow : public KParts::MainWindow
{
    Q_OBJECT
    
public:
    MainWindow();
    MainWindow(const QUrl &);
    virtual ~MainWindow();
    
private:
    void setupAction();
    void setupConnect();
    
private slots:
    void slotNew();
    void slotOpen();
    void slotOpen(const QUrl&);
    void slotClose();
    void updateCaption();
    void updateCaptionModified();
    
private:
    KMarkPad *m_markpad;
    KRecentFilesAction *m_recentFiles;
    bool m_firstTime;
};

#endif