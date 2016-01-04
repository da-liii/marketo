#include "listpanel.h"
#include "listitemdelegate.h"
#include <QPainter>
#include <QStandardItem>

ListItemDelegate::ListItemDelegate(ListPanel* parent)
{
    m_parent = parent;
}

void ListItemDelegate::setSelectedRect(QRect rect)
{
    pre_rect = m_rect;
    m_rect = rect;
}

void ListItemDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    QString text(m_parent->getTitleByIndex(index));
    
    QRect decorationRect = QRect(option.rect.topLeft()+QPoint(2, 0), QSize(24, 24));
    QFont font;
    font.setFamily(font.defaultFamily());
    QFontMetrics fm(font);
    QRect textRect = QRect(decorationRect.topRight()+QPoint(5, 4), QSize(fm.width(text), fm.height()));
    
    painter->drawPixmap(decorationRect, QIcon::fromTheme(QLatin1String("text-markdown")).pixmap(QSize(24, 24)));
    painter->drawText(textRect, text);
    
    if (option.rect.topLeft() == m_rect.topLeft()) {
        painter->setBackgroundMode(Qt::OpaqueMode);
        painter->fillRect(m_rect, QColor(0, 128, 255, 60));
        painter->fillRect(pre_rect, QColor(255, 255, 255, 0));
        painter->setBackgroundMode(Qt::TransparentMode);
    }
}

#include "listitemdelegate.moc"