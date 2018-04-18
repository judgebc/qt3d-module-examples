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

	widget->show();
	widget->resize(1200, 1000);

	return app.exec();
}
