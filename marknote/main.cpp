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

#include "marknote.h"

#include <KApplication>
#include <KAboutData>
#include <KCmdLineArgs>
#include <KLocale>
#include <KFileDialog>

static const char description[] =
    I18N_NOOP("A Markdown based note-taking KDE application");

static const char version[] = "0.1";

int main(int argc, char **argv)
{
    KAboutData about("marknote", 0, ki18n("MarkNote"), version, ki18n(description),
                     KAboutData::License_GPL, ki18n("(C) 2015 Darcy Shen"), KLocalizedString(), 0, "sadhen@zoho.com");
    about.addAuthor( ki18n("Darcy Shen"), KLocalizedString(), "sadhen@zoho.com" );
    KCmdLineArgs::init(argc, argv, &about);

    KCmdLineOptions options;
    options.add("+[URL]", ki18n( "Document to open" ));
    KCmdLineArgs::addCmdLineOptions(options);
    KApplication app;

    KSharedConfigPtr config = KSharedConfig::openConfig();
    KConfigGroup cfg(config, "General Options");
    if (!cfg.hasKey("NoteDir")) {
        QUrl url = KFileDialog::getExistingDirectoryUrl(QDir::homePath(),
                                                        0,
                                                        i18n("Choose where your notes save"));
        cfg.writeEntry("NoteDir", url.toLocalFile());
        config->sync();
    }
    
    MarkNote *mainWindow = new MarkNote;
    mainWindow->show();
    
    return app.exec();
}
