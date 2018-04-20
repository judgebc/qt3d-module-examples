#include <QGuiApplication>

#include <Qt3DCore\qentity.h>
#include <Qt3DCore\qaspectengine.h>
#include <Qt3DCore\qtransform.h>

#include <Qt3DRender\qcamera.h>
#include <Qt3DRender\qrenderaspect.h>
#include <Qt3DRender\qtextureimage.h>
#include <Qt3DRender\qmesh.h>

#include <Qt3DInput\qinputaspect.h>

#include <Qt3DExtras\qphongmaterial.h>
#include <Qt3DExtras\qdiffusemapmaterial.h>
#include <Qt3DExtras\qforwardrenderer.h>
#include <Qt3DExtras\qt3dwindow.h>
#include <Qt3DExtras\qfirstpersoncameracontroller.h>
#include <Qt3DExtras\qplanemesh.h>
#include <Qt3DExtras\qnormaldiffusespecularmapmaterial.h>

#include "renderableentity.h"
#include "planeentity.h"
#include "rotatingtrefoilknot.h"
#include "barrel.h"

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

	{
		auto planeEntity{ new PlaneEntity(sceneRoot) };
		planeEntity->mesh()->setHeight(100.0f);
		planeEntity->mesh()->setWidth(100.0f);
		planeEntity->mesh()->setMeshResolution(QSize(20, 20));

		auto normalDSM{ new Qt3DExtras::QNormalDiffuseSpecularMapMaterial };
		normalDSM->setTextureScale(10.0f);
		normalDSM->setShininess(80.0f);
		normalDSM->setAmbient(QColor::fromRgbF(0.2f, 0.2f, 0.2f, 1.0f));

		auto diffuseImage{ new Qt3DRender::QTextureImage };
		diffuseImage->setSource(QUrl(QStringLiteral("qrc:/textures/floor/diffuse")));
		normalDSM->diffuse()->addTextureImage(diffuseImage);

		auto specularImage{ new Qt3DRender::QTextureImage };
		specularImage->setSource(QUrl(QStringLiteral("qrc:/textures/floor/specular")));
		normalDSM->specular()->addTextureImage(specularImage);

		auto normalImage{ new Qt3DRender::QTextureImage };
		normalImage->setSource(QUrl(QStringLiteral("qrc:/textures/floor/normal")));
		normalDSM->normal()->addTextureImage(normalImage);

		planeEntity->addComponent(normalDSM);
	}

	{
		auto chest{ new RenderableEntity(sceneRoot) };
		chest->transform()->setScale(0.03f);
		chest->mesh()->setSource(QUrl(QStringLiteral("qrc:/mesh/chest")));

		auto diffuseMap{ new Qt3DExtras::QDiffuseMapMaterial };
		diffuseMap->setSpecular(QColor::fromRgbF(0.2f, 0.2f, 0.2f, 1.0f));
		diffuseMap->setShininess(2.0f);

		auto diffuseImage{ new Qt3DRender::QTextureImage };
		diffuseImage->setSource(QUrl(QStringLiteral("qrc:/textures/chest")));
		diffuseMap->diffuse()->addTextureImage(diffuseImage);

		chest->addComponent(diffuseMap);
	}

	{
		auto trefoil{ new RotatingTrefoilKnot(sceneRoot) };
		trefoil->setPosition(QVector3D(0.0f, 3.5f, 0.0f));
		trefoil->setScale(0.5f);

		auto phongMat{ new Qt3DExtras::QPhongMaterial };
		phongMat->setDiffuse(QColor(204, 205, 75));
		phongMat->setSpecular(Qt::white);

		trefoil->addComponent(phongMat);
	}

	{
		auto basicBarrel{ new Barrel(sceneRoot) };
		basicBarrel->transform()->setTranslation(QVector3D(8.0f, 0.0f, 0.0f));

		auto rustyBarrel{ new Barrel(sceneRoot) };
		rustyBarrel->setDiffuse(Barrel::DiffuseColor::RustDiffuse);
		rustyBarrel->setSpecular(Barrel::SpecularColor::RustSpecular);
		rustyBarrel->setBumps(Barrel::Bumps::HardBumps);
		rustyBarrel->transform()->setTranslation(QVector3D(10.0f, 0.0f, 0.0f));

		auto blueBarrel{ new Barrel(sceneRoot) };
		blueBarrel->setDiffuse(Barrel::DiffuseColor::Blue);
		blueBarrel->setBumps(Barrel::Bumps::SoftBumps);
		blueBarrel->transform()->setTranslation(QVector3D(12.0f, 0.0f, 0.0f));

		auto greenBarrel{ new Barrel(sceneRoot) };
		greenBarrel->setDiffuse(Barrel::DiffuseColor::Green);
		greenBarrel->setBumps(Barrel::Bumps::SoftBumps);
		greenBarrel->transform()->setTranslation(QVector3D(14.0f, 0.0f, 0.0f));

		auto stainlessBarrel{ new Barrel(sceneRoot) };
		stainlessBarrel->setDiffuse(Barrel::DiffuseColor::StainlessSteelDiffuse);
		stainlessBarrel->setSpecular(Barrel::SpecularColor::StainlessSteelSpecular);
		stainlessBarrel->setBumps(Barrel::Bumps::NoBumps);
		stainlessBarrel->setShininess(150.0f);
		stainlessBarrel->transform()->setTranslation(QVector3D(16.0f, 0.0f, 0.0f));
	}

	return sceneRoot;
}
