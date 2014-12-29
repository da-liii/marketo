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
#include <KDE/KWebView>

#include <QWidget>
#include <QModelIndex>

namespace KTextEditor
{
  class View;
  class Document;
}

class KMarknote : public KXmlGuiWindow
{
    Q_OBJECT
public:
    KMarknote(QWidget *parent = 0);
    virtual ~KMarknote();
    
    void unpreview();   
    void setupAction();
    void setupConnect();
    
private slots:
    void newNote();
    void open();
    void open(const QModelIndex &index);
    void updateCaption();
    void preview();
    void updatePreviewer();
    void togglePreview();
    void oneColView();
    void twoColView();
    void threeColView();
    
private:
    KTextEditor::Document *m_note;
    KTextEditor::View *m_editor;
    MainView *m_view;
    int column;
    bool isPreview;
};

#endif // _KMARKNOTE_H_