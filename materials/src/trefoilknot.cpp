#include "trefoilknot.h"

#include <Qt3DCore\qtransform.h>

#include <Qt3DRender\qmesh.h>

#include <qmatrix4x4.h>

TrefoilKnot::TrefoilKnot(Qt3DCore::QNode * parent) :
  RenderableEntity(parent),
  m_position(),
  m_scale(1.0f)
{
  mesh()->setSource(QUrl(QStringLiteral("qrc:/mesh/trefoil")));
}

void TrefoilKnot::updateTransform()
{
  QMatrix4x4 m;
  m.translate(m_position);
  m.rotate(m_phi, QVector3D(1.0f, 0.0f, 0.0f));
  m.rotate(m_phi, QVector3D(0.0f, 1.0f, 0.0f));
  m.scale(m_scale);

  transform()->setMatrix(m);
}

float TrefoilKnot::theta() const
{
  return m_theta;
}

float TrefoilKnot::phi() const
{
  return m_phi;
}

QVector3D TrefoilKnot::position() const
{
  return m_position;
}

float TrefoilKnot::scale() const
{
  return m_scale;
}

void TrefoilKnot::setTheta(float theta)
{
  if(m_theta == theta) return;

  m_theta = theta;
  emit thetaChanged(theta);
  updateTransform();
}

void TrefoilKnot::setPhi(float phi)
{
  if(m_phi == phi) return;

  m_phi = phi;
  emit phiChanged(phi);
  updateTransform();
}

void TrefoilKnot::setPosition(QVector3D position)
{
  if(m_position == position) return;

  m_position = position;
  emit positionChanged(position);
  updateTransform();
}

void TrefoilKnot::setScale(float scale)
{
  if(m_scale == scale) return;

  m_scale = scale;
  emit scaleChanged(scale);
  updateTransform();
}