#ifndef MARKETO_PART_H
#define MARKETO_PART_H

#include <KPluginFactory>
#include <KParts/ReadOnlyPart>
#include <QLabel>

namespace Marketo {
class Part : public KParts::ReadOnlyPart
{
    Q_OBJECT
    
private:
    QLabel *mMainWidget;
    
public:
    Part(QWidget *parentWidget, QObject *parent, const QVariantList&);
    QLabel* MainWidget() { return mMainWidget; };
    
    virtual ~Part();
};
} // namespace Marketo
#endif
