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
    QRect textRect = QRect(decorationRect.topRight()+QPoint(5, 4), QSize(fm.width(text), fm.height()));
    
    painter->drawPixmap(decorationRect, QIcon::fromTheme(QLatin1String("text-markdown")).pixmap(QSize(24, 24)));
    painter->drawText(textRect, text);
    
//    QStandardItem *pluginItem = qobject_cast<const QStandardItemModel *>(index.model())->itemFromIndex(index);
//    pluginItem->setCheckState(Qt::Checked);
}


#include "listitemdelegate.moc"
