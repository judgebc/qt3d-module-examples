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

void addWidgets(QWidget *, QVBoxLayout *);

int main(int argc, char ** argv)
{
	QApplication app(argc, argv);

	auto view{ new Qt3DExtras::Qt3DWindow() };
	view->defaultFrameGraph()->setClearColor(QColor(QRgb(0x4d4d4f)));

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

	addWidgets(widget, vLayout);

	widget->show();
	widget->resize(1200, 1000);

	return app.exec();
}

void addWidgets(QWidget * parent, QVBoxLayout * layout)
{
	auto info{ new QCommandLinkButton };
	info->setText(QStringLiteral("Qt3D ready-made meshes"));
	info->setDescription(QString::fromLatin1("Qt3D provides several ready-made meshes, like torus, cylinder, cone, cube, plane, and sphere."));
	info->setIconSize(QSize(0, 0));

	auto torus{ new QCheckBox(parent) };
	torus->setChecked(true);
	torus->setText(QStringLiteral("Torus"));

	auto cone{ new QCheckBox(parent) };
	cone->setChecked(true);
	cone->setText(QStringLiteral("Cone"));

	auto cylinder{ new QCheckBox(parent) };
	cylinder->setChecked(true);
	cylinder->setText(QStringLiteral("Cylinder"));

	auto cuboid{ new QCheckBox(parent) };
	cuboid->setChecked(true);
	cuboid->setText(QStringLiteral("Cuboid"));

	auto plane{ new QCheckBox(parent) };
	plane->setChecked(true);
	plane->setText(QStringLiteral("Plane"));

	auto sphere{ new QCheckBox(parent) };
	sphere->setChecked(true);
	sphere->setText(QStringLiteral("Sphere"));

	layout->addWidget(info);
	layout->addWidget(torus);
	layout->addWidget(cone);
	layout->addWidget(cylinder);
	layout->addWidget(cuboid);
	layout->addWidget(plane);
	layout->addWidget(sphere);
}