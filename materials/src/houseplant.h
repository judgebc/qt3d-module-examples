#pragma once

#include <Qt3DCore\qentity.h>

class RenderableEntity;

namespace Qt3DRender
{
	class QTextureImage;
}

namespace Qt3DExtras
{
	class QNormalDiffuseMapMaterial;
	class QNormalDiffuseMapAlphaMaterial;
}

class HousePlant : public Qt3DCore::QEntity
{
	Q_OBJECT

public:
	explicit HousePlant(Qt3DCore::QNode * parent = Q_NULLPTR);

	enum class PotShape
	{
		Cross = 0,
		Square,
		Triangle,
		Sphere
	};

	enum class Plant
	{
		Bamboo = 0,
		Palm,
		Pine,
		Spikes,
		Shrub
	};

	void setPotShape(PotShape shape);
	void setPlantType(Plant plant);

	PotShape potShape() const;
	Plant plant() const;

	void setPosition(const QVector3D& pos);
	void setScale(float scale);

	QVector3D position() const;
	float scale() const;

private:
	RenderableEntity * m_pot;
	RenderableEntity * m_plant;
	RenderableEntity * m_cover;

	Qt3DExtras::QNormalDiffuseMapMaterial * m_potMaterial;
	Qt3DExtras::QNormalDiffuseMapAlphaMaterial * m_plantMaterial;
	Qt3DExtras::QNormalDiffuseMapMaterial * m_coverMaterial;

	Qt3DRender::QTextureImage * m_potImage;
	Qt3DRender::QTextureImage * m_potNormalImage;
	Qt3DRender::QTextureImage * m_plantImage;
	Qt3DRender::QTextureImage * m_plantNormalImage;
	Qt3DRender::QTextureImage * m_coverImage;
	Qt3DRender::QTextureImage * m_coverNormalImage;

	Plant m_plantType;
	PotShape m_potShape;

	void updatePotShape();
	void updatePlantType();
};