#pragma once

#include <QtCore\QObject>

#include <memory>

namespace Qt3DCore
{
	class QEntity;
}

class SceneModifier : public QObject
{
	Q_OBJECT
public:
	explicit SceneModifier(Qt3DCore::QEntity * rootEntity);

public slots:
	void enableTorus(bool enabled);
	void enableCone(bool enabled);
	void enableCylinder(bool enabled);
	void enableCuboid(bool enabled);
	void enablePlane(bool enabled);
	void enableSphere(bool enabled);

private:
	Qt3DCore::QEntity * m_coneEntity;
	Qt3DCore::QEntity * m_cylinderEntity;
	Qt3DCore::QEntity * m_torusEntity;
	Qt3DCore::QEntity * m_cuboidEntity;
	Qt3DCore::QEntity * m_planeEntity;
	Qt3DCore::QEntity * m_sphereEntity;
};