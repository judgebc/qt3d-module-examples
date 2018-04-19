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
  PlaneEntity(Qt3DCore::QNode * parent = Q_NULLPTR);
  ~PlaneEntity();

private:
  Qt3DExtras::QPlaneMesh * m_mesh;
  Qt3DCore::QTransform * m_transform;
};