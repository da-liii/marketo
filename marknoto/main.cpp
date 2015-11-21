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

#include <KAboutData>
#include <KLocalizedString>

#include <QFileDialog>
#include <QApplication>
#include <QCommandLineParser>

#define DESCRIPTION "A Markdown based note-taking KDE application"
#define VERSION "0.1"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    
    KAboutData about(QStringLiteral("marknote"),
        i18n("Marketo"),
        QStringLiteral(VERSION),
        i18n(DESCRIPTION),
        KAboutLicense::LGPL_V2,
        i18n("(C) 2015 Darcy Shen"),
        QString(),
        QStringLiteral("sadhen@zoho.com"));
    about.addAuthor( i18n("Darcy Shen"), i18n("Developer"), "sadhen@zoho.com" );

    /**
     * register about data
     */
    KAboutData::setApplicationData(about);

    /**
     * set app stuff from about data component name and org. name from KAboutData
     */
    app.setApplicationName(about.componentName());
    app.setApplicationDisplayName(about.displayName());
    app.setOrganizationDomain(about.organizationDomain());
    app.setApplicationVersion(about.version());
    
    QCommandLineParser parser;
    about.setupCommandLine(&parser);
    parser.setApplicationDescription(about.shortDescription());
    parser.addHelpOption();
    parser.addVersionOption();
    parser.process(app);
    about.processCommandLine(&parser);

    KSharedConfigPtr config = KSharedConfig::openConfig();
    KConfigGroup cfg(config, "General Options");
    if (!cfg.hasKey("NoteDir")) {
        QUrl url = QFileDialog::getExistingDirectoryUrl(0,
                                            i18n("Choose where your notes save"),
                                            QDir::homePath(),
                                            QFileDialog::ShowDirsOnly
                                            | QFileDialog::DontResolveSymlinks);
        cfg.writeEntry("NoteDir", url.toLocalFile());
        config->sync();
    }
    
    MarkNote *mainWindow = new MarkNote;
    mainWindow->show();
    
    return app.exec();
}
