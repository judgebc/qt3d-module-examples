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

Qt3DCore::QEntity * createSceneRoot();

int main(int argc, char * argv[])
{
  QGuiApplication app(argc, argv);

  Qt3DCore::QEntity * sceneRoot{ createSceneRoot() };

  Qt3DExtras::Qt3DWindow view;
  view.setRootEntity(sceneRoot);
  view.show();

  return app.exec();
}

Qt3DCore::QEntity * createSceneRoot()
{
  Qt3DCore::QEntity * sceneRoot{ new Qt3DCore::QEntity };

  return sceneRoot;
}
