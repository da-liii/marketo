/***************************************************************************
 *   Copyright (C) 2015 by Darcy Shen <sadhen1992@gmail.com>               *
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

// application header
#include "kmarknote.h"
// KDE headers
#include <KDE/KApplication>
#include <KDE/KAboutData>
#include <KDE/KCmdLineArgs>
#include <KDE/KLocale>

static const char description[] =
    I18N_NOOP("A Markdown based note-taking KDE application");

static const char version[] = "0.1";

int main(int argc, char **argv)
{
    KAboutData about("KMarkNote", 0, ki18n("KMarkNote"), version, ki18n(description),
                     KAboutData::License_GPL, ki18n("(C) 2015 Darcy Shen"), KLocalizedString(), 0, "sadhen1992@gmail.com");
    about.addAuthor( ki18n("Darcy Shen"), KLocalizedString(), "sadhen1992@gmail.com" );
    KCmdLineArgs::init(argc, argv, &about);

    KCmdLineOptions options;
    options.add("+[URL]", ki18n( "Document to open" ));
    KCmdLineArgs::addCmdLineOptions(options);
    KApplication app;

    KMarkNote *mainWindow = new KMarkNote();
    mainWindow->show();
    
    return app.exec();
}
