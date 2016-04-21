#include "webpage.h"

#include <QUrl>

bool WebPage::acceptNavigationRequest(const QUrl & url, QWebEnginePage::NavigationType type, bool)
{
    if (type == QWebEnginePage::NavigationTypeLinkClicked)
    {
        emit linkClicked(url);
        return false;
    }
    return true;
}