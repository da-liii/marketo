/***************************************************************************
 *   Copyright (C) %{CURRENT_YEAR} by %{AUTHOR} <%{EMAIL}>                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA .        *
 ***************************************************************************/

#ifndef KMARKNOTE_H
#define KMARKNOTE_H

#include "mainview.h"
#include <KDE/KXmlGuiWindow>
#include <KConfigGroup>
#include <KSharedConfig>

class KRecentFilesAction;

class KMarkNote : public KXmlGuiWindow
{
    Q_OBJECT
public:
    KMarkNote(QWidget *parent = 0);
    virtual ~KMarkNote();
    
    void unpreview();   
    void setupAction();
    void setupUI();
    void setupConnect();
    
private slots:
    void newNote();
    void updateCaptionModified();
    void updateCaption();
    void togglePreview();
    void slotDocumentUrlChanged();
    
private:
    KTextEditor::Document *m_note;
    MainView *m_view;
    bool isPreview;
    bool m_firstTextChange;
    
    // session management
private:
    void readConfig();
    void writeConfig();
    void writeConfig(KSharedConfigPtr config);
    void readConfig(KSharedConfigPtr config);
    void readProperties(const KConfigGroup &config) override;
    void saveProperties(KConfigGroup &config) override;
    KRecentFilesAction *m_recentFiles;
};

#endif // _KMARKNOTE_H_