#pragma once

#include "renderableentity.h"

namespace Qt3DExtras
{
	class QNormalDiffuseSpecularMapMaterial;
}

namespace Qt3DRender
{
	class QTextureImage;
}

class Barrel : public RenderableEntity
{
public:
	explicit Barrel(Qt3DCore::QNode * parent = Q_NULLPTR);

	enum class DiffuseColor
	{
		Red = 0,
		Blue,
		Green,
		RustDiffuse,
		StainlessSteelDiffuse
	};

	enum class SpecularColor
	{
		RustSpecular = 0,
		StainlessSteelSpecular,
		None
	};

	enum class Bumps
	{
		NoBumps = 0,
		SoftBumps,
		MiddleBumps,
		HardBumps
	};

	void setDiffuse(DiffuseColor diffuse);
	void setSpecular(SpecularColor specular);
	void setBumps(Bumps bumps);
	void setShininess(float shininess);

	DiffuseColor diffuse() const;
	SpecularColor specular() const;
	Bumps bumps() const;
	float shininess() const;

private:
	Bumps m_bumps;
	DiffuseColor m_diffuse;
	SpecularColor m_specular;

	Qt3DExtras::QNormalDiffuseSpecularMapMaterial * m_material;

	Qt3DRender::QTextureImage * m_diffuseTextureImage;
	Qt3DRender::QTextureImage * m_normalTextureImage;
	Qt3DRender::QTextureImage * m_specularTextureImage;

	void setNormalTextureSource();
	void setDiffuseTextureSource();
	void setSpecularTextureSource();
};