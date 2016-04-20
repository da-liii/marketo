#include "listpanel.h"
#include "listitemdelegate.h"
#include <QPainter>
#include <QStandardItem>

ListItemDelegate::ListItemDelegate(ListPanel* parent)
{
    m_parent = parent;
}

void ListItemDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    QString text(m_parent->getTitleByIndex(index));
    
    QRect decorationRect = QRect(option.rect.topLeft()+QPoint(2, 0), QSize(24, 24));
    QFont font;
    font.setFamily(font.defaultFamily());
    QFontMetrics fm(font);
    QRect textRect = QRect(decorationRect.topRight()+QPoint(5, 2), QSize(fm.width(text)+2, fm.height()+4));
    
    painter->setBackgroundMode(Qt::TransparentMode);
    painter->drawPixmap(decorationRect, QIcon::fromTheme(QLatin1String("text-markdown")).pixmap(QSize(24, 24)));
    painter->drawText(textRect, text);
    
    painter->setBackgroundMode(Qt::OpaqueMode);
    if (option.state & QStyle::State_Selected)
        painter->fillRect(option.rect, QColor(0, 128, 255, 60));
    else if (option.state & QStyle::State_MouseOver)
        painter->fillRect(option.rect, QColor(0, 128, 255, 10));
    else
        painter->fillRect(option.rect, QColor(255, 255, 255, 0));
}

#include "listitemdelegate.moc"