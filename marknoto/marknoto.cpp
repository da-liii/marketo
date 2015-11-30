/***************************************************************************
 *   Copyright (C) 2015 by Darcy Shen <sadhen@zoho.com>                    *
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

#include "marknoto.h"

#include <KLocalizedString>
#include <KXMLGUIFactory>
#include <KStandardAction>
#include <KActionCollection>
#include <KRecentFilesAction>

#include <QUrl>
#include <QAction>
#include <QKeySequence>

MarkNote::MarkNote(QWidget* parent)
    : KXmlGuiWindow(parent)
    , m_firstTextChange(false)
    , actions(actionCollection())
    , m_recentFiles(0)
{
    QAction* previewAction = actionCollection()->addAction("file_preview", this, SLOT(togglePreview()));
    previewAction->setIcon(QIcon::fromTheme(QLatin1String("document-preview")));
    previewAction->setText(i18n("Preview"));
    previewAction->setCheckable(true);
    actions->setDefaultShortcut(previewAction, QKeySequence("F8"));
    
    m_view = new MainView(parent, actionCollection());
    m_note = m_view->note;
    setupAction();
    setupUI();
    setupConnect();

    m_view->goHome();
    actionCollection()->action("go_backward")->setChecked(true);
    m_view->preview();
}

void MarkNote::setupAction()
{
    //KStandardAction::openNew(this, SLOT(newNote()), actionCollection());
    //KStandardAction::close(this, SLOT(close()), actionCollection());
    
    QAction* oneColAction = actionCollection()->addAction("win_onecol", m_view, SLOT(oneColView()));
    QAction* twoColAction = actionCollection()->addAction("win_twocol", m_view, SLOT(twoColView()));
    QAction* threeColAction = actionCollection()->addAction("win_threecol", m_view, SLOT(threeColView()));
    QAction* addNoteAction = actionCollection()->addAction("add_note", m_view, SLOT(newNote()));
    QAction* goHomeAction = actionCollection()->addAction("go_home", m_view, SLOT(goHome()));
    QAction* backwardAction = actionCollection()->addAction("go_backward", this, SLOT(backward()));
    QAction* forwardAction = actionCollection()->addAction("go_forward", this, SLOT(forward()));
    
    forwardAction->setCheckable(true);
    forwardAction->setChecked(true);
    backwardAction->setCheckable(true);
    
    oneColAction->setText(i18n("Focus"));
    twoColAction->setText(i18n("Split"));
    threeColAction->setText(i18n("Browse"));
    addNoteAction->setText(i18n("New Note"));
    forwardAction->setText(i18n("Forward"));
    backwardAction->setText(i18n("Backward"));

    actions->setDefaultShortcut(addNoteAction, QKeySequence("Ctrl+N"));
    actions->setDefaultShortcut(forwardAction, QKeySequence("Alt+Right"));
    actions->setDefaultShortcut(backwardAction, QKeySequence("Alt+Left"));
    
    oneColAction->setIcon(QIcon::fromTheme(QLatin1String("view-split-top-bottom")));
    twoColAction->setIcon(QIcon::fromTheme(QLatin1String("view-split-left-right")));
    threeColAction->setIcon(QIcon::fromTheme(QLatin1String("view-file-columns")));
    addNoteAction->setIcon(QIcon::fromTheme(QLatin1String("list-add")));
    goHomeAction->setIcon(QIcon::fromTheme(QLatin1String("go-home")));
    forwardAction->setIcon(QIcon::fromTheme(QLatin1String("arrow-right")));
    backwardAction->setIcon(QIcon::fromTheme(QLatin1String("arrow-left")));

    
    m_recentFiles = KStandardAction::openRecent(m_view, SLOT(slotOpen(QUrl)), this);
    actionCollection()->addAction(m_recentFiles->objectName(), m_recentFiles);
    m_recentFiles->setWhatsThis(i18n("This lists files which you have opened recently, and allows you to easily open them again."));
    
    //QAction* terminalAction = actionCollection()->addAction("toggle_terminal", m_view, SLOT(toggleTerminal()));
    //terminalAction->setShortcut(QKeySequence("F4"));
}

void MarkNote::setupUI()
{
    setCentralWidget(m_view);
    setupGUI(QSize(500,600), Default, "marknoto.rc");
    guiFactory()->addClient(m_view->getEditor());
    setStandardToolBarMenuEnabled(true);
    setAutoSaveSettings();
    readConfig();
 }

void MarkNote::setupConnect()
{
    connect(m_note, &KTextEditor::Document::modifiedChanged,
            this, &MarkNote::updateCaption);
    connect(m_note, &KTextEditor::Document::documentUrlChanged,
            this, &MarkNote::slotDocumentUrlChanged);
    connect(m_note, &KTextEditor::Document::textChanged,
            this, &MarkNote::updateCaptionModified);
}

//common config
void MarkNote::readConfig(KSharedConfigPtr config)
{
    KConfigGroup cfg(config, "General Options");

    m_recentFiles->loadEntries(config->group("Recent Files"));
}

void MarkNote::writeConfig(KSharedConfigPtr config)
{
    KConfigGroup generalOptions(config, "General Options");

    m_recentFiles->saveEntries(KConfigGroup(config, "Recent Files"));

    config->sync();
}

//config file
void MarkNote::readConfig()
{
    readConfig(KSharedConfig::openConfig());
}

void MarkNote::writeConfig()
{
    writeConfig(KSharedConfig::openConfig());
}

void MarkNote::readProperties(const KConfigGroup &config)
{
    Q_UNUSED(config);
    readConfig();
}

void MarkNote::saveProperties(KConfigGroup &config)
{
    Q_UNUSED(config);
    writeConfig();
}

void MarkNote::newNote()
{
    m_view->newNote();
}

void MarkNote::updateCaptionModified()
{
    // The first textChanged signal is caused by document loading
    // Thus, we should ignore it
    if (m_firstTextChange) {
        m_firstTextChange = false;
        return ;
    }
    setCaption(m_note->url().fileName() + " [modified]- Marketo");
}

void MarkNote::updateCaption()
{
    setCaption(m_note->url().fileName() + " - Marketo");
}

void MarkNote::slotDocumentUrlChanged()
{
    // TODO: figure out how Qt signal slot works and make sure
    // slotDocumentUrlChanged is done before updateCaptionModified
    m_firstTextChange = true;
    updateCaption();
    if (!m_note->url().isEmpty())
        m_recentFiles->addUrl(m_note->url());
}

void MarkNote::togglePreview()
{
    if (!actions->action("file_preview")->isChecked())
        m_view->unpreview();
    else
        m_view->preview();
}

void MarkNote::forward()
{
    if (m_view->noteView->canForward()) {
        m_view->noteView->forward();
        actionCollection()->action("go_backward")->setChecked(false);
    }
    if (m_view->noteView->canForward())
        actionCollection()->action("go_forward")->setChecked(false);
    else
        actionCollection()->action("go_forward")->setChecked(true);
}

void MarkNote::backward()
{
    if (m_view->noteView->canBackward()) {
        m_view->noteView->backward();
        actionCollection()->action("go_forward")->setChecked(false);
    }
    if (m_view->noteView->canBackward())
        actionCollection()->action("go_backward")->setChecked(false);
    else
        actionCollection()->action("go_backward")->setChecked(true);
}

MarkNote::~MarkNote()
{
    writeConfig();
}

#include "marknoto.moc"
