#include "barrel.h"

#include <Qt3DCore\qtransform.h>

#include <Qt3DRender\qabstracttexture.h>
#include <Qt3DRender\qtextureimage.h>
#include <Qt3DRender\qmesh.h>

#include <Qt3DExtras\qnormaldiffusespecularmapmaterial.h>

#include <vector>
#include <string>

std::vector<std::string> diffuseColorNames{
	"red",
	"blue",
	"green",
	"rust",
	"stainless_steel"
};

std::vector<std::string> specularColorNames{
	"_rust",
	"_stainless_steel",
	""
};

std::vector<std::string> bumpsNames{
	"no_bumps",
	"soft_bumps",
	"middle_bumps",
	"hard_bumps"
};

Barrel::Barrel(Qt3DCore::QNode * parent) :
	RenderableEntity(parent),
	m_bumps(Bumps::NoBumps),
	m_diffuse(DiffuseColor::Red),
	m_specular(SpecularColor::None),
	m_material(new Qt3DExtras::QNormalDiffuseSpecularMapMaterial),
	m_diffuseTextureImage(new Qt3DRender::QTextureImage),
	m_normalTextureImage(new Qt3DRender::QTextureImage),
	m_specularTextureImage(new Qt3DRender::QTextureImage)
{
	mesh()->setSource(QUrl(QStringLiteral("qrc:/mesh/barrel")));
	transform()->setScale(0.03f);

	m_material->diffuse()->addTextureImage(m_diffuseTextureImage);
	m_material->normal()->addTextureImage(m_normalTextureImage);
	m_material->specular()->addTextureImage(m_specularTextureImage);

	setNormalTextureSource();
	setDiffuseTextureSource();
	setSpecularTextureSource();

	m_material->setShininess(10.0f);

	addComponent(m_material);
}

void Barrel::setDiffuse(DiffuseColor color)
{
	if (color == m_diffuse) return;

	m_diffuse = color;
	setDiffuseTextureSource();
}

void Barrel::setSpecular(SpecularColor color)
{
	if (color == m_specular) return;

	m_specular = color;
	setSpecularTextureSource();
}

void Barrel::setBumps(Bumps bumps)
{
	if (bumps == m_bumps) return;

	m_bumps = bumps;
	setNormalTextureSource();
}

void Barrel::setShininess(float shininess)
{
	if (shininess == m_material->shininess()) return;

	m_material->setShininess(shininess);
}

Barrel::DiffuseColor Barrel::diffuse() const
{
	return m_diffuse;
}

Barrel::SpecularColor Barrel::specular() const
{
	return m_specular;
}

Barrel::Bumps Barrel::bumps() const
{
	return m_bumps;
}

float Barrel::shininess() const
{
	return m_material->shininess();
}

void Barrel::setNormalTextureSource()
{
	m_normalTextureImage->setSource(QUrl(QStringLiteral("qrc:/textures/barrel/normal_") + bumpsNames[static_cast<int>(m_bumps)].c_str()));
}

void Barrel::setDiffuseTextureSource()
{
	m_diffuseTextureImage->setSource(QUrl(QStringLiteral("qrc:/textures/barrel/diffuse_") + diffuseColorNames[static_cast<int>(m_diffuse)].c_str()));
}

void Barrel::setSpecularTextureSource()
{
	m_specularTextureImage->setSource(QUrl(QStringLiteral("qrc:/textures/barrel/specular") + specularColorNames[static_cast<int>(m_specular)].c_str()));
}