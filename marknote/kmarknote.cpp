/***************************************************************************
 *   Copyright (C) 2015 by Darcy Shen <sadhen@zoho.com>               *
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

#include "kmarknote.h"

#include <KLocalizedString>
#include <KConfigGroup>
#include <KGlobal>
#include <KXMLGUIFactory>
#include <KStandardAction>
#include <KActionCollection>
#include <KFileDialog>
#include <QUrl>
#include <KWebView>
#include <KMenuBar>
#include <KShortcut>
#include <KIcon>

#include <QAction>
#include <QKeySequence>

KMarkNote::KMarkNote(QWidget* parent)
    : KXmlGuiWindow(parent)
    , isPreview(false)
{
    QAction* previewAction = actionCollection()->addAction("file_preview", this, SLOT(togglePreview()));
    previewAction->setIcon(KIcon("document-preview"));
    previewAction->setText(i18n("Preview"));
    previewAction->setCheckable(true);
    
    m_view = new MainView(parent, previewAction);
    m_note = m_view->note;
    setupAction();
    setupUI();
    setupConnect();
}

void KMarkNote::setupAction()
{
    KStandardAction::openNew(this, SLOT(newNote()), actionCollection());
    KStandardAction::close(this, SLOT(close()), actionCollection());
    
    QAction* oneColAction = actionCollection()->addAction("win_onecol", m_view, SLOT(oneColView()));
    QAction* twoColAction = actionCollection()->addAction("win_twocol", m_view, SLOT(twoColView()));
    QAction* threeColAction = actionCollection()->addAction("win_threecol", m_view, SLOT(threeColView()));
    
    oneColAction->setText(i18n("One Column View"));
    twoColAction->setText(i18n("Two Column View"));
    threeColAction->setText(i18n("Three Column View"));
    
    oneColAction->setIcon(KIcon("view-split-top-bottom"));
    twoColAction->setIcon(KIcon("view-split-left-right"));
    threeColAction->setIcon(KIcon("view-file-columns"));
    
    QAction* terminalAction = actionCollection()->addAction("toggle_terminal", m_view, SLOT(toggleTerminal()));
    terminalAction->setShortcut(QKeySequence("F4"));
}

void KMarkNote::setupUI()
{
    KConfigGroup cg(KGlobal::config(), "KMarkNote");
    setAutoSaveSettings(cg, true);
    
    setCentralWidget(m_view);
    setupGUI(QSize(500,600), Default, "kmarknote.rc");
    guiFactory()->addClient(m_view->getEditor());
    setStandardToolBarMenuEnabled(true);
    restoreWindowSize(cg);
 }

void KMarkNote::setupConnect()
{
    connect(m_note, SIGNAL(modifiedChanged(KTextEditor::Document*)),
            this, SLOT(updateCaption()));
    connect(m_note, SIGNAL(documentUrlChanged(KTextEditor::Document*)),
            this, SLOT(updateCaption()));
    connect(m_note, SIGNAL(textChanged(KTextEditor::Document *)), 
            this, SLOT(updateCaptionModified()));
}

void KMarkNote::newNote()
{
    m_view->newNote();
}

void KMarkNote::updateCaptionModified()
{
    setCaption(m_note->url().fileName() + " [modified]- KMarkNote");
}

void KMarkNote::updateCaption()
{
    setCaption(m_note->url().fileName() + " - KMarkNote");
}

void KMarkNote::togglePreview()
{
    if (isPreview)
        isPreview = m_view->unpreview();
    else
        isPreview = m_view->preview();
    actionCollection()->action("file_preview")->setChecked(isPreview);
}

KMarkNote::~KMarkNote()
{
}

#include "kmarknote.moc"