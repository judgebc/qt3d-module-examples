#include <QGuiApplication>

#include <Qt3DCore\QEntity>
#include <Qt3DCore\qtransform.h>
#include <Qt3DCore\qaspectengine.h>

#include <Qt3DRender\qcamera.h>
#include <Qt3DRender\qcameralens.h>
#include <Qt3DRender\qrenderaspect.h>

#include <Qt3DInput\qinputaspect.h>

#include <Qt3DExtras\qforwardrenderer.h>
#include <Qt3DExtras\qphongmaterial.h>
#include <Qt3DExtras\qcylindermesh.h>
#include <Qt3DExtras\qspheremesh.h>
#include <Qt3DExtras\qtorusmesh.h>
#include <Qt3DExtras\qt3dwindow.h>
#include <Qt3DExtras\qorbitcameracontroller.h>

#include <qpropertyanimation.h>

Qt3DCore::QEntity * createScene();

int main(int argc, char * argv[])
{
  QGuiApplication app(argc, argv);

  Qt3DExtras::Qt3DWindow view;

  Qt3DRender::QCamera * camera = view.camera();
  camera->lens()->setPerspectiveProjection(45.0f, 16.0f / 9.0f, 0.1f, 1000.0f);
  camera->setPosition(QVector3D(0.0f, 0.0f, 40.0f));
  camera->setViewCenter(QVector3D(0.0f, 0.0f, 0.0f));

  Qt3DCore::QEntity * scene = createScene();

  auto orbitController{ new Qt3DExtras::QOrbitCameraController(scene) };
  orbitController->setLinearSpeed(50.0f);
  orbitController->setLookSpeed(180.0f);
  orbitController->setCamera(camera);

  view.setRootEntity(scene);
  view.show();

  return app.exec();
}

Qt3DCore::QEntity * createScene()
{
	auto root{ new Qt3DCore::QEntity };

	auto material{ new Qt3DExtras::QPhongMaterial(root) };

	{
		auto torusEntity{ new Qt3DCore::QEntity(root) };
		auto torusMesh{ new Qt3DExtras::QTorusMesh };
		torusMesh->setRadius(5);
		torusMesh->setMinorRadius(1);
		torusMesh->setRings(100);
		torusMesh->setSlices(20);

		auto torusTransform{ new Qt3DCore::QTransform };
		torusTransform->setScale3D(QVector3D(1.5, 1, 0.5));
		torusTransform->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(1, 0, 0), 45.0f));

		torusEntity->addComponent(material);
		torusEntity->addComponent(torusMesh);
		torusEntity->addComponent(torusTransform);
	}

	{
		auto sphereEntity{ new Qt3DCore::QEntity(root) };
		auto sphereMesh{ new Qt3DExtras::QSphereMesh };
		sphereMesh->setRadius(3);

		auto sphereTransform{ new Qt3DCore::QTransform };

		auto sphereRotateAnimation{ new QPropertyAnimation(sphereTransform) };
		sphereRotateAnimation->setPropertyName("angle");
		sphereRotateAnimation->setStartValue(QVariant::fromValue(0));
		sphereRotateAnimation->setStartValue(QVariant::fromValue(360));
		sphereRotateAnimation->setDuration(10000);
		sphereRotateAnimation->setLoopCount(-1);
		sphereRotateAnimation->start();

		sphereEntity->addComponent(sphereMesh);
		sphereEntity->addComponent(sphereTransform);
		sphereEntity->addComponent(material);
	}

	return root;
}
