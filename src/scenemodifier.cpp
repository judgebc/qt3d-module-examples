#include "scenemodifier.h"

#include <Qt3DCore\qentity.h>
#include <Qt3DCore/qtransform.h>

#include <Qt3DExtras/QTorusMesh>
#include <Qt3DExtras/QConeMesh>
#include <Qt3DExtras/QCylinderMesh>
#include <Qt3DExtras/QCuboidMesh>
#include <Qt3DExtras/QPlaneMesh>
#include <Qt3DExtras/QSphereMesh>
#include <Qt3DExtras/QPhongMaterial>

SceneModifier::SceneModifier(Qt3DCore::QEntity * rootEntity) :
	m_torusEntity(new Qt3DCore::QEntity(rootEntity)),
	m_coneEntity(new Qt3DCore::QEntity(rootEntity)),
	m_cuboidEntity(new Qt3DCore::QEntity(rootEntity)),
	m_cylinderEntity(new Qt3DCore::QEntity(rootEntity)),
	m_planeEntity(new Qt3DCore::QEntity(rootEntity)),
	m_sphereEntity(new Qt3DCore::QEntity(rootEntity))
{
	{
		auto torusMesh{ new Qt3DExtras::QTorusMesh };
		torusMesh->setRadius(1.0f);
		torusMesh->setMinorRadius(0.4f);
		torusMesh->setRings(100);
		torusMesh->setSlices(20);

		auto torusTransform{ new Qt3DCore::QTransform };
		torusTransform->setScale(2.0f);
		torusTransform->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 1.0f, 0.0f), 25.0f));
		torusTransform->setTranslation(QVector3D(5.0f, 4.0f, 0.0f));

		auto torusMaterial{ new Qt3DExtras::QPhongMaterial };
		torusMaterial->setDiffuse(QColor(QRgb(0xbeb32b)));

		m_torusEntity->addComponent(torusMesh);
		m_torusEntity->addComponent(torusMaterial);
		m_torusEntity->addComponent(torusTransform);
	}
}

void SceneModifier::enableTorus(bool enabled)
{
	m_torusEntity->setEnabled(enabled);
}

void SceneModifier::enableCone(bool enabled)
{
	m_coneEntity->setEnabled(enabled);
}

void SceneModifier::enableCylinder(bool enabled)
{
	m_cylinderEntity->setEnabled(enabled);
}

void SceneModifier::enableCuboid(bool enabled)
{
	m_cuboidEntity->setEnabled(enabled);
}

void SceneModifier::enablePlane(bool enabled)
{
	m_planeEntity->setEnabled(enabled);
}

void SceneModifier::enableSphere(bool enabled)
{
	m_sphereEntity->setEnabled(enabled);
}
