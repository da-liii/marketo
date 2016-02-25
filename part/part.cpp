#include "part.h"

namespace Marketo {
Part::Part(QWidget* parentWidget, QObject* parent, const QVariantList&)
    : KParts::ReadOnlyPart(parent)
{
    mMainWidget = new QLabel();
    mMainWidget->setText("Hello");
    setWidget(mMainWidget);
}

Part::~Part()
{
}

} // namespace Marketo
