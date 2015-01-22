#include "panel.h"
#include <KUrl>

Panel::Panel(QWidget* parent)
    : QWidget(parent)
    , m_url()
{
}

Panel::~Panel()
{
}

KUrl Panel::url() const
{
    return m_url;
}

QSize Panel::sizeHint() const
{
    // The size hint will be requested already when starting Dolphin even
    // if the panel is invisible. For performance reasons most panels delay
    // the creation and initialization of widgets until a showEvent() is called.
    // Because of this the size-hint of the embedded widgets cannot be used
    // and a default size is provided:
    return QSize(180, 180);
}

void Panel::setUrl(const KUrl& url)
{
    if (url.equals(m_url, KUrl::CompareWithoutTrailingSlash)) {
        return;
    }

    const KUrl oldUrl = m_url;
    m_url = url;
    const bool accepted = urlChanged();
    if (!accepted) {
        m_url = oldUrl;
    }
}

void Panel::readSettings()
{

}

#include "panel.moc"
