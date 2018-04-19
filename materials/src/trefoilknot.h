#pragma once

#include <Qt3DCore\qentity.h>
#include <qvector3d.h>

#include "renderableentity.h"

class TrefoilKnot : public RenderableEntity
{
  Q_OBJECT
  Q_PROPERTY(float theta READ theta WRITE setTheta NOTIFY thetaChanged)
  Q_PROPERTY(float phi READ phi WRITE setPhi NOTIFY phiChanged)
  Q_PROPERTY(float scale READ scale WRITE setScale NOTIFY scaleChanged)
  Q_PROPERTY(QVector3D position READ position WRITE setPosition NOTIFY positionChanged)

public:
  explicit TrefoilKnot(Qt3DCore::QNode * parent = Q_NULLPTR);

  float theta() const;
  float phi() const;
  QVector3D position() const;
  float scale() const;

public slots:
  void setTheta(float theta);
  void setPhi(float phi);
  void setPosition(QVector3D position);
  void setScale(float scale);

signals:
  void thetaChanged(float theta);
  void phiChanged(float phi);
  void positionChanged(QVector3D position);
  void scaleChanged(float scale);

protected:
  void updateTransform();

private:
  float m_theta;
  float m_phi;
  QVector3D m_position;
  float m_scale;
};