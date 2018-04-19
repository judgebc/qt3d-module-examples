#include "rotatingtrefoilknot.h"

#include <qpropertyanimation.h>

RotatingTrefoilKnot::RotatingTrefoilKnot(Qt3DCore::QNode * parent) :
  TrefoilKnot(parent),
  m_thetaAnimation(new QPropertyAnimation(this)),
  m_phiAnimation(new QPropertyAnimation(this))
{
  m_thetaAnimation->setDuration(2000);
  m_thetaAnimation->setStartValue(0.0f);
  m_thetaAnimation->setEndValue(360.0f);
  m_thetaAnimation->setLoopCount(-1);
  m_thetaAnimation->setTargetObject(this);
  m_thetaAnimation->setPropertyName("phi");
  m_thetaAnimation->start();

  m_phiAnimation->setDuration(2000);
  m_phiAnimation->setStartValue(0.0f);
  m_phiAnimation->setEndValue(360.0f);
  m_phiAnimation->setLoopCount(-1);
  m_phiAnimation->setTargetObject(this);
  m_phiAnimation->setPropertyName("theta");
  m_phiAnimation->start();
}