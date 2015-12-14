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
    for (auto item : findItems("*", Qt::MatchWildcard))
        size += itemWidget(item)->sizeHint().width() + 5;
    
    setFixedWidth(size);
}

QString TagList::tagText(int i) const {
    return (dynamic_cast<QLabel*> (itemWidget(item(i))))->text();
}

void TagList::addTags(const QString &tags)
{
    qDebug() << "add " + tags + " to tagList";
    QStringListIterator tagIter(tags.split(";", QString::SkipEmptyParts));
    while (tagIter.hasNext()) {
        QString tag(tagIter.next());
        QListWidgetItem *item = nullptr;
        
        // the full item list is a set
        for (auto iter : findItems("*", Qt::MatchWildcard))
            if (tag == tagText(row(iter))) {
                item = iter;
                break;
            }
            
        if (item == nullptr) {
            QListWidgetItem *newItem = new QListWidgetItem(this);
            setItemWidget(newItem, new QLabel(tag));
            newItem->setText("");
            newItem->setSizeHint(itemWidget(newItem)->sizeHint() + QSize(5, 5));
            addItem(newItem);
        } else {
            auto itemToDelete = takeItem(row(item));
            delete itemWidget(itemToDelete);
            delete itemToDelete;
        }
    } // end of outer while
}

TagList::~TagList()
{
    for (auto item : findItems("*", Qt::MatchWildcard))
        delete itemWidget(item);
}



#include "taglist.moc"