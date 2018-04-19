#include <QGuiApplication>

#include <QtWidgets\QApplication>
#include <QtWidgets\QWidget>
#include <QtWidgets\QHBoxLayout>
#include <QtWidgets\QCheckBox>
#include <QtWidgets\QCommandLinkButton>

#include <QtGui\QScreen>

#include <Qt3DCore\QTransform>
#include <Qt3DCore\QAspectEngine>

#include <Qt3DRender\QMesh>
#include <Qt3DRender\QCamera>
#include <Qt3DRender\QTechnique>
#include <Qt3DRender\QMaterial>
#include <Qt3DRender\QEffect>
#include <Qt3DRender\QTexture>
#include <Qt3DRender\QRenderPass>
#include <Qt3DRender\QSceneLoader>
#include <Qt3DRender\QPointLight>
#include <Qt3DRender\QRenderAspect>

#include <Qt3DInput\QInputAspect>

#include <Qt3DExtras\qtorusmesh>
#include <Qt3DExtras\QForwardRenderer>
#include <Qt3DExtras\Qt3DWindow>
#include <Qt3DExtras\QFirstPersonCameraController>

#include "scenemodifier.h"

void addWidgets(QWidget *, QVBoxLayout *, SceneModifier *);
Qt3DCore::QEntity * setupScene(Qt3DExtras::Qt3DWindow *);

int main(int argc, char ** argv)
{
	QApplication app(argc, argv);

	auto view{ new Qt3DExtras::Qt3DWindow() };
	view->defaultFrameGraph()->setClearColor(QColor(QRgb(0x4d4d4f)));

	auto root = setupScene(view);
	auto sceneModifier{ new SceneModifier(root) };

	QWidget * container{ QWidget::createWindowContainer(view) };
	container->setMinimumSize(QSize(200, 100));
	container->setMaximumSize(view->screen()->size());

	auto widget{ new QWidget };
	auto hLayout{ new QHBoxLayout(widget) };
	auto vLayout{ new QVBoxLayout };

	vLayout->setAlignment(Qt::AlignTop);
	hLayout->addWidget(container, 1);
	hLayout->addLayout(vLayout);

	widget->setWindowTitle(QStringLiteral("Basic Shapes"));

	addWidgets(widget, vLayout, sceneModifier);

	widget->show();
	widget->resize(1200, 1000);

	return app.exec();
}

Qt3DCore::QEntity * setupScene(Qt3DExtras::Qt3DWindow * view)
{
	auto input{ new Qt3DInput::QInputAspect };
	view->registerAspect(input);

	auto cameraEntity = view->camera();

	cameraEntity->lens()->setPerspectiveProjection(45.0f, 16.0f / 9.0f, 0.1f, 100.0f);
	cameraEntity->setPosition(QVector3D(0, 0, 20.0f));
	cameraEntity->setUpVector(QVector3D(0, 1, 0));
	cameraEntity->setViewCenter(QVector3D(0, 0, 0));

	auto rootEntity{ new Qt3DCore::QEntity };

	auto lightEntity{ new Qt3DCore::QEntity(rootEntity) };
	auto light{ new Qt3DRender::QPointLight(lightEntity) };
	light->setColor("white");
	light->setIntensity(1);
	lightEntity->addComponent(light);

	auto lightTransform{ new Qt3DCore::QTransform(lightEntity) };
	lightTransform->setTranslation(cameraEntity->position());
	lightEntity->addComponent(lightTransform);

	auto camController{ new Qt3DExtras::QFirstPersonCameraController(rootEntity) };
	camController->setCamera(cameraEntity);

	view->setRootEntity(rootEntity);

	return rootEntity;
}

void addWidgets(QWidget * parent, QVBoxLayout * layout, SceneModifier * sceneModifier)
{
	auto info{ new QCommandLinkButton };
	info->setText(QStringLiteral("Qt3D ready-made meshes"));
	info->setDescription(QString::fromLatin1("Qt3D provides several ready-made meshes, like torus, cylinder, cone, cube, plane, and sphere."));
	info->setIconSize(QSize(0, 0));

	auto torus{ new QCheckBox(parent) };
	torus->setText(QStringLiteral("Torus"));

	auto cone{ new QCheckBox(parent) };
	cone->setText(QStringLiteral("Cone"));

	auto cylinder{ new QCheckBox(parent) };
	cylinder->setText(QStringLiteral("Cylinder"));

	auto cuboid{ new QCheckBox(parent) };
	cuboid->setText(QStringLiteral("Cuboid"));

	auto plane{ new QCheckBox(parent) };
	plane->setText(QStringLiteral("Plane"));

	auto sphere{ new QCheckBox(parent) };
	sphere->setText(QStringLiteral("Sphere"));

	layout->addWidget(info);
	layout->addWidget(torus);
	layout->addWidget(cone);
	layout->addWidget(cylinder);
	layout->addWidget(cuboid);
	layout->addWidget(plane);
	layout->addWidget(sphere);

	QObject::connect(torus, &QCheckBox::stateChanged, sceneModifier, &SceneModifier::enableTorus);

	torus->setChecked(true);
	cone->setChecked(true);
	cylinder->setChecked(true);
	cuboid->setChecked(true);
	plane->setChecked(true);
	sphere->setChecked(true);
}