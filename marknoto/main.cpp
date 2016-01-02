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

#include <KAboutData>
#include <KLocalizedString>
#include <KFileMetaData/UserMetaData>

#include <QFile>
#include <QFileDialog>
#include <QApplication>
#include <QCommandLineParser>
#include <QStandardPaths>
#include <QDir>
#include <QIcon>

#define DESCRIPTION "Marknoto - Note-taking Part of Marketo"
#define VERSION "0.2.1"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    
    KAboutData about(QStringLiteral("marknoto"),
        i18n("Marknoto"),
        QStringLiteral(VERSION),
        i18n(DESCRIPTION),
        KAboutLicense::GPL_V3,
        i18n("(C) 2015 Darcy Shen"),
        QString(),
        QStringLiteral("https://github.com/sadhen/marketo"));
    about.addAuthor( i18n("Darcy Shen"), i18n("Developer"), "sadhen@zoho.com" );
    KLocalizedString::setApplicationDomain("marknoto");

    KAboutData::setApplicationData(about);

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
    if ( !cfg.hasKey("NoteDir") || !QFile::exists(cfg.readEntry("NoteDir")) )
    {
        QUrl url = QFileDialog::getExistingDirectoryUrl(0,
                                            i18n("Choose where your notes save"),
                                            QDir::homePath(),
                                            QFileDialog::ShowDirsOnly
                                            | QFileDialog::DontResolveSymlinks);
        cfg.writeEntry("NoteDir", url.toLocalFile());
        config->sync();
        
    }

    QString noteDir(cfg.readEntry("NoteDir"));
    
    // create the Home note
    if (!QFile::exists(noteDir + "/Home.md")) {
        QFile::copy(QStandardPaths::locate(QStandardPaths::GenericDataLocation,
                                           QLatin1String("marknoto/Home.md")),
                    QString(noteDir + "/Home.md"));
        KFileMetaData::UserMetaData metaData(noteDir + "/Home.md");
        metaData.setTags(QStringList() << QString("@todo"));
    }
        
    // create the Trash dir
    QDir qDir(noteDir + "/Trash");
    if (!qDir.exists())
        qDir.mkpath(qDir.path());

    QIcon::setThemeName(QStringLiteral("breeze"));

    MarkNote *mainWindow = new MarkNote;
    mainWindow->show();
    
    return app.exec();
}
