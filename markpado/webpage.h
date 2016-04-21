#ifndef WEBPAGE_H
#define WEBPAGE_H
#include <QWebEnginePage>

class WebPage : public QWebEnginePage
{
    Q_OBJECT
public:
    WebPage(QObject* parent = 0) : QWebEnginePage(parent){}

    bool acceptNavigationRequest(const QUrl & url, QWebEnginePage::NavigationType type, bool);
signals:
    void linkClicked(const QUrl&);

};
#endif