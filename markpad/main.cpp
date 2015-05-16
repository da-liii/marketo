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

#include "mainwindow.h"

#include <QDebug>

#include <KAboutData>
#include <KLocalizedString>

#include <QApplication>
#include <QCommandLineParser>

#define DESCRIPTION "KMarkPad - Advanced Markdown Editor"

#define VERSION "0.1"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    /*
     * enable high dpi support
     */
    app.setAttribute(Qt::AA_UseHighDpiPixmaps, true);
    KLocalizedString::setApplicationDomain("kmarkpad");

    KAboutData about(QStringLiteral("kmarkpad"),
                i18n("KMarkPad"),
                QStringLiteral(VERSION),
                i18n(DESCRIPTION),
                KAboutLicense::LGPL_V2,
                i18n("(C) 2015 Darcy Shen"),
                QString(),
                QStringLiteral("https://github.com/sadhen/KMarkNote"));
    about.addAuthor(i18n("Darcy Shen"), i18n("Developer"), "sadhen@zoho.com" );

    QCommandLineParser parser;
    about.setupCommandLine(&parser);
    parser.setApplicationDescription(about.shortDescription());
    parser.addHelpOption();
    parser.addVersionOption();
    parser.process(app);
    about.processCommandLine(&parser);
    
    MainWindow *mainwindow = new MainWindow();

    return app.exec();
}
