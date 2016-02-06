#ifndef LISTITEMDELEGATE_H
#define LISTITEMDELEGATE_H

#include <QStyledItemDelegate>

class ListPanel;
class QRect;

class ListItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit ListItemDelegate(ListPanel *parent);
    virtual void paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const override;
    
private:
    ListPanel *m_parent;
    QRect pre_rect;
    QRect m_rect;
};

#endif