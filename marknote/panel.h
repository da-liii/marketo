#ifndef PANEL_H
#define PANEL_H

#include <QWidget>
#include <KUrl>

class Panel : public QWidget
{
    Q_OBJECT

public:
    explicit Panel(QWidget* parent = 0);
    virtual ~Panel();

    /** Returns the current set URL of the active Dolphin view. */
    KUrl url() const;

    /** @see QWidget::sizeHint() */
    virtual QSize sizeHint() const;

signals:
    void changeUrl(const KUrl &url);
    
public slots:
    /**
     * This is invoked every time the folder being displayed in the
     * active Dolphin view changes.
     */
    void setUrl(const KUrl& url);

    /**
     * Refreshes the view to get synchronized with the settings.
     */
    virtual void readSettings();

protected:
    /**
     * Must be implemented by derived classes and is invoked when
     * the URL has been changed (see Panel::setUrl()).
     * @return True, if the new URL will get accepted by the derived
     *         class. If false is returned,
     *         the URL will be reset to the previous URL.
     */
    virtual bool urlChanged() = 0;

private:
    KUrl m_url;
};

#endif // PANEL_H
