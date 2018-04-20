#include "orbittransformcontroller.h"

#include <Qt3DCore\qtransform.h>

OrbitTransformController::OrbitTransformController(QObject * parent) :
	QObject(parent),
	m_target(nullptr),
	m_matrix(),
	m_radius(1.0f),
	m_angle(0.0f)
{
}

void OrbitTransformController::setTarget(Qt3DCore::QTransform * target)
{
	if (target == m_target) return;

	m_target = target;
	emit targetChanged();
}

Qt3DCore::QTransform * OrbitTransformController::target() const
{
	return m_target;
}

void OrbitTransformController::setRadius(float radius)
{
	if (radius == m_radius) return;

	m_radius = radius;
	updateMatrix();
	emit radiusChanged();
}

float OrbitTransformController::radius() const
{
	return m_radius;
}

void OrbitTransformController::setAngle(float angle)
{
	if (angle == m_angle) return;

	m_angle = angle;
	updateMatrix();
	emit angleChanged();
}

float OrbitTransformController::angle() const
{
	return m_angle;
}

void OrbitTransformController::updateMatrix()
{
	m_matrix.setToIdentity();
	m_matrix.rotate(m_angle, QVector3D(0.0, 1.0, 0.0));
	m_matrix.translate(m_radius, 0.0, 0.0);

	m_target->setMatrix(m_matrix);
}