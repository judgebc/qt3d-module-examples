#include <QGuiApplication>

#include <Qt3DCore\QEntity>
#include <Qt3DCore\qtransform.h>

#include <Qt3DRender\qcamera.h>
#include <Qt3DRender\qcameralens.h>

#include <Qt3DExtras\qfirstpersoncameracontroller.h>
#include <Qt3DExtras\qt3dwindow.h>
#include <Qt3DExtras\qforwardrenderer.h>
#include <Qt3DExtras\qskyboxentity.h>

#include <iostream>

Qt3DCore::QEntity * createScene(Qt3DRender::QCamera *);

int main(int argc, char * argv[])
{
	QGuiApplication app(argc, argv);

	Qt3DExtras::Qt3DWindow view;

	view.defaultFrameGraph()->setClearColor(Qt::red);

	Qt3DRender::QCamera * camera = view.camera();

	camera->lens()->setPerspectiveProjection(45.0f, 16.0f / 9.0f, 0.1f, 1000.0f);
	camera->setPosition(QVector3D(0.0f, 0.0f, 0.0f));
	camera->setUpVector(QVector3D(0.0f, 1.0f, 0.0f));
	camera->setViewCenter(QVector3D(0.0f, 0.0f, -1.0f));

	Qt3DCore::QEntity * scene = createScene(camera);

	auto controller{ new Qt3DExtras::QFirstPersonCameraController(scene) };
	controller->setLinearSpeed(50.0f);
	controller->setLookSpeed(180.0f);
	controller->setCamera(camera);

	view.setRootEntity(scene);

	view.show();

	return app.exec();
}

Qt3DCore::QEntity * createScene(Qt3DRender::QCamera * cam)
{
	auto root{ new Qt3DCore::QEntity };

	{
		auto skybox{ new Qt3DExtras::QSkyboxEntity(root) };
		skybox->setBaseName(QStringLiteral("qrc:/box"));
		skybox->setExtension(QStringLiteral(""));

		auto skyboxTransform{ new Qt3DCore::QTransform };
		QMatrix3x3 m(cam->viewMatrix().normalMatrix());
		QMatrix4x4 m2(m);
		skyboxTransform->setMatrix(m2);
		skyboxTransform->setScale(100.0f);

		QObject::connect(cam, &Qt3DRender::QCamera::viewMatrixChanged, [cam, skyboxTransform]()
		{
			QMatrix3x3 m(cam->viewMatrix().normalMatrix());
			QMatrix4x4 m2(m);

			skyboxTransform->setMatrix(m2);
			skyboxTransform->setScale(100.0f);
		});

		skybox->addComponent(skyboxTransform);
	}

	return root;
}
