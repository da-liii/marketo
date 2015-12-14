#include "taglist.h"

#include <QList>
#include <QLabel>
#include <QDebug>

TagList::TagList(QWidget* parent)
    : QListWidget(parent)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFrameShape(QFrame::NoFrame);
    setFlow(QListView::LeftToRight);
    setContentsMargins(0, 0, 0, 0);
    setFixedHeight(24);
    sizePolicy().setHorizontalPolicy(QSizePolicy::MinimumExpanding);
}

void TagList::stretchWidth()
{
    int size = 0;
    for (auto item : findItems("*", Qt::MatchWildcard)) {
        if (!item->text().isEmpty()) {
            setItemWidget(item, new QLabel(item->text()));
            item->setText("");
            item->setSizeHint(itemWidget(item)->sizeHint() + QSize(5, 5));
        }
        size += itemWidget(item)->sizeHint().width() + 5;
    }
    
    setFixedWidth(size);
}

QString TagList::tagText(int i) const {
    return (dynamic_cast<QLabel*> (itemWidget(item(i))))->text();
}

void TagList::addTags(const QString &tags)
{
    QList<QListWidgetItem *> *list = new QList<QListWidgetItem *>;
    for (auto tag : tags.split(";")) {
        for (auto iter : findItems("*", Qt::MatchWildcard))
            if (tag == tagText(row(iter)))
                list->append(iter);
        if (list->isEmpty())
            addItem(tag);
        else
            for (auto iter=list->cbegin(); iter!=list->cend(); iter++) {
                auto itemToDelete = takeItem(row(*iter));
                delete itemWidget(itemToDelete);
                delete itemToDelete;
            }
    }
    delete list;
}

TagList::~TagList()
{
    for (auto item : findItems("*", Qt::MatchWildcard))
        delete itemWidget(item);
}



#include "taglist.moc"