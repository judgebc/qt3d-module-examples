#include <QGuiApplication>

#include <Qt3DCore\QEntity>

#include <Qt3DRender\qcamera.h>
#include <Qt3DRender\qcameralens.h>

#include <Qt3DExtras\qorbitcameracontroller.h>
#include <Qt3DExtras\qt3dwindow.h>

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

  auto controller{ new Qt3DExtras::QOrbitCameraController(scene) };
  controller->setLinearSpeed(50.0f);
  controller->setLookSpeed(180.0f);
  controller->setCamera(camera);

  view.setRootEntity(scene);

  view.show();

  return app.exec();
}

Qt3DCore::QEntity * createScene()
{
	auto root{ new Qt3DCore::QEntity };

	return root;
}
