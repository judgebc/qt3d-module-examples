#include <QGuiApplication>

#include <Qt3DCore\qentity.h>
#include <Qt3DCore\qaspectengine.h>

#include <Qt3DRender\qcamera.h>
#include <Qt3DRender\qrenderaspect.h>
#include <Qt3DRender\qtextureimage.h>

#include <Qt3DInput\qinputaspect.h>

#include <Qt3DExtras\qphongalphamaterial.h>
#include <Qt3DExtras\qdiffusemapmaterial.h>
#include <Qt3DExtras\qforwardrenderer.h>
#include <Qt3DExtras\qt3dwindow.h>
#include <Qt3DExtras\qfirstpersoncameracontroller.h>

Qt3DCore::QEntity * createSceneRoot(const Qt3DExtras::Qt3DWindow&);

int main(int argc, char * argv[])
{
  QGuiApplication app(argc, argv);

  Qt3DExtras::Qt3DWindow view;

  Qt3DCore::QEntity * sceneRoot{ createSceneRoot(view) };

  view.setRootEntity(sceneRoot);
  view.show();

  return app.exec();
}

Qt3DCore::QEntity * createSceneRoot(const Qt3DExtras::Qt3DWindow& view)
{
  Qt3DCore::QEntity * sceneRoot{ new Qt3DCore::QEntity };

  {
    Qt3DRender::QCamera * camera = view.camera();
    camera->setProjectionType(Qt3DRender::QCameraLens::PerspectiveProjection);
    camera->setUpVector(QVector3D(0.0, 1.0f, 0.0f));
    camera->setViewCenter(QVector3D(0.0f, 3.5f, 0.0f));
    camera->setPosition(QVector3D(0.0f, 3.5f, 25.0f));

    auto camController{ new Qt3DExtras::QFirstPersonCameraController(sceneRoot) };
    camController->setCamera(camera);
  }

  return sceneRoot;
}
