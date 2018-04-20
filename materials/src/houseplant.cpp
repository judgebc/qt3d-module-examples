#include "houseplant.h"
#include "renderableentity.h"

#include <Qt3DCore\qtransform.h>

#include <Qt3DRender\qtextureimage.h>
#include <Qt3DRender\qmesh.h>

#include <Qt3DExtras\qnormaldiffusemapmaterial.h>
#include <Qt3DExtras\qnormaldiffusemapalphamaterial.h>

#include <vector>
#include <string>

std::vector<std::string> potNames{
	"cross",
	"square",
	"triangle",
	"sphere"
};

std::vector<std::string> plantNames{
	"bamboo",
	"palm",
	"pine",
	"spikes",
	"shrub"
};

HousePlant::HousePlant(Qt3DCore::QNode * parent) :
	Qt3DCore::QEntity(parent),
	m_pot(nullptr),
	m_plant(nullptr),
	m_cover(nullptr),
	m_potMaterial(new Qt3DExtras::QNormalDiffuseMapMaterial),
	m_plantMaterial(new Qt3DExtras::QNormalDiffuseMapAlphaMaterial),
	m_coverMaterial(new Qt3DExtras::QNormalDiffuseMapMaterial),
	m_potImage(new Qt3DRender::QTextureImage),
	m_potNormalImage(new Qt3DRender::QTextureImage),
	m_plantImage(new Qt3DRender::QTextureImage),
	m_plantNormalImage(new Qt3DRender::QTextureImage),
	m_coverImage(new Qt3DRender::QTextureImage),
	m_coverNormalImage(new Qt3DRender::QTextureImage),
	m_plantType(Plant::Bamboo),
	m_potShape(PotShape::Cross)
{
	m_pot = new RenderableEntity(this);
	m_pot->transform()->setScale(0.03f);
	m_pot->addComponent(m_potMaterial);

	m_plant = new RenderableEntity(m_pot);
	m_plant->addComponent(m_plantMaterial);

	m_cover = new RenderableEntity(m_pot);
	m_cover->addComponent(m_coverMaterial);

	m_potMaterial->diffuse()->addTextureImage(m_potImage);
	m_potMaterial->normal()->addTextureImage(m_potNormalImage);

	m_plantMaterial->diffuse()->addTextureImage(m_plantImage);
	m_plantMaterial->normal()->addTextureImage(m_plantNormalImage);

	m_coverMaterial->diffuse()->addTextureImage(m_coverImage);
	m_coverMaterial->normal()->addTextureImage(m_coverNormalImage);

	updatePlantType();
	updatePotShape();
}

void HousePlant::setPotShape(PotShape shape)
{
	if (shape == m_potShape) return;

	m_potShape = shape;
	updatePotShape();
}

void HousePlant::setPlantType(Plant plant)
{
	if (plant == m_plantType) return;

	m_plantType = plant;
	updatePlantType();
}

HousePlant::PotShape HousePlant::potShape() const
{
	return m_potShape;
}

HousePlant::Plant HousePlant::plant() const
{
	return m_plantType;
}

void HousePlant::setPosition(const QVector3D& pos)
{
	m_pot->transform()->setTranslation(pos);
}

void HousePlant::setScale(float scale)
{
	m_pot->transform()->setScale(scale);
}

QVector3D HousePlant::position() const
{
	return m_pot->transform()->translation();
}

float HousePlant::scale() const
{
	return m_pot->transform()->scale();
}

void HousePlant::updatePotShape()
{
	m_pot->mesh()->setSource(QUrl(QStringLiteral("qrc:/mesh/") + potNames[static_cast<int>(m_potShape)].c_str() + QStringLiteral("-pot")));
	m_plant->mesh()->setSource(QUrl(QStringLiteral("qrc:/mesh/") + potNames[static_cast<int>(m_potShape)].c_str() + QStringLiteral("-") + plantNames[static_cast<int>(m_plantType)].c_str()));
}

void HousePlant::updatePlantType()
{
	m_plant->mesh()->setSource(QUrl(QStringLiteral("qrc:/mesh/") + potNames[static_cast<int>(m_potShape)].c_str() + QStringLiteral("-") + plantNames[static_cast<int>(m_plantType)].c_str()));

	m_plantImage->setSource(QUrl(QStringLiteral("qrc:/textures/plant/") + plantNames[static_cast<int>(m_plantType)].c_str()));
	m_plantNormalImage->setSource(QUrl(QStringLiteral("qrc:/textures/plant/") + plantNames[static_cast<int>(m_plantType)].c_str() + QStringLiteral("_normal")));
}