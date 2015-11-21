#ifndef ICONFILTER_H
#define ICONFILTER_H

#include <QFileIconProvider>

class QFileInfo;

class IconFilter : public QFileIconProvider
{
 public:
  IconFilter() = default;
  ~IconFilter();
  
  QIcon icon(IconType type) const override;
  QIcon icon(const QFileInfo &info) const override;
  QString type(const QFileInfo &info) const override;
};

#endif
