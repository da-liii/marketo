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
    void open();
    void updateCaptionModified();
    void updateCaption();
    void togglePreview();
    
private:
    KTextEditor::Document *m_note;
    MainView *m_view;
    bool isPreview;
};

#endif // _KMARKNOTE_H_