#pragma once

#include <Qt3DCore/qentity.h>

namespace Qt3DExtras
{
  class QPlaneMesh;
}

namespace Qt3DCore
{
  class QTransform;
}

class PlaneEntity : public Qt3DCore::QEntity
{
public:
  explicit PlaneEntity(Qt3DCore::QEntity * parent = Q_NULLPTR);

  Qt3DExtras::QPlaneMesh * mesh() const;

private:
  Qt3DExtras::QPlaneMesh * m_mesh;
  Qt3DCore::QTransform * m_transform;
};