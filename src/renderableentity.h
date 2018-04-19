#pragma once

#include <Qt3DCore\qentity.h>

namespace Qt3DRender
{
  class QMesh;
};

namespace Qt3DCore
{
  class QTransform;
}

class RenderableEntity : public Qt3DCore::QEntity
{
public:
  RenderableEntity(Qt3DCore::QNode * parent = Q_NULLPTR);

  Qt3DRender::QMesh * mesh() const;
  Qt3DCore::QTransform * transform() const;

private:
  Qt3DRender::QMesh * m_mesh;
  Qt3DCore::QTransform * m_transform;
};