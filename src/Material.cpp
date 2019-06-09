#include "Material.h"

namespace uGLy
{

	Material::Material()
	{
	}

	Material::~Material()
	{
	}

	bool Material::HasAmbientMap()
	{
		return (this->ambientMap != nullptr) && (this->ambientMap->id > 0);
	}

	bool Material::HasDiffuseMap()
	{
		return (this->diffuseMap != nullptr) && (this->diffuseMap->id > 0);
	}

	bool Material::HasSpecularMap()
	{
		return (this->specularMap != nullptr) && (this->specularMap->id > 0);
	}

	bool Material::HasNormalMap()
	{
		return (this->normalMap != nullptr) && (this->normalMap->id > 0);
	}

}