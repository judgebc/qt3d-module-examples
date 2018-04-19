#pragma once

#include "trefoilknot.h"

class QPropertyAnimation;

class RotatingTrefoilKnot : public TrefoilKnot
{
public:
  explicit RotatingTrefoilKnot(Qt3DCore::QNode * parent = Q_NULLPTR);

private:
  QPropertyAnimation * m_thetaAnimation;
  QPropertyAnimation * m_phiAnimation;
};